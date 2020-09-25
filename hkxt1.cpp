#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "lianbiao.h"
#pragma warning(disable:4996)  //���Ծ���

void meau1(void);//���˵�
void printOneofAirMsg(int i);//��ʾ��Ӧ�ĺ�����Ϣ
void searchbyAirno();//�ɺ���Ų��Һ�����Ϣ
void meau2(void);//�Ӳ˵�
void searchbystartPlace();//����ɵ���Һ�����Ϣ
void searchbyEndPlace();//�ɵ������Һ�����Ϣ



#define MAXSIZE 10/*���庽���������ֵ*/
#define MAX  20
#define BOOKMAX  100


//����Ʊ�ͻ��б���ṹ�嶨��
typedef struct Book
{
	char Airnum[8];//�����
	char name[20];//�ͻ����� 
	char didentify[6];//���֤�� 
	int  order_amount;//��Ʊ����
	int grade;
	struct Book *Pnext;//ָ����һ���û����׵�ַ
}*PBookList, BookList;

//������Ϣ�ṹ�嶨��,ÿ������Ŷ����в�ͬ�ĳ˿�����������ÿ�����඼Ӧ����һ������
typedef struct airinfo
{
	char Airno[8];//�����
	char start[6];//������
	char end[6];//Ŀ�ĵ�
	char sche[6];//������
	char time1[8];//����ʱ��
	char time2[8];//����ʱ��
	char mode[5];//����
	int  price;//Ʊ��
	int  fixed;//  �˿Ͷ���
	int  remained;//��Ʊ
	PBookList order;/*ָ���Ա���������ͷָ�룬ͨ�����ָ��Ϳ����ҵ����г˿͵�������*/
}AirInfo,*PAirInfo;

//������Ϣ����ṹ�嶨��
typedef struct
{
	AirInfo s[MAX]; //������Ϣ����
	int acount;  //��¼��ǰ������Ϣ��
}List;
//�����ͻ�������Ϣ
typedef struct
{
	BookList book[BOOKMAX];
	int book_acount;
}SbookList;



//�½��ṹ�����L,����������Ϣ������Ϣ�ͺ���ĸ�����������s[MAX]��AirInfo�ṹ���С������
List L;
//�½��ṹ�����飬ÿ��
SbookList B;


//��ȡ�����ͻ����ļ�������Ĳ�����BookList�ṹ�������ָ�롣
//��ȡ�������ͻ�����ϢӦ���Ǵ洢��һ���������档���磺book[BOOKMAX];
void readinfo_book(SbookList * book)
{
	FILE *fp;//�����ļ�ָ��
	if ((fp = fopen("��Ʊ��Ϣ.txt", "r")) == NULL)  //��ֻ���ķ�ʽ��
	{
		printf("��Ʊ��Ϣ.txt�ļ������� \n");
		exit(1);
	}
	else
	{
		int i = 0; char title[500];  //��
		B.book_acount = 0;
		while (!feof(fp))  //C�ṩ��һ�������ļ�״̬�ĺ���feof(pf)�����ļ�δ����ʱfeof������ֵΪ0��
			               //����Ϊ��0ֵ��ʹ�ú���feof���ж��ļ��Ƿ�����ȿ������ı��ļ����������ڶ������ļ�
		{
			fgets(title, 500, fp);//��ȡ��һ��˵��:�����  ���    �յ� ��ȥ;
			//��ȡ��ȷ����Ϣ,��ʽ����ȡ��Ϣ����fp��ָ����ļ���ȡ���ṹ������ȥ
			if (4 != fscanf(fp, "%s %s %s %d", B.book[i].Airnum, B.book[i].name, B.book[i].didentify, &B.book[i].order_amount))
			{
				printf("��ȡ�ļ�����\n");
				//�ر��ļ���ָ��,�˳�;
				fclose(fp);
				exit(1);
			}
			i++;
			B.book_acount++;
		}
	}
	fclose(fp);
}

