#include "device_file.h"
#include <linux/init.h>
#include <linux/module.h>

MODULE_DESCRIPTION("Simple Linux driver");
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Siliang Zhang, Envision");

static int my_init(void)
{
    int result = 0;
    printk(KERN_NOTICE "Simple-driver: Initialization started \n");
    result = register_device();
    return result;
}

static void my_exit(void)
{
    printk(KERN_NOTICE "Simple-driver: Exiting\n");
    return;
}

module_init(my_init);
module_exit(my_exit);