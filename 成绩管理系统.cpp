#pragma warning(disable:4996)
#include<stdio.h> 
#include<stdlib.h>
#include<string.h>
#include<conio.h>
#include<windows.h>
int sub;//添加信息时学生的课程数
int flagg;//判断是老师系统还是学生系统
char subjects[10][10] = { "语文","数学","英语","物理","生物","化学","历史","政治","地理" };
int courses[10];//储存选择课程的序号 
struct student
{
	long long id;//学号
	char name[20];//学生姓名
	char term[20];//学期
	char sex[5];//性别
	double score[10];//课程分数
	double sum;//总分
	struct student *next;
};
typedef struct student stu;
struct message
{
	long long account;//账户账号
	char password[20];//账户密码
	char name[20];//账户户名
	char identify[10];//身份信息
	struct message *next;
};
typedef struct message messages;
stu *h;
void creat_file();//创建文件 
stu *creat_list();//创建链表 
void add_student();//新建或添加学生信息 
void print_stu_all();//打印全部 
void update_stu_id_name();//更新某一个同学的成绩 
void serch_stu();//查找某一个同学的成绩 
void gotoxy(int x, int y);//光标定位函数 
void DrawList(int x, int y, int column, int line, int width, int hight);
void delete_stu();//删除某个同学的信息 
void menu_teacher();//老师菜单
int menu_student_selete();
void menu_initial();//初始菜单
int menu_initial_selete();
void creat_file_m();//创建账户信息
messages *creat_list_message();
void menu_student();//学生菜单
int menu_teacher_selete();
void sort_stu();//按课程排序
void login();
void register_m();
void sort_stu_id();
int sort_selete();
void sort_stu_id();
void sort_stu_sub();
void sort_stu_sum();
void welcome();//欢迎界面 
void end();//结束界面 
void screen();//筛选成绩
void DrawRec(int X, int Y, int w, int h);
int main()
{
	system("color b0");//颜色参数 
	welcome();
	creat_file_m();
	creat_file();
	menu_initial();
	return 0;
}
void gotoxy(int x, int y)
{
	COORD xy = { 0,0 };
	HANDLE hout = GetStdHandle(STD_OUTPUT_HANDLE);
	xy.X = x;
	xy.Y = y;
	SetConsoleCursorPosition(hout, xy);
}
void DrawRec(int X, int Y, int w, int h)
{
	int i;
	//到达x,y
	gotoxy(X, Y);
	//上边--------------------第一排
	printf("┏ ");
	for (i = 0; i < w; i++)
	{
		printf("━ ");
	}
	printf("┓ ");
	//左边

	for (i = 0; i < h; i++)
	{
		gotoxy(X, Y + 1 + i);
		printf("┃ ");
	}
	//右边

	for (i = 0; i < h; i++)
	{
		gotoxy(X + 2 + w * 2, Y + 1 + i);
		printf("┃ ");
	}
	//下边
	gotoxy(X, Y + 1 + h);
	//上边--------------------
	printf("┗ ");
	for (i = 0; i < w; i++)
	{
		printf("━ ");
	}
	printf("┛ ");

}
void DrawList(int x, int y, int column, int line, int width, int hight)
{
	/*绘制表格 参数依次为 左顶点坐标 列数 行数  行宽 行高*/
	//画横线
	//第一排
	gotoxy(x, y);
	for (int i = 0; i < (width + 1)*column + 1; i++)  //第一排 //  每小格的左上角和宽度为单位 最后一个停止
	{
		if (i == 0)
		{
			printf("┏ ");			//值得注意 这里按理说这个字符应该占两个字符位 
									//但实际上只占了一个  所以我在制表符后面加了一个空格
									//不然会产生错误 下面所有制表符同样如此
			continue;
		}
		if (i == (width + 1)*column)
		{
			printf("┓ ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("┳ ");
		else
			printf("━ ");
	}
	//中间排
	for (int j = 0; j < line; j++)
	{
		if (j == 0)
			gotoxy(x, y + 2 * hight);
		else
			gotoxy(x, y + 2 * hight*j);
		for (int i = 0; i < (width + 1)*column + 1; i++)
		{
			if (i == 0)
			{
				printf("┣ ");
				continue;
			}
			if (i == (width + 1)*column)
			{
				printf("┫ ");
				break;
			}
			if (i % (width + 1) == 0)
				printf("╋ ");
			else
				printf("━ ");
		}
	}
	//最后一排
	gotoxy(x, y + (hight + 1)*line);
	for (int i = 0; i < (width + 1)*column + 1; i++)
	{
		if (i == 0)
		{
			printf("┗ ");
			continue;
		}
		if (i == (width + 1)*column)
		{
			printf("┛ ");
			break;
		}
		if (i % (width + 1) == 0)
			printf("┻ ");
		else
			printf("━ ");
	}
	//画竖线
	for (int i = 0; i < line; i++)
		for (int j = 0; j <= column; j++)
		{
			if (i == 0)
				gotoxy(x + 2 * (width + 1)*j, y + i + 1);
			else
				gotoxy(x + 2 * (width + 1)*j, y + i * 2 + 1);
			printf("┃");
		}

}
void welcome()
{
	gotoxy(45, 11);
	printf("欢"); Sleep(400);//延时 
	printf("迎"); Sleep(400);
	printf("使"); Sleep(400);
	printf("用"); Sleep(400);
	printf("成"); Sleep(400);
	printf("绩"); Sleep(400);
	printf("管"); Sleep(400);
	printf("理"); Sleep(400);
	printf("系"); Sleep(400);
	printf("统\n"); Sleep(400);
}
void end()
{
	system("cls");
	gotoxy(52, 13);
	printf("谢谢使用\n");
	gotoxy(85, 27);
	printf("1905-陈汶君");
	Sleep(3000);
	exit(0);
}
void menu_student()
{
	int x;
	while (1)
	{
		x = menu_student_selete();
		switch (x)
		{
		case 1: print_stu_all(); break;
		case 2: serch_stu(); break;
		case 3: sort_stu(); break;
		case 4: end(); break;
		}
	}
}
int menu_student_selete()
{
	system("cls");
	DrawList(45, 4, 1, 5, 11, 1);
	gotoxy(47, 5); printf("1、打印学生信息");
	gotoxy(47, 7); printf("2、查询学生信息");
	gotoxy(47, 9); printf("3、对学生成绩进行排序");
	gotoxy(47, 11); printf("4、结束运行");
	gotoxy(47, 13); printf("输入左边数字选择功能:");
	int n;
	scanf("%d", &n);
	while (1)
	{
		if (n >= 1 && n <= 4)
		{
			return n;
		}
		else
		{
			printf("\n\n\n\n\n\t\t\t\t\t输入错误，请重新输入\n");
			system("pause");
			return 0;
		}
	}
}
void menu_teacher()
{
	int x;
	while (1)
	{
		x = menu_teacher_selete();
		switch (x)
		{
		case 1: add_student(); break;
		case 2: update_stu_id_name(); break;
		case 3: print_stu_all(); break;
		case 4: serch_stu(); break;
		case 5: delete_stu(); break;
		case 6: sort_stu(); break;
		case 7: screen(); break;
		case 8: end(); break;
		}
	}
}
int menu_teacher_selete()
{
	system("cls");
	DrawList(45, 4, 1, 9, 11, 1);
	gotoxy(47, 5); printf("1、添加学生信息");
	gotoxy(47, 7); printf("2、修改学生信息");
	gotoxy(47, 9); printf("3、打印学生信息");
	gotoxy(47, 11); printf("4、查询学生信息");
	gotoxy(47, 13); printf("5、删除学生信息");
	gotoxy(47, 15); printf("6、对学生成绩进行排序");
	gotoxy(47, 17); printf("7、筛选学生成绩");
	gotoxy(47, 19); printf("8、结束运行");
	gotoxy(47, 21); printf("输入左边数字选择功能:");
	int n;
	scanf("%d", &n);
	while (1)
	{
		if (n >= 1 && n <= 8)
		{
			return n;
		}
		else
		{
			printf("\n\n\n\n\n\t\t\t\t\t输入错误，请重新输入\n\t\t\t\t");
			system("pause");
			return 0;
		}
	}
}
void menu_initial()
{
	int x;
	while (1)
	{
		x = menu_initial_selete();
		switch (x)
		{
		case 1: login(); break;
		case 2: register_m(); break;
		case 3: end(); break;
		}
	}
}
int menu_initial_selete()
{
	system("cls");
	DrawList(45, 4, 1, 4, 11, 1);
	gotoxy(47, 5); printf("1、登录");
	gotoxy(47, 7); printf("2、注册");
	gotoxy(47, 9); printf("3、结束运行");
	gotoxy(47, 11); printf("输入左边数字选择功能:");
	int n;
	scanf("%d", &n);
	while (1)
	{
		if (n >= 1 && n <= 3)
		{
			return n;
		}
		else
		{
			printf("\n\n\n\n\n\t\t\t\t\t输入错误，请重新输入\n");
			system("pause");
			return 0;
		}
	}
}
messages *creat_list_message()
{
	messages t;
	messages *head, *p, *q;
	FILE *fp = NULL;
	p = (messages *)malloc(sizeof(messages));
	head = p;
	if ((fp = fopen("messages.txt", "r")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	//rewind(fp);
	/*while (!feof(fp))
	{
		fscanf(fp, "%lld", &t.account);
		fscanf(fp, "%s%s%s", t.password, t.name, t.identify);
		q = (messages *)malloc(sizeof(messages));
		q->account = t.account;
		strcpy(q->password, t.password);
		strcpy(q->name, t.name);
		strcpy(q->identify, t.identify);
		p->next = q;
		p = q;
	}*/
	//p->next = NULL;
	while (fread(&t, sizeof(t), 1, fp) != 0)
	{
		q = (message *)malloc(sizeof(message));
		q->account = t.account;
		strcpy(q->password, t.password);
		strcpy(q->name, t.name);
		strcpy(q->identify, t.identify);
		p->next = q;
		p = q;
	}
	p->next = NULL;
	if (fclose(fp))
	{
		printf("File close error!\n");
		exit(0);
	}
	return head;
}
void login()
{
	messages *ptr = NULL;
	messages *h;
	int flag = 0;//判断是否登陆成功
	h = creat_list_message();
	ptr = h;
	long long account;
	char a[10] = "老师";
	char b[10] = "学生";
	char c[20];//记录密码
	system("cls");
	DrawList(38, 4, 2, 2, 9, 1);
	gotoxy(47, 5); printf("账号");
	gotoxy(60, 5); scanf("%lld", &account);
	gotoxy(47, 7); printf("密码");
	gotoxy(60, 7);
	int i = 0;
	while (1)//密码星号处理
	{
		c[i] = getch();
		if (c[i] == '\r')
			break;
		if (c[i] == '\b')
		{
			i--;
			putchar('\b');//退格键
			putchar(' ');
			putchar('\b');
		}
		else
		{
			putchar('*');
			i++;
		}
		if (i == -1)
		{
			i = 0;
		}
		if (i == 0)//保证光标在最开始位置不变
			gotoxy(60, 7);

	}
	c[i] = '\0';
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->account == account)
		{
			if (strcmp(ptr->password, c) == 0)
			{
				flag = 1;
				system("cls");
				printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t登录成功\n\t\t\t\t\t\t");
				system("pause");
				if (strcmp(ptr->identify, a) == 0)
				{
					flagg = 1;
					menu_teacher();
				}
				else if (strcmp(ptr->identify, b) == 0)
				{
					flagg = 0;
					menu_student();
				}
			}
		}
	}
	if (flag == 0)
	{
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t账号或密码错误\n\t\t\t\t\t");
		system("pause");
		return;
	}
}
void register_m()
{
	FILE *fp = NULL;
	messages *ptr = NULL;
	messages t;
	messages *h;
	char a[10] = "老师";
	char b[10] = "学生";
	if ((fp = fopen("messages.txt", "a")) == NULL)
	{
		if ((fp = fopen("messages.txt", "w")) == NULL)
		{
			printf("File opens error!\n");
			exit(0);
		}
	}
	system("cls");
	DrawList(38, 4, 2, 4, 9, 1);
	gotoxy(47, 5); printf("账号");
	gotoxy(60, 5); scanf("%lld", &t.account);//写：判断文件中是否存在账号
	h = creat_list_message();
	ptr = h;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->account == t.account)
		{
			system("cls");
			printf("\n\n\n\n\n\n\t\t\t\t该账号已存在\n\t\t\t\t");
			system("pause");
			return;
		}
	}
	gotoxy(47, 7); printf("密码");
	gotoxy(60, 7); scanf("%s", t.password);
	gotoxy(47, 9); printf("姓名");
	gotoxy(60, 9); scanf("%s", t.name);
	gotoxy(42, 11); printf("身份(老师/学生)");
	gotoxy(60, 11); scanf("%s", t.identify);
	if (strcmp(t.identify, a) != 0 && strcmp(t.identify, b) != 0)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n\t\t\t\t\t\t输入错误请重新输入\n\t\t\t\t\t\t");
		system("pause");
		menu_initial();
	}
	//fprintf(fp, "%lld %s %s %s", t.account, t.password, t.name, t.identify);
	//fprintf(fp, "\n");
	fwrite(&t, sizeof(t), 1, fp);
	if (fclose(fp))
	{
		printf("file close error!\n");
		exit(0);
	}
	system("cls");
	printf("\n\n\n\n\n\n\n\n\t\t\t\t\t\t账号创建成功\n\t\t\t\t\t\t\t");
	system("pause");
}
void creat_file()//创建学生成绩信息文件 
{
	system("cls");
	FILE *fp = NULL;
	if ((fp = fopen("student.txt", "rb")) == NULL)
	{
		if ((fp = fopen("student.txt", "wb")) == NULL)
		{
			printf("File opens error!\n");
			exit(0);
		}
	}
	if (fclose(fp))
	{
		printf("file close error!\n");
		exit(0);
	}
}
void creat_file_m()//创建账户信息文件 
{
	system("cls");
	FILE *fp = NULL;
	if ((fp = fopen("messages.txt", "r")) == NULL)
	{
		if ((fp = fopen("messages.txt", "w")) == NULL)
		{
			printf("File opens error!\n");
			exit(0);
		}
	}
	if (fclose(fp))
	{
		printf("file close error!\n");
		exit(0);
	}
}
void add_student()//录入学生信息 
{
	system("cls");
	FILE *fp = NULL;
	stu t;
	int n;//学生的人数 
	int i;
	if ((fp = fopen("student.txt", "ab")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	system("cls");
	printf("\n\n\n\n\n\t\t\t\t\t请输入学生的人数:");
	scanf("%d", &n);
	system("cls");
	printf("\n\n\n\n\n\t\t\t\t\t请输入该学期的课程数:");
	scanf("%d", &sub);
	if (sub < 1 || sub>9)
	{
		system("cls");
		printf("\n\n\n\n\n\n\t\t\t\t\t输入错误请重新输入\n\t\t\t\t\t");
		system("pause");
		return;
	}
	system("cls");
	DrawList(10, 4, 9, 1, 5, 1);
	gotoxy(12, 5);
	printf("1、语文     2、数学     3、英语     4、物理     5、生物     6、化学     7、历史     8、政治     9、地理");
	printf("\n\n\n\n\n\t\t\t请输入该学期相应课程前的序号,输入一个序号回车确认:\n");
	printf("\t\t\t");
	for (i = 1; i <= sub; i++)
	{
		scanf("%d", &courses[i]);
		printf("\t\t\t");
		if (courses[i] < 1 || courses[i]>9 || courses[i] == courses[i - 1])
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t输入错误，请重新输入:");
			system("pause");
			return;
		}
	}
	for (int i = 1; i <= n; i++)
	{
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t请输入第%d位同学的学号 姓名 学期 性别:\n", i);
		DrawList(45, 6, 2, 4, 6, 1);
		gotoxy(50, 7); printf("学号");
		gotoxy(61, 7); scanf("%lld", &t.id);
		gotoxy(50, 9); printf("姓名");
		gotoxy(61, 9); scanf("%s", t.name);
		gotoxy(50, 11); printf("学期");
		gotoxy(61, 11); scanf("%s", t.term);
		gotoxy(50, 13); printf("性别");
		gotoxy(61, 13); scanf("%s", t.sex);
		int k = 1;//控制课程输出
		int r = 1;
		double sum = 0;
		system("cls");
		printf("\n\n\n\n\n");
		for (int i = 1; i <= 9; i++)
		{
			t.score[i] = -1;
		}
		gotoxy(45, 5); printf("请输入课程的分数:");
		DrawList(45, 6, 2, sub, 6, 1);
		int q = 7;
		for (int j = 1; j <= sub; j++)
		{
			gotoxy(50, q);
			printf("%s", subjects[courses[k++] - 1]);
			gotoxy(61, q);
			scanf("%lf", &t.score[courses[r]]);//1、语文，2、数学，3、英语 ,4、物理，5、生物，6、化学，7、历史，8、政治，9、地理 
			sum += t.score[courses[r]];
			t.sum = sum;
			r++;
			q += 2;//控制光标下一行
		}
		fwrite(&t, sizeof(t), 1, fp);//结构体写入文件
	}
	if (fclose(fp))
	{
		system("cls");
		printf("file close error!\n");
		exit(0);
	}
}
stu *creat_list()//创建链表 
{
	system("cls");
	stu t;
	stu *head, *p, *q;
	FILE *fp = NULL;
	int i;
	p = (stu *)malloc(sizeof(stu));
	head = p;
	if ((fp = fopen("student.txt", "rb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	rewind(fp);
	while (fread(&t, sizeof(t), 1, fp) != 0)
	{
		q = (stu *)malloc(sizeof(stu));
		q->id = t.id;
		strcpy(q->name, t.name);
		strcpy(q->term, t.term);
		strcpy(q->sex, t.sex);
		int k = 1;
		for (i = 1; i <= 9; i++)
		{
			q->score[i] = t.score[i];
		}
		q->sum = t.sum;
		p->next = q;
		p = q;
	}
	p->next = NULL;
	if (fclose(fp))
	{
		printf("File close error!\n");
		exit(0);
	}
	return head;
}
void print_stu_all()//打印所有学生成绩      
{
	system("cls");
	FILE *fp = NULL;
	int i, j;
	stu *ptr;
	h = creat_list();
	ptr = h;
	if (h == NULL)
	{
		printf("\n\n\n\n\n\n\n\t\t\t\t没有学生信息\n");
		system("pause");
		if (flagg == 1)
			return;
		else if (flagg == 0)
			return;
	}
	if (ptr->next != NULL)
	{
		system("cls");
		printf("\n\n\n\n\n\n\n学号\t\t姓名\t学期\t性别"); 
		for (j = 1; j <= 9; j++)
		{
			//		count = courses[k++] - 1;
			printf("\t%s", subjects[j - 1]);
		}
		printf("\t总分");
		printf("\n");
	}
	else if (ptr->next == NULL)
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t没有数据\n");
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->id >= 1e7)
			printf("%lld\t", ptr->id);
		else printf("%lld\t\t", ptr->id);
		printf("%s\t%s\t%s", ptr->name, ptr->term, ptr->sex);
		for (i = 1; i <= 9; i++)
		{
			if (ptr->score[i] >= 0)
			{
				printf("\t%.2lf", ptr->score[i]);
			}
			else if (ptr->score[i] < 0)
			{
				printf("\t");
			}
		}
		printf("\t%.2lf", ptr->sum);
		printf("\n");
		//	printf("\t");
	}
	system("pause");
}
void update_stu_id_name()//更新某一个同学成绩 
{
	system("cls");
	int flag2 = 0;
	stu *t;//记录找到学生的节点
	FILE *fp = NULL;
	stu *ptr = NULL;
	int sub_id;//要修改的课程序号 
	long long id;
	char name[20];
	double score;
	int flag1 = 0;//记录是否找到学生
	int flag;//判断是学号查询还是姓名查询 
	system("cls");
	h = creat_list();
	system("cls");
	DrawList(45, 4, 1, 2, 9, 1);
	gotoxy(47, 5); printf("1、按学号查找");
	gotoxy(47, 7); printf("2、按姓名查找");
	gotoxy(47, 9);
	scanf("%d", &flag);
	if (flag != 1 && flag != 2)
	{
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t\t\t输入错误请重新输入\n\t\t\t\t\t");
		system("pause");
		return;
	}
	if (flag == 1)
	{
		system("cls");
		DrawList(45, 4, 2, 1, 9, 1);
		gotoxy(50, 5); printf("请输入学号");
		gotoxy(67, 5); scanf("%lld", &id);
	}
	else if (flag == 2)
	{
		system("cls");
		DrawList(45, 4, 2, 1, 9, 1);
		gotoxy(50, 5); printf("请输入姓名");
		gotoxy(67, 5); scanf("%s", &name);
	}
	system("cls");
	double temp;
	ptr = h;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (flag == 1)
		{
			if (ptr->id == id)
			{
				flag1 = 1;
				t = ptr;
				system("cls");
				DrawList(10, 2, 9, 1, 5, 1);
				gotoxy(12, 3);
				printf("1、语文     2、数学     3、英语     4、物理     5、生物     6、化学     7、历史     8、政治     9、地理");
				DrawList(38, 5, 2, 2, 9, 1);
				gotoxy(39, 6); printf("请输入课程前的序号:");
				gotoxy(60, 6); scanf("%d", &sub_id);
				if (sub_id < 1 || sub_id>9)
				{
					system("cls");
					printf("\n\n\n\n\n\n\t\t\t\t\t输入错误请重新输入\n\t\t\t\t");
					system("pause");
					return;
				}
				gotoxy(39, 8); printf("输入修改后的分数:");
				gotoxy(60, 8); scanf("%lf", &score);
				if (ptr->score[sub_id] >= 0)
				{
					temp = score - ptr->score[sub_id];//记录修改后与修改前分数的差值 
					ptr->score[sub_id] = score;
					ptr->sum += temp;
					break;
				}
				else
				{
					ptr->score[sub_id] = score;
					ptr->sum += score;
					break;
				}
			}
		}
		else if (flag == 2)
		{
			if (strcmp(name, ptr->name) == 0)
			{
				flag1 = 1;
				t = ptr;
				system("cls");
				DrawList(10, 2, 9, 1, 5, 1);
				gotoxy(12, 3);
				printf("1、语文     2、数学     3、英语     4、物理     5、生物     6、化学     7、历史     8、政治     9、地理");
				DrawList(38, 5, 2, 2, 9, 1);
				gotoxy(39, 6); printf("请输入课程前的序号:");
				gotoxy(60, 6); scanf("%d", &sub_id);
				if (sub_id < 1 || sub_id>9)
				{
					system("cls");
					printf("\n\n\n\n\n\n\t\t\t\t\t输入错误请重新输入\n\t\t\t\t");
					system("pause");
					return;
				}
				gotoxy(39, 8); printf("输入修改后的分数:");
				gotoxy(60, 8); scanf("%lf", &score);
				if (ptr->score[sub_id] >= 0)
				{
					temp = score - ptr->score[sub_id];//记录修改后与修改前分数的差值 
					ptr->score[sub_id] = score;
					ptr->sum += temp;
					break;
				}
				else
				{
					ptr->score[sub_id] = score;
					ptr->sum += score;
					break;
				}
			}
		}
	}
	if (flag1 == 0)
	{
		printf("\n\n\n\n\n\n\t\t\t\t\t没有学生信息\n\t\t\t\t\t");
		system("pause");
		return;
	}
	if ((fp = fopen("student.txt", "wb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	ptr = h;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		fwrite(ptr, sizeof(stu), 1, fp);
	}
	if (fclose(fp))
	{
		printf("File close error!\n");
		exit(0);
	}
	system("pause");
}
void serch_stu()//查找某一个同学成绩 
{
	system("cls");
	FILE *fp = NULL;
	long long id;
	stu *t = NULL;//记录找到学生的节点
	char name[20];
	stu *ptr;
	int flag;
	h = creat_list();
	ptr = h;
	int flag1 = 0;
	system("cls");
	DrawList(45, 4, 1, 2, 11, 1);
	gotoxy(47, 5); printf("1、按学号查找");
	gotoxy(47, 7); printf("2、按姓名查找");
	gotoxy(47, 9);
	scanf("%d", &flag);
	if (flag != 1 && flag != 2)
	{
		system("cls");
		printf("\n\n\n\n\n\t\t\t\t\t\t输入错误请重新输入\n\t\t\t\t\t");
		system("pause");
		return;
	}
	else if (flag == 1 || flag == 2)
	{
		if (flag == 1)
		{
			system("cls");
			DrawList(45, 4, 2, 1, 9, 1);
			gotoxy(50, 5); printf("请输入学号");
			gotoxy(67, 5); scanf("%lld", &id);
		}
		else if (flag == 2)
		{
			system("cls");
			DrawList(45, 4, 2, 1, 9, 1);
			gotoxy(50, 5); printf("请输入姓名");
			gotoxy(67, 5); scanf("%s", name);
		}
		ptr = h;
		while (ptr->next != NULL)
		{
			ptr = ptr->next;
			if (flag == 1)
			{
				if (ptr->id == id)
				{
					flag1 = 1;
					t = ptr;
					int k = 1;
					system("cls");
					printf("\n\n\n\n\n\n\n学号\t\t姓名\t学期\t性别");
					for (int i = 1; i <= 9; i++)
					{
						if (ptr->score[i] >= 0)
						{
							printf("\t%s", subjects[i - 1]);
						}
					}
					printf("\t总分\n");
					break;
				}
			}
			else if (flag == 2)
			{
				if (strcmp(name, ptr->name) == 0)
				{
					flag1 = 1;
					t = ptr;
					int k = 1;
					system("cls");
					printf("\n\n\n\n\n\n\n学号\t\t姓名\t学期\t性别");
					for (int i = 1; i <= 9; i++)
					{
						if (ptr->score[i] > 0)
						{
							printf("\t%s", subjects[i - 1]);
						}
					}
					printf("\t总分\n");
					break;
				}
			}
		}
		if (flag1 == 0)
		{
			system("cls");
			printf("\n\n\n\n\n\n\n\t\t\t\t\t\t无该学生信息\n");
			system("pause");
			return;
		}
		else
		{
			if (ptr->id >= 1e7)
				printf("%lld\t", ptr->id);
			else printf("%lld\t\t", ptr->id);
			printf("%s\t%s\t%s", t->name, t->term, t->sex);
			for (int i = 1; i <= 9; i++)
			{
				if (t->score[i] >= 0)
				{
					printf("\t%.2lf", t->score[i]);
				}
			}
			printf("\t%.2lf\n", t->sum);
		}
	}
	system("pause");
}
void delete_stu()//删除同学信息 
{
	system("cls");
	stu *ptr, *q;
	long long id;
	char name[20];
	FILE *fp = NULL;
	h = creat_list();
	stu *run;
	int len = 0;//判断链表多长
	run = h;
	ptr = h;
	int flag;
	int flag1 = 0;
	int flag2 = 0;
	system("cls");
	DrawList(45, 4, 1, 2, 11, 1);
	gotoxy(47, 5); printf("1、删除某位同学信息");
	gotoxy(47, 7); printf("2、删除全部信息");
	gotoxy(47, 9);
	scanf("%d", &flag2);
	if (flag2 == 2)
	{
		if ((fp = fopen("student.txt", "wb")) == NULL)
		{
			printf("File opens error!\n");
			exit(0);
		}
		if (fclose(fp))
		{
			printf("File close error!\n");
			exit(0);
		}
		system("cls");
		printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t信息已全部删除\n");
		system("pause");
		return;
	}
	else if (flag2 == 1)
	{
		system("cls");
		DrawList(45, 4, 1, 2, 9, 1);
		gotoxy(47, 5); printf("1、按学号查找");
		gotoxy(47, 7); printf("2、按姓名查找");
		gotoxy(47, 9);
		scanf("%d", &flag);
		if (flag == 1)
		{
			system("cls");
			DrawList(45, 4, 2, 1, 9, 1);
			gotoxy(50, 5); printf("请输入学号");
			gotoxy(67, 5); scanf("%lld", &id);
		}
		else if (flag == 2)
		{
			system("cls");
			DrawList(45, 4, 2, 1, 9, 1);
			gotoxy(50, 5); printf("请输入姓名");
			gotoxy(67, 5); scanf("%s", name);
		}
		while (ptr->next != NULL)
		{
			q = ptr;
			ptr = ptr->next;
			if (flag == 1)
			{
				if (ptr->id == id)//找到节点 
				{
					q->next = ptr->next;
					free(ptr);//释放节点
					flag1 = 1;
					break;
				}
			}
			else if (flag == 2)
			{
				if (strcmp(ptr->name, name) == 0)
				{
					q->next = ptr->next;
					free(ptr);
					flag1 = 1;
					break;
				}
			}
		}
		if ((fp = fopen("student.txt", "wb")) == NULL)
		{
			printf("File opens error!\n");
			exit(0);
		}
		run = h;
		while (run->next != NULL)
		{
			run = run->next;
			fwrite(run, sizeof(stu), 1, fp);
		}
		if (fclose(fp))
		{
			system("cls");
			printf("file close error!\n");
			exit(0);
		}
		system("cls");
		if (flag1 == 1)
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t信息已删除\n");
		else
			printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t\t没有数据\n");
		system("pause");
	}
}
int sort_selete()
{
	int selete;
	system("cls");
	DrawList(45, 4, 1, 4, 13, 1);
	gotoxy(46, 5); printf("1、按学号从小到大排序");
	gotoxy(46, 7); printf("2、按总分从高到低排序");
	gotoxy(46, 9); printf("3、按课程成绩从高到底排序");
	gotoxy(46, 11); printf("请输入左边序号选择功能:");
	int count_id[15] = { 1,2,3,4,5,6,7,8,9,10,11,12 }; 
	int q = 0;
	int k = 1;
	scanf("%d", &selete);
	for (;;)
	{
		if (selete >= 1 && selete <= 3)
		{
			return selete;
		}
		else
		{
			printf("\n\n\n\n\n\n\n\n\t\t\t\t\t输入错误，请重新输入\n\t\t\t\t\t");
			system("pause");
			return 0;
		}
	}
	system("pause");
}
void sort_stu()
{
	system("cls");
	int x;
	while (1)
	{
		x = sort_selete();
		switch (x)
		{
		case 1:sort_stu_id(); break;
		case 2:sort_stu_sum(); break;
		case 3:sort_stu_sub(); break;
		}
		break;
	}
}
void sort_stu_id()//冒泡排序 
{
	system("cls");
	stu *q, *p, *tail;
	stu *t;
	FILE *fp = NULL;
	stu *run;
	tail = NULL;
	h = creat_list();
	while (h->next != tail)
	{
		p = h;
		q = h->next;
		while (q->next != tail)
		{
			if (q->id > q->next->id)
			{
				t = q->next;
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = t;
			}
			// 节点后移
			q = q->next;
			p = p->next;
		}
		tail = q;
	}
	if ((fp = fopen("student.txt", "wb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	run = h;
	//	rewind(fp);
	while (run->next != NULL)
	{
		run = run->next;
		fwrite(run, sizeof(stu), 1, fp);
	}
	if (fclose(fp))
	{
		system("cls");
		printf("file close error!\n");
		exit(0);
	}
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t排序已完成\n\t\t\t\t\t");
	system("pause");
	return;
}
void sort_stu_sub()
{
	system("cls");
	FILE *fp = NULL;
	stu *run;
	int count_id[15] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	int count;//储存课程的序号 
	int l = 0;//输出前的序号 
	int k = 1;
	printf("\n\n\n\n\n\t\t\t1、语文，2、数学，3、英语 ,4、物理，5、生物，6、化学，7、历史，8、政治，9、地理");
	printf("\n\t\t\t\t请输入左边数字选择排序的课程\n");
	printf("\t\t\t\t");
	while (1)
	{
		scanf("%d", &count);
		if (count < 1 || count>9)
		{
			printf("\n\n\n\n\n\n\n\t\t\t\t输入错误，请重新输入\n\t\t\t\t\t\t");
			system("pause");
			return;
		}
		else break;
	}
	stu *q, *p, *tail;
	stu *t;
	tail = NULL;
	h = creat_list();
	while (h->next != tail)
	{
		p = h;
		q = h->next;
		while (q->next != tail)
		{
			if (q->score[count] < q->next->score[count])
			{
				t = q->next;
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = t;
			}
			// 节点后移
			q = q->next;
			p = p->next;
		}
		tail = q;
	}
	if ((fp = fopen("student.txt", "wb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	run = h;
	//	rewind(fp);
	while (run->next != NULL)
	{
		run = run->next;
		fwrite(run, sizeof(stu), 1, fp);
	}
	if (fclose(fp))
	{
		system("cls");
		printf("file close error!\n");
		exit(0);
	}
	system("cls");
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t排序已完成\n\t\t\t\t\t");
	system("pause");
	return;
}
void sort_stu_sum()
{
	FILE *fp = NULL;
	stu *run;
	system("cls");
	stu *q, *p, *tail;
	stu *t;
	tail = NULL;
	h = creat_list();
	while (h->next != tail)
	{
		p = h;
		q = h->next;
		while (q->next != tail)
		{
			if (q->sum < q->next->sum)
			{
				t = q->next;
				p->next = q->next;
				q->next = q->next->next;
				p->next->next = q;
				q = t;
			}
			// 节点后移
			q = q->next;
			p = p->next;
		}
		tail = q;
	}
	if ((fp = fopen("student.txt", "wb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	run = h;
	while (run->next != NULL)
	{
		run = run->next;
		fwrite(run, sizeof(stu), 1, fp);
	}
	if (fclose(fp))
	{
		system("cls");
		printf("file close error!\n");
		exit(0);
	}
	printf("\n\n\n\n\n\n\n\n\n\t\t\t\t\t排序已完成\n\t\t\t\t\t\t");
	system("pause");
	return;
}
void screen()
{
	int nums = 0;//记录分数段中的人数
	FILE *fp = NULL;
	stu *ptr;
	if ((fp = fopen("student.txt", "rb")) == NULL)
	{
		printf("File opens error!\n");
		exit(0);
	}
	h = creat_list();
	printf("\n\n\n\n\n\t1、语文，2、数学，3、英语 ,4、物理，5、生物，6、化学，7、历史，8、政治，9、地理\n");
	printf("\t\t\t请输入筛选的课程序号:");
	int sub_id;
	scanf("%d", &sub_id);
	if (sub_id < 1 || sub_id>9)
	{
		system("cls");
		printf("\n\n\n\n\t\t\t输入错误请重新输入\n\t\t\t\t");
		system("pause");
		return;
	}
	double score_low, score_high;
	system("cls");
	DrawList(45, 4, 2, 2, 9, 1);
	gotoxy(47, 5); printf("1、请输入最低分");
	gotoxy(67, 5); scanf("%lf", &score_low);
	gotoxy(47, 7); printf("2、请输入最高分");
	gotoxy(67, 7); scanf("%lf", &score_high);
	system("cls");
	printf("\n\n\n\n\n\n\n学号\t\t姓名\t学期\t性别");
	for (int j = 1; j <= 9; j++)
		printf("\t%s", subjects[j - 1]);
	printf("\t总分\n");
	ptr = h;
	int flag = 0;
	while (ptr->next != NULL)
	{
		ptr = ptr->next;
		if (ptr->score[sub_id] >= score_low && ptr->score[sub_id] <= score_high)
		{
			nums++;
			flag = 1;
			if (ptr->id >= 1e7)
				printf("%lld\t", ptr->id);
			else
				printf("%lld\t\t", ptr->id);
			printf("%s\t%s\t%s", ptr->name, ptr->term, ptr->sex);
			for (int i = 1; i <= 9; i++)
			{
				if (ptr->score[i] >= 0)
					printf("\t%.2lf", ptr->score[i]);
				else printf("\t");
			}
			printf("\t%.2lf\n", ptr->sum);
		}
	}
	printf("\t\t\t\t%s成绩%.2lf-%.2lf分数段一共有%d人\n", subjects[sub_id - 1], score_low, score_high, nums);
	if (flag == 0)
	{
		system("cls");
		printf("\n\n\n\n\t\t\t\t没有符合条件的数据\n");
		system("pause");
		return;
	}
	system("pause");
	return;
}
