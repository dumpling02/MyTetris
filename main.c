#include <stdio.h>
#include <windows.h>
#include <time.h>
#include <conio.h>
#include <stdlib.h>
 
#define left 'a'
#define right 'd'
#define down 's'
#define change 'w'
 
int xy[55][25]={0};
 
void shape();                 			//方块随机形状
void wall();               		  		//游戏边框
void move();              		   		//物块移动
void Change();            		   		//物块改变形状
void Down();              		   		//物块一直做下落运动
void gotoxy(int a, int b); 		  		//光标跳转
void gotoprint(int x, int y);		 	//打印物块
void gotodelete(int x, int y);			//打印空格来消除物块
void clickcontrol();          		 	// 判断键盘输入
void pause();               	        //游戏暂停
int color(int c);          				//颜色
void remove();                    		//消行
void explation();                		//游戏说明
void end();                    			//游戏结束
 
int i, j, a, b, w_shape, score=0;
char click;            					//键盘输入的值
 
int main()
{
	explation();
    wall();
    gotoxy(55,3);
 
	while (1)
	{   color(6);
	    printf("你的得分是：%d",score);
		shape();
		Down();
		remove();
		gotoxy(55,3);
		for(i=12;i<50;i++)
		if (xy[i][1]==1) {
		    end();
		    break;       //只end一个循环
		}
	}
	return 0;
}
 
void explation()
{
	int i,j = 1;
    system("cls");         //实现清屏
    color(13);
    gotoxy(26,4);
    printf("按键说明");
    color(2);
    for (i = 6; i <= 18; i++)   //输出上下边框===
	{
		for (j = 15; j <= 60; j++)  //输出左右边框||
		{
			gotoxy(j-6, i);
			if (i == 6 || i == 18) printf("=");
			else if (j == 15 || j == 59) printf("||");
		}
	}
    color(3);
    gotoxy(12,7);
    printf("tip1: 玩家可以通过 a,d方向键来移动方块");
    color(10);
    gotoxy(12,9);
    printf("tip2: 通过 w使方块旋转");
    color(14);
    gotoxy(12,11);
    printf("tip3: 通过 s加速方块下落");
    color(11);
    gotoxy(12,13);
    printf("tip4: 按空格键暂停游戏，再按空格键继续");
    color(4);
    gotoxy(12,15);
    printf("tip5: 按ESC退出游戏");
    color(7);
    gotoxy(35,17);
    printf("按任意键进入游戏");
    getch();                //按任意键返回主界面
    system("cls");
}
void wall()
{
	gotoxy(5, 22);
	color(5);
	for (i = 10; i < 50; i+=2)
	{
		gotoxy(i, 22);
		printf("■");
		xy[i][22]=1;               //有问题
		xy[i+1][22]=1;
 
		gotoxy(50,1);
		printf("■");
	}
	for (i = 1; i < 23; i++)
	{
		gotoxy(50, i);
		printf("■");
		xy[50][i] = 1;
		xy[51][i] = 1;
		gotoxy(10,i);
		printf("■");
		xy[11][i] = 1;
		xy[10][i]=1;
	}
}
void shape()
{
	srand((unsigned)time(0));
	w_shape=rand()%7+1;
//    w_shape=1;
}
void gotoxy(int x, int y)
{
    // 更新光标位置 	                     //句柄就好像一个指针？
    COORD pos;                 				 //COORD是一个结构体，表示一个坐标。定义包含在window.s的头文件里
    HANDLE hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	//HANDLE就是句柄数据类型。GetStdHandle(STD_OUTPUT_HANDLE)固定格式，获取一个标准输出函数的句柄。
    pos.X = x;
    pos.Y = y;                          	 //设置坐标
    SetConsoleCursorPosition(hOutput, pos);	 //设置控制台光标位置。API中定位光标位置的函数。
    // 把光标和句柄联系起来？
    // 隐藏光标
    CONSOLE_CURSOR_INFO cursor;
    cursor.bVisible = FALSE;
    cursor.dwSize = sizeof(cursor);
    SetConsoleCursorInfo(hOutput, &cursor);
}
 
