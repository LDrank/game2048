#include"stdio.h"
#include"time.h"
#include"stdlib.h"

int randnum;                      //定义随机数
int random = 101;
typedef int squar[4][4];          
void option();                 //菜单选项
void start(squar &sq);         //开始游戏进程
int  moveup(squar &sq);        
int  movedown(squar &sq);
int  moveleft(squar &sq);
int  moveright(squar &sq);        //上下左右移动操作
int  search2048(squar sq);          //判断是否存在2048
void creatnum();                   //生成一个随机数
void insertnum(squar &sq);               //随机插入一个元素2
void printsquar(squar sq);              //输出数组
int failmove(squar sq);                  //判断数组内元素是否已经不能移动（不完美的算法）需要搭配full（）来使用
int full(squar sq);                     //判断数组是否已经满
int searchnull(squar sq, int &i, int  &j);               //为了简化随机位置插入元素的函数，当只有一个空时，直接插入

int searchnull(squar sq, int &i, int  &j)
{                                              //首先在二维数组里查找为0的元素，将其坐标放入cc[4][2]中，根据原有的随机数经过一定运算对count取余数rad，然后从cc中取第rad个元素作为下一个随机元素的坐标
	int a,b,,rad,count=0,k=0;
	int cc[4][2];
	for(a=0;a<4;a++)
		for (b = 0; b < 4; b++)
		{
			if (sq[a][b] == 0)
			{
				cc[k++][0] = a;
				cc[k++][1] = b;
				count++;
			}
		}
	if (count <5 )
	{
		rad = ((randnum++ / count) + (randnum++ / (count + 1)) % count;
		i = cc[rad][0];
		j = cc[rad][1];
		return 1;
	}
	else
		return 0;
}

int failmove(squar sq)
{                                             //判断数组中元素是否已经楼上能根据游戏规则移动，这个算法不成熟，需要判断是否全满是才能准确返回值，即判断当前元素是否与其右面和下面的元素相同，从二维数组坐标为00处开始判断
	int i, j, k ,flag=1;
	for(i=0;i<3;i++)
		for (j = 0; j < 3; j++)
		{
			k = 1;
			while (k--)
			{
				if (sq[j][i] == sq[j + 1][i])
					return 0;
			    if (sq[j][i] == sq[j][i + 1])
					return 0;
			}
		}
	return 1;
}

int full(squar sq)                          //就是简单的在数组中查找是否全部都有元素
{
	int i, j;
	for (i = 0; i<4; i++)
		for (j = 0; j < 4; j++)
			if (sq[i][j] == 0)
				return 0;
	return 1;
}
 

//整个程序的重点部分，对游戏进行上下左右操作时的算法
//将每个移动分为两个部分，一是查找相同的元素将其合并，二是将所有不为0的元素移动到数组的一侧
//四个移动其实都是一个算法，只是对二维数组的操作方法不同，其核心算法是一样的
int moveup(squar &sq)                                              
{
	int i, j, k, flag, count = 0, count1 = 0,count2 = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (sq[j][i] == sq[j + 1][i])
				count1 ++;
			if (sq[i][j] == 0)
				count2 ++;
		}
	}
	if (count1 || count2)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (sq[j][i] == 0)
					continue;
				else
				{
					for (k = j + 1; k < 4; k++)
					{
						if ((sq[k][i] != sq[j][i]) && (sq[k][i] != 0))
							break;
						else if (sq[k][i] == sq[j][i])
						{
							sq[j][i] += sq[k][i];
							sq[k][i] = 0;
							count++;
						}
					}
				}
			}
		}
	}
	else
	{
		puts("\n对不起~~~操作失败~~~~~~\n");
		return 0;
	}
	for (i = 0; i < 4; i++)
	{
		flag = 0;
		for (j = 0; j < 4; j++)
		{
			if (sq[j][i] == 0)
                continue;
			else
		    {
				sq[flag][i] = sq[j][i];
				if (j != flag)
					sq[j][i] = 0;
				flag++;
			}	
		}
	}
	if (search2048(sq))
	{
		printsquar(sq);
		puts("游戏结束，恭喜您闯关成功！！！");
		return (13);
	}
	else
	{
		insertnum(sq);
		return count;
	}
}

