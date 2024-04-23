#include <stdio.h>
#include<malloc.h>
#pragma warning(disable : 4996)

#define TOWPERSON_TABLE 2  //二人桌数量
#define FOURPERSON_TABLE 3 //四人桌数量
#define SIXPERSON_TABLE 2  //六人桌数量
#define OUTSIZE_PERSON_MAX 12 //门外最大容纳人数

//桌号：
//二人桌：0 1 
//四人组：2 3 4
//六人桌：5 6
int table[7] = { 0 };

//采用链表形式
struct Person
{
	int personNum = 0;//本次到店人数
	char sitting = 0; //就坐
	struct Person* next = NULL;
	int tableNumber = -1;

	int selectTable();//选座

};

//双向链表
struct DoubleLinkList
{
	int length = 0; //链表的长度
	struct Person* front; //表头指针
	struct Person* rear; //表尾指针
};





//链表初始化，将链表初始化为空链表
void initDoubleLinkList(struct DoubleLinkList* LQ);

//判断链表是否为满
int isFull(struct DoubleLinkList* LQ);

//判断链表为空
int isEmpty(struct DoubleLinkList* LQ);

//进入,将元素 data 插入到表 LQ 中
int enterDoubleLinkList(struct DoubleLinkList* LQ, int pNum);

//离开，将链表中表头的元素抽出，其后的第一个元素成为新的表首
int DeleteDoubleLinkList(struct DoubleLinkList* LQ, struct Person* p);

//入表
void enter();

//结账
void settle();

//查看就餐情况和等待人数
void check();

//整理等待链表
void adjustWaitList();

struct DoubleLinkList* LQ = (struct DoubleLinkList*)malloc(sizeof(struct DoubleLinkList));
int waitPerson = 0;
int waitPersonlist[OUTSIZE_PERSON_MAX] = { 0 };//最多12个单人组
int j = 0;


int main()
{
	initDoubleLinkList(LQ);
	char select;
	while (1)
	{
		printf("-------------------------------------------------------------------------------------------------\n");
		printf("请选择需要进行哪步操作：A、加入  B、结账  C、查看就餐情况和等待人数\n");
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

//选择入座
int Person::selectTable()
{
	if (personNum < 2 && personNum > 0)//二人桌
	{
		for (int i = 0; i < 2; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("成功选座，本次桌号为%d\n", i);
				return 1;
			}
		}
	}
	else if (personNum == 2)//二人和四人桌
	{
		for (int i = 0; i < 5; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("成功选座，本次桌号为%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum == 3)//四人桌
	{
		for (int i = 5; i < 5; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("成功选座，本次桌号为%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum == 4)//四人和六人桌
	{
		for (int i = 5; i < 7; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("成功选座，本次桌号为%d\n", i);
				return 1;
			}

		}
	}
	else if (personNum <= 6 && personNum > 4)//六人桌
	{
		for (int i = 8; i < 7; i++)
		{
			if (!table[i])
			{
				table[i] = 1;
				tableNumber = i;
				sitting = 1;
				printf("成功选座，本次桌号为%d\n", i);
				return 1;
			}

		}
	}
	else
	{
		printf("本批次人数超过存在桌子最大容纳人数！\n");
	}
	return 0;
}



//链表初始化，将链表初始化为空链表
void initDoubleLinkList(struct DoubleLinkList* LQ)
{
	if (!LQ) return;
	LQ->length = 0;
	LQ->front = LQ->rear = NULL; //把对头和表尾指针同时置 0
}

//判断链表是否为满
int isFull(struct DoubleLinkList* LQ)
{
	if (!LQ) return 0;
	if (LQ->length == 7)//允许最大10桌
	{
		return 1;
	}
	return 0;
}

//判断链表为空
int isEmpty(struct DoubleLinkList* LQ)
{
	if (!LQ) return 0;
	if (LQ->front == NULL)
	{
		return 1;
	}
	return 0;
}

//入表,将元素 data 插入到链表 LQ 中
int enterDoubleLinkList(struct DoubleLinkList* LQ, int pNum) {
	if (!LQ) return 0;
	if (isFull(LQ)) {
		printf("链表已满！！！\n");
		waitPerson += pNum;//等待人数增加pNum
		if (waitPerson > 12)//无法容纳
		{
			waitPerson -= pNum;//还原
			printf("等待地区无法再容纳%d人\n", pNum);
		}
		else //进入等待
		{
			waitPersonlist[j] = pNum;
			j++;//等待列表下表+1
			printf("该%d人进入等待地区\n", pNum);
		}
		return 0;
	}

	//链表未满
	struct Person* P = (struct Person*)malloc(sizeof(struct Person));
	P->personNum = pNum;
	if (!P->selectTable())//选座
	{
		printf("不存在合适的桌子与之人数匹配！！！\n");
		waitPerson += pNum;
		if (waitPerson > 12)
		{
			waitPerson -= pNum;
			printf("等待地区无法再容纳%d人\n", pNum);
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
			printf("该%d人进入等待地区\n", pNum);
		}
		free(P);
		return 0;
	}
	P->next = NULL;
	if (isEmpty(LQ)) {//空链表
		LQ->front = LQ->rear = P;
	}
	else {
		LQ->rear->next = P;//在表尾插入节点 qNode
		LQ->rear = P; //表尾指向新插入的节点
	}
	LQ->length++;
	return 1;
}


//出表，将链表中表头的元素出表，其后的第一个元素成为新的表首
int DeleteDoubleLinkList(struct DoubleLinkList* LQ, struct Person* p)
{
	struct Person* tmp = NULL;
	if (!LQ || isEmpty(LQ)) {
		printf("链表为空！！！！\n");
		return 0;
	}
	if (!p) return 0;
	tmp = LQ->front;
	while (1)
	{
		if (tmp == p) {
			LQ->front = p->next;
			if (!LQ->front) LQ->rear = NULL;//如果对头出列后不存在其他元素，则rear 节点也要置空
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

//加入
void enter()
{
	int num;
	printf("请输入本次入表人数：");
	scanf("%d", &num);
	enterDoubleLinkList(LQ, num);//入表
}

//结账
void settle()
{
	int tableNum;
	struct Person* p;
	printf("请选择哪个桌号的人？\n");
	scanf("%d", &tableNum);
	if (!table[tableNum]) printf("桌号%d空闲!!\n", tableNum);

	p = LQ->front;//指向表头
	while (p)
	{
		if (p->tableNumber == tableNum) break;
		p = p->next;
	}

	table[tableNum] = 0;
	if (DeleteDoubleLinkList(LQ, p))
	{
		printf("桌号%d的人已结账离开，桌号%d空闲!!\n", tableNum, tableNum);

	}
}

//查询
void check()
{
	for (int i = 0; i < 7; i++)
	{
		if (table[i])
			printf("桌号%d占用!!\n", i);
		else
			printf("桌号%d空闲!!\n", i);

	}
	printf("目前等待人数：%d!!\n", waitPerson);
}

void adjustWaitList()
{
	for (int i = 0; i < 12; i++)
		waitPersonlist[i] = waitPersonlist[i + 1];
}
