#include<iostream>
#include <windows.h>
#include <conio.h>
#include <time.h>
using namespace std;
//游戏窗口
#define FrameX 4   //游戏窗口左上角的X轴坐标
#define FrameY 4   //游戏窗口左上角的Y轴坐标
#define Frame_height  20 //游戏窗口的高度
#define Frame_width   12 //游戏窗口的宽度
//定义全局变量
int i,j,temp,temp1,temp2,temp3,temp4; //temp,temp1,temp2用于记住和转换方块变量的值
int a[80][80]={0};   //标记游戏屏幕的图案：2,1,0分别表示该位置为游戏边框、方块、无图案;初始化为无图案
int b[4];            //标记4个"口"方块：1表示有方块，0表示无方块
class player1{
	void run(){
	};
};
class player2{
	void run(){
	};
};
//声明俄罗斯方块的结构体
struct Tetris
{
 int x;     //中心方块的x轴坐标
 int y;     //中心方块的y轴坐标
 int flag;    //标记方块类型的序号
 int next;    //下一个俄罗斯方块类型的序号
 int speed;    //俄罗斯方块移动的速度
 int count;    //产生俄罗斯方块的个数
 int score;    //游戏的分数
 int level;    //游戏的等级
};
//函数原型声明
//光标移到指定位置
void gotoxy(HANDLE hOut, int x, int y);
//制作游戏窗口
void make_frame();
//随机产生方块类型的序号
void get_flag(struct Tetris *);
//制作俄罗斯方块
void make_tetris(struct Tetris *);
//打印俄罗斯方块
void print_tetris(HANDLE hOut,struct Tetris *);
//清除俄罗斯方块的痕迹
void clear_tetris(HANDLE hOut,struct Tetris *);
//判断是否能移动，返回值为1，能移动，否则，不动
int if_moveable(struct Tetris *);
//判断是否满行，并删除满行的俄罗斯方块
void del_full(HANDLE hOut,struct Tetris *);
//开始游戏
void start_game();

/******光标移到指定位置**************************************************************/
void gotoxy(HANDLE hOut, int x, int y)
{
 COORD pos;
 pos.X = x;  //横坐标
 pos.Y = y;  //纵坐标
 SetConsoleCursorPosition(hOut, pos);
}
/******制作游戏窗口******************************************************************/
void make_frame()
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量
 gotoxy(hOut,FrameX+Frame_width-5,FrameY-2);   //打印游戏名称
 
cout<<"玩家1"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+7);  //打印选择菜单
cout<<"**********下一个方块："<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+13);
cout<<"**********"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+17);
cout<<"↑键：变体"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+19);
cout<<"空格：暂停游戏"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+15);
cout<<"Esc ：退出游戏"<<endl;
 gotoxy(hOut,FrameX,FrameY);       //打印框角并记住该处已有图案
cout<<"╔"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY);
cout<<"╗"<<endl;
 gotoxy(hOut,FrameX,FrameY+Frame_height);
cout<<"╚"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+Frame_height);
cout<<"╝"<<endl;
 a[FrameX][FrameY+Frame_height]=2;     
 a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY);
 cout<<"═"<<endl;         //打印上横框
 }
 for(i=2;i<2*Frame_width-2;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY+Frame_height);
 cout<<"═"<<endl;         //打印下横框
  a[FrameX+i][FrameY+Frame_height]=2;    //记住下横框有图案
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX,FrameY+i); 
 cout<<"║"<<endl;         //打印左竖框
  a[FrameX][FrameY+i]=2;       //记住左竖框有图案
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX+2*Frame_width-2,FrameY+i); 
 cout<<"║"<<endl;         //打印右竖框
  a[FrameX+2*Frame_width-2][FrameY+i]=2;   //记住右竖框有图案
 }
  //HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量
 gotoxy(hOut,FrameX+Frame_width-5+50,FrameY-2);   //打印游戏名称
 
