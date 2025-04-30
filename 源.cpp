#include <windows.h>
#include<iostream>
#include<graphics.h>
#include<time.h>
#include<stdio.h>
#include<easyx.h>
#include<stdlib.h>
#include <direct.h>
#include <sys/stat.h>

#define _CRT_SECURE_NO_WARNING 1
#pragma warning(disable:4996)
#pragma warning(disable:4244)
#pragma warning(disable:4819)
#pragma warning(disable:4267)
#define filecoor_x "coor_x.txt"
#define filecoor_y "coor_y.txt"
#define filenames "names.txt"
#define FILE_DISTANCE "distance.txt"
#define FILE_VIEW "view.txt"
#define FILE_SHADE "shade.txt"

#define INF 99999999
#define V 70
#define 教师公寓 0
#define 水房 1
#define 安悦公寓 2
#define 安美公寓 3
#define 东升苑 4
#define 建设中 5
#define 逸夫教学楼 6
#define 东区西门 7
#define 东区正门 8
#define 天桥 9
#define 西区东门 10
#define 人工湖 11
#define 北门 12
#define 行政楼 13
#define 大学生活动中心 14
#define 图书馆 15
#define 通院 16
#define 电院 17
#define 自动化院理学院 18
#define 教学A楼 19
#define 教学B楼 20
#define 西邮宾馆 21
#define 创业园区 22
#define 美广 23
#define 医务室 24
#define 浴室 25
#define 小操场 26
#define 大操场 27
#define 篮球场 28
#define 羽毛球 29
#define 旭日苑 30
#define 体育馆 31
#define 超市 32
#define 长思 33
#define 长智 34

/*三种权值*/
int distance[V][V];//距离
int view[V][V];//景色
int shade[V][V];//林荫
/*景点坐标*/
int coor_x[70];
int coor_y[70];
/*景点名称*/
const char* names[70] = { "教师公寓", "水房", "安悦公寓", "安美公寓", "东升苑",
"建设中", "逸夫教学楼", "东区西门", "东区正门", "天桥",
"西区东门", "人工湖", "北门", "行政楼", "通院", "电院", "自动化院理学院", "教学A楼", "教学B楼", "西邮宾馆",
"创业园区", "美广", "医务室", "浴室", "小操场", "大操场", "篮球场",
"羽毛球", "旭日苑", "体育馆", "大学生活动中心", "超市" "长思", "长智" };
/*界面函数*/
void home();
void change();
void reset();
/*最短路径*/
void dijkstra_distance(int graph[V][V], int src, int dest);
int minDistance_distance(int dist[], bool sptSet[]);
void printSolution_distance(int dist[], int parent[], int src, int dest);
void printPath_distance(int parent[], int j, char path[], char message[]);
void dijkstra_view(int graph[V][V], int src, int dest);
int minDistance_view(int dist[], bool sptSet[]);
void printSolution_view(int dist[], int parent[], int src, int dest);
void printPath_view(int parent[], int j, char path[], char message[]);
void dijkstra_shade(int graph[V][V], int src, int dest);
int minDistance_shade(int dist[], bool sptSet[]);
void printSolution_shade(int dist[], int parent[], int src, int dest);
void printPath_shade(int parent[], int j, char path[], char message[]);
/*文件处理*/
int check_file(const char* filename);//检查文件是否为空
void distance_Init();//初始化
void view_Init();
void shade_Init();
void coor_Init();//景点坐标初始化
void name_Init();//初始化景点名称
void distance_write_file();//写入文件
void distance_read_file();//读取文件
void view_write_file();
void view_read_file();
void shade_write_file();
void shade_read_file();
void read_names();
void read_coor_x();
void read_coor_y();
void write_names();
void write_coor_x();
void write_coor_y();
/*数据处理*/
int get_names(const char* names[]);//返回最后一个值不为空的下标
void delete_names(const char* names[], int index);
void delete_distance(int distance[V][V], int index);
void delete_view(int view[V][V], int index);
void delete_shade(int shade[V][V], int index);
void delete_coor(int arr[], int index);
int str_to_int(const char* str);//字符数字转换

