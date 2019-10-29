#include<iostream>
#include <stdlib.h>
#include<windows.h>
using namespace std;

int list[8][8] = { 0 };   //����״̬,1�Ǻ��ӣ�2�ǰ��ӣ�0�ǿյ�
int p = 1, aip = 0, air, aic, lastr = 0, lastc = 0;	//p�����ڸ�˭�£�1�Ǻڷ���2�ǰ׷�
int p1, p2, p3, p4, temp1[8][8], temp2[8][8], temp3[8][8], temp4[8][8];//4�㲩�Ķ�Ӧ��AI���������
const int dr[8] = { 0, 0, 1, 1, 1, -1, -1, -1 }, dc[8] = { 1, -1, 0, 1, -1, 0, 1, -1 };//8����������
int book[65]; //����
const int no = 1000;//AI�ķ��������ܴﵽ���Ͻ�ֵ
const int prio[8][8] =
{                       //prio��ÿ��λ�õ����ȼ�����ֵԽ��Խ��
	{ 80, -20, 8, 6, 6, 8, -20, 80 },
	{ -20, -20, 0, -1, -1, 0, -20, -20 },
	{ 8, 0, 3, 5, 5, 3, 0, 8 },
	{ 6, -1, 5, 1, 1, 5, -1, 6 },
	{ 6, -1, 5, 1, 1, 5, -1, 6 },
	{ 8, 0, 3, 5, 5, 3, 0, 8 },
	{ -20, -20, 0, -1, -1, 0, -20, -20 },
	{ 80, -20, 8, 6, 6, 8, -20, 80 }
};

bool playOK(int r, int c, int dr, int dc)					//�ж�ĳ�����ӵ�ĳ�������ܷ�����
{
	if (list[r][c] != 0)return false;
	int tr = r, tc = c;                  //tr��tc�ֱ��ʾ�õ�ͨ���к������ض������ƶ��������
	while (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && list[tr + dr][tc + dc] == 3 - p)
	{		//ѭ��������δ����߽�����ұߵ������ǶԷ�����ѭ������������ѭ���˳�
		tr += dr, tc += dc;    //�ƶ�����
	}
	//��ʹѭ���˳�����һ����ǶԷ������ӣ���(r,c)�����ӣ����򲻿�����
	if (tr == r && tc == c)return false;		//�ѵ㣬��һ�䲻����
	if (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && list[tr + dr][tc + dc] == p)return true;
	return false;
}

bool OK(int r, int c)					//�ж�ĳ�������ܷ�����
{
	if (list[r][c])return false;
	for (int i = 0; i < 8; i++)  //ֻҪһ��������������µ��������Ϳ�����
	if (playOK(r, c, dr[i], dc[i]))return true;   //����
	return false;
}

int num(int k)  //ͳ��������Ŀ��1�Ǻ��ӣ�2�ǰ���
{
	int s = 0;
	for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)if (list[i][j] == k)s++;
	return s;
}

void display()  //��ʾ���̺�����
{
	system("cls");
	for (int i = 0; i < 8; i++)
	{
		if (!i)
		{
			cout << "    ";
			for (int j = 0; j < 8; j++)cout << char('A' + j) << "    ";
			cout << endl;
		}
		cout << i + 1 << "  ";
		for (int j = 0; j < 8; j++)
		{
			if (list[i][j] == 2)cout << "��"; else if (list[i][j] == 1)cout << "��";
			else if (OK(i, j))cout << "��"; else	cout << " .";    //����
			cout << "   ";
		}
		cout << endl << endl;
	}
	cout << "�ڷ���" << num(1) << "      �׷���" << num(2) << "       �ֵ�";  //����
	if (p == 1)cout << "�ڷ���\n"; else cout << "�׷���\n";
	cout << "��ѡ��:";
	for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)if (OK(i, j))    //����
		cout << "  " << char('1' + i) << char('A' + j);
	cout << "\n���һ������λ����" << lastr + 1 << char(lastc + 'A');
}

void init()  //��ʼ��
{
	list[3][3] = list[4][4] = 2;
	list[3][4] = list[4][3] = 1;
	while (aip != 1 && aip != 2 && aip != 3)
	{
		cout << "ѡ��\n1���˻���ս��AI��\n2���˻���ս�������\n3��˫�˶�ս\n";
		cin >> aip;
	}
	display();  //����
}

bool end_()  //�ж���Ϸ�Ƿ����
{
	for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)if (OK(i, j))return false;   //����
	p = 3 - p;			//�ı�p��2���ط�֮һ
	for (int i = 0; i < 8; i++)for (int j = 0; j < 8; j++)if (OK(i, j))return false;  //����
	display();
	cout << "\n��Ϸ����\n";
	if (num(1) < num(2))cout << "�׷�ʤ��";    //����
	else if (num(1)>num(2))cout << "�ڷ�ʤ��";    //����
	else cout << "ƽ��";
	return true;
}


