#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/sched.h>

static int c;
DEFINE_SPINLOCK(l);
struct task_struct* rt, *wt;

static void wf(void*_){
  while(!kthread_should_stop()){
    spin_lock(&l);
    c++;
    spin_unlock(&l);
    msleep(500);
  }
  do_exit(0);
}
static void rf(void*_){
  while(!kthread_should_stop()){
    spin_lock(&l);
    printk("c=%d\n", c);
    spin_unlock(&l);
    msleep(500);
  }
  do_exit(0);
}
static int __init my_init(void){
  printk("Hello\n");
  c=0;
  rt=kthread_run(rf, NULL, "rt");
  wt=kthread_run(wf,NULL,"wt");
  return 0;
}
static void __exit my_exit(void){
  kthread_stop(rt);
  kthread_stop(wt);
  printk("Bye\n");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