/*主函数*/
int main()
{
	initgraph(1400, 764, EW_SHOWCONSOLE);
	home();
	return 0;
}
/*界面绘制*/
void home()
{
	// 隐藏控制台窗口
	HWND hWnd = GetConsoleWindow();
	ShowWindow(hWnd, SW_HIDE);

	cleardevice();
	setbkcolor(WHITE);
	cleardevice();
	
	IMAGE map;
	loadimage(&map, "map.jpg", 720, 764);
	putimage(0, 0, &map); 
	IMAGE ma;
	loadimage(&ma, "选项.jpg", 540-34, 100);
	putimage(800+34, 44, &ma);
	IMAGE mb;
	loadimage(&mb, "选项.jpg", 540-34, 100);
	putimage(800+34, 188, &mb);
	IMAGE mc;
	loadimage(&mc, "选项.jpg", 540-34, 100);
	putimage(800+34, 332, &mc);
	IMAGE md;
	loadimage(&md, "选项.jpg", 540-34, 100);
	putimage(800+34, 476, &md);
	IMAGE me;
	loadimage(&me, "选项.jpg", 540-34, 100);
	putimage(800+34, 620, &me);
	//setfillcolor(RGB(232,214,69));//设置填充颜色-黄色
	//setfillstyle(BS_SOLID);//设置填充模式，自定义填充，交叉网
	//setlinecolor(RGB(232,214,69));//设置线的颜色-红色
	//setlinestyle(PS_SOLID);//设置线的模式为虚线，粗细为两个像素
	//fillrectangle(800, 44, 1340, 144);//查找位置
	//fillrectangle(800, 188, 1340, 288);//地点信息
	//fillrectangle(800, 332, 1340, 432);//查找路径
	//fillrectangle(800, 476, 1340, 576);//修改信息
	//fillrectangle(800, 620, 1340, 720);//退出系统
	//fillrectangle(0, 0, 100, 60);//主页
	//fillrectangle(100, 0, 200, 60);//重置
	//画线
	//setlinecolor(RGB(225, 236, 76));//RGB(255,236,76)
	//setlinestyle(PS_SOLID,4);
	//line(800, 44, 800-1, 144-1);//
	//line(800, 44, 1340-1, 44-1);
	//line(800, 188, 1340-1, 188-1);//
	//line(800, 188, 800-1, 288-1);
	//line(800, 332, 800-1, 432-1);//
	//line(800, 332, 1340-1, 332-1);
	//line(800, 476, 800-1, 576-1);//
	//line(800, 476, 1340-1, 476-1);
	//line(800, 620, 800-1, 720-1);//
	//line(800, 620, 1340-1, 620-1);
	//line(0, 0, 0, 60-1);//
	//line(0, 0, 100-1, 0);
	//line(100, 0, 100-1, 60-1);//
	//line(100, 0, 200-1, 0);
	LOGFONT f;
	gettextstyle(&f);                   // 获取当前字体设置
	f.lfHeight = 60;                     // 设置字体高度为60
	_tcscpy_s(f.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	f.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&f);                    // 应用字体设置
	setbkcolor(RGB(240, 180, 180));
	settextcolor(BLACK);
	outtextxy(800 + 155, 44 + 20, "查 找 位 置");
	outtextxy(800 + 155, 188 + 20, "地 点 信 息");
	outtextxy(800 + 155, 332 + 20, "查 找 路 径");
	outtextxy(800 + 155, 476 + 20, "修 改 信 息");
	outtextxy(800 + 155, 620 + 20, "退 出 系 统");

	LOGFONT g;
	gettextstyle(&g);                   // 获取当前字体设置
	g.lfHeight = 40;                     // 设置字体高度为60
	_tcscpy_s(g.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	g.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&g);                    // 应用字体设置
	setbkcolor(RGB(240, 180, 180));
	settextcolor(BLACK);
	outtextxy(10, 10, "地 图");
	outtextxy(110, 10, "重 置");

	LOGFONT h;
	gettextstyle(&h);                   // 获取当前字体设置
	h.lfHeight = 20;                     // 设置字体高度为60
	_tcscpy_s(h.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	h.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&h);                    // 应用字体设置
	setbkcolor(WHITE);
	settextcolor(BLACK);
	outtextxy(0, 60, "单击[地图]可清除痕迹返回主页  ");
	outtextxy(0, 80, "单击[重置]可恢复原始设定数据  ");

	/*文件处理*/
	if (check_file(filenames) == 0)
	{
		name_Init();//初始化
		write_names();//写入文件
	}
	if (check_file(filecoor_x) == 0)
	{
		coor_Init();
		write_coor_x();
		write_coor_y();
	}
	if (check_file(FILE_DISTANCE) == 0)
	{
		distance_Init();
		distance_write_file();
	}
	if (check_file(FILE_VIEW) == 0)
	{
		view_Init();
		view_write_file();
	}
	if (check_file(FILE_SHADE) == 0)
	{
		shade_Init();
		shade_write_file();
	}

	ExMessage msg;
	while (1)
	{
		IMAGE h;
		loadimage(&h, "得意.jpg", 399/3.5, 399/3.5);
		putimage(720, 0, &h);
		read_names();//读取文件
		read_coor_x();
		read_coor_y();
		distance_read_file();
		view_read_file();
		shade_read_file();
		msg = getmessage(EX_MOUSE);
		switch (msg.message)
		{
			//鼠标单击
		case WM_LBUTTONDOWN:
			//查找位置
			if (msg.x > 800 && msg.x < 1340 && msg.y>44 && msg.y < 144)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				char s[20];
				int m = 0;//查找标志位
				InputBox(s, 20, _T(" 请输入要查询的地址名称："));
				for (int i = 0; i < 70 && names[i] != NULL; i++){
					if (strstr(names[i],s) != NULL) {//包含该字符串
						m = 1;//更改标志位
						IMAGE map;
						loadimage(&map, "派蒙.jpg", 701 / 8, 706 / 8);
						putimage(coor_x[i] - 701 / 8 / 2, coor_y[i] - 706 / 8 / 2, &map);
						break;
					}
				}
				if (m == 0)
				{
					IMAGE hh;
					loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
					putimage(720, 0, &hh);
					Sleep(350);//ms
					IMAGE kk;
					loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
					putimage(720, 0, &kk);
					HWND hnd = GetHWnd();
					MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
				}
			}
			//地点信息
			if (msg.x > 800 && msg.x < 1340 && msg.y>188 && msg.y < 288)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				char t[20];
				int m = 0;//查找标志位
				int p;//查询下标
				InputBox(t, 20, _T(" 请输入要查询的地址名称："));
				for (int i = 0; i < V && names[i] != NULL; i++){
					if (strstr(names[i],t) != NULL) {//包含该字符串
						m = 1;//更改标志位
						p = i;
						break;
					}
				}
				if (m == 0)
				{
					IMAGE hh;
					loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
					putimage(720, 0, &hh);
					Sleep(350);//ms
					IMAGE kk;
					loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
					putimage(720, 0, &kk);
					HWND hnd = GetHWnd();
					MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
				}
				//输入成功
				else
				{	
					for (int i = 0; i <= get_names(names); i++)
					{
						if (distance[p][i] < INF&& distance[p][i]!=0)//可直达
						{
							char s[100] = "";
							strcat(s, t);
							char y[20];
							char s_distance[20];
							char s_shade[20];
							char s_view[20];
							char b[200] = "可到达地点：";
							char c[] = "\n两点间距离：";
							char e[] = "\n林荫满意度：";
							char f[] = "\n风景满意度：";
							char x[20];
							char a[50] = "(坐标：";
							strcat(s, a);                //xx(坐标：
							sprintf(x, "%d", coor_x[p]);
							sprintf(y, "%d", coor_y[p]);
							strcat(s, x);                //xx（坐标：x
							strcat(s, ",");              //xx（坐标：x,
							strcat(s, y);                //xx（坐标：x,y
							strcat(s, ")");              //xx（坐标：x,y)
							sprintf(s_distance, "%d", distance[p][i]);
							sprintf(s_shade, "%d", shade[p][i]);
							sprintf(s_view, "%d", view[p][i]);
							strcat(b, names[i]);  //可到达地点：xx
							strcat(b, c);         //可到达地点：xx   距离：
							strcat(b, s_distance);//可到达地点：xx   距离：xx
							strcat(b, "m");
							strcat(b, e);         //可到达地点：xx   距离：xx   林荫满意度：
							strcat(b, s_shade);   //可到达地点：xx   距离：xx   林荫满意度：xx
							strcat(b, "分");
							strcat(b, f);         //可到达地点：xx   距离：xx   林荫满意度：xx   风景满意度：
							strcat(b, s_view);    //可到达地点：xx   距离：xx   林荫满意度：xx   风景满意度：xx
							strcat(b, "分");
							HWND hnd = GetHWnd();
							MessageBox(hnd, b, s, MB_OKCANCEL);
						}
					}
				}
			}
			//查找路径
			if (msg.x > 800 && msg.x < 1340 && msg.y>332 && msg.y < 432)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				int m = 0;//查找标志位
				char s[20];//起点
				char t[20];//终点
				int ss;
				int tt;
				while (1)//输入起点
				{
					InputBox(s, 20, _T(" 请输入起点地址名称："));
					for (int i = 0; i < 70 && names[i] != NULL; i++) {
						if (strstr(names[i],s) != NULL) {//包含该字符串
							m = 1;//更改标志位
							ss = i;
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;
				while (1)//输入终点
				{
					InputBox(t, 20, _T(" 请输入终点地址名称："));
					for (int i = 0; i < 70 && names[i] != NULL; i++) {
						if (strstr(names[i],t) != NULL) {//包含该字符串
							m = 1;//更改标志位
							tt = i;
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				dijkstra_distance(distance, ss, tt);
				printf("\n\n");
				dijkstra_view(view, ss, tt);
				printf("\n\n");
				dijkstra_shade(shade, ss, tt);
				printf("\n\n");
			}
			//修改信息
			if (msg.x > 800 && msg.x < 1340 && msg.y>476 && msg.y < 576)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				change();//修改信息界面
			}
			//退出系统
			if (msg.x > 800 && msg.x < 1340 && msg.y>620 && msg.y < 720)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				exit(0);
			}
			//主页地图
			if (msg.x > 0 && msg.x < 100 && msg.y>0 && msg.y < 60)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				home();
			}
			//重置数据
			if (msg.x > 100 && msg.x < 200 && msg.y>0 && msg.y < 60)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				reset();
			}
			write_names();//写入文件
			write_coor_x();
			write_coor_y();
			distance_write_file();
			view_write_file();
			shade_write_file();
			break;
		}
	}
	while (1);
	closegraph();
}
void change()
{
	//// 隐藏控制台窗口
	//HWND hWnd = GetConsoleWindow();
	//ShowWindow(hWnd, SW_HIDE);
	//initgraph(1400, 764, EW_SHOWCONSOLE);
	cleardevice();
	setbkcolor(WHITE);
	cleardevice();
	
	IMAGE map;
	loadimage(&map, "map.jpg", 720, 764);
	putimage(0, 0, &map);
	IMAGE ma;
	loadimage(&ma, "选项.jpg", 540, 100);
	putimage(1000-175, 44, &ma);
	IMAGE mb;
	loadimage(&mb, "选项.jpg", 540, 100);
	putimage(1000-175, 332, &mb);
	IMAGE mc;
	loadimage(&mc, "选项.jpg", 540, 100);
	putimage(1000-175, 620, &mc);
	//setfillcolor(RGB(232,214,69));//设置填充颜色-黄色
	//setfillstyle(BS_SOLID);//设置填充模式，自定义填充，交叉网
	//setlinecolor(RGB(232,214,69));//设置线的颜色-红色
	//setlinestyle(PS_SOLID);//设置线的模式为虚线，粗细为两个像素
	//fillrectangle(1000, 44, 1190, 144);//添加
	//fillrectangle(1000, 332, 1190, 432);//删除
	//fillrectangle(1000, 620, 1190, 720);//修改
	//fillrectangle(0, 0, 100, 60);//主页
	//fillrectangle(100, 0, 200, 60);//重置
	LOGFONT f;
	gettextstyle(&f);                   // 获取当前字体设置
	f.lfHeight = 60;                     // 设置字体高度为48
	_tcscpy_s(f.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	f.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&f);                    // 应用字体设置
	setbkcolor(RGB(240,180,180));
	settextcolor(BLACK);
	outtextxy(1000+40, 44+18 , "添 加");
	outtextxy(1000 + 40, 332 + 18, "删 除");
	outtextxy(1000+40, 620+18, "修 改");
	
	LOGFONT g;
	gettextstyle(&g);                   // 获取当前字体设置
	g.lfHeight = 40;                     // 设置字体高度为60
	_tcscpy_s(g.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	g.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&g);                    // 应用字体设置
	setbkcolor(RGB(240, 180, 180));
	settextcolor(BLACK);
	outtextxy(20, 10, "地 图");
	outtextxy(110, 10, "重 置");

	LOGFONT h;
	gettextstyle(&h);                   // 获取当前字体设置
	h.lfHeight = 20;                     // 设置字体高度为60
	_tcscpy_s(h.lfFaceName, _T("微软雅黑")); // 设置字体为微软雅黑
	h.lfQuality = ANTIALIASED_QUALITY;   // 设置输出质量为抗锯齿
	settextstyle(&h);                    // 应用字体设置
	setbkcolor(WHITE);
	settextcolor(BLACK);
	outtextxy(0, 60, "单击[地图]可清除痕迹返回主页  ");
	outtextxy(0, 80, "单击[重置]可恢复原始设定数据  ");
	ExMessage msg;
	while (1)
	{
		msg = getmessage(EX_MOUSE);
		switch (msg.message)
		{
		case WM_LBUTTONDOWN:
			//添加
			if (msg.x > 1000 && msg.x < 1190 && msg.y>44 && msg.y < 144)
			{ 
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				char s[20];//名称
				char t[20];
				char x_s[20];
				char y_s[20];
				char dis_s[20];
				char sha_s[20];
				char vie_s[20];
				int  i;//最新空位下标
				int j;//可直达景点
				int x, y;//坐标
				int dis, sha, vie;
				int m;//标志位
				i = get_names(names);//i
				InputBox(s, 20, _T(" 请输入新地点名称："));
				m = 0;//x
				while (1)
				{
					InputBox(x_s, 20, _T(" 请输入景点坐标X："));
					if (str_to_int(x_s) != -1)
					{
						x = str_to_int(x_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//y
				while (1)
				{
					InputBox(y_s, 20, _T(" 请输入景点坐标Y："));
					if (str_to_int(y_s) != -1)
					{
						y = str_to_int(y_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//j
				while (1)
				{
					InputBox(t, 20, _T(" 请输入可直达地点名称(从已存在地点中选择)："));
					for (int p = 0; p < 70 && names[p] != NULL; p++) {
						if (strstr(names[p],t) != NULL) {//包含该字符串
							m = 1;//更改标志位
							j = p;//记录直达位置
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//dis
				while (1)
				{
					InputBox(dis_s, 20, _T(" 请输入距离："));
					if (str_to_int(dis_s) != -1)
					{
						dis = str_to_int(dis_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//vie
				while (1)
				{
					InputBox(vie_s, 20, _T(" 请输入沿路风景满意度："));
					if (str_to_int(vie_s) != -1)
					{
						vie = str_to_int(vie_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//sha
				while (1)
				{
					InputBox(sha_s, 20, _T(" 请输入沿路林荫满意度："));
					if (str_to_int(sha_s) != -1)
					{
						sha = str_to_int(sha_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;
				names[i] = s;//记录数据
				coor_x[i] = x;
				coor_y[i] = y;
				distance[i][j] = dis;
				distance[j][i] = dis;
				view[i][j] = vie;
				view[j][i] = vie;
				shade[i][j] = sha;
				shade[j][i] = sha;
				write_names();//写入文件
				write_coor_x();
				write_coor_y();
				distance_write_file();
				view_write_file();
				shade_write_file();
			}
			//删除
			if (msg.x > 1000 && msg.x < 1190 && msg.y>332 && msg.y < 432)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				char s[20];
				int m = 0;
				int ss;
				while (1)
				{
					InputBox(s, 20, _T(" 请输入所删除地点名称："));
					for (int i = 0; i < 70 && names[i] != NULL; i++) {
						if (strstr( names[i],s) != NULL) {//包含该字符串
							m = 1;//更改标志位
							ss = i;//记录删除位置
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				//删除数据
				delete_names(names, ss);
				delete_distance(distance, ss);
				delete_shade(shade, ss);
				delete_view(view, ss);
				delete_coor(coor_x, ss);
				delete_coor(coor_y, ss);
				//重新写入
				write_names();
				write_coor_x();
				write_coor_y();
				distance_write_file();
				shade_write_file();
				view_write_file();
			}
			//修改
			if (msg.x > 1000 && msg.x < 1190 && msg.y>620 && msg.y < 720)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				int m = 0;
				char s[20];//起点
				char t[20];//终点
				char x_s[20];
				char y_s[20];
				char dis_s[20];
				char sha_s[20];
				char vie_s[20];
				int  i;//最新空位下标
				int j;//可直达景点
				int x, y;//坐标
				int dis, sha, vie;
				//i
				while (1)
				{
					InputBox(s, 20, _T(" 请输入要修改的地点名称："));
					for (int p = 0; p < 70 && names[p] != NULL; p++) {
						if (strstr( names[p],s) != NULL) {//包含该字符串
							m = 1;//更改标志位
							i = p;//记录修改位置
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//x
				while (1)
				{
					InputBox(x_s, 20, _T(" 请输入景点坐标X："));
					if (str_to_int(x_s) != -1)
					{
						x = str_to_int(x_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//y
				while (1)
				{
					InputBox(y_s, 20, _T(" 请输入景点坐标Y："));
					if (str_to_int(y_s) != -1)
					{
						y = str_to_int(y_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//j
				while (1)
				{
					InputBox(t, 20, _T(" 请输入终点的地点名称："));
					for (int p = 0; p < 70 && names[p] != NULL; p++) {
						if (strstr(names[p],t) != NULL) {//包含该字符串
							m = 1;//更改标志位
							j = p;//记录直达位置
							break;
						}
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "未查找到！\n请确认输入是否正确或完整", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//dis
				while (1)
				{
					InputBox(dis_s, 20, _T(" 请输入距离："));
					if (str_to_int(dis_s) != -1)
					{
						dis = str_to_int(dis_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//vie
				while (1)
				{
					
					InputBox(vie_s, 20, _T(" 请输入沿路风景满意度："));
					if (str_to_int(vie_s) != -1)
					{
						vie = str_to_int(vie_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;//sha
				while (1)
				{
					InputBox(sha_s, 20, _T(" 请输入沿路林荫满意度："));
					if (str_to_int(sha_s) != -1)
					{
						sha = str_to_int(sha_s);//字符转换
						m = 1;
					}
					if (m == 0)
					{
						IMAGE hh;
						loadimage(&hh, "错.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &hh);
						Sleep(350);//ms
						IMAGE kk;
						loadimage(&kk, "得意.jpg", 399 / 3.5, 399 / 3.5);
						putimage(720, 0, &kk);
						HWND hnd = GetHWnd();
						MessageBox(hnd, "输入格式错误", "提示", MB_OKCANCEL);
					}
					else
						break;
				}
				m = 0;
				names[i] = s;//记录数据
				coor_x[i] = x;
				coor_y[i] = y;
				distance[i][j] = dis;
				distance[j][i] = dis;
				view[i][j] = vie;
				view[j][i] = vie;
				shade[i][j] = sha;
				shade[j][i] = sha;
				write_names();//写入文件
				write_coor_x();
				write_coor_y();
				distance_write_file();
				view_write_file();
				shade_write_file();
			}
			//主页地图
			if (msg.x > 0 && msg.x < 170 && msg.y>0 && msg.y < 110)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				cleardevice();
				home();
			}
			//重置数据
			if (msg.x > 100 && msg.x < 200 && msg.y>0 && msg.y < 60)
			{
				IMAGE pp;
				loadimage(&pp, "对.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &pp);
				Sleep(350);//ms
				IMAGE qq;
				loadimage(&qq, "得意.jpg", 399 / 3.5, 399 / 3.5);
				putimage(720, 0, &qq);
				reset();
			}
			break;
		}
	}
}
void reset()
{
	name_Init();//初始化
	write_names();//写入文件
	coor_Init();
	write_coor_x();
	write_coor_y();
	distance_Init();
	distance_write_file();
	view_Init();
	view_write_file();
	shade_Init();
	shade_write_file();
}
/*文件处理*/
int check_file(const char* filename) {
	FILE* file = fopen(filename, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filename);
		return 0;
	}

	fseek(file, 0, SEEK_END);
	long size = ftell(file);

	fclose(file);

	if (size == 0) {
		printf("文件 %s 为空\n", filename);
		return 0;
	}
	else {
		
		return 1;
	}
}
void name_Init() {
	names[0] = "教师公寓";
	names[1] = "水房";
	names[2] = "安悦公寓";
	names[3] = "安美公寓";
	names[4] = "东升苑";
	names[5] = "建设中";
	names[6] = "逸夫教学楼";
	names[7] = "东区西门";
	names[8] = "东区正门";
	names[9] = "天桥";
	names[10] = "西区东门";
	names[11] = "人工湖";
	names[12] = "北门";
	names[13] = "行政楼";
	names[14] = "大学生活动中心";
	names[15] = "图书馆";
	names[16] = "通院";
	names[17] = "电院";
	names[18] = "自动化院理学院";
	names[19] = "教学A楼";
	names[20] = "教学B楼";
	names[21] = "西邮宾馆";
	names[22] = "创业园区";
	names[23] = "美广";
	names[24] = "医务室";
	names[25] = "浴室";
	names[26] = "小操场";
	names[27] = "大操场";
	names[28] = "篮球场";
	names[29] = "羽毛球";
	names[30] = "旭日苑";
	names[31] = "体育馆";
	names[32] = "超市";
	names[33] = "长思";
	names[34] = "长智";
}
void coor_Init()
{
	coor_x[0] = 146;//教师公寓
	coor_y[0] = 235;
	coor_x[1] = 115 / 1.5;//水房
	coor_y[1] = 628 / 1.5;
	coor_x[2] = 112 / 1.5;//安悦公寓
	coor_y[2] = 745 / 1.5;
	coor_x[3] = 124 / 1.5;//安美公寓
	coor_y[3] = 854 / 1.5;
	coor_x[4] = 267 / 1.5;//东升苑
	coor_y[4] = 611 / 1.5;
	coor_x[5] = 333 / 1.5;//建设中
	coor_y[5] = 730 / 1.5;
	coor_x[6] = 200 / 1.5;//逸夫教学楼
	coor_y[6] = 982 / 1.5;
	coor_x[7] = 374 / 1.5;//东区西门
	coor_y[7] = 578 / 1.5;
	coor_x[8] = 368 / 1.5;//东区正门
	coor_y[8] = 962 / 1.5;
	coor_x[9] = 414 / 1.5;//天桥
	coor_y[9] = 622 / 1.5;
	coor_x[10] = 468 / 1.5;//西区东门
	coor_y[10] = 576 / 1.5;
	coor_x[11] = 600 / 1.5;//人工湖
	coor_y[11] = 710 / 1.5;
	coor_x[12] = 748 / 1.5;//北门
	coor_y[12] = 1093 / 1.5;
	coor_x[13] = 544 / 1.5;//行政楼
	coor_y[13] = 1033 / 1.5;
	coor_x[14] = 388;//大学生活动中心
	coor_y[14] = 550;
	coor_x[15] = 713 / 1.5;//图书馆
	coor_y[15] = 617 / 1.5;
	coor_x[16] = 959 / 1.5;//通院
	coor_y[16] = 714 / 1.5;
	coor_x[17] = 930 / 1.5;//电院
	coor_y[17] = 778 / 1.5;
	coor_x[18] = 916 / 1.5;//自动化院理学院
	coor_y[18] = 856 / 1.5;
	coor_x[19] = 877 / 1.5;//教学A楼
	coor_y[19] = 995 / 1.5;
	coor_x[20] = 848 / 1.5;//教学B楼
	coor_y[20] = 933 / 1.5;
	coor_x[21] = 975 / 1.5;//西邮宾馆
	coor_y[21] = 1080 / 1.5;
	coor_x[22] = 946 / 1.5;//创业园区
	coor_y[22] = 631 / 1.5;
	coor_x[23] = 993 / 1.5;//美广
	coor_y[23] = 387 / 1.5;
	coor_x[24] = 994 / 1.5;//医务室
	coor_y[24] = 505 / 1.5;
	coor_x[25] = 1023 / 1.5;//浴室
	coor_y[25] = 630 / 1.5;
	coor_x[26] = 855 / 1.5;//小操场
	coor_y[26] = 392 / 1.5;
	coor_x[27] = 551 / 1.5;//大操场
	coor_y[27] = 423 / 1.5;
	coor_x[28] = 860 / 1.5;//篮球场
	coor_y[28] = 495 / 1.5;
	coor_x[29] = 651 / 1.5;//羽毛球
	coor_y[29] = 481 / 1.5;
	coor_x[30] = 770 / 1.5;//旭日苑
	coor_y[30] = 137 / 1.5;
	coor_x[31] = 651 / 1.5;//体育馆
	coor_y[31] = 372 / 1.5;
	coor_x[32] = 749 / 1.5;//超市
	coor_y[32] = 63 / 1.5;
	coor_x[33] = 558 / 1.5;//长思
	coor_y[33] = 163 / 1.5;
	coor_x[34] = 947 / 1.5;//长智
	coor_y[34] = 169 / 1.5;
}
void write_names() {
	FILE* file = fopen(filenames, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filenames);
		return;
	}

	for (int i = 0; i < get_names(names); i++) {
		fprintf(file, "%s\n", names[i]);
	}

	fclose(file);
}
void write_coor_x() {
	FILE* file = fopen(filecoor_x, "wb"); // 打开文件以二进制写入模式
	if (file == NULL) {
		// 文件不存在时创建文件
		file = fopen(filecoor_x, "wb+");
		if (file == NULL) {
			printf("无法创建文件：%s\n", filecoor_x);
			return;
		}
	}

	fwrite(coor_x, sizeof(int), get_names(names), file); // 将数组写入文件

	fclose(file); // 关闭文件
}
void write_coor_y() {
	FILE* file = fopen(filecoor_y, "wb"); // 打开文件以二进制写入模式
	if (file == NULL) {
		// 文件不存在时创建文件
		file = fopen(filecoor_y, "wb+");
		if (file == NULL) {
			printf("无法创建文件：%s\n", filecoor_y);
			return;
		}
	}

	fwrite(coor_y, sizeof(int), get_names(names), file); // 将数组写入文件

	fclose(file); // 关闭文件
}
void read_names() {
	FILE* file = fopen(filenames, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", filenames);
		return;
	}

	char buffer[70];  // 假设每行最多70个字符

	for (int i = 0; i < get_names(names); i++) {
		if (fgets(buffer, sizeof(buffer), file) != NULL) {
			int len = strlen(buffer);
			if (len > 0 && buffer[len - 1] == '\n') {
				buffer[len - 1] = '\0';  // 去除换行符
			}
			names[i] = strdup(buffer);
		}
	}

	fclose(file);
}
void read_coor_x() {
	FILE* file = fopen(filecoor_x, "rb"); // 打开文件以二进制读取模式
	if (file == NULL) {
		printf("无法打开文件：%s\n", filecoor_x);
		return;
	}

	fread(coor_x, sizeof(int), get_names(names), file); // 从文件中读取数组

	fclose(file); // 关闭文件
}
void read_coor_y() {
	FILE* file = fopen(filecoor_y, "rb"); // 打开文件以二进制读取模式
	if (file == NULL) {
		printf("无法打开文件：%s\n", filecoor_y);
		return;
	}

	fread(coor_y, sizeof(int), get_names(names), file); // 从文件中读取数组

	fclose(file); // 关闭文件
}
void distance_Init()
{
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			distance[i][j] = INF;
		}
	}
	distance[教师公寓][东升苑] = 57;
	distance[水房][东升苑] = 22;
	distance[水房][安悦公寓] = 125;
	distance[安悦公寓][建设中] = 22;
	distance[安悦公寓][安美公寓] = 93;
	distance[安悦公寓][水房] = 125;
	distance[安美公寓][安悦公寓] = 93;
	distance[安美公寓][逸夫教学楼] = 63;
	distance[逸夫教学楼][东区正门] = 25;
	distance[逸夫教学楼][安美公寓] = 63;
	distance[东区西门][天桥] = 28;
	distance[东区西门][东升苑] = 32;
	distance[东升苑][教师公寓] = 57;
	distance[东升苑][水房] = 22;
	distance[东升苑][东区西门] = 32;
	distance[东区正门][逸夫教学楼] = 25;
	distance[建设中][安悦公寓] = 22;
	distance[天桥][东区西门] = 32;
	distance[天桥][西区东门] = 28;
	distance[西区东门][天桥] = 28;
	distance[西区东门][图书馆] = 228;
	distance[图书馆][西区东门] = 228;
	distance[人工湖][图书馆] = 45;
	distance[图书馆][人工湖] = 45;
	distance[人工湖][大学生活动中心] = 100;
	distance[大学生活动中心][人工湖] = 100;
	distance[大学生活动中心][行政楼] = 75;
	distance[行政楼][大学生活动中心] = 75;
	distance[行政楼][北门] = 114;
	distance[北门][行政楼] = 114;
	distance[北门][西邮宾馆] = 100;
	distance[西邮宾馆][北门] = 100;
	distance[西邮宾馆][教学A楼] = 73;
	distance[教学A楼][西邮宾馆] = 73;
	distance[教学A楼][教学B楼] = 65;
	distance[教学B楼][教学A楼] = 65;
	distance[教学B楼][自动化院理学院] = 103;
	distance[自动化院理学院][教学B楼] = 103;
	distance[自动化院理学院][电院] = 67;
	distance[电院][自动化院理学院] = 67;
	distance[电院][通院] = 67;
	distance[通院][电院] = 67;
	distance[通院][图书馆] = 180;
	distance[图书馆][通院] = 180;
	distance[自动化院理学院][大学生活动中心] = 219;
	distance[大学生活动中心][自动化院理学院] = 219;
	distance[图书馆][创业园区] = 241;
	distance[创业园区][图书馆] = 241;
	distance[创业园区][通院] = 52;
	distance[通院][创业园区] = 52;
	distance[创业园区][浴室] = 20;
	distance[浴室][创业园区] = 20;
	distance[浴室][医务室] = 50;
	distance[医务室][浴室] = 50;
	distance[医务室][创业园区] = 50;
	distance[创业园区][医务室] = 50;
	distance[医务室][篮球场] = 80;
	distance[篮球场][医务室] = 80;
	distance[医务室][美广] = 50;
	distance[美广][医务室] = 50;
	distance[小操场][美广] = 50;
	distance[美广][小操场] = 50;
	distance[美广][长智] = 76;
	distance[长智][美广] = 76;
	distance[小操场][篮球场] = 30;
	distance[篮球场][小操场] = 30;
	distance[小操场][旭日苑] = 100;
	distance[旭日苑][小操场] = 100;
	distance[篮球场][羽毛球] = 200;
	distance[羽毛球][篮球场] = 200;
	distance[羽毛球][大操场] = 50;
	distance[大操场][羽毛球] = 50;
	distance[体育馆][羽毛球] = 50;
	distance[羽毛球][体育馆] = 50;
	distance[体育馆][大操场] = 20;
	distance[大操场][体育馆] = 20;
	distance[大操场][长思] = 88;
	distance[长思][大操场] = 88 ;
	distance[体育馆][长思] = 88;
	distance[长思][体育馆] = 88;
	distance[长思][超市] = 67;
	distance[超市][长思] = 67;
	distance[超市][旭日苑] = 80;
	distance[旭日苑][超市] = 80;
	distance[长智][超市] = 67;
	distance[超市][长智] = 67;
}//
void distance_write_file() {
	FILE* file = fopen(FILE_DISTANCE, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_DISTANCE);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fprintf(file, "%d ", distance[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
void distance_read_file() {
	FILE* file = fopen(FILE_DISTANCE, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_DISTANCE);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fscanf(file, "%d", &distance[i][j]);
		}
	}

	fclose(file);
}
void view_Init()
{
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			view[i][j] = INF;
		}
	}
	view[教师公寓][东升苑] = 57;
	view[水房][东升苑] = 40;
	view[水房][安悦公寓] = 125;
	view[安悦公寓][建设中] = 22;
	view[安悦公寓][安美公寓] = 93;
	view[安悦公寓][水房] = 125;
	view[安美公寓][安悦公寓] = 93;
	view[安美公寓][逸夫教学楼] = 63;
	view[逸夫教学楼][东区正门] = 25;
    view[逸夫教学楼][安美公寓] = 63;
	view[东区西门][天桥] = 28;
	view[东区西门][东升苑] = 32;
	view[东升苑][教师公寓] = 57;
	view[东升苑][水房] = 40;
	view[东升苑][东区西门] = 32;
	view[东区正门][逸夫教学楼] = 25;
	view[建设中][安悦公寓] = 22;
	view[天桥][东区西门] = 32;
	view[天桥][西区东门] = 28;
	view[西区东门][天桥] = 28;
	view[西区东门][图书馆] = 30;
	view[图书馆][西区东门] = 30;
	view[人工湖][图书馆] = 45;
	view[图书馆][人工湖] = 45;
	view[人工湖][大学生活动中心] = 55;
	view[大学生活动中心][人工湖] = 55;
	view[大学生活动中心][行政楼] = 95;
	view[行政楼][大学生活动中心] = 95;
	view[行政楼][北门] = 88;
	view[北门][行政楼] = 88;
	view[北门][西邮宾馆] = 160;
	view[西邮宾馆][北门] = 160;
	view[西邮宾馆][教学A楼] = 43;
	view[教学A楼][西邮宾馆] = 43;
	view[教学A楼][教学B楼] = 65;
	view[教学B楼][教学A楼] = 65;
	view[教学B楼][自动化院理学院] = 103;
	view[自动化院理学院][教学B楼] = 103;
	view[自动化院理学院][电院] = 67;
	view[电院][自动化院理学院] = 67;
	view[电院][通院] = 99;
	view[通院][电院] = 99;
	view[通院][图书馆] = 180;
	view[图书馆][通院] = 180;
	view[自动化院理学院][大学生活动中心] = 21;
	view[大学生活动中心][自动化院理学院] = 21;
	view[图书馆][创业园区] = 41;
	view[创业园区][图书馆] = 41;
	view[创业园区][通院] = 52;
	view[通院][创业园区] = 52;
	view[创业园区][浴室] = 20;
	view[浴室][创业园区] = 20;
	view[浴室][医务室] = 90;
	view[医务室][浴室] = 90;
	view[医务室][创业园区] = 50;
	view[创业园区][医务室] = 50;
	view[医务室][篮球场] = 80;
	view[篮球场][医务室] = 80;
	view[医务室][美广] = 50;
	view[美广][医务室] = 50;
	view[小操场][美广] = 50;
	view[美广][小操场] = 50;
	view[美广][长智] = 76;
	view[长智][美广] = 76;
	view[小操场][篮球场] = 30;
	view[篮球场][小操场] = 30;
	view[小操场][旭日苑] = 150;
	view[旭日苑][小操场] = 150;
	view[篮球场][羽毛球] = 200;
	view[羽毛球][篮球场] = 200;
	view[羽毛球][大操场] = 50;
	view[大操场][羽毛球] = 50;
	view[体育馆][羽毛球] = 50;
	view[羽毛球][体育馆] = 50;
	view[体育馆][大操场] = 20;
	view[大操场][体育馆] = 20;
	view[大操场][长思] = 88;
	view[长思][大操场] = 88;
	view[体育馆][长思] = 88;
	view[长思][体育馆] = 88;
	view[长思][超市] = 20;
	view[超市][长思] = 20;
	view[超市][旭日苑] = 45;
	view[旭日苑][超市] = 45;
	view[长智][超市] = 10;
	view[超市][长智] = 10;
}
void view_write_file() {
	FILE* file = fopen(FILE_VIEW, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_VIEW);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fprintf(file, "%d ", view[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
void view_read_file() {
	FILE* file = fopen(FILE_VIEW, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_VIEW);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fscanf(file, "%d", &view[i][j]);
		}
	}

	fclose(file);
}
void shade_Init()
{
	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			shade[i][j] = INF;
		}
	}
	shade[教师公寓][东升苑] = 57;
	shade[水房][东升苑] = 20;
	shade[水房][安悦公寓] = 15;
	shade[安悦公寓][建设中] = 22;
	shade[安悦公寓][安美公寓] = 93;
	shade[安悦公寓][水房] = 15;
	shade[安美公寓][安悦公寓] = 93;
	shade[安美公寓][逸夫教学楼] = 99;
	shade[逸夫教学楼][东区正门] = 25;
	shade[逸夫教学楼][安美公寓] = 99;
	shade[东区西门][天桥] = 28;
	shade[东区西门][东升苑] = 32;
	shade[东升苑][教师公寓] = 57;
	shade[东升苑][水房] = 20;
	shade[东升苑][东区西门] = 32;
	shade[东区正门][逸夫教学楼] = 25;
	shade[建设中][安悦公寓] = 22;
	shade[天桥][东区西门] = 32;
	shade[天桥][西区东门] = 28;
	shade[西区东门][天桥] = 28;
	shade[西区东门][图书馆] = 28;
	shade[图书馆][西区东门] = 28;
	shade[人工湖][图书馆] = 70;
	shade[图书馆][人工湖] = 70;
	shade[人工湖][大学生活动中心] = 10;
	shade[大学生活动中心][人工湖] = 10;
	shade[大学生活动中心][行政楼] = 95;
	shade[行政楼][大学生活动中心] = 95;
	shade[行政楼][北门] = 140;
	shade[北门][行政楼] = 140;
	shade[北门][西邮宾馆] = 160;
	shade[西邮宾馆][北门] = 160;
	shade[西邮宾馆][教学A楼] = 13;
	shade[教学A楼][西邮宾馆] = 13;
	shade[教学A楼][教学B楼] = 65;
	shade[教学B楼][教学A楼] = 65;
	shade[教学B楼][自动化院理学院] = 103;
	shade[自动化院理学院][教学B楼] = 103;
	shade[自动化院理学院][电院] = 97;
	shade[电院][自动化院理学院] = 97;
	shade[电院][通院] = 27;
	shade[通院][电院] = 27;
	shade[通院][图书馆] = 10;
	shade[图书馆][通院] = 10;
	shade[自动化院理学院][大学生活动中心] = 29;
	shade[大学生活动中心][自动化院理学院] = 29;
	shade[图书馆][创业园区] = 44;
	shade[创业园区][图书馆] = 44;
	shade[创业园区][通院] = 32;
	shade[通院][创业园区] = 32;
	shade[创业园区][浴室] = 120;
	shade[浴室][创业园区] = 120;
	shade[浴室][医务室] = 50;
	shade[医务室][浴室] = 50;
	shade[医务室][创业园区] = 150;
	shade[创业园区][医务室] = 150;
	shade[医务室][篮球场] = 89;
	shade[篮球场][医务室] = 89;
	shade[医务室][美广] = 20;
	shade[美广][医务室] = 20;
	shade[小操场][美广] = 50;
	shade[美广][小操场] = 50;
	shade[美广][长智] = 36;
	shade[长智][美广] = 36;
	shade[小操场][篮球场] = 30;
	shade[篮球场][小操场] = 30;
	shade[小操场][旭日苑] = 100;
	shade[旭日苑][小操场] = 100;
	shade[篮球场][羽毛球] = 20;
	shade[羽毛球][篮球场] = 20;
	shade[羽毛球][大操场] = 150;
	shade[大操场][羽毛球] = 150;
	shade[体育馆][羽毛球] = 52;
	shade[羽毛球][体育馆] = 52;
	shade[体育馆][大操场] = 20;
	shade[大操场][体育馆] = 20;
	shade[大操场][长思] = 98;
	shade[长思][大操场] = 98;
	shade[体育馆][长思] = 88;
	shade[长思][体育馆] = 88;
	shade[长思][超市] = 99;
	shade[超市][长思] = 99;
	shade[超市][旭日苑] = 70;
	shade[旭日苑][超市] = 70;
	shade[长智][超市] = 69;
	shade[超市][长智] = 69;
}//
void shade_write_file() {
	FILE* file = fopen(FILE_SHADE, "w");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_SHADE);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fprintf(file, "%d ", shade[i][j]);
		}
		fprintf(file, "\n");
	}

	fclose(file);
}
void shade_read_file() {
	FILE* file = fopen(FILE_SHADE, "r");
	if (file == NULL) {
		printf("无法打开文件 %s\n", FILE_SHADE);
		return;
	}

	int i, j;
	for (i = 0; i < V; i++) {
		for (j = 0; j < V; j++) {
			fscanf(file, "%d", &shade[i][j]);
		}
	}

	fclose(file);
}
/*最短路径*/
int minDistance_distance(int dist[], bool sptSet[]) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}
	return min_index;
}
void dijkstra_distance(int distance[V][V], int src, int dest)
{
	int dist[V]; // 存储从源点到各个顶点的最短距离
	bool sptSet[V]; // 存储已经找到最短路径的顶点
	int parent[V]; // 存储最短路径的父节点
	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		parent[i] = -1;
	}
	dist[src] = 0;
	for (int count = 0; count < V - 1; count++) {
		int u = minDistance_distance(dist, sptSet);
		sptSet[u] = true;
		for (int v = 0; v < V; v++) {
			if (!sptSet[v] && distance[u][v] && dist[u] != INT_MAX && dist[u] + distance[u][v] < dist[v]) {
				dist[v] = dist[u] + distance[u][v];
				parent[v] = u;
			}
		}
	}
	printSolution_distance(dist, parent, src, dest);
}
void printSolution_distance(int dist[], int parent[], int src, int dest) {
	char message[200] = "";
	sprintf(message, "行程:%s->%s\n距离:%dm\n最短路线:", names[src], names[dest], dist[dest]);
	char path[200] = "";
	printPath_distance(parent, dest, path, message);
}
void printPath_distance(int parent[], int j, char path[], char message[]) {
	if (parent[j] == -1) {
		char temp[200] = "";
		strcat(temp, names[j]);
		strcat(temp, path);
		strcat(message, temp);
		HWND hnd = GetHWnd();
		MessageBox(hnd, message, "最短路径信息", MB_OK);
		return;
	}
	char temp[200] = "";
	sprintf(temp, "->%s", names[j]);
	strcat(temp, path);

	setfillcolor(RED); // 设置填充颜色为红色
	setlinestyle(PS_SOLID, 3);
	setlinecolor(RED); // 设置线条颜色为红色
	// 绘制顶点
	for (int i = 0; i < V; i++) {
		fillcircle(coor_x[j], coor_y[j], 5);
	}
	// 绘制最短路径
	line(coor_x[j], coor_y[j], coor_x[parent[j]], coor_y[parent[j]]);

	printPath_distance(parent, parent[j], temp, message);
}
/*林荫路径*/
int minDistance_view(int dist[], bool sptSet[]) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}
void dijkstra_view(int distance[V][V], int src, int dest)
{
	int dist[V]; // 存储从源点到各个顶点的最短距离
	bool sptSet[V]; // 存储已经找到最短路径的顶点
	int parent[V]; // 存储最短路径的父节点

	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		parent[i] = -1;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance_view(dist, sptSet);
		sptSet[u] = true;

		for (int v = 0; v < V; v++) {
			if (!sptSet[v] && distance[u][v] && dist[u] != INT_MAX && dist[u] + distance[u][v] < dist[v]) {
				dist[v] = dist[u] + distance[u][v];
				parent[v] = u;
			}
		}
	}

	printSolution_view(dist, parent, src, dest);
}
void printSolution_view(int dist[], int parent[], int src, int dest) {
	char message[200] = "";
	sprintf(message, "行程:%s->%s\n林荫满意度:%d分\n林荫路线:", names[src], names[dest], dist[dest]);
	char path[200] = "";
	printPath_view(parent, dest, path, message);
}
void printPath_view(int parent[], int j, char path[], char message[]) {
	if (parent[j] == -1) {
		char temp[200] = "";
		strcat(temp, names[j]);
		strcat(temp, path);
		strcat(message, temp);
		HWND hnd = GetHWnd();
		MessageBox(hnd, message, "最短路径信息", MB_OK);
		return;
	}
	char temp[200] = "";
	sprintf(temp, "->%s", names[j]);
	strcat(temp, path);

	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLUE); // 设置线条颜色为蓝色
	line(coor_x[j], coor_y[j], coor_x[parent[j]], coor_y[parent[j]]);// 绘制最短路径

	printPath_view(parent, parent[j], temp, message);
}
/*美景路径*/
int minDistance_shade(int dist[], bool sptSet[]) {
	int min = INT_MAX, min_index;

	for (int v = 0; v < V; v++) {
		if (sptSet[v] == false && dist[v] <= min) {
			min = dist[v];
			min_index = v;
		}
	}

	return min_index;
}
void dijkstra_shade(int distance[V][V], int src, int dest)
{
	int dist[V]; // 存储从源点到各个顶点的最短距离
	bool sptSet[V]; // 存储已经找到最短路径的顶点
	int parent[V]; // 存储最短路径的父节点

	for (int i = 0; i < V; i++) {
		dist[i] = INT_MAX;
		sptSet[i] = false;
		parent[i] = -1;
	}

	dist[src] = 0;

	for (int count = 0; count < V - 1; count++) {
		int u = minDistance_shade(dist, sptSet);
		sptSet[u] = true;

		for (int v = 0; v < V; v++) {
			if (!sptSet[v] && distance[u][v] && dist[u] != INT_MAX && dist[u] + distance[u][v] < dist[v]) {
				dist[v] = dist[u] + distance[u][v];
				parent[v] = u;
			}
		}
	}

	printSolution_shade(dist, parent, src, dest);
}
void printSolution_shade(int dist[], int parent[], int src, int dest) {
	char message[200] = "";
	sprintf(message, "行程:%s->%s\n风景满意度:%d分\n美景路线:", names[src], names[dest], dist[dest]);
	char path[200] = "";
	printPath_shade(parent, dest, path, message);
}
void printPath_shade(int parent[], int j, char path[], char message[]) {
	if (parent[j] == -1) {
		char temp[200] = "";
		strcat(temp, names[j]);
		strcat(temp, path);
		strcat(message, temp);
		HWND hnd = GetHWnd();
		MessageBox(hnd, message, "最短路径信息", MB_OK);
		return;
	}
	char temp[200] = "";
	sprintf(temp, "->%s", names[j]);
	strcat(temp, path);

	setlinestyle(PS_SOLID, 3);
	setlinecolor(BLACK); // 设置线条颜色为黑色
	line(coor_x[j], coor_y[j], coor_x[parent[j]], coor_y[parent[j]]);// 绘制最短路径

	printPath_shade(parent, parent[j], temp, message);
}
/*数据处理*/
int get_names(const char* names[]) {
	int i = 0;
	while (names[i] != NULL) {
		i++;
	}
	if (i == 69) {
		return -1;  // 如果没有为空的位置，返回-1
	}
	return i;
}
void delete_names(const char* names[], int index) {
	int len = 0;
	while (names[len] != NULL) {
		len++;
	}

	if (index >= 0 && index < len) {
		for (int i = index; i < len - 1; i++) {
			names[i] = names[i + 1];
		}
		names[len - 1] = NULL;
	}
}
void delete_distance(int distance[V][V], int index) {
	if (index >= 0 && index < V && index < V) {
		for (int i = index; i < V - 1; i++) {
			for (int j = 0; j < V; j++) {
				distance[i][j] = distance[i + 1][j];
			}
		}

		for (int j = index; j < V - 1; j++) {
			for (int i = 0; i < V; i++) {
				distance[i][j] = distance[i][j + 1];
			}
		}

		distance[V - 1][V - 1] = 0;
	}
}
void delete_view(int view[V][V], int index) {
	if (index >= 0 && index < V && index < V) {
		for (int i = index; i < V - 1; i++) {
			for (int j = 0; j < V; j++) {
				view[i][j] = view[i + 1][j];
			}
		}

		for (int j = index; j < V - 1; j++) {
			for (int i = 0; i < V; i++) {
				view[i][j] = view[i][j + 1];
			}
		}

		view[V - 1][V - 1] = 0;
	}
}
void delete_shade(int shade[V][V], int index) {
	if (index >= 0 && index < V && index < V) {
		for (int i = index; i < V - 1; i++) {
			for (int j = 0; j < V; j++) {
				shade[i][j] = shade[i + 1][j];
			}
		}

		for (int j = index; j < V - 1; j++) {
			for (int i = 0; i < V; i++) {
				shade[i][j] = shade[i][j + 1];
			}
		}

		shade[V - 1][V - 1] = 0;
	}
}
void delete_coor(int arr[],  int index) {
	if (index < 0 || index >= V) {
		printf("无效的索引\n");
		return;
	}

	// 将后续元素前移
	for (int i = index; i < V - 1; i++) {
		arr[i] = arr[i + 1];
	}

	// 最后一个元素置为 0 或者其他默认值
	arr[V - 1] = 0;
}
int str_to_int(const char* str) {
	char* endptr;
	long int num = strtol(str, &endptr, 10);
	if (*endptr != '\0' || num < 0) {
		return -1;
	}
	return (int)num;
}