//��ȡ�ı���Ϣ,����ֵ���ṹ�����,����Ĳ�����SSList�ṹ�������ָ��
void readinfo(List *L)
{
	FILE *fp;//�����ļ�ָ��
	if ((fp = fopen("������Ϣ.txt", "r")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		int i = 0; char tep[500];
		L->acount = 0;     //���������ʼ��
		while (!feof(fp))
		{
			fgets(tep, 500, fp);//��ȡ��һ��˵��:�����  ���  �յ� ��..;
			//��ȡ��ȷ����Ϣ;
			if (10 !=
				fscanf(fp, "%s %s %s %s %s %s %s %d %d %d",
				L->s[i].Airno, L->s[i].start, L->s[i].end, L->s[i].sche,
				L->s[i].time1,L->s[i].time2,L->s[i].mode, &L->s[i].price, 
				&L->s[i].fixed, &L->s[i].remained))
			{
				printf("��ȡ�ļ�����\n");
				//�ر��ļ���ָ��,�˳�;
				fclose(fp);
				exit(1);
			}
			i++;
			L->acount++;
		}
	}
	fclose(fp);
}

//д��
void rewrite(List L)
{
	FILE *fp; int i;//�����ļ�ָ��
	if ((fp = fopen("������Ϣp.txt", "w+")) == NULL)
	{
		printf("�����ļ������� \n");
		exit(1);
	}
	else
	{
		//д��һЩ˵����Ϣ;
		fprintf(fp, "�����\t���\t�յ�\t������\t���ʱ��\t����ʱ��\t����\t�۸�\t��Ա����\t��Ʊ��\n");
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
	
		printf("����� ��� �յ� ������ ���ʱ�� ����ʱ�� ���� �۸� ��Ա���� ��Ʊ��\n");
		printf("%s %s %s %s %s %s %s %d %d %d\r\n", L.s[i].Airno, L.s[i].start, L.s[i].end, L.s[i].sche, L.s[i].time1, L.s[i].time2, L.s[i].mode, L.s[i].price, L.s[i].fixed, L.s[i].remained);

}
void printAllofAirMsg(void)
{
	int i = 0;
	for (i = 0; i < L.acount; i++)
	{
		printf("����� ��� �յ� ������ ���ʱ�� ����ʱ�� ���� �۸� ��Ա���� ��Ʊ��\n");
		printf("%s %s %s %s %s %s %s %d %d %d\r\n", L.s[i].Airno, L.s[i].start, L.s[i].end, L.s[i].sche, L.s[i].time1, L.s[i].time2, L.s[i].mode, L.s[i].price, L.s[i].fixed, L.s[i].remained);


	}
}

/*���ݿͻ�����ĺ�������������Ϣ*/
void searchbyAirno()
{
	PAirInfo info, a;
	char Airnum01[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== Ϊ���г�����Ź���ѡ��   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].Airno);

	}
	printf("===============================\n");
	printf("������Ҫѡ�񺽰�����:");
	scanf("%d", &sel);
	//�����û���ѡ�񣬸�Airnumber������ֵ��ͬ�ĺ����
	if (sel >= L.acount) {
		printf("�������\n");
		return;
	}
	else  //��������к���Ч
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
		printf("�Բ��𣬸ú���δ�ҵ�!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("����� ��� �յ� ������ ���ʱ�� ����ʱ�� ���� �۸� ��Ա���� ��Ʊ��\n");
		printOneofAirMsg(i);
	}
}
/*���ݿͻ���������վ�����������Ϣ*/
void searchbystartPlace()
{
	PAirInfo info, a;
	char StartPlace[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== Ϊ���г����к�������վ����ѡ��   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].start);

	}
	printf("===============================\n");
	printf("������Ҫѡ�񺽰�����:");
	scanf("%d", &sel);
	//�����û���ѡ�񣬸�Airnumber������ֵ��ͬ�ĺ����
	if (sel >= L.acount) {
		printf("�������\n");
		return;
	}
	else  //��������к���Ч
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
		printf("�Բ��𣬸ú���δ�ҵ�!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("����� ��� �յ� ������ ���ʱ�� ����ʱ�� ���� �۸� ��Ա���� ��Ʊ��\n");
		printOneofAirMsg(i);
	}
}
/*���ݿͻ�������յ�վ�����������Ϣ*/
void searchbyEndPlace()
{
	PAirInfo info, a;
	char EndPlace[10];
	int i = 0, sel;
	info = L.s;
	a = L.s;
	printf("===============================\n");
	printf("== Ϊ���г������յ�վ����ѡ��   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].end);

	}
	printf("===============================\n");
	printf("������Ҫѡ�񺽰�����:");
	scanf("%d", &sel);
	//�����û���ѡ�񣬸�Airnumber������ֵ��ͬ�ĺ����
	if (sel >= L.acount) {
		printf("�������\n");
		return;
	}
	else  //��������к���Ч
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
		printf("�Բ��𣬸ú���δ�ҵ�!\n");
		printf("\n\n");
	}

	else
	{
		printf("================================================================================\n");
		//printf("����� ��� �յ� ������ ���ʱ�� ����ʱ�� ���� �۸� ��Ա���� ��Ʊ��\n");
		printOneofAirMsg(i);
	}
}

