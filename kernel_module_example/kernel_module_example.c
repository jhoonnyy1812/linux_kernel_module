#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init linux_kernel_module_init(void) {
 printk(KERN_INFO "Hello, World!\n");
 return 0;
}
static void __exit linux_kernel_module_exit(void) {
 printk(KERN_INFO "Goodbye, World!\n");
}
module_init(linux_kernel_module_init);
module_exit(linux_kernel_module_exit);