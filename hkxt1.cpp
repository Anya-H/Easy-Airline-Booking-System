#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lianbiao.h"
#pragma warning(disable:4996)  //忽略警告

void meau1(void);//主菜单
void printOneofAirMsg(int i);//显示对应的航班信息
void searchbyAirno();//由航班号查找航班信息
void meau2(void);//子菜单
void searchbystartPlace();//由起飞点查找航班信息
void searchbyEndPlace();//由到达点查找航班信息



#define MAXSIZE 10/*定义航线量的最大值*/
#define MAX  20
#define BOOKMAX  100


//航订票客户列表体结构体定义
typedef struct Book
{
	char Airnum[8];//航班号
	char name[20];//客户姓名 
	char didentify[6];//身份证号 
	int  order_amount;//订票数量
	int grade;
	struct Book *Pnext;//指向下一个用户的首地址
}*PBookList, BookList;

//航班信息结构体定义,每个航班号都会有不同的乘客名单，所以每个航班都应该有一个链表
typedef struct airinfo
{
	char Airno[8];//航班号
	char start[6];//出发地
	char end[6];//目的地
	char sche[6];//飞行日
	char time1[8];//出发时间
	char time2[8];//到达时间
	char mode[5];//机型
	int  price;//票价
	int  fixed;//  乘客定额
	int  remained;//余票
	PBookList order;/*指向乘员名单链表的头指针，通过这个指针就可以找到所有乘客的名单了*/
}AirInfo,*PAirInfo;

//航班信息总体结构体定义
typedef struct
{
	AirInfo s[MAX]; //航班信息数组
	int acount;  //记录当前航班信息数
}List;
//订单客户总体信息
typedef struct
{
	BookList book[BOOKMAX];
	int book_acount;
}SbookList;



//新建结构体变量L,包括航班信息整体信息和航班的个数，生成了s[MAX]个AirInfo结构体大小的数组
List L;
//新建结构体数组，每个
SbookList B;


//读取订单客户的文件，传入的参数是BookList结构体变量的指针。
//读取到订单客户的信息应给是存储在一个数组里面。例如：book[BOOKMAX];
void readinfo_book(SbookList * book)
{
	FILE *fp;//定义文件指针
	if ((fp = fopen("订票信息.txt", "r")) == NULL)  //以只读的方式打开
	{
		printf("订票信息.txt文件不存在 \n");
		exit(1);
	}
	else
	{
		int i = 0; char title[500];  //读
		B.book_acount = 0;
		while (!feof(fp))  //C提供了一个测试文件状态的函数feof(pf)，当文件未结束时feof函数的值为0，
			               //否则为非0值。使用函数feof来判断文件是否结束既可用于文本文件，还可用于二进制文件
		{
			fgets(title, 500, fp);//读取第一行说明:航班号  起点    终点 略去;
			//读取正确的信息,格式化读取信息，把fp所指向的文件读取到结构体里面去
			if (4 != fscanf(fp, "%s %s %s %d", B.book[i].Airnum, B.book[i].name, B.book[i].didentify, &B.book[i].order_amount))
			{
				printf("读取文件出错\n");
				//关闭文件流指针,退出;
				fclose(fp);
				exit(1);
			}
			i++;
			B.book_acount++;
		}
	}
	fclose(fp);
}

//读取文本信息,并赋值给结构体变量,传入的参数是SSList结构体变量的指针
void readinfo(List *L)
{
	FILE *fp;//定义文件指针
	if ((fp = fopen("航班信息.txt", "r")) == NULL)
	{
		printf("航班文件不存在 \n");
		exit(1);
	}
	else
	{
		int i = 0; char tep[500];
		L->acount = 0;     //航班次数初始化
		while (!feof(fp))
		{
			fgets(tep, 500, fp);//读取第一行说明:航班号  起点  终点 略..;
			//读取正确的信息;
			if (10 !=
				fscanf(fp, "%s %s %s %s %s %s %s %d %d %d",
				L->s[i].Airno, L->s[i].start, L->s[i].end, L->s[i].sche,
				L->s[i].time1,L->s[i].time2,L->s[i].mode, &L->s[i].price, 
				&L->s[i].fixed, &L->s[i].remained))
			{
				printf("读取文件出错\n");
				//关闭文件流指针,退出;
				fclose(fp);
				exit(1);
			}
			i++;
			L->acount++;
		}
	}
	fclose(fp);
}