cout<<"玩家2"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+7);  //打印选择菜单
cout<<"**********下一个方块："<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+13);
cout<<"**********"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+17);
cout<<"↑键：变体"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+19);
cout<<"空格：暂停游戏"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+15);
cout<<"Esc ：退出游戏"<<endl;
 gotoxy(hOut,FrameX+50,FrameY);       //打印框角并记住该处已有图案
cout<<"╔"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width-2+50,FrameY);
cout<<"╗"<<endl;
 gotoxy(hOut,FrameX+50,FrameY+Frame_height);
cout<<"╚"<<endl;
 gotoxy(hOut,FrameX+2*Frame_width-2+50,FrameY+Frame_height);
cout<<"╝"<<endl;
 a[FrameX][FrameY+Frame_height]=2;     
 a[FrameX+2*Frame_width-2][FrameY+Frame_height]=2;
 for(i=52;i<2*Frame_width-2+50;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY);
 cout<<"═"<<endl;         //打印上横框
 }
 for(i=2+50;i<2*Frame_width-2+50;i+=2)
 {
  gotoxy(hOut,FrameX+i,FrameY+Frame_height);
 cout<<"═"<<endl;         //打印下横框
  a[FrameX+i][FrameY+Frame_height]=2;    //记住下横框有图案
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX+50,FrameY+i); 
 cout<<"║"<<endl;         //打印左竖框
  a[FrameX][FrameY+i]=2;       //记住左竖框有图案
 }
 for(i=1;i<Frame_height;i++)
 {
  gotoxy(hOut,FrameX+2*Frame_width-2+50,FrameY+i); 
 cout<<"║"<<endl;         //打印右竖框
  a[FrameX+2*Frame_width-2][FrameY+i]=2;   //记住右竖框有图案
 }
}

