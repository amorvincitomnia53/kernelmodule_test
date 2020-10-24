#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/string.h>
#include <linux/gfp.h>
#include <linux/highmem.h>

static int __init test_init(void)
{
  printk(KERN_INFO "hoge: Hello\n");
  const char* str = "48206105";
  struct page* my_page = alloc_page(GFP_HIGHUSER);
  if(my_page == NULL){
    printk(KERN_INFO "hoge: No memory\n");
    return -1;
  }
  
  char* dest = (char*)kmap(my_page);
  
  strcpy(dest,str);
  
  printk(KERN_INFO "%s\n",dest);

  kunmap(my_page);
  __free_page(my_page);
  
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
