/*
 * Test application that data integraty of inter processor
 * communication from linux userspace to a remote software
 * context. The application sends chunks of data to the
 * remote processor. The remote side echoes the data back
 * to application which then validates the data returned.
 */

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <linux/rpmsg.h>
#include <poll.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <time.h>
#include <unistd.h>

#define RPMSG_HEADER_LEN 16
#define MAX_RPMSG_BUFF_SIZE (512 - RPMSG_HEADER_LEN)
#define PAYLOAD_MAX_SIZE (MAX_RPMSG_BUFF_SIZE - 24)
#define CLOCKS_PER_MS (double)CLOCKS_PER_SEC / 1000.0
#define RPMSG_BUS_SYS "/sys/bus/rpmsg"

struct _payload
{
  unsigned long num;
  unsigned long size;
  char data[];
};

static int charfd = -1;

struct _payload *i_payload =
    (struct _payload *)malloc(2 * sizeof(unsigned long) + PAYLOAD_MAX_SIZE);
struct _payload *r_payload =
    (struct _payload *)malloc(2 * sizeof(unsigned long) + PAYLOAD_MAX_SIZE);

// send time of each payload
const int num_payloads = 1000000;
clock_t send_time_array[num_payloads] = {0};
clock_t receive_time_array[num_payloads] = {0};
char rpmsg_dev[] = "virtio0.rpmsg-openamp-demo-channel.-1.0";

int g_fd;                           // the file handler of rpmsg character device
struct rpmsg_endpoint_info eptinfo; // save the eptinfo

static int rpmsg_create_ept(int rpfd, struct rpmsg_endpoint_info *eptinfo)
{
  int ret;

  ret = ioctl(rpfd, RPMSG_CREATE_EPT_IOCTL, eptinfo);
  if (ret)
    perror("Failed to create endpoint.\n");
  return ret;
}

static char *get_rpmsg_ept_dev_name(const char *rpmsg_char_name,
                                    const char *ept_name, char *ept_dev_name)
{
  char sys_rpmsg_ept_name_path[64];
  char svc_name[64];
  char sys_rpmsg_path[] = "/sys/class/rpmsg";
  FILE *fp;
  int i;
  int ept_name_len;

  for (i = 0; i < 128; i++)
  {
    sprintf(sys_rpmsg_ept_name_path, "%s/%s/rpmsg%d/name", sys_rpmsg_path,
            rpmsg_char_name, i);
    printf("checking %s\n", sys_rpmsg_ept_name_path);
    if (access(sys_rpmsg_ept_name_path, F_OK) < 0)
      continue;
    fp = fopen(sys_rpmsg_ept_name_path, "r");
    if (!fp)
    {
      printf("failed to open %s\n", sys_rpmsg_ept_name_path);
      break;
    }
    fgets(svc_name, sizeof(svc_name), fp);
    fclose(fp);
    printf("svc_name: %s.\n", svc_name);
    ept_name_len = strlen(ept_name);
    if (ept_name_len > sizeof(svc_name))
      ept_name_len = sizeof(svc_name);
    if (!strncmp(svc_name, ept_name, ept_name_len))
    {
      sprintf(ept_dev_name, "rpmsg%d", i);
      return ept_dev_name;
    }
  }

  printf("Not able to RPMsg endpoint file for %s:%s.\n", rpmsg_char_name,
         ept_name);
  return NULL;
}

static int bind_rpmsg_chrdev(const char *rpmsg_dev_name)
{
  char fpath[256];
  char rpmsg_chdrv[] = "rpmsg_char_notify";
  int fd;
  int ret;

  /* rpmsg dev overrides path */
  sprintf(fpath, "%s/devices/%s/driver_override", RPMSG_BUS_SYS,
          rpmsg_dev_name);
  fd = open(fpath, O_WRONLY);
  if (fd < 0)
  {
    fprintf(stderr, "Failed to open %s, %s\n", fpath, strerror(errno));
    return -EINVAL;
  }
  ret = write(fd, rpmsg_chdrv, strlen(rpmsg_chdrv) + 1);
  if (ret < 0)
  {
    fprintf(stderr, "Failed to write %s to %s, %s\n", rpmsg_chdrv, fpath,
            strerror(errno));
    return -EINVAL;
  }
  close(fd);

  /* bind the rpmsg device to rpmsg char driver */
  sprintf(fpath, "%s/drivers/%s/bind", RPMSG_BUS_SYS, rpmsg_chdrv);
  fd = open(fpath, O_WRONLY);
  if (fd < 0)
  {
    fprintf(stderr, "Failed to open %s, %s\n", fpath, strerror(errno));
    return -EINVAL;
  }
  ret = write(fd, rpmsg_dev_name, strlen(rpmsg_dev_name) + 1);
  if (ret < 0)
  {
    fprintf(stderr, "Failed to write %s to %s, %s\n", rpmsg_dev_name, fpath,
            strerror(errno));
    return -EINVAL;
  }
  close(fd);
  return 0;
}

