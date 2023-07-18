#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>

MODULE_LICENSE("GPL");

static int __init drv_init(void) {
	pr_info("Initialized\n");
	return 0;
}

static void __exit drv_exit(void) {
	pr_info("Released\n");
}

module_init(drv_init);
module_exit(drv_exit);