int movedown(squar &sq)
{
	int i, j, k,flag, count = 0, count1 = 0, count2 = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 3; j >=0; j--)
		{
			if (sq[j][i] == sq[j - 1][i])
				count1++;
			if (sq[i][j] == 0)
				count2++;
		}
	}
	if (count1 || count2)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (sq[j][i] == 0)
					continue;
				else
				{
					for (k = j - 1; k >= 0; k--)
					{
						if ((sq[k][i] != sq[j][i]) && (sq[k][i] != 0))
							break;
						else if (sq[k][i] == sq[j][i])
						{
							sq[j][i] += sq[k][i];
							sq[k][i] = 0;
							count++;
						}
					}
				}
			}
		}
	}
	else
	{
		puts("\n对不起~~~操作失败~~~~~~\n");
		return 0;
	}
	for (i = 0; i < 4; i++)
	{
		flag = 3;
		for (j = 3; j >=0; j--)
		{
			if (sq[j][i] == 0)
				continue;
			else
			{
				sq[flag][i] = sq[j][i];
				if (j != flag)
					sq[j][i] = 0;
				flag--;
			}
		}
	}
	if (search2048(sq))
	{
		printsquar(sq);
		puts("游戏结束，恭喜您闯关成功！！！");
		return (13);
	}
	else
	{
		insertnum(sq);
		return count;
	}
}

int moveleft(squar &sq)
{
	int i, j,k, flag, count=0, count1 = 0, count2 = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			if (sq[i][j] == sq[i][j + 1])
				count1++;
			if (sq[i][j] == 0)
				count2++;
		}
	}
	if (count1 || count2)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 0; j < 4; j++)
			{
				if (sq[i][j] == 0)
					continue;
				else
				{
					for (k = j + 1; k < 4; k++)
					{
						if ((sq[i][k] != sq[i][j]) && (sq[i][k] != 0))
							break;
						else if (sq[i][k] == 0)
							continue;
						else if (sq[i][k] == sq[i][j])
						{
							sq[i][j] += sq[i][k];
							sq[i][k] = 0;
							count++;
						}
					}
				}
			}
		}
	}
	else
	{
		puts("\n对不起~~~操作失败~~~~~~\n");
		return 0;
	}
	for (i = 0; i < 4; i++)
	{
		flag = 0;
		for (j = 0; j < 4; j++)
		{
			if (sq[i][j] == 0)
				continue;
			else
			{
				sq[i][flag] = sq[i][j];
				if (j != flag)
					sq[i][j] = 0;
				flag++;
			}
		}
	}
	if (search2048(sq))
	{
		printsquar(sq);
		puts("游戏结束，恭喜您闯关成功！！！");
		return (13);
	}
	else
	{
		insertnum(sq);
		return count;
	}
}

int moveright(squar &sq)
{
	int i, j,k, flag, count = 0, count1 = 0, count2 = 0;
	for (i = 0; i < 4; i++)
	{
		for (j = 3; j >= 0; j--)
		{
			if (sq[i][j] == sq[i][j - 1])
				count1++;
			if (sq[i][j] == 0)
				count2++;
		}
	}
	if (count1||count2)
	{
		for (i = 0; i < 4; i++)
		{
			for (j = 3; j > 0; j--)
			{
				if (sq[i][j] == 0)
					continue;
				else
				{
					for (k = j - 1; k >= 0; k--)
					{
						if ((sq[i][k] != sq[i][j]) && (sq[i][k] != 0))
							break;
						else if (sq[i][k] == 0)
							continue;
						else if (sq[i][k] == sq[i][j])
						{
							sq[i][j] += sq[i][k];
							sq[i][k] = 0;
							count++;
						}
					}
				}
			}
		}
	}
	else
	{
		puts("\n对不起~~~操作失败~~~~~~\n");
		return 0;
	}
	for (i = 0; i < 4; i++)
	{
		flag = 3;
		for (j = 3; j >=0; j--)
		{
			if (sq[i][j] == 0)
				continue;
			else
			{
				sq[i][flag] = sq[i][j];
				if (j != flag)
					sq[i][j] = 0;
				flag--;
			}
		}
	}
	if (search2048(sq))
	{
		printsquar(sq);
		puts("游戏结束，恭喜您闯关成功！！！");
		return (13);
	}
	else
	{
		insertnum(sq);
		return count;
	}
}