/******制作俄罗斯方块********************************************************************/
void make_tetris(struct Tetris *tetris)
{
 a[tetris->x][tetris->y]=b[0];    //中心方块位置的图形状态:1-有,0-无
 switch(tetris->flag)            //共6大类，19种类型
 {
  case 1:         //田字方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 2:         //直线方块:----
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y]=b[2];
    a[tetris->x+4][tetris->y]=b[3];
    break;
   }
  case 3:         //直线方块: |
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y-2]=b[2];
    a[tetris->x][tetris->y+1]=b[3];
    break;
   }
  case 4:         //T字方块
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y]=b[2];
    a[tetris->x][tetris->y+1]=b[3];
    break;
   }
  case 5:         //T字顺时针转90度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y]=b[3];
    break;
   }
  case 6:         //T字顺时针转180度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 7:         //T字顺时针转270度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 8:         //Z字方块
   {  
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x+2][tetris->y+1]=b[3];
    break;
   }
  case 9:         //Z字顺时针转90度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y]=b[2];
    a[tetris->x-2][tetris->y+1]=b[3];
    break;
   }
  case 10:        //Z字顺时针转180度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x-2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 11:        //Z字顺时针转270度方块
   {  
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 12:        //7字方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y-1]=b[3];
    break;
   }
  case 13:        //7字顺时针转90度方块
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x-2][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 14:        //7字顺时针转180度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y+1]=b[3];
    break;
   }
  case 15:        //7字顺时针转270度方块
   {
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 16:        //倒7字方块
   { 
    a[tetris->x][tetris->y+1]=b[1];
    a[tetris->x][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y-1]=b[3];
    break;
   }
  case 17:        //倒7字顺指针转90度方块
   { 
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x-2][tetris->y-1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
  case 18:        //倒7字顺时针转180度方块
   {  
    a[tetris->x][tetris->y-1]=b[1];
    a[tetris->x][tetris->y+1]=b[2];
    a[tetris->x-2][tetris->y+1]=b[3];
    break;
   }
  case 19:        //倒7字顺时针转270度方块
   {  
    a[tetris->x-2][tetris->y]=b[1];
    a[tetris->x+2][tetris->y+1]=b[2];
    a[tetris->x+2][tetris->y]=b[3];
    break;
   }
 } 
}
//******判断是否可动*************************************************************************/
int if_moveable(struct Tetris *tetris)
{
 if(a[tetris->x][tetris->y]!=0)//当中心方块位置上有图案时，返回值为0，即不可移动
 {
  return 0;
 }
 else
 {
  if( //当为田字方块且除中心方块位置外，其他"口"字方块位置上无图案时，返回值为1，即可移动
   ( tetris->flag==1  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   //或为直线方块且除中心方块位置外，其他"口"字方块位置上无图案时，返回值为1，即可移动
   ( tetris->flag==2  && ( a[tetris->x-2][tetris->y]==0   && 
    a[tetris->x+2][tetris->y]==0 && a[tetris->x+4][tetris->y]==0 ) )   ||
   ( tetris->flag==3  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y-2]==0 && a[tetris->x][tetris->y+1]==0 ) )   ||
   ( tetris->flag==4  && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y]==0 && a[tetris->x][tetris->y+1]==0 ) )   ||
   ( tetris->flag==5  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y]==0 ) )   ||
   ( tetris->flag==6  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y]==0 ) )   ||
   ( tetris->flag==7  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) )   ||
   ( tetris->flag==8  && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==9  && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y]==0 && a[tetris->x-2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==10 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==11 && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==12 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y-1]==0 ) ) ||
   ( tetris->flag==13 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x-2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==14 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x+2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==15 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==16 && ( a[tetris->x][tetris->y+1]==0   &&
    a[tetris->x][tetris->y-1]==0 && a[tetris->x+2][tetris->y-1]==0 ) ) ||
   ( tetris->flag==17 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x-2][tetris->y-1]==0 && a[tetris->x+2][tetris->y]==0 ) ) ||
   ( tetris->flag==18 && ( a[tetris->x][tetris->y-1]==0   &&
    a[tetris->x][tetris->y+1]==0 && a[tetris->x-2][tetris->y+1]==0 ) ) ||
   ( tetris->flag==19 && ( a[tetris->x-2][tetris->y]==0   &&
    a[tetris->x+2][tetris->y+1]==0 && a[tetris->x+2][tetris->y]==0 ) ) )
   {
    return 1;
   }
 }
 return 0;
}
/******随机产生俄罗斯方块类型的序号**********************************************************/
void get_flag(struct Tetris *tetris)
{
 tetris->count++;     //记住产生方块的个数
 //srand((unsigned)time(NULL));  //初始化随机数
 if(tetris->count==1)
 {
  tetris->flag = rand()%19+1;  //记住第一个方块的序号
 }
 tetris->next = rand()%19+1;   //记住下一个方块的序号
}
/******打印俄罗斯方块**********************************************************************/
void print_tetris(HANDLE hOut,struct Tetris *tetris)
{
 for(i=0;i<4;i++)
 {
  b[i]=1;                  //数组b[4]的每个元素的值都为1
 }
 make_tetris(tetris);      //制作俄罗斯方块
 for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 {
  for(j=tetris->y-2;j<=tetris->y+1;j++)
  {
   if( a[i][j]==1 && j>FrameY )
   {
    gotoxy(hOut,i,j);
   cout<<"□"<<endl;     //打印边框内的方块
   }
  }
 }
 //打印菜单信息
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+1);
cout<<"level : "<<tetris->level<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+3);
cout<<"score :"<<tetris->score<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3,FrameY+5);
cout<<"speed :"<<tetris->speed<<"ms"<<endl;
gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+1);
cout<<"level : "<<tetris->level<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+3);
cout<<"score :"<<tetris->score<<endl;
 gotoxy(hOut,FrameX+2*Frame_width+3+50,FrameY+5);
cout<<"speed :"<<tetris->speed<<"ms"<<endl;
}

