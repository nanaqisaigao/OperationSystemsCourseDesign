#include "stdafx.h"
#include "TaskPrio.h"
#include<cstdio>
//�򵥵Ļ������ȼ��������������ʵ�֣�ʹ�����������ݽṹ


//���������
TaskPrio::TaskPrio()
{
	pr = NULL;
	plist = new Plist();
}


TaskPrio::~TaskPrio()
{
}
//����������ʾ�����н��̵���Ϣ��������һ�� PCB* ������
// ����ӡ������ÿ�����̵Ľ���ID��pid�������ȼ���prio����
void TaskPrio::show(PCB* p) {
	while (p != NULL) {
		printf("P%d=%d ",p->pid,p->prio);
		p = p->next;
	}
	puts("\n-------");
}
//ģ���˽��̵�ִ�й���
void TaskPrio::myTask() 
{//������10�����̣�PCB�����������ǲ���������ȼ���������
	for (int i = 1; i <= 10; i++) {
		PCB *p=plist->create();
		plist->insertP(p);
	}
	int i = 0;
	while (!plist->empty()) {
		//�ظ��ش��б��л�ȡ����������ȼ��Ľ��̣�pr�������������ȼ���ִ��ʱ�䣬
		// ���������Ƿ���Ҫ��һ�������������²����б���߽����Ƶ���һ���б�pf���У�
		// ��ʾ��ִ�������
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
