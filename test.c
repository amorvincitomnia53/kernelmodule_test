#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/spinlock.h>
#include <linux/kthread.h>
#include <linux/sched.h>

static int c;
DEFINE_RWLOCK(l);
struct task_struct* rt1, *rt2, *rt3, *wt;

static int wf(void*_){
  while(!kthread_should_stop()){
    write_lock(&l);
    c++;
    write_unlock(&l);
    msleep(500);
  }
  do_exit(0);
}
static int rf(void*_){
  while(!kthread_should_stop()){
    read_lock(&l);
    printk("c=%d\n",c);
    read_unlock(&l);
    msleep(500);
  }
  do_exit(0);
}
static int __init my_init(void){
  printk("Hello\n");
  c=0;
  rt1=kthread_run(rf,NULL,"rt1");
  rt2=kthread_run(rf,NULL,"rt2");
  rt3=kthread_run(rf,NULL,"rt3");
  wt=kthread_run(wf,NULL,"wt");
  return 0;
}
static void __exit my_exit(void){
  kthread_stop(rt1);
  kthread_stop(rt2);
  kthread_stop(rt3);
  kthread_stop(wt);
  printk("Bye\n");
}
module_init(my_init);
module_exit(my_exit);
MODULE_LICENSE("GPL");