static int get_rpmsg_chrdev_fd(const char *rpmsg_dev_name,
                               char *rpmsg_ctrl_name)
{
  char dpath[256];
  char fpath[256];
  char rpmsg_ctrl_prefix[] = "rpmsg_ctrl";
  DIR *dir;
  struct dirent *ent;
  int fd;

  sprintf(dpath, "%s/devices/%s/rpmsg", RPMSG_BUS_SYS, rpmsg_dev_name);
  dir = opendir(dpath);
  if (dir == NULL)
  {
    fprintf(stderr, "Failed to open dir %s\n", dpath);
    return -EINVAL;
  }
  while ((ent = readdir(dir)) != NULL)
  {
    if (!strncmp(ent->d_name, rpmsg_ctrl_prefix, strlen(rpmsg_ctrl_prefix)))
    {
      printf("Opening file %s.\n", ent->d_name);
      sprintf(fpath, "/dev/%s", ent->d_name);
      fd = open(fpath, O_RDWR | O_NONBLOCK);
      if (fd < 0)
      {
        fprintf(stderr, "Failed to open rpmsg char dev %s,%s\n", fpath,
                strerror(errno));
        return fd;
      }
      sprintf(rpmsg_ctrl_name, "%s", ent->d_name);
      return fd;
    }
  }

  fprintf(stderr, "No rpmsg char dev file is found\n");
  return -EINVAL;
}

void sigio_handler(int signum)
{
  // printf("received the signal from driver.\n");

  if (r_payload == 0)
  {
    fprintf(stderr, "can't allocate memory for receive payload.\n");
    return;
  }

  int bytes_rcvd =
      read(g_fd, r_payload, (2 * sizeof(unsigned long)) + PAYLOAD_MAX_SIZE);
  receive_time_array[r_payload->num] = clock();

  /* Validate data buffer integrity. */
  // for (int k = 0; k < r_payload->size; k++)
  //{
  // if (r_payload->data[k] != 0xA5)
  //{
  // printf(" \r\n Data corruption");
  // printf(" at index %d \r\n", k);
  // break;
  //}
  //}
  // printf("The data is complete.\n");
}

float timedifference_msec(struct timeval t0, struct timeval t1)
{
  return (t1.tv_sec - t0.tv_sec) * 1000.0f + (t1.tv_usec - t0.tv_usec) / 1000.0f;
}

void calculate_average_delay(int payload_size)
{
  // calculate average time
  clock_t total_time = 0;
  double counter = 0;
  clock_t max_delay = 0;
  clock_t min_delay = __INT_MAX__;
  for (int i = 0; i < num_payloads; i++)
  {
    if (receive_time_array[i] == 0)
    {
      continue;
    }
    // printf("receive time: %d tick.\n", receive_time_array[i]);
    // printf("send time: %d tick.\n", send_time_array[i]);
    clock_t diff = receive_time_array[i] - send_time_array[i];
    if (diff > max_delay)
    {
      max_delay = diff;
    }

    if (diff < min_delay)
    {
      min_delay = diff;
    }
    // printf("%i ", diff);
    total_time += diff;
    counter += 1.0;
  }
  // printf("\n");
  double avg_delay = (double)total_time / ((double)CLOCKS_PER_MS * counter);
  double max_delay_ms;
  max_delay_ms = (double)max_delay / (double)CLOCKS_PER_MS;
  double min_delay_ms;
  min_delay_ms = (double)min_delay / (double)CLOCKS_PER_MS;
  printf("two way payload %d, %lf runs:\n", payload_size, counter);
  printf("clocks per ms: %lf", (double)CLOCKS_PER_MS);
  printf("total ticks: %lf, max ticks: %lf, min ticks: %lf.\n", (double)total_time, (double)max_delay, (double)min_delay);
  printf("max time: %f ms, min time: %f ms, avg time: %lf ms.\n", max_delay_ms, min_delay_ms, avg_delay);
}

