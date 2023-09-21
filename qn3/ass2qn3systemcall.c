#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/sched/signal.h>
#include <linux/init.h>
#include <asm/unistd.h>
#include <asm/special_insns.h>
#include <asm/processor-flags.h>

#ifdef pr_fmt
#undef pr_fmt
#endif
#define pr_fmt(fmt) KBUILD_MODNAME ": " fmt

typedef long (*sys_call_ptr_t)(const struct pt_regs *);
static sys_call_ptr_t original_read;

MODULE_LICENSE("GPL");
MODULE_AUTHOR("DUSHYANT");
MODULE_DESCRIPTION("ASS2");

static unsigned long sys_call_table_addr;
module_param(sys_call_table_addr, ulong ,0);
MODULE_PARM_DESC(sys_call_table_addr, "Address of sys_call_table");

static void write_cr0_unsafe(unsigned long val)
{
    asm volatile("mov %0, %%cr0": "+r" (val) : : "memory");
}

static long mysys(const struct pt_regs *regs){
    struct task_struct *str;
    int n=0;
    //pr_info("read(%ld, 0x%lx, %lx)\n", regs->di, regs->si, regs->dx);
    for_each_process(str){
        if((str->state==TASK_RUNNING))
        {
            //printk(KERN_INFO "TT");
            n++;}
        }
    printk(KERN_INFO "COUNT: %d\n",n);
    return -EPERM;
}

static int __init display_init(void){
    unsigned long old_cr0;
    sys_call_ptr_t *real_sys_call_table;
    if(!sys_call_table_addr){
        printk(KERN_ERR "sys_call_table_addr not set");
        return -EINVAL;
    }
    real_sys_call_table=(sys_call_ptr_t *)sys_call_table_addr;
    old_cr0=read_cr0();
    write_cr0_unsafe(old_cr0 & ~(X86_CR0_WP));
    original_read=real_sys_call_table[__NR_read];
    real_sys_call_table[__NR_read]=mysys;
    write_cr0_unsafe(old_cr0);
    return 0;
}

static void __exit display_cleanup(void){
    unsigned long old_cr0;
    sys_call_ptr_t *real_sys_call_table;
    real_sys_call_table=(sys_call_ptr_t *)sys_call_table_addr;
    old_cr0=read_cr0();
    write_cr0_unsafe(old_cr0 & ~(X86_CR0_WP));
    if(original_read)
    real_sys_call_table[__NR_read]=original_read;
    write_cr0_unsafe(old_cr0);
    printk(KERN_INFO "EXITING\n\n");
}

module_init(display_init);
module_exit(display_cleanup);