//写入
void rewrite(List L)
{
	FILE *fp; int i;//定义文件指针
	if ((fp = fopen("航班信息p.txt", "w+")) == NULL)
	{
		printf("航班文件不存在 \n");
		exit(1);
	}
	else
	{
		//写入一些说明信息;
		fprintf(fp, "航班号\t起点\t终点\t飞行日\t起飞时间\t到达时间\t机型\t价格\t乘员定额\t余票量\n");
		for (i = 0; i < L.acount; i++)
		{
			fprintf(fp, "%s\t%s\t%s\t%s\t%s\t%s\t%s\t%d\t%d\t%d \n", L.s[i].Airno, L.s[i].start, L.s[i].end, L.s[i].sche, L.s[i].time1, L.s[i].time2, L.s[i].mode,
				L.s[i].price, L.s[i].fixed, L.s[i].remained);
		}
		fclose(fp);
	}
}
void printOneofAirMsg(int i)
{
	
		printf("航班号 起点 终点 飞行日 起飞时间 到达时间 机型 价格 乘员定额 余票量\n");
		printf("%s %s %s %s %s %s %s %d %d %d\r\n", L.s[i].Airno, L.s[i].start, L.s[i].end, L.s[i].sche, L.s[i].time1, L.s[i].time2, L.s[i].mode, L.s[i].price, L.s[i].fixed, L.s[i].remained);

}
void printAllofAirMsg(void)
{
	int i = 0;
	for (i = 0; i < L.acount; i++)
	{
		printf("航班号 起点 终点 飞行日 起飞时间 到达时间 机型 价格 乘员定额 余票量\n");
		printf("%s %s %s %s %s %s %s %d %d %d\r\n", L.s[i].Airno, L.s[i].start, L.s[i].end, L.s[i].sche, L.s[i].time1, L.s[i].time2, L.s[i].mode, L.s[i].price, L.s[i].fixed, L.s[i].remained);


	}
}

/*根据客户提出的航班号输出航线信息*/
void searchbyAirno()
{
	PAirInfo info, a;
	char Airnum01[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== 为您列出航班号供您选择：   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].Airno);

	}
	printf("===============================\n");
	printf("请输入要选择航班的序号:");
	scanf("%d", &sel);
	//根据用户的选择，给Airnumber变量赋值不同的航班号
	if (sel >= L.acount) {
		printf("输入错误\n");
		return;
	}
	else  //输入的序列号有效
	{
		strcpy(Airnum01, info[sel].Airno);
	}

	while (i < L.acount)
	{
		if (!strcmp(Airnum01, a[i].Airno)) break;
		i++;
	}
	if (i >= L.acount)
	{
		printf("\n\n");
		printf("对不起，该航线未找到!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("航班号 起点 终点 飞行日 起飞时间 到达时间 机型 价格 乘员定额 余票量\n");
		printOneofAirMsg(i);
	}
}
/*根据客户提出的起点站名输出航线信息*/
void searchbystartPlace()
{
	PAirInfo info, a;
	char StartPlace[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== 为您列出所有航班的起点站供您选择：   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].start);

	}
	printf("===============================\n");
	printf("请输入要选择航班的序号:");
	scanf("%d", &sel);
	//根据用户的选择，给Airnumber变量赋值不同的航班号
	if (sel >= L.acount) {
		printf("输入错误\n");
		return;
	}
	else  //输入的序列号有效
	{
		strcpy(StartPlace, info[sel].start);
	}

	while (i < MAXSIZE)
	{
		if (!strcmp(StartPlace, a[i].start)) break;
		i++;
	}
	if (i >= MAXSIZE)
	{
		printf("\n\n");
		printf("对不起，该航线未找到!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("航班号 起点 终点 飞行日 起飞时间 到达时间 机型 价格 乘员定额 余票量\n");
		printOneofAirMsg(i);
	}
}
/*根据客户提出的终点站名输出航线信息*/
void searchbyEndPlace()
{
	PAirInfo info, a;
	char EndPlace[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== 为您列出所有终点站供您选择：   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].end);

	}
	printf("===============================\n");
	printf("请输入要选择航班的序号:");
	scanf("%d", &sel);
	//根据用户的选择，给Airnumber变量赋值不同的航班号
	if (sel >= L.acount) {
		printf("输入错误\n");
		return;
	}
	else  //输入的序列号有效
	{
		strcpy(EndPlace, info[sel].end);
	}

	while (i < MAXSIZE)
	{
		if (!strcmp(EndPlace, a[i].end)) break;
		i++;
	}
	if (i >= MAXSIZE)
	{
		printf("\n\n");
		printf("对不起，该航线未找到!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("航班号 起点 终点 飞行日 起飞时间 到达时间 机型 价格 乘员定额 余票量\n");
		printOneofAirMsg(i);
	}
}