/*����ϵͳ����ĺ���Ų�ѯ����ָ����ʽ����*/

PAirInfo findByAirno()
{
	PAirInfo info, a;
	char Airnumber[10];
	int sel = 0;
	int i = 0;
	//L��SSList���͵ģ���L.s��PairInfo���͵ģ�����ΪL.s�������һ����ַ��
	info = L.s;  //��ȡ��������ĸ���������Ϣ,s�Ǻ���������Ϣ������L.s[0]�����һ�麽��������Ϣ����������ţ�������....��
	a = L.s;      
	printf("===============================\n");
	printf("== Ϊ���г�����Ź���ѡ��   =\n");
	for (int j = 0; j < L.acount; j++)
	{
		printf("%d           %s\n", j, a[j].Airno); //��ӡ�����к���ĺ����
	}
	printf("===============================\n");
	//���û�ѡ��һ�����кţ��������кŽ���ѡ��
	printf("������Ҫѡ�񺽰�����:");
	scanf("%d", &sel);
	//�����û���ѡ�񣬸�Airnumber������ֵ��ͬ�ĺ����
	if (sel >= L.acount) {
		printf("�������\n"); 
		return 0;
	}
	else  //��������к���Ч
	{
		strcpy(Airnumber, info[sel].Airno);
	}
	while (i < L.acount)
	{
		//��������ַ���һ��strcmp���ص���ֵ��0
		//ȡ������˼���Ǿ���Ϊ1��������ͬʱ�򷵻�info�ĺ�����Ϣ
		if (!strcmp(Airnumber, info[i].Airno))
		{
			printf("==================================================================\n");
			printf("��ѡ��ĺ��������Ϣ���£�\n\n");
			printOneofAirMsg(i);
			//���ص��Ǵ������ߵĵ�ַ,��ô�͵õ�����������Ϣ��
			return &info[i];
		}
		i++;   //�����еĺ���
	}
	if (i >= L.acount)
	{
		printf("\n\n");
		printf("�Բ��𣬸ú���δ�ҵ�!\n");
		printf("\n\n");
	}
	return NULL;
}