int search2048(squar sq)                     //在数组中查找2048
{
	int i, j;
	for (i = 0; i < 4; i++)
		for (j = 0; j < 4; j++)
		{
			if (sq[i][j] == 2048)
				return (1);
		}
	return 0;
}

void creatnum()                          //根据时间函数生成一个伪随机数
{
	srand((unsigned int)time(0));
	randnum = rand();
}

void insertnum(squar &sq)                //在随机为0的位置插入一个元素2 
{                                        //对randnum伪随机数进行随机数处理生成另一个伪随机数num，对num惊醒随机处理生成两个小于4的伪随机数这两个数就是随机元素的坐标，如果为0则直接插入，如果都为零，则进行searchnull（）操作，返回值为真则直接插入，否则递归insertnum（）
	int i, j,num,a,b;
	num=randnum++%random;
	i = num % 4;
	j = (num / 3) % 4;
	random += (num % (random%(num%3));
	if (sq[i][j] == 0)
		sq[i][j] = 2;
	else if (sq[j][i] == 0)
		sq[j][i] = 2;
	else if (searchnull(sq, a, b))
	{
		sq[a][b] = 2;
	}
	else
		insertnum(sq);
}

void option()                 //输出菜单
{
	puts("1:开始游戏");
	puts("2:退出游戏\n");
	puts("请输入对应序号：");
}

void printsquar(squar sq)                     //输出游戏界面
{
	int i, j;
	printf("\n---------------------\n");
	for (i = 0; i < 4; i++)
	{
		printf("|");
		for (j = 0; j < 4; j++)
		{
			if (sq[i][j] == 0)
				printf("    |");
			else
				printf("%4d|", sq[i][j]);
		}
		printf("\n---------------------\n");
	}
	puts("\n");
}

void start( squar &sq)             //对游戏控制的函数
{
	char cho,q;
	int i, j, k,w,s,a,d;
	creatnum();
	i = randnum % 2;
	j = randnum % 3;
	k = randnum % 4;
	if (i == j)
	{
		i=i/2;
		sq[i][j] = 2;
		sq[j][k] = 2;
	}
	else if (j == k)
	{
		j = j / 2;
		sq[i][j] = 2;
		sq[j][k] = 2;
	}
	else if (i == k)
	{
		k += i;
		sq[i][j] = 2;
		sq[j][k] = 2;
	}
	else
	{
		sq[i][j] = 2;
		sq[j][k] = 2;                  
	}                                //首先随机位置插入两个元素2
	while (1)                                   //游戏运行
	{                  
		if (failmove(sq)&&full(sq))                //判断是否全满且不能移动
		{
			puts("对不起游戏失败，请不要气馁，再接再厉！");
			break;
		}
		printsquar(sq);
		puts("请输入W（上）S（下）A（左）D（右）进行游戏（大写）：");
		scanf("%c", &cho);
		q = getchar();
		if (cho == 'W')                  //也可以用case语句
		{
  			w=moveup(sq);
			if (w == 13)
				break;
			else
			    continue;
		}
		else if (cho == 'S')
		{
			s=movedown(sq);
			if (s == 13)
				break;
			continue;
		}
		else if (cho == 'A')
		{
			a=moveleft(sq);
			if (a == 13)
				break;
			else 
			    continue;
		}
		else if (cho == 'D')
		{
			d=moveright(sq);
			if (d == 13)
				break;
			else 
			    continue;
		}
		else
		{
			puts("输入错误，请重新输入：");
			continue;
		}
	}
}

int main()
{
	char q;
	squar sq;
	int opt=0,i,j;
	for (i = 0; i < 4; i++)                //数组所有元素置为0
		for (j = 0; j < 4; j++)
			sq[i][j] = 0;
	puts("欢迎来到Drank为您定制的2048!\n");
	while (1)                                //对游戏菜单的控制
	{
		option();
		scanf("%d", &opt);
		q = getchar();
		switch (opt)
		{
		case 1:start(sq); break;
		case 2: {system("pause"); return 0; } break;
		default : puts("Error!");
		}
	}
	system("pause");
	return 0;
}