/*根据系统提出的航班号查询并以指针形式返回*/

PAirInfo findByAirno()
{
	PAirInfo info, a;
	char Airnumber[10];
	int sel = 0;
	int i = 0;
	//L是SSList类型的，而L.s是PairInfo类型的，（因为L.s本身就是一个地址）
	info = L.s;  //读取我们输入的各个航班信息,s是航班数组信息，比如L.s[0]代表第一组航班所有信息（包括航班号，出发点....）
	a = L.s;      
	printf("===============================\n");
	printf("== 为您列出航班号供您选择：   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].Airno); //打印出所有航班的航班号
	}
	printf("===============================\n");
	//让用户选择一个序列号，根据序列号进行选择
	printf("请输入要选择航班的序号:");
	scanf("%d", &sel);
	//根据用户的选择，给Airnumber变量赋值不同的航班号
	if (sel >= L.acount) {
		printf("输入错误\n"); 
		return 0;
	}
	else  //输入的序列号有效
	{
		strcpy(Airnumber, info[sel].Airno);
	}
	while (i < L.acount)
	{
		//如果两个字符串一样strcmp返回的数值是0
		//取反的意思就是就是为1，所以相同时候返回info的航线信息
		if (!strcmp(Airnumber, info[i].Airno))
		{
			printf("==================================================================\n");
			printf("您选择的航班具体信息如下：\n\n");
			printOneofAirMsg(i);
			//返回的是此条航线的地址,那么就得到这个航班的信息了
			return &info[i];
		}
		i++;   //找所有的航线
	}
	if (i >= L.acount)
	{
		printf("\n\n");
		printf("对不起，该航线未找到!\n");
		printf("\n\n");
	}
	return NULL;
}


//返回值是BookList类型变量的地址，而传入的也是BookList类型变量的地址，
//插入链表，第一个参数是这个链表的头指针，每一个链表的头指针都是不一样的，根据航班号来区分
//第二个参数是传入航班号，类型是char类型
PBookList insertlink(PBookList head, char Airnum[], int amount, char name[], int grade, char ID[])
{
	//生成两个存放订单客户链表结构体变量的地址,注意这两个变量只能存放的是BookInfoList变量的地址
	PBookList p1, new1;
	//使用p1接受这个航班号的头指针
	p1 = head;
	//生成一个新的块，给这个块动态分配一个BookInfoList结构体大小的控件
	new1 = (PBookList)malloc(sizeof(BookList));  //动态分配一个新的块
	//内存分配失败
	if (new1 == NULL)
	{
		printf("\n动态内存分配失败，请联系管理员!\n");
		return NULL;
	}
	//给新增加的链表节点赋值
	//添加航班号
	strcpy(new1->Airnum, Airnum);
	//客户姓名
	strcpy(new1->name, name);
	//订票量
	new1->order_amount = amount;
	//仓位等级
	new1-> grade = grade;
	//身份证号码
	strcpy(new1->didentify, ID);
	//下一个指向空
	new1->Pnext = NULL;
	if (head == NULL)/*若原无订票客户信息，那么就应该把头结点指向这个新生成的块，然后新的块指向空*/
	{
		head = new1; new1->Pnext = NULL;
	}
	/*如果头指针不指向空的话，说明已经有客户订单了
	  刚在前面p1=head，那么p1和头指针head保存同一个地址，确切的说他们指向同一块地址，
	  接着新生成一个新的块，new1指向了这个新的块，那么此时首节点保存的是最近一个订票用户的信息
	  接着把 p1 的值赋值给new1->next，此时整个链表就连接起来了。*/
	else {
		head = new1;
		new1->Pnext = p1;
	}
	return head;   //返回头指针
}