//����ֵ��BookList���ͱ����ĵ�ַ���������Ҳ��BookList���ͱ����ĵ�ַ��
//����������һ����������������ͷָ�룬ÿһ�������ͷָ�붼�ǲ�һ���ģ����ݺ����������
//�ڶ��������Ǵ��뺽��ţ�������char����
PBookList insertlink(PBookList head, char Airnum[], int amount, char name[], int grade, char ID[])
{
	//����������Ŷ����ͻ�����ṹ������ĵ�ַ,ע������������ֻ�ܴ�ŵ���BookInfoList�����ĵ�ַ
	PBookList p1, new1;
	//ʹ��p1�����������ŵ�ͷָ��
	p1 = head;
	//����һ���µĿ飬������鶯̬����һ��BookInfoList�ṹ���С�Ŀؼ�
	new1 = (PBookList)malloc(sizeof(BookList));  //��̬����һ���µĿ�
	//�ڴ����ʧ��
	if (new1 == NULL)
	{
		printf("\n��̬�ڴ����ʧ�ܣ�����ϵ����Ա!\n");
		return NULL;
	}
	//�������ӵ�����ڵ㸳ֵ
	//��Ӻ����
	strcpy(new1->Airnum, Airnum);
	//�ͻ�����
	strcpy(new1->name, name);
	//��Ʊ��
	new1->order_amount = amount;
	//��λ�ȼ�
	new1-> grade = grade;
	//���֤����
	strcpy(new1->didentify, ID);
	//��һ��ָ���
	new1->Pnext = NULL;
	if (head == NULL)/*��ԭ�޶�Ʊ�ͻ���Ϣ����ô��Ӧ�ð�ͷ���ָ����������ɵĿ飬Ȼ���µĿ�ָ���*/
	{
		head = new1; new1->Pnext = NULL;
	}
	/*���ͷָ�벻ָ��յĻ���˵���Ѿ��пͻ�������
	  ����ǰ��p1=head����ôp1��ͷָ��head����ͬһ����ַ��ȷ�е�˵����ָ��ͬһ���ַ��
	  ����������һ���µĿ飬new1ָ��������µĿ飬��ô��ʱ�׽ڵ㱣��������һ����Ʊ�û�����Ϣ
	  ���Ű� p1 ��ֵ��ֵ��new1->next����ʱ������������������ˡ�*/
	else {
		head = new1;
		new1->Pnext = p1;
	}
	return head;   //����ͷָ��
}


//�Ѷ����ļ����û����ݺ����д�뵽��ͬ����������ȥ
void InitOrder()
{
	PAirInfo info;
	//L��SSList���͵ģ���L.s��PairInfo���͵ģ�����ΪL.s�������һ����ַ��
	info = L.s;  //��ȡ��������ĸ���������Ϣ,s�Ǻ���������Ϣ������L.s[0]�����һ�麽��������Ϣ����������ţ�������....��
	for (int i = 0; i < B.book_acount; i++)
	{//�Ƚ�ÿ�������ͻ�����ţ�������ԭ�еĺ���ţ������Ӧ�Ļ����뵽��Ӧ����ŵ��б�����ȥ
		for (int j = 0; j < L.acount; j++)
		{
			if (!strcmp(B.book[i].Airnum, info[j].Airno))  //���õ�һ�������ͻ��ĺ���ź��������еĺ���Ž��бȽ�
			{
				printf("��%d�������ͻ�ƥ����Ϣ�������Ϊ%s.", i, info[j].Airno);
				//������Ӧ����ŵ�������,Ȼ�󷵻���Ӧ�����ͷָ��
				info[j].order = insertlink(info[j].order, B.book[i].Airnum, B.book[i].order_amount, B.book[i].name, B.book[i].grade, B.book[i].didentify);

				//��ӡ�ɹ�����ĺ���
				printOneofAirMsg(j);
				//���ص��Ǵ������ߵĵ�ַ,��ô�͵õ�����������Ϣ��
				//return &info[i];
			}
		}
	}

}
void printOrderCustomByAirNum1()
{
	PBookList p;
	PAirInfo info;
	info = findByAirno();  //info�Ƿ���ĳ�����庽����׵�ַ
	//���ͷָ�룬�����������
	p = info->order; //��þ��庽��ŵĶ����û�ͷָ��
	                 //�����û���ʱ����������
	if (p != NULL) {
		printf("===============================\n");
		printf("===============================\n\n\n");
		printf("�����    ����    ���֤   ��Ʊ����   ��λ�ȼ�\n");
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
		printf("!!!!!�ú���û�пͻ���Ϣ!!!!!\n");
		printf("\n\n");
	}
	
}



