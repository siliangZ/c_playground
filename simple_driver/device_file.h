#ifndef DEVICE_FILE_H
#define DEVICE_FILE_H
#include <linux/compiler.h>

__must_check int register_device(void);
void unregister_device(void);

#endif // DEVICE_FILE_H