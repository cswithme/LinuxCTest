/*
 * 典型的单向链表
 *
 * 有两种数据类型: 链表头、链表元素
 * 表元素: 自己定义一个结构体, 结构体中要包含下一个元素的指针, 该指针用SLIST_ENTRY声明
 * 表头: 用SLIST_HEAD声明的结构体
 * 程序自己负责内存的申请和释放!!!!!!!!!!!!!
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/queue.h>


//主要的宏
// SLIST_ENTRY(type): 声明链表元素 下一个元素的指针, type是表元素定义
// SLIST_HEAD(name, type): 声明链表头, type是表元素定义
// SLIST_INIT(head) : 对head进行初始化
// SLIST_INSERT_HEAD(head, elm, field) : 从list头部插入elm   field:元素中通过SLIST_ENTRY定义的变量名
// SLIST_INSERT_AFTER(slistelm, elm, field) : 将elm 插入到slistelm后面 field:元素中通过SLIST_ENTRY定义的变量名
// SLIST_REMOVE_HEAD(head, field) : 从list的头部删除一个节点 field:元素中通过SLIST_ENTRY定义的变量名
// SLIST_REMOVE(head, elm, type, field) : 从list中删除elm  //type:要删除元素的结构体名
// SLIST_FOREACH(var, head, field) : 循环遍历所有节点, var为中间变量
// SLIST_EMPTY(head) : 判断list是否为空
// SLIST_FIRST(head) : 获取第一个节点
// SLIST_NEXT(elm, field) : 获取elm的下一个节点


//元素定义
struct ST_SLIST_ELEMENT{
	SLIST_ENTRY(ST_SLIST_ELEMENT) next;
	int iContent;
};

//头定义
SLIST_HEAD(ST_HEAD, ST_SLIST_ELEMENT);

static struct ST_HEAD _head;
static struct ST_HEAD *head = &_head;



static void addHeadElement(int Content)
{
	struct ST_SLIST_ELEMENT *element = (struct ST_SLIST_ELEMENT*)malloc(sizeof(struct ST_SLIST_ELEMENT));
	element->iContent = Content;

	SLIST_INSERT_HEAD(head, element, next);
}

static void addElementAfter(struct ST_SLIST_ELEMENT *posElm, int Content)
{
	struct ST_SLIST_ELEMENT *element = (struct ST_SLIST_ELEMENT*)malloc(sizeof(struct ST_SLIST_ELEMENT));
	element->iContent = Content;

	SLIST_INSERT_AFTER(posElm, element, next);
}

static void printSList()
{
	struct ST_SLIST_ELEMENT *tmp;
	SLIST_FOREACH(tmp, head, next){
		printf("%d->", tmp->iContent);
	}
	printf("null\n");
}


void SListTest()
{
	SLIST_INIT(head);

	addHeadElement(1);
	addHeadElement(0);
	printf("After add Head: ");
	printSList();

	struct ST_SLIST_ELEMENT *num0 = SLIST_FIRST(head);
	struct ST_SLIST_ELEMENT *num1 = SLIST_NEXT(num0, next);

	addElementAfter(num1, 4);
	addElementAfter(num1, 3);
	addElementAfter(num1, 2);
	printf("After add after: ");
	printSList();

	struct ST_SLIST_ELEMENT *fistElm = SLIST_FIRST(head);
	SLIST_REMOVE_HEAD(head, next);
	free(fistElm);
	printf("After SLIST_REMOVE_HEAD: ");
	printSList();

	struct ST_SLIST_ELEMENT *num2 = SLIST_NEXT(SLIST_FIRST(head), next);
	SLIST_REMOVE(head, num2, ST_SLIST_ELEMENT, next);
	free(num2);
	printf("After SLIST_REMOVE: ");
	printSList();

	while(!SLIST_EMPTY(head)){
		struct ST_SLIST_ELEMENT *fistElm = SLIST_FIRST(head);
		printf("Remove value: %d\n", fistElm->iContent);
		SLIST_REMOVE(head, fistElm, ST_SLIST_ELEMENT, next);
		free(fistElm);
	}

	printf("After clear: ");
	printSList();

}
