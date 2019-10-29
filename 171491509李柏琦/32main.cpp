#include<cstdio>
#include<cstdlib>
#include<algorithm>
using namespace std;
const int inf=1e9;
int n,a,b,c,d,f[2][69][21][21][21][21];
int dx[8]={1,0,-1,0,2,0,-2,0};
int dy[8]={0,1,0,-1,0,2,0,-2};
int dfs(int x,int y,int a,int b,int c,int d)
 {if(y>3*n) return inf;
  if(a==c && b==d){if(x) return inf; return 0;}
  if(f[x][y][a][b][c][d]) return f[x][y][a][b][c][d];
  int ans,xx,yy;
  if(x)
    {ans=inf;
     for(int i=0;i<=7;i++)
      {xx=c+dx[i],yy=d+dy[i];
       if(1<=xx && xx<=n && 1<=yy && yy<=n)
            ans=min(ans,dfs(0,y+1,a,b,xx,yy));
      }
    }
  else
     {ans=0;
      for(int i=0;i<=3;i++)
       {xx=a+dx[i],yy=b+dy[i];
       if(1<=xx && xx<=n && 1<=yy && yy<=n)
            ans=max(ans,dfs(1,y+1,xx,yy,c,d));
       }
     }
  ans++;
  return f[x][y][a][b][c][d]=ans;
 }
int main()
{scanf("%d%d%d%d%d",&n,&a,&b,&c,&d);

 if(abs(a-c)+abs(b-d)<=1)	printf("WHITE 1");
 else                       printf("BLACK %d",dfs(0,0,a,b,c,d));

return 0;
}
