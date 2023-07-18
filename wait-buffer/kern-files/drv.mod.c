#include <linux/module.h>
#define INCLUDE_VERMAGIC
#include <linux/build-salt.h>
#include <linux/elfnote-lto.h>
#include <linux/export-internal.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;
BUILD_LTO_INFO;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(".gnu.linkonce.this_module") = {
	.name = KBUILD_MODNAME,
	.init = init_module,
#ifdef CONFIG_MODULE_UNLOAD
	.exit = cleanup_module,
#endif
	.arch = MODULE_ARCH_INIT,
};

#ifdef CONFIG_RETPOLINE
MODULE_INFO(retpoline, "Y");
#endif


static const struct modversion_info ____versions[]
__used __section("__versions") = {
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0x92997ed8, "_printk" },
	{ 0x5b8239ca, "__x86_return_thunk" },
	{ 0xe2c17b5d, "__SCT__might_resched" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x1000e51, "schedule" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xd0da656b, "__stack_chk_fail" },
	{ 0x167e7f9d, "__get_user_1" },
	{ 0x87a21cb3, "__ubsan_handle_out_of_bounds" },
	{ 0xc3aaf0a9, "__put_user_1" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0x425364b1, "__register_chrdev" },
	{ 0xaee657ee, "__class_create" },
	{ 0xf2d7865d, "device_create" },
	{ 0x48931e20, "device_destroy" },
	{ 0x7377b2e, "class_unregister" },
	{ 0x645620c0, "class_destroy" },
	{ 0x6bc3fbc0, "__unregister_chrdev" },
	{ 0x541a6db8, "module_layout" },
};

MODULE_INFO(depends, "");


MODULE_INFO(srcversion, "1874F23A6C1F05BAC2E3B76");
