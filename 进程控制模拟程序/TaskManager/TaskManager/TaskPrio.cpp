#include "stdafx.h"
#include "TaskPrio.h"
#include<cstdio>
//简单的基于优先级的任务调度器的实现，使用了链表数据结构


//任务调度器
TaskPrio::TaskPrio()
{
	pr = NULL;
	plist = new Plist();
}


TaskPrio::~TaskPrio()
{
}
//函数用于显示链表中进程的信息。它接受一个 PCB* 参数，
// 并打印链表中每个进程的进程ID（pid）和优先级（prio）。
void TaskPrio::show(PCB* p) {
	while (p != NULL) {
		printf("P%d=%d ",p->pid,p->prio);
		p = p->next;
	}
	puts("\n-------");
}
//模拟了进程的执行过程
void TaskPrio::myTask() 
{//创建了10个进程（PCB），并将它们插入基于优先级的链表中
	for (int i = 1; i <= 10; i++) {
		PCB *p=plist->create();
		plist->insertP(p);
	}
	int i = 0;
	while (!plist->empty()) {
		//重复地从列表中获取具有最高优先级的进程（pr），降低其优先级和执行时间，
		// 并根据其是否需要进一步处理，将其重新插入列表或者将其移到另一个列表（pf）中，
		// 表示其执行已完成
		pr = plist->firstin();
		pr->need_time -= 1;
		pr->prio -= 3;
		pr->cpu_time += 1;
		pr->need_time -= 1;
		if (pr->need_time <= 0) {
			pr->next = pf;
			pf = pr;
		}
		else plist->insertP(pr);
		show(plist->getHead());
		if (++i == 550) break;
	}
	show(pf);
}
