#include <stdio.h>

#include <stdlib.h>

#include <conio.h>

#define m 50

int no1;        //������

int no2;        //��Դ��

int r;             //�����ж�ϵͳ�Ƿ�ȫ

int max[m][m], allocation[m][m], need[m][m], available[m];

void input();

void check();

void print();



int main()

{

    int i, j, p = 0, q = 0;

    char c;

    int request[m], allocation1[m][m], need1[m][m], available1[m];

    input();    //����

    print();  //�����֪����

    check();       //���TOʱ����֪�����İ�ȫ״̬

    if (r == 1) //�����ȫ��ִ�����´���

    {

        do {

            q = 0;

            p = 0;

            printf("\n������������Դ�Ľ��̺�(0~%d): ", no1 - 1);

            while (1)

            {

                scanf("%d", &i);

                if (i >= no1)

                {

                    printf("�������,����������: ");

                    continue;

                }

                else break;

            }

            printf("\n������ý������������Դ��request[j]: ");

            for (j = 0; j < no2; j++)

                scanf("%d", &request[j]);

            for (j = 0; j < no2; j++)

                if (request[j] > need[i][j])

                {

                    p = 1;      //�ж������Ƿ񳬹��ý�������Ҫ����Դ��

                    break;

                }

            if (p) printf("������Դ�����ý�����Դ������,����ʧ��!\n\n");

            else

            {

                for (j = 0; j < no2; j++)

                    if (request[j] > available[j]) q = 1;      //�ж������Ƿ񳬹�������Դ��

                if (q) printf("\nû���㹻����Դ����,����ʧ��!\n\n");

                else    //������������

                {

                    for (j = 0; j < no2; j++)

                    {

                        available1[j] = available[j];

                        allocation1[i][j] = allocation[i][j];

                        need1[i][j] = need[i][j];     //����ԭ�ѷ������Դ��������Ҫ����Դ���Ϳ��õ���Դ��



                        available[j] = available[j] - request[j];

                        allocation[i][j] += request[j];

                        need[i][j] = need[i][j] - request[j];     //ϵͳ���԰���Դ���������Ľ���

                    }

                    printf("\n���Է������й���Դ����\n");

                    print();

                    printf("\n�������ϵͳ�Ƿ�ȫ��......\n");

                    check();   //�������İ�ȫ��

                    if (r == 0)   //��������ϵͳ����ȫ

                    {

                        for (j = 0; j < no2; j++)

                        {

                            available[j] = available1[j];

                            allocation[i][j] = allocation1[i][j];

                            need[i][j] = need1[i][j];     //��ԭ�ѷ������Դ������Ҫ����Դ���Ϳ��õ���Դ��

                        }

                        printf("���ط���ǰ��Դ��\n");

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

            printf("\n�Ƿ���Ҫ��������? (Y or N ?)\n");   //�ж��Ƿ����������Դ����

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

    printf("*               ���м��㷨�������ʵ��               *\n");

    printf("******************************************************\n");

    printf("�������������: ");              //P1��P2��P3��

    scanf("%d", &no1);

    printf("��������Դ������: ");         //A��B��C��

    scanf("%d", &no2);



    printf("������Max����:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            scanf("%d", &max[i][j]);      //������֪���������Դ������



    printf("������Allocation����:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            scanf("%d", &allocation[i][j]);           //������֪�Ľ����ѷ������Դ��



    //printf("need����Ϊ:\n");

    for (i = 0; i < no1; i++)

        for (j = 0; j < no2; j++)

            need[i][j] = max[i][j] - allocation[i][j];               //���������������������need�����ֵ



    printf("�����������Դ��Available[i]: ");

    for (i = 0; i < no2; i++)

        scanf("%d", &available[i]);          //���뼺֪�Ŀ�����Դ��

}



void check()       //��ȫ�㷨����

{

    int k, f, v = 0, i, j;

    int work[m], a[m];

    bool finish[m];

    r = 1;

    for (i = 0; i < no1; i++)

        finish[i] = false; //��ʼ�����̾�û�õ��㹻��Դ�������

    for (i = 0; i < no2; i++)

        work[i] = available[i];       //work���ṩ���̼������еĸ�����Դ��

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

                if (f == 1)   //�ҵ���û�������������С�ڿ��ṩ���̼������е���Դ���Ľ���

                {

                    finish[i] = true;

                    a[v++] = i;       //��¼��ȫ���к�

                    for (j = 0; j < no2; j++)

                        work[j] += allocation[i][j];        //�ͷŸý��̼��������Դ

                }

            }

        }

        k--;

    } while (k > 0);

    f = 1;

    for (i = 0; i < no1; i++) //�ж��Ƿ����еĽ��̶����

    {

        if (finish[i] == false)

        {

            f = 0;

            break;

        }

    }

    if (f == 0) //���н���û��ɣ���Ϊ����ȫ״̬

    {

        printf("\nϵͳ���ڲ���ȫ״̬!");

        r = 0;

    }

    else

    {

        printf("\nϵͳ��ǰΪ��ȫ״̬,��ȫ����Ϊ: ");

        printf("{ p%d", a[0]);

        for (i = 1; i < no1 - 1; i++)

            printf(", p%d", a[i]); //�����ȫ����

        printf(", p%d }", a[i]);

        printf("\n");

    }

}



void print() //�������

{

    int i, j;

    printf("\n");

    printf("------------------------------��ʱ����Դ�������------------------------------\n");

    printf("|    ������    |     Max     |   Allocation   |    Need    |    Available    |\n");

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
