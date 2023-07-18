#include <linux/init.h>
#include <linux/module.h>
#include <linux/pci.h>

#define DEV_NAME "ethe"

MODULE_LICENSE("GPL");

static struct pci_device_id ethernet_driver_id_table[] = {
	{0x10ec, 0x8086},
	{0x10ec, 0x100f},
	{0,},
};

MODULE_DEVICE_TABLE(pci, ethernet_driver_id_table);

static int ethernet_driver_probe(struct pci_dev *, const struct pci_device_id *);
static void ethernet_driver_remove(struct pci_dev *);

static struct pci_driver ethernet_pci_driver = {
	.name = DEV_NAME,
	.id_table = ethernet_driver_id_table,
	.probe = ethernet_driver_probe,
	.remove = ethernet_driver_remove,
};

static int __init ethernet_init_module(void) {
	printk(KERN_INFO "Init\n");
	return pci_register_driver(&ethernet_pci_driver);
}

void __exit ethernet_cleanup_module(void) {
	printk(KERN_INFO "Exit\n");
	pci_unregister_driver(&ethernet_pci_driver);
}

int ethernet_driver_probe(struct pci_dev *dev, const struct pci_device_id *id) {
	printk(KERN_INFO "Loaded\n");
	return 0;
}

void ethernet_driver_remove(struct pci_dev *dev) {
	printk(KERN_INFO "Removed\n");
}

module_init(ethernet_init_module);
module_exit(ethernet_cleanup_module);