void Down()
{
	a = 28;
	b = 0;
	for (i = 0; i <= 10; i++)
	{
//		clickcontrol();
//		for(j=0;j<400000000;j++);
	b = b + 1;
	gotoprint(a, b);
//		pause();
	for (j = 0; j < 320000000; j++)
			;
		if (1)
		{
		if(w_shape==1){ 				//形状1
			if (xy[a-4][b + 1]  || xy[a - 2][b + 1] || xy[a ][b + 1]  || xy[a + 3][b + 1]){
				for(i=-4;i<4;i++)
			    	xy[a+i][b]= 1;
				break;
			}
		}
	    if (w_shape==2){				//形状2
			if (xy[a][b + 2] ){
				for(i=-2;i<2;i++){
					    xy[a][b+i] = 1;
					    xy[a+1][b+i]=1;
					}
				break;
			}
    	}
		if(w_shape==3){					//形状3
			if(xy[a][b+2]||xy[a+2][b+2]){
				for(i=0;i<4;i++){
					xy[a+i][b]=1;
					xy[a+i][b+1]=1;
				}
				break;
			}
		}
		if(w_shape==4){               //形状4
			if(xy[a-2][b+2]||xy[a][b+2]||xy[a+2][b+2]){
				xy[a][b]=1;xy[a+1][b]=1;
				for(i=0;i<6;i++){
					xy[a+i-2][b+1]=1;
				}
				break;
			}
		}
		if(w_shape==5){              //形状5
			if(xy[a-2][b+1]||xy[a-1][b+1]||xy[a][b+2]||xy[a+1][b+2]){
				xy[a-2][b]=1;xy[a-1][b]=1;
				for(i=-1;i<2;i++){
					xy[a][b+i]=1;
					xy[a+1][b+i]=1;
				}
				break;
			}
		}
		if(w_shape==6){				//形状6
			if(xy[a-2][b]||xy[a][b+1]||xy[a+2][b]){
				xy[a][b]=1;xy[a+1][b]=1;
				for(i=-2;i<4;i++){
					xy[a+i][b-1]=1;
				}
				break;
			}
		}
		if(w_shape==7){				 //形状7
			if(xy[a+2][b+1]||xy[a+1][b+1]||xy[a][b+2]||xy[a+1][b+2]){
				xy[a+2][b]=1;xy[a+1][b]=1;
				for(i=-1;i<2;i++){
					xy[a][b+i]=1;
					xy[a+1][b+i]=1;
				}
				break;
			}
		}
	}
//	    clickcontrol();
//        pause();
        gotodelete(a, b);
		for(j=0;j<10;j++)
            clickcontrol();
	}
}
 
void clickcontrol()
{
	if (_kbhit())
	{
	    click = _getch();
    	if(click == ' '){
			    gotoprint(a,b+1);
    	    	pause();
		}
		else if (click==27){       //ESC结束游戏
			end();
		}
		else
		    move();
	}
}
void pause()
{
	char a;
 	while(1){
 	    if(_kbhit){
	    	a = _getch();
        if (a==' ')
            break;
	    }
   }
}
 
int color(int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);        //更改文字颜色
	return 0;
}
 
void gotoprint(int x, int y)
{
	int c,b;
	gotoxy(x, y);
	color(01);
	if(w_shape==1){   			//形状1  ----
		gotoxy(x-4,y);
	    for (i = -2; i < 6; i+=2)
		printf("■");
	}
	color(06);
	if(w_shape==2)  			 //形状2  |
	for (i = -2; i < 2; i++){
		gotoxy(x, y + i);
		printf("■");
	}
	color(02);
	if(w_shape==3)  			 //形状3   田
		for (i = 0; i < 2; i++){
    		c=rand()%13+1;
    		color(c);
		    gotoxy(x, y + i);
	    	printf("■");
	    	b=rand()%6+1;
	    	color(b);
	    	gotoxy(x+2,y+i);
	    	printf("■");
        }
 
    color(2);
    if(w_shape==4){ 			  //形状4  _|_
	    gotoxy(x,y);
	    printf("■");
		for(i=0;i<6;i+=2){
		    gotoxy(x+i-2,y+1);
			printf("■");
		}
	}
 
	color(9);
	if(w_shape==5){   			 //形状5    -|
		gotoxy(x-2,y);
		printf("■");
		for(i=-1;i<2;i++){
			gotoxy(x,y+i);
			printf("■");
		}
	}
 
	color(6);
    if(w_shape==6){  			  //形状6  -_-
        gotoxy(x,y);
        printf("■");
    	for(i=-2;i<4;i+=2){
	        gotoxy(x+i,y-1);
	    	printf("■");
	    }
	}
 
	color(4);
	if(w_shape==7){   			 //形状7  |-
		gotoxy(x+2,y);
		printf("■");
		for(i=-1;i<2;i++){
			gotoxy(x,y+i);
			printf("■");
		}
	}
}
 