/*����Ʊҵ��*/
void orderTicket()
{
	PAirInfo info;

	//���嶩Ʊ�û���Ϣ����
	int amount, grade;
	char name[10];
	char ID[21];

	//L��SSList���͵ģ���L.s��PairInfo���͵ģ�����ΪL.s�������һ����ַ��
	info = L.s;   
	//findByAirno�������ص��ǣ������ĸ�����ĵ�ַ������  PairInfo ���͵ļ�Ϊ��AirInfo *��
	//��� (*info).Airnum��ô���Ǿ�����ĸ�������� ,Ҳ������info->Airnum��ʾ
	//��Ʊ֮ǰ��Ҫ������ĺ���ţ���Ϊ����ÿһ�����඼��һ���˿͵��������ݺ���Ĳ�ͬ��������ͬ������
	//����������˵���м����û�������Ҫ���������Ǿ�����Ҫ����Ӧ�����ı�ͷ������Airinfo�Ľṹ���Ѿ��ж���
	
	
	if (!(info = findByAirno())) return;/*���ݿͻ��ṩ�ĺ���Ž��в�ѯ����Ϊ�գ��˳���ģ��,�Ҳ����ú����*/
	printf("�������㶩Ʊ����Ҫ������:");
	scanf("%d", &amount);
	if (amount > info->fixed)/*���ͻ���Ʊ�����Ա��Ʊ�ܶ�˳�*/
	{
		printf("\n�Բ����������Ʊ�������Ѿ�������Ա����!");
		return;
	}
	if (amount <= info->remained)/*���ͻ���Ʊ��ĩ������Ʊ������Ʊ�ɹ����ȼ��ͻ���Ϣ*/
	{
		
		printf("��������������: ");
		scanf("%s", name);
		printf("������ͻ������֤����: ");
		scanf("%s", ID);
		printf("������%s�ͻ��Ĳ�λ�ȼ�: ", name);
		scanf("%d", &grade);
		//info->order ��Ϊinfo�Ѿ���ĳһ�����庽��ĵ�ַ�ˣ�����info->order����������������
		//info->Airno���������κ���ţ���ô��������Ӧ�ÿ�����һ��char���͵�
		info->order = insertlink(info->order,info->Airno, amount, name, grade, ID);/*�ڶ�Ʊ��Ա����������ӿͻ���Ϣ*/
		for (int i = 0; i < amount; i++)/*��������ö�Ʊ�ͻ�����λ��*/
			printf("%s����λ����:%d\n", name, (info->fixed) - (info->remained) + i + 1);
		info->remained -= amount;/*�ú��ߵ���Ʊ��Ӧ�����ÿͻ��Ķ�Ʊ��*/
		rewrite(L);
		printf("\n=========��Ʊ�ɹ�========\n");
		printf("========ף����;��죡======\n");
		
	}

}
/*������Ʊҵ��*/
void refund_ticket()
{
	PAirInfo info;   //�ṹ��ָ�������������Ϣ
	//qnode *t, *back, *f, *r;
	int grade;
	PBookList p1, p2 = NULL, head;  //�ṹ��ָ������������ͻ�
	char cusname[10];
	if (!(info = findByAirno())) return;/*���ݺ���Ż�ȡ�ú������Ϣ*/
	head = info->order;  //����info�Ľṹ���������ȡָ������εĳ˳�������ͷָ�룬��Ϊ�����������ͻ�������
	p1 = head;  //p1Ҳָ�����ͷָ��
	printf("��������������:");
	scanf("%s", cusname); //�õ��ͻ�������
	while (p1 != NULL) {/*���p1��ָ���ǿյĻ���֤��û�пͻ�����Ʊ����Ϊ�գ��ǾͿ�һ�������ܲ���ƥ�俩*/
		//����ƥ��Ļ�strcmp��������0����0����1��������Ҳ����˵����ƥ��Ļ�ֱ���˳����whileѭ����
		if (!strcmp(cusname, p1->name)) break;
		//���������ƥ��Ļ����Ǿͣ�����������һֱ��ѯ����
		//������������˳����whileѭ����1.�ҵ�ƥ�����֣�2.�������
		p2 = p1;
		p1 = p1->Pnext;
	}
	if (p1 == NULL) { printf("�Բ�����û�ж���Ʊ!\n"); return; }/*����������������Ȼû���ҵ�ƥ�������*/
	else
	{/*���������������������ǿ϶������ҵ�ƥ���������,��������ɾ������˵���Ϣ*/
		//p1��ָ��Ľڵ����Ҫɾ���Ľڵ�
		if (p1 == head)
		{
			head = p1->Pnext;  //���p1����head˵��������û����׽ڵ㣬��ֱ�Ӱ�ͷָ��ָ����һ����ɾ���������Ϣ��
			printf("hello\n");
		}
		else
		{
			p2->Pnext = p1->Pnext;
		}      //���򣬾Ͱ��ҵ����ĸ��ڵ����һ���ĺ�ǰһ������������������ɾ�����ҵ�����һ��
		info->remained += p1->order_amount;  //��ôʣ��Ʊ��Ӧ������
		grade = p1->grade;  //��סɾ���Ĳ�λ�ȼ�
		printf("%s�ɹ���Ʊ��\n", p1->name);
		free(p1); //�ͷű�ɾ���ͻ��Ŀռ�
	}

	info->order = head;
}


