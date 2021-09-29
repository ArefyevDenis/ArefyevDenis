#include <linux/init.h>             // Macros used to mark up functions e.g., __init __exit
#include <linux/module.h>           // Core header for loading LKMs into the kernel
#include <linux/kernel.h>           // Contains types, macros, functions for the kernel

#include <asm/io.h>
#include <linux/kthread.h>  // for kthread_run
#include <linux/wait.h>     // for wait queue
#include <linux/delay.h>    // for msleep

MODULE_LICENSE("GPL");              ///< The license type -- this affects runtime behavior
MODULE_AUTHOR("Denis Arefyev");      ///< The author -- visible when you use modinfo
MODULE_DESCRIPTION("A simple Linux driver for the BBB.");  ///< The description -- see modinfo
MODULE_VERSION("0.1");              ///< The version of the module

static char *name = "world";        ///< An example LKM argument -- default value is "world"
module_param(name, charp, S_IRUGO); ///< Param desc. charp = char ptr, S_IRUGO can be read/not changed
MODULE_PARM_DESC(name, "The name to display in /var/log/kern.log");  ///< parameter description



static int keyboard_led(void *unused)
{
    int count=32;
    pr_info("Start: %s \n",__PRETTY_FUNCTION__);
    do{
 /*       unsigned char in_b = inb (0x64);
            if(in_b & 0x01){} // проверка состояния выходного буфера (1) он заполнен можно читать
            if(!(in_b & 0x02)){
                outb (0x60, 0xed);
                 msleep(10);
                outb (0x60, count%8); 
            } // состояние входного буфера 0-пуст 1-заполнен
            if(in_b & 0x04){}
            if(in_b & 0x08){}
            if(in_b & 0x10){}
            if(in_b & 0x20){}
            if(in_b & 0x40){}
            if(in_b & 0x80){}*/
            msleep(1000);
            
    }while(count--);
    pr_info("Stop: %s \n",__PRETTY_FUNCTION__);
    
    return 0;
}

static int __init Key_init(void)
{
   int pid;
   pr_info("Message: %s %s\n",__PRETTY_FUNCTION__, name);
   pid = kthread_run(keyboard_led, NULL, __PRETTY_FUNCTION__);
   return 0;
}

static void __exit Key_exit(void)
{
   pr_info("Message: %s %s\n",__PRETTY_FUNCTION__, name);
}

module_init(Key_init);
module_exit(Key_exit);
