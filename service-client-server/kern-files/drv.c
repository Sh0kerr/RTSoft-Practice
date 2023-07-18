#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include "drv_ioctl.h"

#define MAX_SIZE_OF_BUFF 256
#define DEVICE_NAME "taskbuff"
#define CLASS_NAME "task"

MODULE_LICENSE("GPL");

static int major_num;
static short size_of_buffer;
static struct class* TaskbuffClass = NULL;
static struct device* TaskbuffDevice = NULL;
static int val = 0;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
//static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static long dev_ioctl(struct file *, unsigned int, unsigned long);

static struct file_operations fops = {
	.open = dev_open,
	.release = dev_release,
	//.read = dev_read,
	.unlocked_ioctl = dev_ioctl
};

static int __init dev_init(void) {
	printk(KERN_INFO "Initializing\n");
	
	major_num = register_chrdev(0, DEVICE_NAME, &fops);
	if (major_num < 0) {
		printk(KERN_ALERT "Initialization failed\n");
		return major_num;
	}
	
	TaskbuffClass = class_create(THIS_MODULE, CLASS_NAME);
	TaskbuffDevice = device_create(TaskbuffClass, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);
	
	printk(KERN_INFO "Initialized successfully\n");
	return 0;
}

static void __exit dev_exit(void) {
	device_destroy(TaskbuffClass, MKDEV(major_num, 0));
	class_unregister(TaskbuffClass);
	class_destroy(TaskbuffClass);
	unregister_chrdev(major_num, DEVICE_NAME);

	printk(KERN_INFO "Closed\n");
}

static int dev_open(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "Opened\n");
	return 0;
}

static int dev_release(struct inode *inodep, struct file *filep) {
	printk(KERN_INFO "Released\n");
	return 0;
}

/*
static ssize_t dev_read(struct file *fd, char *buff, size_t len, loff_t *offset) {
	copy_to_user(buff, val, sizeof(int));
	return 0;
}


static long dev_ioctl(struct file *fd, unsigned int cmd, unsigned long arg) { 
	switch(cmd) {
		case IOC_SET:
			val += 10;
			printk(val);
			break;
		default:
			return -EINVAL;
	}
	return 0;
}
*/
 
static long dev_ioctl(struct file *fd, unsigned int cmd, unsigned long arg) {
	switch(cmd) {
	case IOC_GET:
		val += 10;
		copy_to_user((int*) arg, &val, sizeof(int));
		break;
	default:
		return -EINVAL;
	}
	return 0;
}

module_init(dev_init);
module_exit(dev_exit);

