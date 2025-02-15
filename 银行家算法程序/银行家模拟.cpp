#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#define m 50

int no1;        //进程数

int no2;        //资源数

int r;             //用于判断系统是否安全

int max[m][m], allocation[m][m], need[m][m], available[m];

void input();

void check();

void print();



int main()

{

    int i, j, p = 0, q = 0;

    char c;

    int request[m], allocation1[m][m], need1[m][m], available1[m];

    input();    //输入

    print();  //输出已知条件

    check();       //检测TO时刻已知条件的安全状态

    if (r == 1) //如果安全则执行以下代码

    {

        do {

            q = 0;

            p = 0;

            printf("\n请输入请求资源的进程号(0~%d): ", no1 - 1);

            while (1)

            {

                scanf("%d", &i);

                if (i >= no1)

                {

                    printf("输入错误,请重新输入: ");

                    continue;

                }

                else break;

            }

            printf("\n请输入该进程所请求的资源数request[j]: ");

            for (j = 0; j < no2; j++)

                scanf("%d", &request[j]);

            for (j = 0; j < no2; j++)

                if (request[j] > need[i][j])

                {

                    p = 1;      //判断请求是否超过该进程所需要的资源数

                    break;

                }

            if (p) printf("请求资源超过该进程资源需求量,请求失败!\n\n");

            else

            {

                for (j = 0; j < no2; j++)

                    if (request[j] > available[j]) q = 1;      //判断请求是否超过可用资源数

                if (q) printf("\n没有足够的资源分配,请求失败!\n\n");

                else    //请求满足条件

                {

                    for (j = 0; j < no2; j++)

                    {

                        available1[j] = available[j];

                        allocation1[i][j] = allocation[i][j];

                        need1[i][j] = need[i][j];     //保存原已分配的资源数，仍需要的资源数和可用的资源数



                        available[j] = available[j] - request[j];

                        allocation[i][j] += request[j];

                        need[i][j] = need[i][j] - request[j];     //系统尝试把资源分配给请求的进程

                    }

                    printf("\n尝试分配后的有关资源数据\n");

                    print();

                    printf("\n检查分配后系统是否安全中......\n");

                    check();   //检测分配后的安全性

                    if (r == 0)   //如果分配后系统不安全

                    {

                        for (j = 0; j < no2; j++)

                        {

                            available[j] = available1[j];

                            allocation[i][j] = allocation1[i][j];

                            need[i][j] = need1[i][j];     //还原已分配的资源数仍需要的资源数和可用的资源数

                        }

                        printf("返回分配前资源数\n");

                        print();

                    }

                    else if (r == 1)

                    {

                        int flag = 1;

                        for (j = 0; j < no2; j++)

                        {

                            if (need[i][j] != 0)

                            {

                                flag = 0;

                                break;

                            }

                        }

                        if (flag == 1)

                        {

                            for (j = 0; j < no2; j++)

                            {

                                available[j] += allocation[i][j];

                                allocation[i][j] = 0;

                            }

                        }

                        print();

                    }

                }

            }

            printf("\n是否还需要继续分配? (Y or N ?)\n");   //判断是否继续进行资源分配

            c = getche();

            printf("\n");

        } while (c == 'y' || c == 'Y');

    }

    system("pause");

    return 0;

}



void input()

{

    int i, j;

    printf("******************************************************\n");

    printf("*               银行家算法的设计与实现               *\n");

    printf("******************************************************\n");

    printf("请输入进程总数: ");              //P1、P2、P3等

    scanf("%d", &no1);

    printf("请输入资源种类数: ");         //A、B、C等

    scanf("%d", &no2);



    printf("请输入Max矩阵:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            scanf("%d", &max[i][j]);      //输入已知进程最大资源需求量



    printf("请输入Allocation矩阵:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            scanf("%d", &allocation[i][j]);           //输入已知的进程已分配的资源数



    //printf("need矩阵为:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            need[i][j] = max[i][j] - allocation[i][j];               //根据输入的两个数组计算出need矩阵的值



    printf("请输入可用资源数Available[i]: ");

    for (i = 0; i < no2; i++)

        scanf("%d", &available[i]);          //输入己知的可用资源数

}



void check()       //安全算法函数

{

    int k, f, v = 0, i, j;

    int work[m], a[m];

    bool finish[m];

    r = 1;

    for (i = 0; i < no1; i++)

        finish[i] = false; //初始化进程均没得到足够资源数并完成

    for (i = 0; i < no2; i++)

        work[i] = available[i];       //work表提供进程继续运行的各类资源数

    k = no1;

    do {

        for (i = 0; i < no1; i++)

        {

            if (finish[i] == false)

            {
 
                f = 1;

                for (j = 0; j < no2; j++)

                    if (need[i][j] > work[j])

                    {

                        f = 0;

                        break;

                    }

                if (f == 1)   //找到还没有完成且需求数小于可提供进程继续运行的资源数的进程

                {

                    finish[i] = true;

                    a[v++] = i;       //记录安全序列号

                    for (j = 0; j < no2; j++)

                        work[j] += allocation[i][j];        //释放该进程己分配的资源

                }

            }

        }

        k--;

    } while (k > 0);

    f = 1;

    for (i = 0; i < no1; i++) //判断是否所有的进程都完成

    {

        if (finish[i] == false)

        {

            f = 0;

            break;

        }

    }

    if (f == 0) //若有进程没完成，则为不安全状态

    {

        printf("\n系统处在不安全状态!");

        r = 0;

    }

    else

    {

        printf("\n系统当前为安全状态,安全序列为: ");

        printf("{ p%d", a[0]);

        for (i = 1; i < no1 - 1; i++)

            printf(", p%d", a[i]); //输出安全序列

        printf(", p%d }", a[i]);

        printf("\n");

    }

}



void print() //输出函数

{

    int i, j;

    printf("\n");

    printf("------------------------------此时刻资源分配情况------------------------------\n");

    printf("|    进程名    |     Max     |   Allocation   |    Need    |    Available    |\n");

    for (i = 0; i < no1; i++)

    {

        printf("       p%d         ", i, i);

        for (j = 0; j < no2; j++)

            printf("%d   ", max[i][j]);

        printf("\t ");

        for (j = 0; j < no2; j++)

            printf("%d   ", allocation[i][j]);

        printf("\t ");

        for (j = 0; j < no2; j++)

            printf("%d   ", need[i][j]);

        printf("\t");

        if (i == 0)

        {

            for (j = 0; j < no2; j++)

                printf("%d   ", available[j]);

        }

        printf("\n");

    }

    printf("------------------------------------------------------------------------------\n");

}
