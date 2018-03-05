#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/list.h>
#include <linux/types.h>
#include <linux/slab.h>

struct birthday {
	int day;
	int month;
	int year;
	struct list_head list;
};

static LIST_HEAD(birthday_list);

/* This function is called when the module is loaded. */
int simple_init(void)
{
	struct birthday *p1, *p2, *p3, *p4, *p5;
	struct birthday *ptr;

	printk(KERN_INFO "Loading Module\n");

	p1 = kmalloc(sizeof(*p1), GFP_KERNEL);
	p1->day = 2;
	p1->month = 8;
	p1->year = 1995;
	list_add_tail(&p1->list, &birthday_list);

	p2 = kmalloc(sizeof(*p2), GFP_KERNEL);
	p2->day = 3;
	p2->month = 9;
	p2->year = 1996;
	list_add_tail(&p2->list, &birthday_list);

	p3 = kmalloc(sizeof(*p3), GFP_KERNEL);
	p3->day = 4;
	p3->month = 10;
	p3->year = 1997;
	list_add_tail(&p3->list, &birthday_list);

	p4 = kmalloc(sizeof(*p4), GFP_KERNEL);
	p4->day = 5;
	p4->month = 11;
	p4->year = 1998;
	list_add_tail(&p4->list, &birthday_list);
	
	p5 = kmalloc(sizeof(*p5), GFP_KERNEL);
	p5->day = 6;
	p5->month = 12;
	p5->year = 1999;
	list_add_tail(&p5->list, &birthday_list);

	list_for_each_entry(ptr, &birthday_list, list) {
		printk(KERN_INFO "Person's birthday: %d/%d/%d\n", ptr->month, ptr->day, ptr->year);
	}

       return 0;
}

/* This function is called when the module is removed. */
void simple_exit(void) {

	struct birthday *ptr, *next;

	printk(KERN_INFO "Removing Module\n");
	
	list_for_each_entry_safe(ptr, next, &birthday_list, list) {
		printk(KERN_INFO "Removing birthday\n");
		list_del(&ptr->list);
		kfree(ptr);
	}
}

/* Macros for registering module entry and exit points. */
module_init( simple_init );
module_exit( simple_exit );

MODULE_LICENSE("GPL");
MODULE_DESCRIPTION("Simple Module");
MODULE_AUTHOR("SGG");

