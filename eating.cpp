#include <stdio.h>
#include<malloc.h>
#pragma warning(disable : 4996)

#define TOWPERSON_TABLE 2  //����������
#define FOURPERSON_TABLE 3 //����������
#define SIXPERSON_TABLE 2  //����������
#define OUTSIZE_PERSON_MAX 12 //���������������

//���ţ�
//��������0 1 
//�����飺2 3 4
//��������5 6
int table[7] = { 0 };

//����������ʽ
struct Person
{
	int personNum = 0;//���ε�������
	char sitting = 0; //����
	struct Person* next = NULL;
	int tableNumber = -1;

	int selectTable();//ѡ��

};

//˫������
struct DoubleLinkList
{
	int length = 0; //����ĳ���
	struct Person* front; //��ͷָ��
	struct Person* rear; //��βָ��
};





//�����ʼ�����������ʼ��Ϊ������
void initDoubleLinkList(struct DoubleLinkList* LQ);

//�ж������Ƿ�Ϊ��
int isFull(struct DoubleLinkList* LQ);

//�ж�����Ϊ��
int isEmpty(struct DoubleLinkList* LQ);

//����,��Ԫ�� data ���뵽�� LQ ��
int enterDoubleLinkList(struct DoubleLinkList* LQ, int pNum);

//�뿪���������б�ͷ��Ԫ�س�������ĵ�һ��Ԫ�س�Ϊ�µı���
int DeleteDoubleLinkList(struct DoubleLinkList* LQ, struct Person* p);

//���
void enter();

//����
void settle();

//�鿴�Ͳ�����͵ȴ�����
void check();

//����ȴ�����
void adjustWaitList();

struct DoubleLinkList* LQ = (struct DoubleLinkList*)malloc(sizeof(struct DoubleLinkList));
int waitPerson = 0;
int waitPersonlist[OUTSIZE_PERSON_MAX] = { 0 };//���12��������
int j = 0;


int main()
{
	initDoubleLinkList(LQ);
	char select;
	while (1)
	{
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("��ѡ����Ҫ�����Ĳ�������A������  B������  C���鿴�Ͳ�����͵ȴ�����\n");
		scanf("%c", &select);

		switch (select)
		{
		case 'A':
			enter();
			break;
		case 'B':
			settle();
			break;
		case 'C':
			check();
			break;
		default:
			break;
		}

		getchar();
	}

	return 0;

}