int prepare_environment(char *rpmsg_char_name)
{
  printf("\r\n Echo test start \r\n");

  printf("\r\nMaster>probe rpmsg-char-notify\r\n");
  if (system("modprobe rpmsg-char-notify") < 0)
  {
    fprintf(stderr, "Failed to load rpmsg-char-notify driver.\n");
    return -EINVAL;
  }

  char fpath[256];
  sprintf(fpath, "%s/devices/%s", RPMSG_BUS_SYS, rpmsg_dev);
  if (access(fpath, F_OK))
  {
    fprintf(stderr, "Not able to access rpmsg device %s, %s\n", fpath,
            strerror(errno));
    return -EINVAL;
  }

  int ret = bind_rpmsg_chrdev(rpmsg_dev);
  if (ret < 0)
    return ret;

  charfd = get_rpmsg_chrdev_fd(rpmsg_dev, rpmsg_char_name);
  if (charfd < 0)
    return charfd;

  /* Create endpoint from rpmsg char driver */
  strcpy(eptinfo.name, "rpmsg-openamp-demo-channel");
  eptinfo.src = 0xFFFFFFFF;
  eptinfo.dst = 0x0;
  ret = rpmsg_create_ept(charfd, &eptinfo);
  if (ret)
  {
    printf("failed to create RPMsg endpoint.\n");
    return -EINVAL;
  }
  return 0;
}

int main(int argc, char *argv[])
{
  char default_dev_path[] = "/dev/rpmsg0";
  if (access(default_dev_path, F_OK))
  {
    char rpmsg_char_name[16];
    if (prepare_environment(rpmsg_char_name) < 0)
    {
      return -EINVAL;
    }

    char ept_dev_name[16];
    if (!get_rpmsg_ept_dev_name(rpmsg_char_name, eptinfo.name, ept_dev_name))
      return -EINVAL;

    sprintf(default_dev_path, "/dev/%s", ept_dev_name);
  }

  printf("Starting notification test.\n");

  g_fd = open(default_dev_path, O_RDWR | O_NONBLOCK);
  if (g_fd < 0)
  {
    perror("Failed to open rpmsg device.");
    close(charfd);
    return -1;
  }

  // register the signal handler
  signal(SIGIO, sigio_handler);
  fcntl(g_fd, F_SETOWN, getpid());       // Tell the kernel to whom to send the signal? Reflected by PID number
  int Oflags = fcntl(g_fd, F_GETFL);     // The application program reads the flag bit Oflags
  fcntl(g_fd, F_SETFL, Oflags | FASYNC); // And add the flag bit with asynchronous information, the application calling this function will trigger the driver layer to call the fifth_drv_fasync function we wrote

  int payload_size_candidates[5] = {10, 50, 100, 200, 400};
  for (int index = 0; index < 4; index++)
  {
    printf("test payload %d.\n", payload_size_candidates[index]);
    memset(receive_time_array, 0, sizeof(receive_time_array));
    memset(send_time_array, 0, sizeof(send_time_array));
    for (int i = 0; i < num_payloads; i++)
    {
      if (i_payload == 0)
      {
        printf("ERROR: Failed to allocate memory for payload.\n");
        return -1;
      }

      i_payload->num = i;
      i_payload->size = payload_size_candidates[index];
      memset(&(i_payload->data[0]), 0xA5, payload_size_candidates[index]);

      send_time_array[i] = clock();
      int bytes_sent = write(g_fd, i_payload, (2 * sizeof(unsigned long)) + payload_size_candidates[index]);
      if (bytes_sent <= 0)
      {
        printf("\r\n Error sending data");
        printf(" .. \r\n");
        return -1;
      }
      usleep(100); // wait for response to come back
    }
    sleep(5);
    calculate_average_delay(payload_size_candidates[index]);
  }
  free(i_payload);
  free(r_payload);
  close(g_fd);

  if (charfd >= 0)
    close(charfd);
  return 0;
}