/******清除俄罗斯方块的痕迹****************************************************************/
void clear_tetris(HANDLE hOut,struct Tetris *tetris)
{
 for(i=0;i<4;i++)
 {
  b[i]=0;         //数组b[4]的每个元素的值都为0
 }
 make_tetris(tetris);      //制作俄罗斯方块
 for( i=tetris->x-2; i<=tetris->x+4; i+=2 )
 {
  for(j=tetris->y-2;j<=tetris->y+1;j++)
  {
   if( a[i][j]==0 && j>FrameY )
   {
    gotoxy(hOut,i,j);
   cout<<"  "<<endl;     //清除方块
   }
  }
 }
}
/******判断是否满行并删除满行的俄罗斯方块****************************************************/
void del_full1(HANDLE hOut,struct Tetris *tetris)
{       //当某行有Frame_width-2个方块时，则满行
 int k=0,del_count=0;  //分别用于记录某行方块的个数和删除方块的行数的变量
 for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
 {
  k=0;
  for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
  {  
   if(a[i][j]==1) //竖坐标依次从下往上，横坐标依次由左至右判断是否满行
   {
    k++;  //记录此行方块的个数
    if(k==Frame_width-2)
    {
     for(k=FrameX+2;k<FrameX+2*Frame_width-2;k+=2)
     {  //删除满行的方块
      a[k][j]=0;
      gotoxy(hOut,k,j);
      cout<<"  "<<endl;
      Sleep(1);
     }
     for(k=j-1;k>FrameY;k--)
     {  //如果删除行以上的位置有方块，则先清除，再将方块下移一个位置
      for(i=FrameX+2;i<FrameX+2*Frame_width-2;i+=2)
      {
       if(a[i][k]==1)
       {
        a[i][k]=0;
        gotoxy(hOut,i,k);
        cout<<"  "<<endl;
        a[i][k+1]=1;
        gotoxy(hOut,i,k+1);
        cout<<"□"<<endl;
       }
      }
     }
     j++;   //方块下移后，重新判断删除行是否满行
     del_count++; //记录删除方块的行数
    }
   }
  }
 }
 tetris->score+=100*del_count; //每删除一行，得100分
 if( del_count>0 && ( tetris->score%1000==0 || tetris->score/1000>tetris->level-1 ) )
 {        //如果得1000分即累计删除10行，速度加快20ms并升一级
  tetris->speed-=20;
  tetris->level++;
 }
}
void del_full2(HANDLE hOut,struct Tetris *tetris)
{       //当某行有Frame_width-2个方块时，则满行
 int k=0,del_count=0;  //分别用于记录某行方块的个数和删除方块的行数的变量
 for(j=FrameY+Frame_height-1;j>=FrameY+1;j--)
 {
  k=0;
  for(i=FrameX+2+50;i<FrameX+2*Frame_width-2+50;i+=2)
  {  
   if(a[i][j]==1) //竖坐标依次从下往上，横坐标依次由左至右判断是否满行
   {
    k++;  //记录此行方块的个数
    if(k==Frame_width-2)
    {
     for(k=FrameX+2+50;k<FrameX+2*Frame_width-2+50;k+=2)
     {  //删除满行的方块
      a[k][j]=0;
      gotoxy(hOut,k,j);
      cout<<"  "<<endl;
      Sleep(1);
     }
     for(k=j-1;k>FrameY;k--)
     {  //如果删除行以上的位置有方块，则先清除，再将方块下移一个位置
      for(i=FrameX+2+50;i<FrameX+2*Frame_width-2+50;i+=2)
      {
       if(a[i][k]==1)
       {
        a[i][k]=0;
        gotoxy(hOut,i,k);
        cout<<"  "<<endl;
        a[i][k+1]=1;
        gotoxy(hOut,i,k+1);
        cout<<"□"<<endl;
       }
      }
     }
     j++;   //方块下移后，重新判断删除行是否满行
     del_count++; //记录删除方块的行数
    }
   }
  }
 }
 tetris->score+=100*del_count; //每删除一行，得100分
 if( del_count>0 && ( tetris->score%1000==0 || tetris->score/1000>tetris->level-1 ) )
 {        //如果得1000分即累计删除10行，速度加快20ms并升一级
  tetris->speed-=20;
  tetris->level++;
 }
}

