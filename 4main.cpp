//����˼����֮ǰ�����ƣ����ۺ���������Ʒ�ļ�ֵ֮�ͣ���Ҫע��һ����Ʒ���������ڱ�������������ô����Ⱦɫ����Ҵ����Ϊ0
//�������ÿһ����Ʒ�Ƿ�ѡ������Ĭ����10��Ⱦɫ���ڱȽϣ�����ÿһ��Ⱦɫ���ϵĵ�i��������Ǵ����i����Ʒ�Ƿ�ѡ��
//ͻ��������ѡ���Ⱦɫ������λ����0��1,��1��0
//���⽨��ѱ���ĸ��ʵ��ߵ㣬�����п��ܻ�����ֲ�����
#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#define num 10//��Ⱥ�Ĵ�С
#define pm 0.1//����ĸ���
#define pc  0.8//����ĸ���
#define MAX 100//����������
int n,m;//nΪ��Ʒ���࣬mΪ�����ݻ���С
int v[10];//ÿһ����Ʒ�ļ�ֵ
int w[10];//ÿһ����Ʒ������
typedef struct node
{
    int beibao[10];//����ÿһ����Ʒ��״̬
    int adapt;//��ʾ����װ�뷽������Ӧֵ
    double p;//�Ҵ�ĸ���
}node;
node group[num],grouptemp[num];
void groupproduce()
{
    int i,j,t,wsum;
    srand(time(NULL));
    for (i=0;i<num;i++)
    {
        wsum=0;
     for (j=0;j<n;j++)
     {
         t=rand()%100;
         if (t<=49)
           group[i].beibao[j]=0;
         else
           group[i].beibao[j]=1;
        wsum=wsum+group[i].beibao[j]*w[j];
      }
      if (wsum>m)
      i--;
     }
    printf("��ʼ״̬Ϊ:\n");
    for (i=0;i<num;i++)
    {
      for (j=0;j<n;j++)
        printf("%d",group[i].beibao[j]);
        printf("\n");
    }
}
void pingjia()
{
    int i,j,vsum,wsum,sum;
    sum=0;
    for (i=0;i<num;i++)
    {
        vsum=0;//��Ʒ���ܼ�ֵ
        wsum=0;//��Ʒ�����ݻ���ֻҪ����mһ����Ϊ��Ӧ��Ϊ0)
        for (j=0;j<n;j++)
         {
             vsum=vsum+group[i].beibao[j]*v[j];
             wsum=wsum+group[i].beibao[j]*w[j];
         }
         if (wsum>m)
            group[i].adapt=0;
         else
            group[i].adapt=vsum;
            sum=sum+group[i].adapt;
     }
     for (i=0;i<num;i++)
     group[i].p=group[i].adapt*1.0/sum;//�����Ҵ����
     for (i=0;i<num;i++)
        printf("��%d��Ⱦɫ���ֵΪ%d,�Ҵ����Ϊ%.4f\n",i,group[i].adapt,group[i].p);
}
void xuanze()
{
   int i,j,temp;
   double gradient[num];
   double t;
   int xuan[num];
   for (i=0;i<num;i++)
    gradient[i]=0.0;
    gradient[0]=group[0].p;
    for (i=1;i<num;i++)
    gradient[i]=gradient[i-1]+group[i].p;
    srand(time(NULL));
    for (i=0;i<num;i++)
    {
        t=rand()%100;
        t=t/100;
        for (j=0;j<num;j++)
            if (gradient[j]>t)
            {
                xuan[i]=j;
                break;
            }
    }
   for (i=0;i<num;i++)
        {
        for (j=0;j<n;j++)
        grouptemp[i].beibao[j]=group[i].beibao[j];
        grouptemp[i].adapt=group[i].adapt;
        grouptemp[i].p=group[i].p;
        }
        for (i=0;i<num;i++)
        {
            temp=xuan[i];
            group[i].adapt=grouptemp[temp].adapt;
            group[i].p=grouptemp[temp].p;
            for (j=0;j<n;j++)
            group[i].beibao[j]=grouptemp[temp].beibao[j];
        }
}
void jiaopei()
{
  int i,j,t,c,d;
  double jiaopeip[num];
  int jiaopeiflag[num],temp,temp1,temp2,duan;
  srand(time(NULL));
  t=0;
  for (i=0;i<num;i++)
  {
      jiaopeip[i]=rand()%100;
      jiaopeip[i]=jiaopeip[i]/100;
      if (jiaopeip[i]<pc)
       jiaopeiflag[t]=i;
       t++;
  }
  t=t/2*2;
  srand(time(NULL));
  c=0;
  d=1;
  printf("%d\n",t);
  for (i=0;i<t/2;i++)
  {
     temp1=jiaopeiflag[c];
     temp2=jiaopeiflag[d];
     c=c+2;
     d=d+2;
     duan=rand()%num;//����ϵ�
     for (i=0;i<duan;i++)//�ϵ�֮ǰ�Ĳ��ֽ�������
     {
         temp=group[temp1].beibao[i];
         group[temp1].beibao[i]=group[temp2].beibao[i];
         group[temp2].beibao[i]=temp;
     }
    }

}
void bianyi()
{
    int i,j,t;
    double bianyip[num];
    int bianyiflag[num];
    srand(time(NULL));
    memset(bianyiflag,0,sizeof(bianyiflag));
    for (i=0;i<num;i++)
    {
        bianyip[i]=rand()%100;
        bianyip[i]=bianyip[i]/100;
        if (bianyip[i]<pm)
            bianyiflag[i]=1;
    }
    srand(time(NULL));
    for (i=0;i<num;i++)
        if (bianyiflag[i]==1)
    {
        t=rand()%num;//������ɱ������
        group[i].beibao[t]=1-group[i].beibao[t];//0��Ϊ1,1��Ϊ0
    }
}
void shuaixuan()
{
    int i,j;
    double max=group[0].p;
    for (i=1;i<num;i++)
    if (max<group[i].p)
    {
        max=group[i].p;
        j=i;
    }
    printf("����ѡ��Ϊ��\n");
    for (i=0;i<n;i++)
    printf("%d ",group[j].beibao[i]);
    printf("\n");
    printf("������Ϊ:%d\n",group[j].adapt);
}
int main()
{
    int i,t;
    printf("�����뱳������n\n");
    scanf("%d",&n);
    printf("������ÿһ�������������ͼ�ֵ\n");
    for (i=0;i<n;i++)
    scanf("%d%d",&w[i],&v[i]);
    printf("�����뱳���ݻ�\n");
    scanf("%d",&m);
    groupproduce();//���ɳ�ʼ��Ⱥ
    t=0;
    while(t<MAX)
    {
        pingjia();
        xuanze();
        jiaopei();
        bianyi();
        t++;
    }
    pingjia();//���Ҫ����һ�����ۣ���Ϊ֮ǰ����ʱ���Ĺ�beibao����adapt����Ӧ)
    shuaixuan();
    return 0;
}
