#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/kthread.h>
#include <linux/sched.h>
#include <linux/types.h>

static atomic_t c;
struct task_struct *rt, *wt;
static int wf(void* _){
  while(!kthread_should_stop()){
    atomic_inc(&c);
    msleep(500);
  }
  do_exit(0);
}

static int rf(void* _){
  while(!kthread_should_stop()){
    printk("cnt=%d\n", atomic_read(&c));
    msleep(500);
  }
  do_exit(0);
}

static int __init my_init(void){
  printk("Hello\n");
  atomic_set(&c, 0);
  rt = kthread_run(rf, NULL, "rt");
  wt = kthread_run(wf, NULL, "wt");
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