/******开始游戏******************************************************************************/
void start_game()
{
 HANDLE hOut = GetStdHandle(STD_OUTPUT_HANDLE);  //定义显示器句柄变量
 struct Tetris t,s,*tetris=&t,*tetris2=&s;       //定义结构体的指针并指向结构体变量
 unsigned char ch;         //定义接收键盘输入的变量
 tetris->count=0;      //初始化俄罗斯方块数为0个
 tetris->speed=400;    //初始移动速度为400ms
 tetris->score=0;      //初始游戏的分数为0分
 tetris->level=1;      //初始游戏为第1关
 tetris2->count=0;      //初始化俄罗斯方块数为0个
 tetris2->speed=400;    //初始移动速度为400ms
 tetris2->score=0;      //初始游戏的分数为0分
 tetris2->level=1;
 while(1)
{//循环产生方块，直至游戏结束
  get_flag(tetris);     //得到产生俄罗斯方块类型的序号
  temp=tetris->flag;     //记住当前俄罗斯方块序号
  get_flag(tetris2);     //得到产生俄罗斯方块类型的序号
  temp3=tetris2->flag; 
  //打印下一个俄罗斯方块的图形(右边窗口)
  tetris->x=FrameX+2*Frame_width+6;
  tetris->y=FrameY+10;
  tetris->flag = tetris->next;
  tetris2->x=FrameX+2*Frame_width+6+50;
  tetris2->y=FrameY+10;
  tetris2->flag = tetris2->next;
  print_tetris(hOut,tetris);
  print_tetris(hOut,tetris2);
  tetris->x=FrameX+Frame_width;  //初始中心方块x坐标
  tetris->y=FrameY-1;     //初始中心方块y坐标
  tetris->flag=temp;     //取出当前的俄罗斯方块序号
  tetris2->x=FrameX+Frame_width+50;  //初始中心方块x坐标
  tetris2->y=FrameY-1;     //初始中心方块y坐标
  tetris2->flag=temp3;
  while(1)
  {//控制方块方向，直至方块不再下移
   label:print_tetris(hOut,tetris);
   label2:print_tetris(hOut,tetris2);//打印俄罗斯方块
   Sleep(tetris->speed);   //延缓时间
   clear_tetris(hOut,tetris);  //清除痕迹
   Sleep(tetris2->speed);   //延缓时间
   clear_tetris(hOut,tetris2);  //清除痕迹
   temp1=tetris->x;    //记住中心方块横坐标的值
   temp2=tetris->flag;    //记住当前俄罗斯方块序号
   temp3=tetris2->x;    //记住中心方块横坐标的值
   temp4=tetris2->flag; 
   if(kbhit())   
   {        //判断是否有键盘输入
    ch=getch(); 
    if(ch==75)     //按←或者A键则向左动，中心横坐标减2
    {      
     tetris->x-=2;
    }
    if(ch=='S')     //按←或者A键则向左动，中心横坐标减2
    {      
     tetris2->y+=2;
    }
    if(ch=='A'){      
     tetris2->x-=2;
    }
    if(ch==77)     //按→或者D键则向右动，中心横坐标加2
    {      
     tetris->x+=2;    
    }
    if(ch=='D')    
    {      
     tetris2->x+=2;    
    }
    if(ch==72)     //按↑键则变体即当前方块顺时针转90度
    {      
     if( tetris->flag>=2 && tetris->flag<=3 )
     {
      tetris->flag++; 
      tetris->flag%=2;
      tetris->flag+=2;
     }
     if( tetris->flag>=4 && tetris->flag<=7 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=4;
     }    
     if( tetris->flag>=8 && tetris->flag<=11 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=8;
     }    
     if( tetris->flag>=12 && tetris->flag<=15 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=12;
     }    
     if( tetris->flag>=16 && tetris->flag<=19 )
     {
      tetris->flag++;
      tetris->flag%=4;
      tetris->flag+=16;
     }
    }
    if(ch=='E')     //按W键则变体即当前方块顺时针转90度
    {      
     if( tetris2->flag>=2 && tetris2->flag<=3 )
     {
      tetris2->flag++; 
      tetris2->flag%=2;
      tetris2->flag+=2;
     }
     if( tetris2->flag>=4 && tetris2->flag<=7 )
     {
      tetris2->flag++;
      tetris2->flag%=4;
      tetris2->flag+=4;
     }    
     if( tetris2->flag>=8 && tetris2->flag<=11 )
     {
      tetris2->flag++;
      tetris2->flag%=4;
      tetris2->flag+=8;
     }    
     if( tetris2->flag>=12 && tetris2->flag<=15 )
     {
      tetris2->flag++;
      tetris2->flag%=4;
      tetris2->flag+=12;
     }    
     if( tetris2->flag>=16 && tetris2->flag<=19 )
     {
      tetris2->flag++;
      tetris2->flag%=4;
      tetris2->flag+=16;
     }
    }
    if(ch==27){
    	system("cls");
        cout<<"退出游戏成功！"<<endl;
        getch();
	    exit(0);  //退出游戏 
        break;
	}
    if(ch==32)     //按空格键，暂停
    {
     print_tetris(hOut,tetris);
     print_tetris(hOut,tetris2);
     while(1)
     {
      if(kbhit())   //再按空格键，继续游戏
      {
       ch=getch();
       if(ch==32)
       {
        goto label;
        goto label2;
       }
      }
     }
    }
    if(if_moveable(tetris)==0) //如果不可动，上面操作无效
    {
     tetris->x=temp1;
     tetris->flag=temp2;
    }
    else      //如果可动，执行操作
    {
     goto label;
    }
    if(if_moveable(tetris2)==0) //如果不可动，上面操作无效
    {
     tetris2->x=temp3;
     tetris2->flag=temp4;
    }
    else      //如果可动，执行操作
    {
     goto label2;
    }
   }
   tetris->y++; 
   tetris2->y++;    //如果没有操作指令，方块向下移动
   if(if_moveable(tetris)==0)  //如果向下移动且不可动，方块放在此处
   {    
    tetris->y--;
    print_tetris(hOut,tetris);
    del_full1(hOut,tetris);
   }
   if(if_moveable(tetris2)==0)  //如果向下移动且不可动，方块放在此处
   {    
    tetris2->y--;
    print_tetris(hOut,tetris2);
    del_full2(hOut,tetris2);
   }
  }
  j=1; 
  for(i=tetris->y-2;i<tetris->y+2;i++)
  {//游戏结束条件：方块触到框顶位置
   if(i==FrameY)
   {
    j=0;      //如果游戏结束，j=0
   }
  }
  for(i=tetris2->y-2;i<tetris2->y+2;i++)
  {//游戏结束条件：方块触到框顶位置
   if(i==FrameY)
   {
    j=0;      //如果游戏结束，j=0
   }
  }
  if(j==0)       
  {
   system("cls");
   cout<<"Game Over!"<<endl;
   getch();
   break;
  }
  //清除下一个俄罗斯方块的图形(右边窗口)
  tetris->flag = tetris->next;
  tetris->x=FrameX+2*Frame_width+6;
  tetris->y=FrameY+10;
  clear_tetris(hOut,tetris); 
  tetris2->flag = tetris2->next;
  tetris2->x=FrameX+2*Frame_width+6+50;
  tetris2->y=FrameY+10;
  clear_tetris(hOut,tetris2); 
 }
}
int main()
{ 
 //制作游戏窗口
 make_frame();      
 //开始游戏
 start_game();
 return 0; 
}
 