void gotodelete(int x, int y)
{
	gotoxy(x, y);
	if(w_shape==1)
	for (i = -2; i < 6; i+=2){
		gotoxy(x-2+i,y);
		printf("  ");
	}
 
	if(w_shape==2)
	for (i = -2; i < 2 ; i++){
		gotoxy(x, y + i);
		printf("  ");
	}
 
	if(w_shape==3)
	for (i = 0; i < 2; i++){
		gotoxy(x, y + i);
        printf("    ");
	}
 
	if(w_shape==4){
	    gotoxy(x,y);
	    printf("  ");
		for(i=0;i<6;i+=2){
		    gotoxy(x+i-2,y+1);
			printf("  ");
		}
	}
 
	if(w_shape==5){
		gotoxy(x-2,y);
		printf("  ");
		for(i=-1;i<2;i++){
			gotoxy(x,y+i);
			printf("  ");
		}
	}
 
    if(w_shape==6){
       gotoxy(x,y);
       printf("  ");
   		for(i=-2;i<4;i+=2){
      		gotoxy(x+i,y-1);
    		printf("  ");
		}
	}
 
		if(w_shape==7){
		gotoxy(x+2,y);
		printf("  ");
		for(i=-1;i<2;i++){
			gotoxy(x,y+i);
			printf("  ");
		}
	}
 
}
//要改
void move()
{
	if (w_shape==1)
	switch (click){
	case left:
		if (!xy[a - 5][b + 1] && !xy[a - 6][b + 1])
			a -= 2;
		break;
	case right:
		if (!xy[a + 4][b + 1] && !xy[a + 5][b + 1])
			a += 2;
		break;
	case down:
		if(!xy[a-4][b+2]&&!xy[a-2][b+2]&&!xy[a][b+2]&&!xy[a+2][b+2])
	    	b += 1;
		break;
	case change:
		if(!xy[a][b+1] && !xy[a][b+2])
		Change();break;
	}
 
	else if (w_shape==2)
	switch (click){
	case left:
		if (!xy[a - 2][b + 2] && !xy[a - 1][b + 2])
			a -= 2;
		break;
	case right:
		if (!xy[a + 2][b + 2] && !xy[a + 1][b + 2])
			a += 2;
		break;
	case down:
		if(!xy[a][b+3])
	    	b += 1;
		break;
	case change:
	    if(a>=14&&(!xy[a-4][b+1]&&!xy[a-2][b+1])&&!xy[a][b+1]&&!xy[a+2][b])
		Change();break;
	}
	else if (w_shape==3)
	switch (click){
	case left:
		if (!xy[a - 2][b + 2] && !xy[a - 1][b + 2])
			a -= 2;
		break;
	case right:
		if (!xy[a + 3][b + 2] && !xy[a + 4][b + 2])
			a += 2;
		break;
	case down:
	    if (!xy[a][b+3]&&!xy[a+1][b+3])
	    	b += 1;
		break;
	case change:
		Change();break;
	}
 
    else if(w_shape==4)
	switch (click){
	case left:
		if (!xy[a - 4][b + 2] && !xy[a - 3][b + 2])
			a -= 2;
		break;
	case right:
		if (!xy[a + 4][b + 2] && !xy[a + 5][b + 2])
			a += 2;
		break;
	case down:
	    if (!xy[a-2][b+3] &&!xy[a][b+3]&&!xy[a+2][b+3])
	    	b += 1;
		break;
	case change:
		Change();break;
	}
 
    else if(w_shape== 5)
	switch (click){
	case left:
		if (!xy[a - 3][b + 1] && !xy[a - 4][b + 1] &&!xy[a-1][b+2]&&!xy[a - 1][b + 1])
			a -= 2;
		break;
	case right:
		if ( !xy[a + 2][b + 1] && !xy[a+2][b+2] &&!xy[a+2][b])
			a += 2;
		break;
	case down:
	    if (!xy[a-2][b+2] &&!xy[a][b+3])
	    	b += 1;
		break;
	case change:
		Change();break;
	}
 
	else if(w_shape== 6)
	switch (click){
	case left:
		if (!xy[a - 4][b] && !xy[a - 3][b] &&!xy[a - 1][b + 1] && !xy[a][b + 1])
			a -= 2;
		break;
	case right:
		if ( !xy[a + 2][b + 1] && !xy[a+2][b+2] &&!xy[a+2][b])
			a += 2;
		break;
	case down:
	    if (!xy[a-2][b+2] &&!xy[a][b+3]&&!xy[a+2][b+2])
	    	b += 1;
		break;
	case change:
		Change();break;
	}
 
	else if(w_shape== 7)
	switch (click){
	case left:
		if (!xy[a - 2][b ] && !xy[a - 2][b + 1] &&!xy[a-2][b+2])
			a -= 2;
		break;
	case right:
		if ( !xy[a + 4][b + 1] && !xy[a+2][b+2] &&!xy[a+2][b])
			a += 2;
		break;
	case down:
	    if (!xy[a+2][b+2] &&!xy[a][b+3])
	    	b += 1;
		break;
	case change:
		Change();break;
	}
}
 