void turn(int tr, int tc, int dr, int dc)  //���Ӻ���play()��һ������
{
	if (!playOK(tr, tc, dr, dc))return;  //�ѵ㣬��һ�䲻����     //����
	while (tr + dr >= 0 && tr + dr < 8 && tc + dc >= 0 && tc + dc < 8 && list[tr + dr][tc + dc] == 3 - p)
	{
		list[tr + dr][tc + dc] = p; //�ڸô��������ӵ���ɫ
		tr += dr, tc += dc;
	}
}

void play(int r, int c)
{
	lastr = r, lastc = c;
	for (int i = 0; i < 8; i++)turn(r, c, dr[i], dc[i]);     //����
	list[r][c] = p;
	book[num(1) + num(2)] = r * 8 + c;     //����
	p = 3 - p;		//�ı�p��2���ط�֮һ
}

int getPoint()
{
	int point = 0;
	for (int i1 = 0; i1<8; i1++)for (int j1 = 0; j1<8; j1++)
	{
		if (list[i1][j1] == aip)point += prio[i1][j1];   //����ai���ӣ�����ϸ�λ�õĻ���
		if (list[i1][j1] == 3 - aip) point -= prio[i1][j1];   //������ҵ��ӣ����ȥ��λ�õĻ���
	}
	return point;
}

void AI3()//���������ı�p�����ǵ��ú�������ı�p
{
	p4 = no;
	for (int iiii = 0; iiii < 8; iiii++)for (int jjjj = 0; jjjj < 8; jjjj++)  //���Ĳ�
	{
		if (!OK(iiii, jjjj))continue;  //����
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)temp4[i][j] = list[i][j];
		play(iiii, jjjj);//����
		p = 3 - p;
		if (p4 > getPoint())p4 = getPoint();//����
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)list[i][j] = temp4[i][j];
	}
	if (p4 == no)p4 = getPoint();  //����
	if (p3 < p4)p3 = p4;
}
void AI2()//���������ı�p�����ǵ��ú�������ı�p
{
	p3 = -no;
	for (int iii = 0; iii < 8; iii++)for (int jjj = 0; jjj < 8; jjj++)  //������
	{
		if (!OK(iii, jjj))continue; //����
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)temp3[i][j] = list[i][j];
		play(iii, jjj);//����
		AI3();
		p = 3 - p;
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)list[i][j] = temp3[i][j];
	}
	if (p3 == -no)
	{
		p = 3 - p;
		AI3();
		p = 3 - p;
	}
	if (p2 > p3)p2 = p3;
}
void AI()  //���������ı�p�����ǵ��ú�������ı�p
{
	p1 = -no;
	for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)  //��һ��
	{
		if (!OK(i, j))continue;   //����
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)temp1[i][j] = list[i][j];
		play(i, j);//����
		p2 = no;
		for (int ii = 0; ii < 8; ii++)for (int jj = 0; jj < 8; jj++)  //�ڶ���
		{
			if (!OK(ii, jj))continue;   //����
			for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)temp2[i][j] = list[i][j];
			play(ii, jj);//����
			AI3();  //����
			p = 3 - p;
			for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)list[i][j] = temp2[i][j];
		}
		if (p2 == no)
		{
			p = 3 - p;
			AI2();  //����
			p = 3 - p;
		}
		if (p1 < p2)p1 = p2, air = i, aic = j;   //�ѵ㣬�������AI����ȴ1�ζ�û��ִ��������䣬��ôAI�ͻ��´�λ��
		p = 3 - p;
		for (int i = 0; i<8; i++)for (int j = 0; j<8; j++)list[i][j] = temp1[i][j];
	}
}

void go()		//����һ����
{
	display();			//����
	if (p == aip)
	{
		AI();//����
		play(air, aic);//����
		Sleep(1000);
		return;
	}
	cout << "\n��������λ�ã��У�1-8�����У�A-H��    ����00�鿴����" << endl;
	char x, y;
	cin >> x >> y;
	if (x == '0')
	{
		for (int i = 5; i <= num(1) + num(2); i++)cout << "  " << book[i] / 8 + 1 << char(book[i] % 8 + 'A');
		cout << "\n��������˳�";
		system("pause>nul");
		return;
	}
	int r = x - '1', c = y - 'a';
	if (y >= 'A' && y < 'Z')c = y - 'A';
	if (!OK(r, c))  //����
	{
		cout << "ERROR!";
		return;
	}
	play(r, c);		//����
}

int main()
{
	system("color f0");//�׵׺���
	init();
	while (!end_())go();
	system("pause>nul");
	return 0;
}
