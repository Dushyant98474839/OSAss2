

#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h> 
#include <linux/moduleparam.h>

MODULE_LICENSE("GPL"); 
MODULE_AUTHOR("DUSHYANT"); 
MODULE_DESCRIPTION("ASS2");

static int __init display_init(void){ 
	struct task_struct *str;
	int n=0;
	printk(KERN_INFO "LOADING..");
	for_each_process(str){
		//printk(KERN_ALERT "%d\n" +n);
		if(str->state==TASK_RUNNING)
		{
			//printk(KERN_INFO "TT");
			n++;
		}
		//printk(KERN_ALERT "%d\n" +n);
	}
	printk(KERN_INFO "COUNT: %d\n",n); 
	return 0;
}

static void __exit display_cleanup(void){ 
	printk(KERN_INFO "EXITING\n");
}

module_init(display_init);
module_exit(display_cleanup);