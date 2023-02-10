#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <sys/epoll.h>
#include <string.h>

int main(int, char **)
{
    int fd = epoll_create1(0);
    if (fd == -1)
    {
        fprintf(stderr, "can't create epoll file handler.\n");
        return -1;
    }
    struct epoll_event event;
    event.events = EPOLLIN;
    event.data.fd = 0; // the data is binded to file handler 0

    // register the epoll_handler to listen to fd0(stdinput)
    if (epoll_ctl(fd, EPOLL_CTL_ADD, 0, &event))
    {
        fprintf(stderr, "can't add file descriptor to epoll");
        close(fd);
        return -1;
    }

    struct epoll_event events[20];
    while (true)
    {
        printf("polling event ..\n");
        int num_events = epoll_wait(fd, events, 20, 50000);
        printf("polled %d events.\n", num_events);
        for (int i = 0; i < num_events; i++)
        {
            printf("read from event %d\n", i);
            char buf[100];
            size_t ret = read(events[i].data.fd, buf, 10);
            printf("read out %lu bytes.\n", ret);
            buf[ret] = '\0'; // we could print it as a string
            printf("read %s .\n", buf);
        }
    }
    // close the epoll handler
    if (close(fd))
    {
        fprintf(stderr, "can't close epoll file handler.\n");
        return -1;
    }
    return 0;
}