void meau1(void)
{
	int subsel;
	while (1)
	{
		printf("****************03171305��ӱ��****************\n");
		printf("**********    ��������Ϣ���Ӳ˵�    **********\n");
		printf("**********************************************\n");
		printf("*              1.��ʾ���к���                *\n");
		printf("*              2.��ʾ�����ͻ�                *\n");
		printf("*              3.�������˵�                  *\n");
		printf("**********************************************\n");
		printf("�� ѡ ��(1-3):\n");
		scanf("%d", &subsel);
		switch (subsel)
		{
		case 1:printAllofAirMsg(); break;
		case 2:printOrderCustomByAirNum1(); break;
		case 3:return;
		default:printf("�������\n"); break;
		}
	}
}
void meau2(void)
{
	int subsel;
	while (1)
	{
		printf("*****************03171305��ӱ��****************\n");
		printf("**********     ������Ϣ��ѯ�Ӳ˵�    **********\n");
		printf("***********************************************\n");
		printf("*               1.������Ų�ѯ                *\n");
		printf("*               2.�����վ��ѯ                *\n");
		printf("*               3.���յ�վ��ѯ                *\n");
		printf("*               4.�������˵�                  *\n");
		printf("***********************************************\n");
		printf("�� ѡ ��(1-4):\n");
		scanf("%d", &subsel);
		switch (subsel)
		{
		case 1:searchbyAirno(); break;
		case 2:searchbystartPlace(); break;
		case 3:searchbyEndPlace(); break;
		case 4: return;
		default:printf("�������\n"); break;
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
		printf("\t��ӭ���뺽�๺Ʊϵͳ\n");
		printf("--------------------------03171305��ӱ��---------------------------\n");
		printf("                         ���ն�Ʊ����ϵͳ                          \n");
		printf("   --------------------- 1.��ʾ��������Ϣ ----------------------   \n");
		printf("   --------------------- 2.��ѯ��������Ϣ ----------------------   \n");
		printf("   --------------------- 3.��          Ʊ ----------------------   \n");
		printf("   --------------------- 4.��          Ʊ ----------------------   \n");
		printf("   --------------------- 0.��  ��  ϵ  ͳ ----------------------   \n");
		printf("-------------------------------------------------------------------\n");
		printf("�� ѡ ��(0-4):\n");
		scanf("%d", &sel);
		switch (sel)
		{
		case 1:meau1(); break;//ѡ��˵�1
		case 2:meau2(); break;//ѡ��˵�2
		case 3:orderTicket(); break;//��Ʊ
		case 4:refund_ticket(); break;//��Ʊ
		case 0:return 0;//�˳�����
		default:printf("�������\n"); break;
		}
	}
	return 0;
}
