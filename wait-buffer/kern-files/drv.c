#include <linux/init.h>
#include <linux/module.h>
#include <linux/device.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/uaccess.h>
#include <linux/wait.h>

#define MAX_SIZE_OF_BUFF 256
#define DEVICE_NAME "taskbuff"
#define CLASS_NAME "task"

MODULE_LICENSE("GPL");

static int major_num;
static char buffer[MAX_SIZE_OF_BUFF] = {0};
static short size_of_buffer;
static struct class* TaskbuffClass = NULL;
static struct device* TaskbuffDevice = NULL;

static char cycleBuf[MAX_SIZE_OF_BUFF];
static int count_write = 1;
static int count_read = 0;

static char flag = 'n';
static wait_queue_head_t wq_write;
static wait_queue_head_t wq_read;

static int dev_open(struct inode *, struct file *);
static int dev_release(struct inode *, struct file *);
static ssize_t dev_read(struct file *, char *, size_t, loff_t *);
static ssize_t dev_write(struct file *, const char *, size_t, loff_t *);

static struct file_operations fops = {
	.open = dev_open,
	.release = dev_release,
	.read = dev_read,
	.write = dev_write
};

static int __init dev_init(void) {
	printk(KERN_INFO "Initializing\n");

	init_waitqueue_head(&wq_write);
   	init_waitqueue_head(&wq_read);
	
	major_num = register_chrdev(0, DEVICE_NAME, &fops);
	if (major_num < 0) {
		printk(KERN_ALERT "Initialization failed\n");
		return major_num;
	}
	
	TaskbuffClass = class_create(THIS_MODULE, CLASS_NAME);
	TaskbuffDevice = device_create(TaskbuffClass, NULL, MKDEV(major_num, 0), NULL, DEVICE_NAME);

	memset(buffer, 'f', sizeof(buffer));
	
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

static ssize_t dev_read(struct file *filep, char *buff, size_t len, loff_t *offset) {
	if((count_read+1 == count_write) //buffer empty
		&& (filep->f_flags & O_NONBLOCK))
		return -EAGAIN;
	if(wait_event_interruptible(wq_read, (count_read+1 != count_write)))
		return -ERESTARTSYS;
	int bytes_read = 0;
	while(bytes_read < len && (count_read+1 != count_write) )
	{
		put_user(cycleBuf[++count_read], buff++);
		printk(KERN_INFO"read: readc %d, writec %d, buf[read] %c\n", count_read, count_write, cycleBuf[count_read]);
		bytes_read++;
		if(count_read == MAX_SIZE_OF_BUFF-1)
			count_read = -1;
	}
	wake_up_interruptible(&wq_write);
	
	printk(KERN_INFO"read: length %d, bytes %d\n", len, bytes_read);
	return bytes_read;
}

static ssize_t dev_write(struct file *filep, const char *buff, size_t len, loff_t *offset) {
	if((count_read == count_write) && (filep->f_flags & O_NONBLOCK))
		return -EAGAIN;
	if(wait_event_interruptible(wq_write, (count_read != count_write)))
		return -ERESTARTSYS;
	
	int bytes_written = 0;
	while( bytes_written < len && (count_write != count_read) )
	{
		printk(KERN_INFO"write1: readc %d, writec %d\n", count_read, count_write);
		get_user(cycleBuf[count_write++], buff++);
		bytes_written++;
		if(count_write == MAX_SIZE_OF_BUFF)
			count_write = 0;
		printk(KERN_INFO"write2: readc %d, writec %d\n", count_read, count_write);
	}
	wake_up_interruptible(&wq_read);
	
	return bytes_written;
}

module_init(dev_init);
module_exit(dev_exit);

