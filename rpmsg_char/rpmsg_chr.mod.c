#include <linux/build-salt.h>
#include <linux/module.h>
#include <linux/vermagic.h>
#include <linux/compiler.h>

BUILD_SALT;

MODULE_INFO(vermagic, VERMAGIC_STRING);
MODULE_INFO(name, KBUILD_MODNAME);

__visible struct module __this_module
__section(.gnu.linkonce.this_module) = {
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
__used __section(__versions) = {
	{ 0xb3753869, "module_layout" },
	{ 0x78f44845, "cdev_del" },
	{ 0x98200526, "rpmsg_trysendto" },
	{ 0x35216b26, "kmalloc_caches" },
	{ 0xeb233a45, "__kmalloc" },
	{ 0xa3036ef8, "cdev_init" },
	{ 0x409bcb62, "mutex_unlock" },
	{ 0x6091b333, "unregister_chrdev_region" },
	{ 0x3c3ff9fd, "sprintf" },
	{ 0x36e58bcd, "pv_ops" },
	{ 0xc225e884, "rpmsg_poll" },
	{ 0xd9a5ea54, "__init_waitqueue_head" },
	{ 0xbdd8925, "skb_queue_purge" },
	{ 0x6d6cd150, "_dev_warn" },
	{ 0x30258fa4, "device_del" },
	{ 0x3812050a, "_raw_spin_unlock_irqrestore" },
	{ 0x1e83ab89, "rpmsg_create_ept" },
	{ 0x2db3d320, "mutex_lock_interruptible" },
	{ 0x977f511b, "__mutex_init" },
	{ 0xc5850110, "printk" },
	{ 0xffb7c514, "ida_free" },
	{ 0xa1c76e0a, "_cond_resched" },
	{ 0xeb843b, "unregister_rpmsg_driver" },
	{ 0x2ab7989d, "mutex_lock" },
	{ 0xa2d65714, "rpmsg_destroy_ept" },
	{ 0x6fe1a767, "device_add" },
	{ 0xce93ec67, "__register_rpmsg_driver" },
	{ 0x33318306, "rpmsg_sendto" },
	{ 0x18616700, "_dev_err" },
	{ 0xfe487975, "init_wait_entry" },
	{ 0x7afe113a, "cdev_add" },
	{ 0x19c254b2, "compat_ptr_ioctl" },
	{ 0xf6f33474, "skb_queue_tail" },
	{ 0x865dc1d3, "__alloc_skb" },
	{ 0xa191f0a8, "put_device" },
	{ 0xdecd0b29, "__stack_chk_fail" },
	{ 0x1000e51, "schedule" },
	{ 0x8f8fc40f, "kfree_skb" },
	{ 0x4c83f7e8, "_copy_from_iter_full" },
	{ 0x2ea2c95c, "__x86_indirect_thunk_rax" },
	{ 0xbdfb6dbb, "__fentry__" },
	{ 0xf5cb25c8, "kmem_cache_alloc_trace" },
	{ 0xdbf17652, "_raw_spin_lock" },
	{ 0x51760917, "_raw_spin_lock_irqsave" },
	{ 0xfdbce916, "get_device" },
	{ 0x3eeb2322, "__wake_up" },
	{ 0x8c26d495, "prepare_to_wait_event" },
	{ 0x354daecd, "device_for_each_child" },
	{ 0x37a0cba, "kfree" },
	{ 0x69acdf38, "memcpy" },
	{ 0x6ff6e17, "device_initialize" },
	{ 0xb356c301, "class_destroy" },
	{ 0x92540fbf, "finish_wait" },
	{ 0xd3c2f63f, "skb_dequeue" },
	{ 0x7c7b384c, "dev_set_name" },
	{ 0x9d62d17b, "skb_put" },
	{ 0x362ef408, "_copy_from_user" },
	{ 0x8d62ea07, "__class_create" },
	{ 0x382bb5f5, "_copy_to_iter" },
	{ 0x88db9f48, "__check_object_size" },
	{ 0xe3ec2f2b, "alloc_chrdev_region" },
	{ 0xe7a02573, "ida_alloc_range" },
};

MODULE_INFO(depends, "rpmsg_core");


MODULE_INFO(srcversion, "9F5F28A0C8AC6DD87C1FC40");