//把订单文件的用户根据航班号写入到不同的链表里面去
void InitOrder()
{
	PAirInfo info;
	//L是SSList类型的，而L.s是PairInfo类型的，（因为L.s本身就是一个地址）
	info = L.s;  //读取我们输入的各个航班信息,s是航班数组信息，比如L.s[0]代表第一组航班所有信息（包括航班号，出发点....）
	for (int i = 0; i < B.book_acount; i++)
	{//比较每个订单客户航班号，和我们原有的航班号，如果对应的话加入到相应航班号的列表里面去
		for (int j = 0; j < L.acount; j++)
		{
			if (!strcmp(B.book[i].Airnum, info[j].Airno))  //先拿第一个订单客户的航班号和所有现有的航班号进行比较
			{
				printf("第%d个订单客户匹配信息，航班号为%s.", i, info[j].Airno);
				//插入相应航班号的链表中,然后返回相应航班的头指针
				info[j].order = insertlink(info[j].order, B.book[i].Airnum, B.book[i].order_amount, B.book[i].name, B.book[i].grade, B.book[i].didentify);

				//打印成功加入的航班
				printOneofAirMsg(j);
				//返回的是此条航线的地址,那么就得到这个航班的信息了
				//return &info[i];
			}
		}
	}

}
void printOrderCustomByAirNum1()
{
	PBookList p;
	PAirInfo info;
	info = findByAirno();  //info是返回某个具体航班的首地址
	//获得头指针，获得整个链表
	p = info->order; //获得具体航班号的订单用户头指针
	                 //新增用户的时候是增加在
	if (p != NULL) {
		printf("===============================\n");
		printf("===============================\n\n\n");
		printf("航班号    姓名    身份证   订票数量   座位等级\n");
		while (p) {
			printf("%s\t%s\t %s \t%d  %d\n", p->Airnum, p->name, p->didentify,p->order_amount,p->grade);
			p = p->Pnext;
		}
		printf("===============================\n\n\n");
		printf("===============================\n");
	}
	else
	{
		printf("\n\n");
		printf("!!!!!该航线没有客户信息!!!!!\n");
		printf("\n\n");
	}
	
}



/*办理订票业务*/
void orderTicket()
{
	PAirInfo info;

	//定义订票用户信息变量
	int amount, grade;
	char name[10];
	char ID[21];

	//L是SSList类型的，而L.s是PairInfo类型的，（因为L.s本身就是一个地址）
	info = L.s;   
	//findByAirno函数返回的是，具体哪个航班的地址类型是  PairInfo 类型的即为（AirInfo *）
	//如果 (*info).Airnum那么就是具体的哪个航班此了 ,也可以用info->Airnum表示
	//订票之前需要输入你的航班号，因为我们每一个航班都有一个乘客的链表，根据航班的不同，创建不同的链表
	//所有理论来说，有几个用户，就需要几个链表，那就是需要有相应个数的表头，其在Airinfo的结构体已经有定义
	
	
	if (!(info = findByAirno())) return;/*根据客户提供的航班号进行查询，如为空，退出该模块,找不到该航班号*/
	printf("请输入你订票所需要的数量:");
	scanf("%d", &amount);
	if (amount > info->fixed)/*若客户订票额超过乘员定票总额，退出*/
	{
		printf("\n对不起，您输入的票的数量已经超过乘员定额!");
		return;
	}
	if (amount <= info->remained)/*若客户订票额末超过余票量，订票成功并等级客户信息*/
	{
		
		printf("请输入您的姓名: ");
		scanf("%s", name);
		printf("请输入客户的身份证号码: ");
		scanf("%s", ID);
		printf("请输入%s客户的舱位等级: ", name);
		scanf("%d", &grade);
		//info->order 因为info已经是某一个具体航班的地址了，所以info->order就是这个航班的链表
		//info->Airno就是这个班次航班号，那么他的类型应该可以是一个char类型的
		info->order = insertlink(info->order,info->Airno, amount, name, grade, ID);/*在订票乘员名单域中添加客户信息*/
		for (int i = 0; i < amount; i++)/*依次输出该订票客户的座位号*/
			printf("%s的座位号是:%d\n", name, (info->fixed) - (info->remained) + i + 1);
		info->remained -= amount;/*该航线的余票量应减掉该客户的订票量*/
		rewrite(L);
		printf("\n=========订票成功========\n");
		printf("========祝您旅途愉快！======\n");
		
	}

}
/*办理退票业务*/
void refund_ticket()
{
	PAirInfo info;   //结构体指针变量，航班信息
	//qnode *t, *back, *f, *r;
	int grade;
	PBookList p1, p2 = NULL, head;  //结构体指针变量，订单客户
	char cusname[10];
	if (!(info = findByAirno())) return;/*根据航班号获取该航班的信息*/
	head = info->order;  //根据info的结构体变量，获取指定航班次的乘车的链表头指针，即为订制这个航班客户的名单
	p1 = head;  //p1也指向这个头指针
	printf("请输入您的姓名:");
	scanf("%s", cusname); //得到客户的姓名
	while (p1 != NULL) {/*如果p1的指向是空的话，证明没有客户定过票，不为空，那就看一下姓名能不能匹配咯*/
		//姓名匹配的话strcmp函数返回0，！0就是1，成立，也就是说姓名匹配的话直接退出这个while循环了
		if (!strcmp(cusname, p1->name)) break;
		//如果姓名不匹配的话，那就，就在链表中一直轮询查找
		//有两种情况会退出这个while循环，1.找到匹配名字，2.链表结束
		p2 = p1;
		p1 = p1->Pnext;
	}
	if (p1 == NULL) { printf("对不起，你没有订过票!\n"); return; }/*遍历了整个链表，仍然没有找到匹配的姓名*/
	else
	{/*如果不是上面那种情况，那肯定就是找到匹配的名字了,在链表中删除这个人的信息*/
		//p1所指向的节点就是要删除的节点
		if (p1 == head)
		{
			head = p1->Pnext;  //如果p1等于head说明了这个用户在首节点，那直接把头指针指向下一个就删除了这个信息了
			printf("hello\n");
		}
		else
		{
			p2->Pnext = p1->Pnext;
		}      //否则，就把找到的哪个节点的下一个的和前一个连接起来，这样就删除了找到的那一个
		info->remained += p1->order_amount;  //那么剩余票数应该增加
		grade = p1->grade;  //记住删除的仓位等级
		printf("%s成功退票！\n", p1->name);
		free(p1); //释放被删除客户的空间
	}

	info->order = head;
}


