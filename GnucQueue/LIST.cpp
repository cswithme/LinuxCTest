/*
 * 非典型的单向链表,
 * 与SLIST不同, 链表元素保存了(指向前一个元素的next指针的指针)，做到删除元素不用遍历链表 O(1)
 * 有两种数据类型: 链表头、链表元素
 * 表元素: 自己定义一个结构体, 结构体中要包含下一个元素的指针, 该指针用LIST_ENTRY声明
 * 表头: 用LIST_HEAD声明的结构体
 * 程序自己负责内存的申请和释放!!!!!!!!!!!!!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>


//主要的宏
//LIST_INIT(head) :对head进行初始化
//LIST_INSERT_HEAD(head, elm, field) : 从list头部插入elm
//LIST_REMOVE(elm, field) : 将elm从list中删除
//LIST_INSERT_AFTER(listelm, elm, field) : 将elm插入到listelm后面
//LIST_INSERT_BEFORE(listelm, elm, field) : 将elm插入到liistelm之前
//LIST_FOREACH(var, head, field) : 循环遍历所有节点, var为中间变量
//LIST_EMPTY(head) : 判断list是否为空
//LIST_FIRST(head) : 获取第一个节点
//LIST_NEXT(elm, field) : 获取elm的下一个节点



//元素定义
struct ST_LIST_ELEMENT{
	LIST_ENTRY(ST_LIST_ELEMENT) entries;
	int iContent;
};

//头定义
LIST_HEAD(ST_HEAD, ST_LIST_ELEMENT);

static struct ST_HEAD _head;
static struct ST_HEAD *head = &_head;



static void addHeadElement(int Content)
{
	struct ST_LIST_ELEMENT *element = (struct ST_LIST_ELEMENT*)malloc(sizeof(struct ST_LIST_ELEMENT));
	element->iContent = Content;

	LIST_INSERT_HEAD(head, element, entries);
}

static void addElementAfter(struct ST_LIST_ELEMENT *posElm, int Content)
{
	struct ST_LIST_ELEMENT *element = (struct ST_LIST_ELEMENT*)malloc(sizeof(struct ST_LIST_ELEMENT));
	element->iContent = Content;

	LIST_INSERT_AFTER(posElm, element, entries);
}
static void addElementBefore(struct ST_LIST_ELEMENT *posElm, int Content)
{
	struct ST_LIST_ELEMENT *element = (struct ST_LIST_ELEMENT*)malloc(sizeof(struct ST_LIST_ELEMENT));
	element->iContent = Content;

	LIST_INSERT_BEFORE(posElm, element, entries);
}

static void printList()
{
	struct ST_LIST_ELEMENT *tmp;
	LIST_FOREACH(tmp, head, entries){
		printf("%d->", tmp->iContent);
	}
	printf("null\n");
}


void ListTest()
{
	LIST_INIT(head);

	addHeadElement(2);
	addHeadElement(0);
	printf("After add Head: ");
	printList();

	struct ST_LIST_ELEMENT *num0 = LIST_FIRST(head);
	struct ST_LIST_ELEMENT *num1 = LIST_NEXT(num0, entries);

	addElementAfter(num1, 4);
	addElementAfter(num1, 3);
	addElementBefore(num1, 1);
	printf("After add: ");
	printList();

//	struct ST_LIST_ELEMENT *fistElm = LIST_FIRST(head);
//	LIST_REMOVE_HEAD(head, entries);
//	free(fistElm);
//	printf("After LIST_REMOVE_HEAD: ");
//	printList();

	struct ST_LIST_ELEMENT *num2 = LIST_NEXT(LIST_FIRST(head), entries);
	LIST_REMOVE(num2, entries);
	free(num2);
	printf("After LIST_REMOVE: ");
	printList();

	while(!LIST_EMPTY(head)){
		struct ST_LIST_ELEMENT *fistElm = LIST_FIRST(head);
		printf("Remove value: %d\n", fistElm->iContent);
		LIST_REMOVE(fistElm, entries);
		free(fistElm);
	}

	printf("After clear: ");
	printList();

}