void Change()
{
	if (w_shape == 1)
		w_shape = 2;
	else if (w_shape == 2)
	    w_shape = 1;
	else if (w_shape == 3)
		w_shape = 3;
	else if (w_shape == 4)
	    w_shape = 5;
	else if (w_shape == 5)
	    w_shape = 6;
	else if (w_shape == 6)
	    w_shape = 7;
	else if (w_shape == 7)
	    w_shape = 4;
}
 
void remove()
{
    int store[55][25];          //point!!!
	int _i=0;
	int count=0;
	for(i=10;i<22;i++){
		count=0;
	    for(j=12;j<50;j++)
			if(xy[j][i])
            	count+=1;
        if(count>=38){
			_i=i;
			i=22;
            break;
		}
	}
 
	if(count>=38)
	{
    	score+=100;
    	for(j=12;j<50;j++)
	        for(i=0;i<22;i++){
				store[j][i]=xy[j][i];       //point 因为赋值是单个进行而非一段进行(动态)  eg.a[][]={0,1,0}; a[j+1][i]=a[j][i]的结果为a[][]={0,0,0}
				gotoxy(j,i);
//			    if(j!=49)
	            printf(" ");
		}
    	for(j=12;j<50;j++)
	        for(i=0;i<_i;i++){
	        	gotoxy(j,i);
				xy[j][i+1]=store[j][i];     
//	        	printf("%d",xy[j][i]);
		}
    	for(j=12;j<50;j+=2)
	        for(i=2;i<22;i++)
	        if(xy[j][i]==1){             	
	        	color(j%5+1);
	        	gotoxy(j,i);
				printf("■");
		}
    }
}
 
void end()
{
            color(8);
	        gotoxy(12,4);   printf("                                    ");
    		gotoxy(12,5);	printf("    ■■■■   ■     ■   ■■     ");
            gotoxy(12,6);   printf("    ■         ■■   ■   ■  ■   ");
            gotoxy(12,7); 	printf("    ■■■     ■  ■ ■   ■   ■  ");
			gotoxy(12,8);	printf("    ■         ■   ■■   ■  ■   ");
			gotoxy(12,9);	printf("    ■■■■   ■     ■   ■■     ");
			gotoxy(12,10);  printf("                                    ");
			gotoxy(0,24);
			while(1);
}