void meau1(void)
{
	int subsel;
	while (1)
	{
		printf("****************03171305李颖雯****************\n");
		printf("**********    各航线信息的子菜单    **********\n");
		printf("**********************************************\n");
		printf("*              1.显示所有航线                *\n");
		printf("*              2.显示订单客户                *\n");
		printf("*              3.返回主菜单                  *\n");
		printf("**********************************************\n");
		printf("请 选 择(1-3):\n");
		scanf("%d", &subsel);
		switch (subsel)
		{
		case 1:printAllofAirMsg(); break;
		case 2:printOrderCustomByAirNum1(); break;
		case 3:return;
		default:printf("输入错误\n"); break;
		}
	}
}
void meau2(void)
{
	int subsel;
	while (1)
	{
		printf("*****************03171305李颖雯****************\n");
		printf("**********     航线信息查询子菜单    **********\n");
		printf("***********************************************\n");
		printf("*               1.按航班号查询                *\n");
		printf("*               2.按起点站查询                *\n");
		printf("*               3.按终点站查询                *\n");
		printf("*               4.返回主菜单                  *\n");
		printf("***********************************************\n");
		printf("请 选 择(1-4):\n");
		scanf("%d", &subsel);
		switch (subsel)
		{
		case 1:searchbyAirno(); break;
		case 2:searchbystartPlace(); break;
		case 3:searchbyEndPlace(); break;
		case 4: return;
		default:printf("输入错误\n"); break;
		}
	}
}
int main()
{
	int sel;
	readinfo(&L);
	readinfo_book(&B);
	InitOrder();
	while (1)
	{
		printf("\n\n\n\n");
		printf("\t欢迎进入航班购票系统\n");
		printf("--------------------------03171305李颖雯---------------------------\n");
		printf("                         航空订票客运系统                          \n");
		printf("   --------------------- 1.显示各航线信息 ----------------------   \n");
		printf("   --------------------- 2.查询各航线信息 ----------------------   \n");
		printf("   --------------------- 3.订          票 ----------------------   \n");
		printf("   --------------------- 4.退          票 ----------------------   \n");
		printf("   --------------------- 0.退  出  系  统 ----------------------   \n");
		printf("-------------------------------------------------------------------\n");
		printf("请 选 择(0-4):\n");
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:meau1(); break;//选择菜单1
		case 2:meau2(); break;//选择菜单2
		case 3:orderTicket(); break;//订票
		case 4:refund_ticket(); break;//退票
		case 0:return 0;//退出程序
		default:printf("输入错误\n"); break;
		}
	}
	return 0;
}