//ѡ������
int Person::selectTable()
{
	if (personNum < 2 && personNum > 0)//������
	{
		for (int i = 0; i < 2; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("�ɹ�ѡ������������Ϊ%d\n", i);
				return 1;
			}
		}
	}
	else if (personNum == 2)//���˺�������
	{
		for (int i = 0; i < 5; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("�ɹ�ѡ������������Ϊ%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum == 3)//������
	{
		for (int i = 5; i < 5; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("�ɹ�ѡ������������Ϊ%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum == 4)//���˺�������
	{
		for (int i = 5; i < 7; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("�ɹ�ѡ������������Ϊ%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum <= 6 && personNum > 4)//������
	{
		for (int i = 8; i < 7; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("�ɹ�ѡ������������Ϊ%d\n", i);
				return 1;
			}

		}
	}
	else
	{
		printf("�����������������������������������\n");
	}
	return 0;
}



//�����ʼ�����������ʼ��Ϊ������
void initDoubleLinkList(struct DoubleLinkList* LQ)
{
	if (!LQ) return;
	LQ->length = 0;
	LQ->front = LQ->rear = NULL; //�Ѷ�ͷ�ͱ�βָ��ͬʱ�� 0
}

//�ж������Ƿ�Ϊ��
int isFull(struct DoubleLinkList* LQ)
{
	if (!LQ) return 0;
	if (LQ->length == 7)//�������10��
	{
		return 1;
	}
	return 0;
}

//�ж�����Ϊ��
int isEmpty(struct DoubleLinkList* LQ)
{
	if (!LQ) return 0;
	if (LQ->front == NULL)
	{
		return 1;
	}
	return 0;
}

//���,��Ԫ�� data ���뵽���� LQ ��
int enterDoubleLinkList(struct DoubleLinkList* LQ, int pNum) {
	if (!LQ) return 0;
	if (isFull(LQ)) {
		printf("��������������\n");
		waitPerson += pNum;//�ȴ���������pNum
		if (waitPerson > 12)//�޷�����
		{
			waitPerson -= pNum;//��ԭ
			printf("�ȴ������޷�������%d��\n", pNum);
		}
		else //����ȴ�
		{
			waitPersonlist[j] = pNum;
			j++;//�ȴ��б��±�+1
			printf("��%d�˽���ȴ�����\n", pNum);
		}
		return 0;
	}

	//����δ��
	struct Person* P = (struct Person*)malloc(sizeof(struct Person));
	P->personNum = pNum;
	if (!P->selectTable())//ѡ��
	{
		printf("�����ں��ʵ�������֮����ƥ�䣡����\n");
		waitPerson += pNum;
		if (waitPerson > 12)
		{
			waitPerson -= pNum;
			printf("�ȴ������޷�������%d��\n", pNum);
		}
		else
		{
			if (pNum > 6) {
				waitPerson -= pNum;
				free(P);
				return 0;
			}
			waitPersonlist[j] = pNum;
			j++;
			printf("��%d�˽���ȴ�����\n", pNum);
		}
		free(P);
		return 0;
	}
	P->next = NULL;
	if (isEmpty(LQ)) {//������
		LQ->front = LQ->rear = P;
	}
	else {
		LQ->rear->next = P;//�ڱ�β����ڵ� qNode
		LQ->rear = P; //��βָ���²���Ľڵ�
	}
	LQ->length++;
	return 1;
}


//�����������б�ͷ��Ԫ�س������ĵ�һ��Ԫ�س�Ϊ�µı���
int DeleteDoubleLinkList(struct DoubleLinkList* LQ, struct Person* p)
{
	struct Person* tmp = NULL;
	if (!LQ || isEmpty(LQ)) {
		printf("����Ϊ�գ�������\n");
		return 0;
	}
	if (!p) return 0;
	tmp = LQ->front;
	while (1)
	{
		if (tmp == p) {
			LQ->front = p->next;
			if (!LQ->front) LQ->rear = NULL;//�����ͷ���к󲻴�������Ԫ�أ���rear �ڵ�ҲҪ�ÿ�
			break;
		}
		if (tmp->next == p) break;
		tmp = tmp->next;
	}

	tmp->next = p->next;

	LQ->length--;
	table[p->tableNumber] = 0;
	if (waitPerson > 0)
	{

		enterDoubleLinkList(LQ, waitPersonlist[0]);
		waitPerson -= waitPersonlist[0];
		adjustWaitList();
		j--;
	}

	free(tmp);
	return 1;
}

//����
void enter()
{
	int num;
	printf("�����뱾�����������");
	scanf("%d", &num);
	enterDoubleLinkList(LQ, num);//���
}

//����
void settle()
{
	int tableNum;
	struct Person* p;
	printf("��ѡ���ĸ����ŵ��ˣ�\n");
	scanf("%d", &tableNum);
	if (!table[tableNum]) printf("����%d����!!\n", tableNum);

	p = LQ->front;//ָ���ͷ
	while (p)
	{
		if (p->tableNumber == tableNum) break;
		p = p->next;
	}

	table[tableNum] = 0;
	if (DeleteDoubleLinkList(LQ, p))
	{
		printf("����%d�����ѽ����뿪������%d����!!\n", tableNum, tableNum);

	}
}

//��ѯ
void check()
{
	for (int i = 0; i < 7; i++)
	{
		if (table[i])
			printf("����%dռ��!!\n", i);
		else
			printf("����%d����!!\n", i);

	}
	printf("Ŀǰ�ȴ�������%d!!\n", waitPerson);
}

void adjustWaitList()
{
	for (int i = 0; i < 12; i++)
		waitPersonlist[i] = waitPersonlist[i + 1];
}
