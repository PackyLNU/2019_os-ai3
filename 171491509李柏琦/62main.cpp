
#include<iostream>
using namespace std;
int step[10][10]={//代表A-H八种操作在读入的数字种的位置
                   { 0, 2, 6,11,15,20,22},// A
                   { 1, 3, 8,12,17,21,23},// B
                   {10, 9, 8, 7, 6, 5, 4},// C
                     {19,18,17,16,15,14,13},// D
                   {23,21,17,12, 8, 3, 1},//E
                   {22,20,15,11, 6, 2, 0},//F
                   {13,14,15,16,17,18,19},//G
                   { 4, 5, 6, 7, 8, 9,10},//H
				};
int index[9]={6,7,8,11,12,15,16,17};//中心位置的方块用于检查
int map[30];
char ans[100];
int check(){//检查中心的八个方块，是否数字相同
	for(int i=0;i<8;i++){
		if(map[index[0]]!=map[index[i]])
			return 0;
	}
	return 1;
}
int move(int loc){//头位数字放到尾部，其他依次挪一格
	int head=map[step[loc][0]];
	for(int i=0;i<6;i++){
		map[step[loc][i]]=map[step[loc][i+1]];
	}
	map[step[loc][6]]=head;
	return 0;
}
int pre(){//估价函数
	int most=100;
	for(int i=1;i<=3;i++){
		int k=0;
		for(int j=0;j<8;j++)
			if(map[index[j]]!=i)
				k++;
			most=min(most,k);
	}
	return most;
}
int dfs(int d,int dm ){
	if(d==dm)
		return check();
	if(d+pre()>dm)
		return 0;
	for(int i=0;i<8;i++){
		ans[d]=i+'A';
		move(i);
		if(dfs(d+1,dm)){
			return 1;
		}
		if(i%2==0){//撤销刚才的操作
			move((i+5)%8);
		}
		else
			move((i+3)%8);
	}
	return 0;
}
int main(){
	while(cin>>map[0]&&map[0]!=0){
		for(int i=1;i<24;i++){
			cin>>map[i];
		}
//		for(int i=0;i<24;i++){
//			cout<<map[i];
//		}
//		cout<<endl;
		if(check()){
			cout<<"No moves needed"<<endl;
		}
		else{
			int i=1;
			while(!dfs(0,i)){
				i++;
			}
			ans[i]='\0';
			cout<<ans<<endl;
		}
		cout<<map[index[0]]<<endl;
	}
	return 0;
}
