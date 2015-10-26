#include <linux/module.h>    // included for all kernel modules
#include <linux/kernel.h>    // included for KERN_INFO
#include <linux/init.h>      // included for __init and __exit macros

MODULE_LICENSE("GPL");
MODULE_AUTHOR("picrin");
MODULE_DESCRIPTION("A Simple Hello World module");

static int __init hello_init(void)
{
    printk(KERN_INFO "Hello Iva!\n");
    return 0;
}

static void __exit hello_cleanup(void)
{
    //int* null_pointer = NULL;
    //null_pointer[0] = 0;
    panic("ha ha ha ha ha");
    printk(KERN_INFO "Bye Bye Iva.\n");
}

module_init(hello_init);
module_exit(hello_cleanup);
