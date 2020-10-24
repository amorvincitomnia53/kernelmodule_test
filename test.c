#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>
static int __init test_init(void)
{

  const char* str = "48206105";
  char* dest = (char*)kmalloc(256, GFP_KERNEL);
  if(dest == NULL){printk(KERN_INFO "hoge: No memory"); return 0;}
  strcpy(dest,str);
  
  printk(KERN_INFO "%s\n",dest);
  kfree(dest);
  return 0;
  
}

static void __exit test_exit(void)
{
  printk(KERN_INFO "hoge: BYE!\n");
}

module_init(test_init);
module_exit(test_exit);

MODULE_AUTHOR("qwerty");
MODULE_LICENSE("GPL v2");
