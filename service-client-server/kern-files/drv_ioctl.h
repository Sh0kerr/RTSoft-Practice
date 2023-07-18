#ifndef DRV_IOCTL_H
#define DRV_IOCTL_H

#include <linux/ioctl.h>

#define MAGIC_NUM 0xF1
#define IOC_GET _IOR(MAGIC_NUM, 0, int)

#endif

