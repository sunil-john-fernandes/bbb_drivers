#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init init_function(void) {

	/* Module entry function */
	printk(KERN_INFO "Loading module...\n");
	return 0;

}

static void __exit exit_function(void) {

	/* Module exit function */
	printk(KERN_INFO "Exiting module...\n");
}


module_init(init_function);
module_exit(exit_function);
MODULE_AUTHOR("Sunil Fernandes <sunil.fernandes@gmail.com>");
MODULE_DESCRIPTION("Module Template");
MODULE_VERSION("0.1");
MODULE_LICENSE("GPL");
