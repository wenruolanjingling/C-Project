#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"Winmm.lib") 
#include <conio.h>
#include <windows.h>
#include<graphics.h>
#include<math.h>
#include <time.h>
#define pluze 10//10为pluze
#define pluzeshot 11//11为杀手射击
#define pluzeshot2 12//12为死神射击
#define PI 3.1415926535
float mouse_x, mouse_y;
int x_pluze, y_pluze;       //杀手的坐标
int x_pluze2, y_pluze2;		//死神的坐标
int map[1600][3200];//地图数组
int map_x, map_y;//地图上的x，y
int clip = 0;
int game = 1;
int clip1 = 0;
int p;//变量
int temp;//调整杀手的状态
int state;//调整死神的状态
int touch = 0;
int v = 10;//杀手子弹速度
int v_s = 6;//杀手手雷速度
int boom;
double v_x[1000];//子弹水平方向速度
double v_y[1000];//子弹竖直方向速度
int i_bullet = 0;//杀手子弹编号
int bullet_x[1000], bullet_y[1000];//死神子弹位置
int bullet_x2[1000], bullet_y2[1000];//死神右子弹位置
int bullet_x3[1000], bullet_y3[1000];//死神下子弹位置
int kind;
int v2 = 20;                   //死神子弹速度
float hp_pluze = 100;           //杀手生命值
float hp_buck = 100;           //死神生命值
int z, shoot;                 //1子弹的方向
int shoulei_pluze = 2;
int shoulei_buck = 2;//手雷数量
double vs_x[50];
double vs_y[50];//手雷速度
int shoulei_x[50];
int shoulei_y[50];//手雷当前位置
int i_shoulei = 0;//手雷编号
int x_pr[50], y_pr[50];//手雷初始位置
int p_gun1 = 1;//记录枪声1
int p_gun2 = 1;//记录枪声2
int p_shoulei = 1;//记录雷声音
IMAGE imgpluze1, imgpluze2;    //枪手1
IMAGE imgpluze1_M, imgpluze2_M;
IMAGE imgmanblue1, imgmanblue;    //枪手2
IMAGE imgmanblue1_M, imgmanblue_M;
IMAGE imgbullet1;  //左子弹
IMAGE imgbullet_M1;
IMAGE img_wall;
IMAGE imgbullet2;  //右子弹
IMAGE imgbullet_M2;
IMAGE imgbullet3;  //上子弹
IMAGE imgbullet_M3;
IMAGE imgbullet4;  //下子弹
IMAGE imgbullet_M4;
IMAGE imgpluze1shot, imgpluze1shot_M;
IMAGE imgpluze2shot, imgpluze2shot_M;
IMAGE imgpluze3shot, imgpluze3shot_M;
IMAGE imgpluze4shot, imgpluze4shot_M;   //不同方向射击图和掩码图
IMAGE imgbullet, imgbullet_M;      //子弹图和掩码图
IMAGE imgpluzeui;
IMAGE imgbuckui;                 //ui图片
IMAGE imghp;                    //血条
IMAGE imggun;                  //枪
IMAGE imgshoulei, imgshoulei_m;//手雷图片
IMAGE imgboom, imgboom_mask;//爆炸图片
IMAGE imgbk;                //开始画面背景图
IMAGE imgwin1, imgwin2;     //结尾胜利图
IMAGE imgvs,imgb;
IMAGE imgsishen,imgshashou,imgkuang;//加载剧情死神杀手对话框
IMAGE imgabout;//加载制作人信息
MOUSEMSG m;	// 定义鼠标消息
int speed;
time_t start, stop;//计时器
void startup()                       // 数据初始化，显示画面
{
	speed = 4;//速度
	temp = pluze;                    //杀手一开始不持枪状态
	state = pluze - 1;
	x_pluze = 1450;
	y_pluze = 700;                   //杀手初始位置
	x_pluze2 = 100;
	y_pluze2 = 100;                  //死神初始位置
	map[y_pluze][x_pluze] = pluze;   //杀手位置
	map[x_pluze2][y_pluze2] = 9;     //死神位置
	loadimage(&img_wall, _T("demon.jpg"));        //加载障碍物图片
	loadimage(&imgpluze1, _T("杀手收枪.jpg"));    //加载杀手收枪图
	loadimage(&imgpluze1_M, _T("杀手收枪_mask.jpg"));//加载杀手收枪的掩码图
	loadimage(&imgmanblue1, _T("死神收枪.jpg"));//加载死神收枪图
	loadimage(&imgmanblue1_M, _T("死神收枪_mask.jpg"));//加载死神收枪的掩码图
	loadimage(&imgbullet1, _T("zidanl.jpg"));//加载子弹图左方向射击
	loadimage(&imgbullet_M1, _T("zidanl_mask.jpg"));//加载子弹图左方向射击的掩码图
	loadimage(&imgbullet2, _T("zidanr.jpg"));//加载子弹图右方向射击
	loadimage(&imgbullet_M2, _T("zidanr_mask.jpg"));//加载子弹图右方向射击的掩码图
	loadimage(&imgbullet3, _T("zidanu.jpg"));//加载子弹图上方向射击
	loadimage(&imgbullet_M3, _T("zidanu_mask.jpg"));//加载子弹图上方向射击的掩码图
	loadimage(&imgbullet4, _T("zidand.jpg"));//加载子弹图下方向射击
	loadimage(&imgbullet_M4, _T("zidand_mask.jpg"));//加载子弹图下方向射击的掩码图
	loadimage(&imgbullet, _T("绿子弹.jpg"));//加载杀手子弹图
	loadimage(&imgbullet_M, _T("绿子弹_mask1.jpg"));//加载杀手子弹图的掩码图
	loadimage(&imgpluze1shot, _T("杀手掏枪.jpg"));//加载杀手掏枪图
	loadimage(&imgpluze1shot_M, _T("杀手掏枪_mask.jpg"));//加载杀手掏枪图的掩码图
	loadimage(&imgpluze3shot, _T("死神掏枪.jpg"));//加载死神掏枪图
	loadimage(&imgpluze3shot_M, _T("死神掏枪_mask.jpg"));//加载死神掏枪图的掩码图
	loadimage(&imgpluzeui, _T("杀手血条.jpg"));//加载杀手的血条图
	loadimage(&imgbuckui, _T("死神血条.jpg"));//加载死神的血条图
	loadimage(&imghp, _T("小红瓶.jpg"));//加载补血道具图
	loadimage(&imggun, _T("小蓝瓶.jpg"));//加载增加手雷道具图
	loadimage(&imgshoulei, _T("野猪怪物.jpg"));//加载手雷图
	loadimage(&imgshoulei_m, _T("野猪怪物_mask.jpg"));//加载手雷图的掩码图
	loadimage(&imgboom, _T("boom.jpg"));//加载爆炸特效图
	loadimage(&imgboom_mask, _T("boom_mask.jpg"));//加载爆炸特效图的掩码图
	loadimage(&imgbk, _T("bk1.jpg"));//加载开始界面背景图
	loadimage(&imgwin1, _T("死神final.jpg"));//加载死神胜利图
	loadimage(&imgwin2, _T("杀手final.jpg"));//加载杀手胜利图 
	loadimage(&imgsishen,_T("死神win1.jpg"));//加载剧情死神图
	loadimage(&imgshashou,_T("杀手win1.jpg"));//加载剧情杀手图
	loadimage(&imgkuang,_T("对话框.jpg"));//加载对话框
	loadimage(&imgvs,_T("死神拔枪.jpg"));
	loadimage(&imgb,_T("枪.jpg"));
	loadimage(&imgabout,_T("about.jpg"));//加载制作人信息图
	mciSendString(_T("open 骑士bgm.mp3 alias bgm"),NULL,0,NULL);
	mciSendString(_T("open py.mp3 alias gun1"), NULL, 0, NULL);
	mciSendString(_T("open py.mp3 alias gun2"), NULL, 0, NULL);
	mciSendString(_T("open 枪声2.mp3 alias gun1_2"), NULL, 0, NULL);
	mciSendString(_T("open 枪声2.mp3 alias gun2_2"), NULL, 0, NULL);
	mciSendString(_T("open 多声爆炸.mp3 alias shoulei"), NULL, 0, NULL);
	mciSendString(_T("open 多声爆炸.mp3 alias shoulei_2"), NULL, 0, NULL);   //加载背景音乐和音效
	mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
	time_t t;//计时器
	srand((unsigned)time(&t));
	for (map_y = 100; map_y <= 700; map_y = map_y + 50)
		for (map_x = 100; map_x <= 1400; map_x = map_x + 50)
		{
			map[map_y][map_x] = rand() % 50;
			if ((map[map_y][map_x] < 48) && (map[map_y][map_x] > 30))
				map[map_y][map_x] = 1;
			else if ((map[map_y][map_x] <= 30) && (map[map_y][map_x] >= 0))
				map[map_y][map_x] = 0;
			else if (map[map_y][map_x] == 48)
				map[map_y][map_x] = 103;           //hp
			else if (map[map_y][map_x] == 49)
				map[map_y][map_x] = 104;//gun
		}                                          //用来调整随机生成障碍，炸弹，血瓶比例
	for (map_y = 100; map_y <= 700; map_y = map_y + 50)
		for (map_x = 100; map_x <= 1400; map_x = map_x + 50)
		{
			if ((map[map_y - 50][map_x] == 1) && (map[map_y][map_x - 50] == 1))
				map[map_y][map_x] = 1;
		}                                           //防止生成bug地形
}

void show()  // 控制人物和子弹状态
{
	int i, j;
	while (MouseHit())    //自动收枪
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)  //按下鼠标左键
		{

			if (p_gun1 == 1)
			{
				mciSendString(_T("close gun1 "), NULL, 0, NULL);
				mciSendString(_T("open .\\杀手枪声.mp3 alias gun1"), NULL, 0, NULL);
				mciSendString(_T("play gun1 "), NULL, 0, NULL);
				p_gun1 = 2;
			}
			else if (p_gun1 == 2)
			{
				mciSendString(_T("close gun1_2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\杀手枪声.mp3 alias gun1_2"), NULL, 0, NULL);
				mciSendString(_T("play gun1_2 "), NULL, 0, NULL);
				p_gun1 = 1;
			}                          //连续射击时枪声不断
			temp = pluzeshot;          //杀手改变状态，变为持枪
			start = time(NULL);
			bullet_x[i_bullet] = x_pluze + 5;
			bullet_y[i_bullet] = y_pluze + 5;
			map[bullet_y[i_bullet]][bullet_x[i_bullet]] = 20;
			v_x[i_bullet] = v * abs(m.x - x_pluze - 5) / sqrt(pow((m.y - y_pluze - 5),2)+pow((m.x - x_pluze - 5),2));
			v_y[i_bullet] = v * abs(m.y - y_pluze - 5) / sqrt(pow((m.y - y_pluze - 5),2)+pow((m.x - x_pluze - 5),2));
			if (abs(m.y - y_pluze - 5) / abs(m.x - x_pluze - 5) == 1)
			{
				v_x[i_bullet] = 10;
				v_y[i_bullet] = 10;
			}
			if (m.x < x_pluze + 5)
				v_x[i_bullet] = -v_x[i_bullet];
			if (m.y < y_pluze + 5)
				v_y[i_bullet] = -v_y[i_bullet];
			i_bullet++;
		}                             //根据鼠标位置定义子弹x，y速度
		if (m.uMsg != WM_LBUTTONDOWN)
			stop = time(NULL);
		if (stop - start >= 1)
			temp = pluze;
		if (m.uMsg == WM_MOUSEMOVE)
		{
			mouse_x = m.x;
			mouse_y = m.y;            //获取鼠标坐标
		}
		if ((m.uMsg == WM_RBUTTONDOWN) && (shoulei_pluze>0))
		{
			if (p_shoulei == 1)
			{
			
				mciSendString(_T("close shoulei "), NULL, 0, NULL);
				mciSendString(_T("open .\\多声爆炸.mp3 alias shoulei"), NULL, 0, NULL);
				mciSendString(_T("play shoulei "), NULL, 0, NULL);
				p_shoulei = 2;
			}
			else if (p_shoulei == 2)
			{
				mciSendString(_T("close shoueli_2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\多声爆炸.mp3 alias shoulei_2"), NULL, 0, NULL);
				mciSendString(_T("play shoulei_2 "), NULL, 0, NULL);
				p_shoulei = 1;
			}                         //加载手雷音效
			x_pr[i_shoulei] = x_pluze + 5;
			y_pr[i_shoulei] = y_pluze + 5;
			shoulei_x[i_shoulei] = x_pluze + 5;
			shoulei_y[i_shoulei] = y_pluze + 5;
			map[shoulei_y[i_shoulei]][shoulei_x[i_shoulei]] = 105;
			vs_x[i_shoulei] = v * abs(m.x - x_pluze - 5) / sqrt(pow(abs(m.y - y_pluze - 5),2)+pow(abs(m.x - x_pluze - 5),2));
			vs_y[i_shoulei] = v * abs(m.y - y_pluze - 5) / sqrt(pow(abs(m.y - y_pluze - 5),2)+pow(abs(m.x - x_pluze - 5),2));
			if (abs(m.y - y_pluze - 5) / abs(m.x - x_pluze - 5) == 1)
			{
				vs_x[i_shoulei] =10;
				vs_y[i_shoulei] =10;
			}
			if (m.x < x_pluze + 5)
				vs_x[i_shoulei] = -vs_x[i_shoulei];
			if (m.y < y_pluze + 5)
				vs_y[i_shoulei] = -vs_y[i_shoulei];
			i_shoulei++;
			shoulei_pluze--;
		}
	}                                  //控制不同方向子弹的速度一致


	if (mouse_y < y_pluze + 60)
		                              
	{
		rotateimage(&imgpluze2, &imgpluze1, PI / 2 + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2_M, &imgpluze1_M, PI / 2 + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2shot, &imgpluze1shot, PI / 2 + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2shot_M, &imgpluze1shot_M, PI / 2 + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
	}
	else if ((mouse_y == y_pluze + 60) && (x_pluze + 58 > mouse_x))
	{
		rotateimage(&imgpluze2, &imgpluze1, PI / 2 + PI / 2, WHITE);
		rotateimage(&imgpluze2_M, &imgpluze1_M, PI / 2 + PI / 2, WHITE);
		rotateimage(&imgpluze2shot, &imgpluze1shot, PI / 2 + PI / 2, WHITE);
		rotateimage(&imgpluze2shot_M, &imgpluze1shot_M, PI / 2 + PI / 2, WHITE);
	}
	else if ((mouse_y == y_pluze + 60) && (x_pluze + 58 < mouse_x))
	{
		rotateimage(&imgpluze2, &imgpluze1, PI / 2 + PI * 3 / 2, WHITE);
		rotateimage(&imgpluze2_M, &imgpluze1_M, PI / 2 + PI * 3 / 2, WHITE);
		rotateimage(&imgpluze2shot, &imgpluze1shot, PI / 2 + PI * 3 / 2, WHITE);
		rotateimage(&imgpluze2shot_M, &imgpluze1shot_M, PI / 2 + PI * 3 / 2, WHITE);
	}
	else if ((mouse_y == y_pluze + 60) && (x_pluze + 58 == mouse_x))
	{
		rotateimage(&imgpluze2, &imgpluze1, PI / 2, WHITE);
		rotateimage(&imgpluze2_M, &imgpluze1_M, PI / 2, WHITE);
		rotateimage(&imgpluze2shot, &imgpluze1shot, PI / 2, WHITE);
		rotateimage(&imgpluze2shot_M, &imgpluze1shot_M, PI / 2, WHITE);
	}
	else
	{
		rotateimage(&imgpluze2, &imgpluze1, PI / 2 + PI + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2_M, &imgpluze1_M, PI / 2 + PI + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2shot, &imgpluze1shot, PI / 2 + PI + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
		rotateimage(&imgpluze2shot_M, &imgpluze1shot_M, PI / 2 + PI + atan((x_pluze + 58 - mouse_x) / (y_pluze + 60 - mouse_y)), WHITE);
	}                                      // 旋转图像 使人物指向鼠标位置
	BeginBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	map[y_pluze2][x_pluze2] = state;
	for (map_y = 0; map_y <= 800; map_y++)     //根据地图数组输出图片
		for (map_x = 0; map_x <= 1600; map_x++)
		{
			touch++;
			if (map[map_y][map_x] == 1)
				putimage(map_x, map_y, &img_wall);   //1为墙
			else if (map[map_y][map_x] == pluze)
			{
				putimage(map_x, map_y, &imgpluze2_M, NOTSRCERASE);
				putimage(map_x, map_y, &imgpluze2, SRCERASE);
			}
			else if (map[map_y][map_x] == pluze - 1)
			{
				putimage(map_x, map_y, &imgmanblue_M, NOTSRCERASE);
				putimage(map_x, map_y, &imgmanblue, SRCERASE);
			}
			else if (map[map_y][map_x] == pluzeshot)
			{
				putimage(map_x, map_y, &imgpluze2shot_M, NOTSRCERASE);
				putimage(map_x, map_y, &imgpluze2shot, SRCERASE);
			}
			else if (map[map_y][map_x] == pluzeshot2)
			{
				putimage(map_x, map_y, &imgpluze4shot_M, NOTSRCERASE);
				putimage(map_x, map_y, &imgpluze4shot, SRCERASE);
			}
			else if (map[map_y][map_x] == 20)
			{
				putimage(map_x, map_y, &imgbullet_M, NOTSRCERASE);
				putimage(map_x, map_y, &imgbullet, SRCERASE);
			}
			else if (map[map_y][map_x] == 5)
			{
				if (kind == 0)
				{
					putimage(map_x, map_y, &imgbullet_M1, NOTSRCERASE);
					putimage(map_x, map_y, &imgbullet1, SRCERASE);
					map[map_y][map_x] = 0;
					if (map_x > 10)
					{
						map[map_y][map_x - v2] = 5;
					}
				}
				else if (kind == 1)
				{
					putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
					putimage(map_x, map_y, &imgshoulei, SRCERASE);     //手雷
					map[map_y][map_x] = 0;
					if (map_x > 10 && map_x>boom)
					{
						map[map_y][map_x - v2] = 5;
					}
					if (boom >= 128)
					{
						if (map_x< boom)
						{
							map[map_y - 128][map_x - 128] = 106;
							for (i = map_y - 100; i<map_y + 80; i++)
								for (j = map_x - 100; j < map_x + 80; j++)
								{
									if (map[i][j] == 1)
										map[i][j] = 0;
									if (map[i][j] == pluze||map[i][j]==pluzeshot)
										hp_pluze -= 15;
								}
						}
					}
				}
			}
			else if (map[map_y][map_x] == 6)
			{
				if (kind == 0)
				{
					putimage(map_x, map_y, &imgbullet_M2, NOTSRCERASE);
					putimage(map_x, map_y, &imgbullet2, SRCERASE);
				}
				else if (kind == 1)
				{
					putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
					putimage(map_x, map_y, &imgshoulei, SRCERASE);    //手雷
				}
			}
			else if (map[map_y][map_x] == 7)
			{
				if (kind == 0)
				{
					putimage(map_x, map_y, &imgbullet_M3, NOTSRCERASE);
					putimage(map_x, map_y, &imgbullet3, SRCERASE);
					map[map_y][map_x] = 0;
					map[map_y][map_x] = 0;
					if (map_y > 50)
					{
						map[map_y - v2][map_x] = 7;
					}
				}
				else if (kind == 1)
				{
					putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
					putimage(map_x, map_y, &imgshoulei, SRCERASE);    //手雷
					map[map_y][map_x] = 0;
					if (map_y > 50 && map_y>boom)
					{
						map[map_y - v2][map_x] = 7;
					}
					if (boom >= 128)
					{
						if (map_y < boom)
						{
							map[map_y - 80][map_x - 80] = 106;
							for (i = map_y - 100; i<map_y + 80; i++)
								for (j = map_x - 100; j < map_x + 80; j++)
								{
									if (map[i][j] == 1)
										map[i][j] = 0;
									if (map[i][j] == pluze||map[i][j]==pluzeshot)
										hp_pluze -= 15;
								}
						}
					}
				}
			}
			else if (map[map_y][map_x] == 8)
			{
				if (kind == 0)
				{
					putimage(map_x, map_y, &imgbullet_M4, NOTSRCERASE);
					putimage(map_x, map_y, &imgbullet4, SRCERASE);
				}
				else if (kind == 1)
				{
					putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
					putimage(map_x, map_y, &imgshoulei, SRCERASE);   //手雷

				}

			}
			else if (map[map_y][map_x] == 100)
			{
				putimage(map_x, map_y, &imgpluzeui);//杀手  ui
			}
			else if (map[map_y][map_x] == 101)
			{
				putimage(map_x, map_y, &imgbuckui);//死神  ui
			}
			else if (map[map_y][map_x] == 103)
			{
				putimage(map_x, map_y, &imghp);//血条
			}
			else if (map[map_y][map_x] == 104)
			{
				putimage(map_x, map_y, &imggun);//枪
			}
			else if (map[map_y][map_x] == 105)
			{
				putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
				putimage(map_x, map_y, &imgshoulei, SRCERASE);//手雷
			}
			else if (map[map_y][map_x] == 106)
			{
				putimage(map_x, map_y, &imgboom_mask, NOTSRCERASE);
				putimage(map_x, map_y, &imgboom, SRCERASE);//手雷爆炸
				if (touch % 10 == 0)
					map[map_y][map_x] = 0;
			}
		}
	setfillcolor(RED);
	fillroundrect(188, 20, 540 - 340 * (1 - hp_buck / 100), 65,20,20);
	fillroundrect(1010 + 340 * (1 - hp_pluze / 100), 20,1350, 65,20,20);//控制血条的长短，收到伤害或者得到血瓶血条在相应的方向上变长或变短
	for (p = 0; p < shoulei_buck; p++)
	{
		putimage(560 + p * 30, 30, &imgshoulei_m, NOTSRCERASE);
		putimage(560 + p * 30, 30, &imgshoulei, SRCERASE);
	}
	for (p = 0; p < shoulei_pluze; p++)
	{
		putimage(970 - 30 * p, 30, &imgshoulei_m, NOTSRCERASE);
		putimage(970 - 30 * p, 30, &imgshoulei, SRCERASE);
	}
	if (game == 0)
	{
		if (hp_buck < hp_pluze)
		{
			putimage(0, 0, &imgwin2);
			_getch();
			system("pause");
		}
		else if (hp_buck > hp_pluze)
		{
			putimage(0, 0, &imgwin1);
			_getch();
			system("pause");
		}
	}
	FlushBatchDraw();
}                         //游戏结尾判断胜利者出现图像

void updateWithoutInput()  // 与用户输入无关的更新
{
	map[0][50] = 101;
	map[0][1000] = 100;//输出ui
	map[y_pluze][x_pluze] = temp;
	map[y_pluze2][x_pluze2] = state;
	int i, j, back, l;//判断碰撞用变量
	int x, y;
	back = 4;
	if (hp_buck <= 0 || hp_pluze <= 0)
		game = 0;
	for (i = y_pluze - 50; i <= y_pluze + 43; i++)
		for (j = x_pluze - 50; j <= x_pluze + 43; j++)
		{
			if (((map[i][j] == 1) || (map[i][j] == 103) || (map[i][j] == 104)) && (i > y_pluze))
			{
				y_pluze -= back;
				map[y_pluze + back][x_pluze] = 0;
			}

			if (((map[i][j] == 1) || (map[i][j] == 103) || (map[i][j] == 104)) && (j > x_pluze))
			{
				x_pluze -= back;
				map[y_pluze][x_pluze + back] = 0;
			}
			if (((map[i][j] == 1) || (map[i][j] == 103) || (map[i][j] == 104)) && (i <= y_pluze))
			{
				y_pluze += back;
				map[y_pluze - back][x_pluze] = 0;
			}
			if (((map[i][j] == 1) || (map[i][j] == 103) || (map[i][j] == 104)) && (j <= x_pluze))
			{
				x_pluze += back;
				map[y_pluze][x_pluze - back] = 0;
			}
		}//碰到墙后退
	for (l = 0; l < 1000; l++)//子弹移动
	{
		if (map[bullet_y[l]][bullet_x[l]] == 20)
		{
			map[bullet_y[l]][bullet_x[l]] = 0;
			bullet_x[l] = bullet_x[l] + v_x[l];
			bullet_y[l] = bullet_y[l] + v_y[l];
			if (bullet_y[l] < 0)
				bullet_y[l] = -bullet_y[l];
			if (bullet_x[l] < 0)
				bullet_x[l] = -bullet_x[l];
			map[bullet_y[l]][bullet_x[l]] = 20;
		}
		if ((bullet_x[l] > 1500) || (bullet_x[l] < 50))
		{
			map[bullet_y[l]][bullet_x[l]] = 0;
		}
		if ((bullet_y[l] > 800) || (bullet_y[l] < 50))
		{
			map[bullet_y[l]][bullet_x[l]] = 0;
		}
	}
	for (l = 0; l < 50; l++)//手雷移动
	{

		if (map[shoulei_y[l]][shoulei_x[l]] == 105)
		{
			map[shoulei_y[l]][shoulei_x[l]] = 0;
			shoulei_x[l] = shoulei_x[l] + vs_x[l];
			shoulei_y[l] = shoulei_y[l] + vs_y[l];
			map[shoulei_y[l]][shoulei_x[l]] = 105;
		}
		if ((shoulei_x[l] > 1500) || (shoulei_x[l] < 50))
		{
			map[shoulei_y[l]][shoulei_x[l]] = 0;
		}
		if ((shoulei_y[l] > 800) || (shoulei_y[l] < 50))
		{
			map[shoulei_y[l]][shoulei_x[l]] = 0;
		}
		if ((abs(shoulei_x[l] - x_pr[l]) > 200) || ((abs(shoulei_y[l] - y_pr[l]) > 200)))
		{
			map[shoulei_y[l] - 100][shoulei_x[l] - 100] = 106;
			map[shoulei_y[l]][shoulei_x[l]] = 0;
			int x1, y1;
			for (y1 = shoulei_y[l] - 100; y1<shoulei_y[l] + 150; y1++)
				for (x1 = shoulei_x[l] - 200; x1 < shoulei_x[l] + 150; x1++)
				{
					if (map[y1][x1] == 1)
						map[y1][x1] = 0;
					if (map[y1][x1] == 9)
						hp_buck = hp_buck - 30;
					if (map[y1][x1] == 12)
						hp_buck = hp_buck - 30;
				}
			vs_x[l] = 0;
			vs_y[l] = 0;
			shoulei_x[l] = x_pr[l];
			shoulei_y[l] = y_pr[l];
		}
	}
	for (l = 0; l < 1000; l++)
	{
		if (map[bullet_y2[l]][bullet_x2[l]] == 6)
		{
			if (kind == 0)
			{
				map[bullet_y2[l]][bullet_x2[l]] = 0;
				bullet_x2[l] += v2;
				map[bullet_y2[l]][bullet_x2[l]] = 6;
			}
			else if (kind == 1)
			{
				if (bullet_x2[l] < boom)
				{
					map[bullet_y2[l]][bullet_x2[l]] = 0;
					bullet_x2[l] += v2;
					map[bullet_y2[l]][bullet_x2[l]] = 6;
				}
				if (boom <= 1450)
				{
					if (bullet_x2[l]>boom)
					{
						map[bullet_y2[l] - 80][bullet_x2[l] - 128] = 106;
						map[bullet_y2[l]][bullet_x2[l]] = 0;
						for (i = bullet_y2[l] - 100; i<bullet_y2[l] + 100; i++)
							for (j = bullet_x2[l] - 100; j < bullet_x2[l] + 100; j++)
							{
								if (map[i][j] == 1)
									map[i][j] = 0;
								if (map[i][j] == pluze||map[i][j]==pluzeshot)
									hp_pluze -= 30;
							}
					}
				}
			}
		}
		if (bullet_x2[l] > 1450)
		{
			map[bullet_y2[l]][bullet_x2[l]] = 0;
		}
	}
	for (l = 0; l < 1000; l++)
	{
		if (map[bullet_y3[l]][bullet_x3[l]] == 8)
		{
			if (kind == 0)
			{
				map[bullet_y3[l]][bullet_x3[l]] = 0;
				bullet_y3[l] += v2;
				map[bullet_y3[l]][bullet_x3[l]] = 8;
			}
			else if (kind == 1)
			{
				if (bullet_y3[l] < boom)
				{
					map[bullet_y3[l]][bullet_x3[l]] = 0;
					bullet_y3[l] += v2;
					map[bullet_y3[l]][bullet_x3[l]] = 8;
				}
				if (boom <= 800)
				{
					if (bullet_y3[l] > boom)
					{
						map[bullet_y3[l] - 80][bullet_x3[l] - 100] = 106;
						map[bullet_y3[l]][bullet_x3[l]] = 0;
						for (i = bullet_y3[l] - 100; i < bullet_y3[l] + 120; i++)
							for (j = bullet_x3[l] - 100; j < bullet_x3[l] + 120; j++)
							{
								if (map[i][j] == 1)
									map[i][j] = 0;
								if (map[i][j] == pluze||map[i][j]==pluzeshot)
									hp_pluze -= 30;
							}
					}
				}
			}
		}
		if (bullet_y3[l] >800)
		{
			map[bullet_y3[l]][bullet_x3[l]] = 0;
		}
	}
	for (i = 100; i <= 700; i = i + 50)//子弹射中墙后墙消失
		for (j = 100; j <= 1400; j = j + 50)
		{
			if (map[i][j] == 1)
			{
				for (y = i - 25; y <= i + 25; y++)
					for (x = j - 25; x < j + 25; x++)
					{
						if (map[y][x] == 20)
						{
							map[i][j] = 0;
							map[y][x] = 0;
							break;
						}
					}
			}
			if (map[i][j] == 103)
			{
				for (y = i - 25; y <= i + 25; y++)
					for (x = j - 25; x < j + 25; x++)
					{
						if (map[y][x] == 20)
						{
							map[i][j] = 0;
							map[y][x] = 0;
							hp_pluze = hp_pluze + 30;
							break;
						}
					}
			}
			if (map[i][j] == 104)
			{
				for (y = i - 25; y <= i + 25; y++)
					for (x = j - 25; x < j + 25; x++)
					{
						if (map[y][x] == 20)
						{
							map[i][j] = 0;
							map[y][x] = 0;
							shoulei_pluze = shoulei_pluze + 1;
							break;
						}
					}
			}
		}//子弹击中wall 
	for (i = y_pluze2 - 25; i<y_pluze2 + 25; i++)
		for (j = x_pluze2 - 25; j < x_pluze2 + 25; j++)
		{
			if (map[i][j] == 20)
			{
				hp_buck = hp_buck - 10;
				map[i][j] = 0;
			}
		}//子弹击中buck
	for (i = 50; i <= 700; i++)
		for (j = 50; j <= 1400; j++)
		{
			if (map[i][j] == 1)
			{
				for (y = i; y <= i + 50; y++)
					for (x = j; x <= j + 50; x++)
					{
						if (map[y][x] == 5 || map[y][x] == 6 || map[y][x] == 7 || map[y][x] == 8)
						{
							if (kind == 0)
							{
								map[i][j] = 0;
								map[y][x] = 0;
								break;
							}
						}
					}
			}
			if (map[i][j] == 103)
			{
				for (y = i; y <= i + 50; y++)
					for (x = j; x < j + 50; x++)
					{
						if (map[y][x] == 5 || map[y][x] == 6 || map[y][x] == 7 || map[y][x] == 8)
						{
							if (kind == 0)
							{
								map[i][j] = 0;
								map[y][x] = 0;
								hp_buck = hp_buck + 30;
								break;
							}
						}
					}
			}
			if (map[i][j] == 104)
			{
				for (y = i; y <= i + 50; y++)
					for (x = j; x < j + 50; x++)
					{
						if (map[y][x] == 5 || map[y][x] == 6 || map[y][x] == 7 || map[y][x] == 8)
						{
							if (kind == 0)
							{
								map[i][j] = 0;
								map[y][x] = 0;
								shoulei_buck++;
								break;
							}
						}
					}
			}
		}
	for (i = 50; i <= 800; i++)
		for (j = 50; j <= 1600; j++)
		{
			if (map[i][j] == pluze||map[i][j]==pluzeshot)
			{
				for (y = i-25; y <= i + 25; y++)
					for (x = j-25; x < j + 25; x++)
					{
						if (map[y][x] == 5 || map[y][x] == 6 || map[y][x] == 7 || map[y][x] == 8)
						{
							if (kind == 0)
							{
								map[y][x] = 0;
								hp_pluze -= 15;
								break;
							}
						}
					}
			}
		}
	if (x_pluze > 1500)//防止出边界
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze = 1500;
	}
	if (x_pluze < 25)
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze = 25;
	}
	if (y_pluze > 775)
	{
		map[y_pluze][x_pluze] = 0;
		y_pluze = 775;
	}
	if (y_pluze < 50)
	{
		map[y_pluze][x_pluze] = 0;
		y_pluze = 50;
	}
	for (i = y_pluze2 - 50; i <= y_pluze2 + 43; i++)
		for (j = x_pluze2 - 50; j <= x_pluze2 + 43; j++)
		{
			if ((map[i][j] == 1) && (i > y_pluze2))
			{
				y_pluze2 -= back;
				map[y_pluze2 + back][x_pluze2] = 0;
			}

			if ((map[i][j] == 1) && (j > x_pluze2))
			{
				x_pluze2 -= back;
				map[y_pluze2][x_pluze2 + back] = 0;
			}
			if ((map[i][j] == 1) && (i <= y_pluze2))
			{
				y_pluze2 += back;
				map[y_pluze2 - back][x_pluze2] = 0;
			}
			if ((map[i][j] == 1) && (j <= x_pluze2))
			{
				x_pluze2 += back;
				map[y_pluze2][x_pluze2 - back] = 0;
			}
			if ((map[i][j] == 103) && (i > y_pluze2))
			{
				y_pluze2 -= back;
				map[y_pluze2 + back][x_pluze2] = 0;
			}

			if ((map[i][j] == 103) && (j > x_pluze2))
			{
				x_pluze2 -= back;
				map[y_pluze2][x_pluze2 + back] = 0;
			}
			if ((map[i][j] == 103) && (i <= y_pluze2))
			{
				y_pluze2 += back;
				map[y_pluze2 - back][x_pluze2] = 0;
			}
			if ((map[i][j] == 103) && (j <= x_pluze2))
			{
				x_pluze2 += back;
				map[y_pluze2][x_pluze2 - back] = 0;
			}
			if ((map[i][j] == 104) && (i > y_pluze2))
			{
				y_pluze2 -= back;
				map[y_pluze2 + back][x_pluze2] = 0;
			}

			if ((map[i][j] == 104) && (j > x_pluze2))
			{
				x_pluze2 -= back;
				map[y_pluze2][x_pluze2 + back] = 0;
			}
			if ((map[i][j] == 104) && (i <= y_pluze2))
			{
				y_pluze2 += back;
				map[y_pluze2 - back][x_pluze2] = 0;
			}
			if ((map[i][j] == 104) && (j <= x_pluze2))
			{
				x_pluze2 += back;
				map[y_pluze2][x_pluze2 - back] = 0;
			}
		}
	if (x_pluze2 > 1500)//防止出边界
	{
		map[y_pluze2][x_pluze2] = 0;
		x_pluze2 = 1500;
	}
	if (x_pluze2 < 25)
	{
		map[y_pluze2][x_pluze2] = 0;
		x_pluze2 = 25;
	}
	if (y_pluze2 > 775)
	{
		map[y_pluze2][x_pluze2] = 0;
		y_pluze2 = 775;
	}
	if (y_pluze2 < 50)
	{
		map[y_pluze2][x_pluze2] = 0;
		y_pluze2 = 50;
	}
}

void updateWithInput()  // 与用户输入有关的更新
{
	int step = speed;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000))    // 左方向键
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze -= step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze][x_pluze - step] = 0;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))  // 右方向键
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze += step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze][x_pluze - step] = 0;
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000))     // 上方向键
	{
		map[y_pluze][x_pluze] = 0;
		y_pluze -= step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze + step][x_pluze] = 0;
	}
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))  // 下方向键
	{
		map[y_pluze][x_pluze] = 0;
		y_pluze += step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze - step][x_pluze] = 0;
	}

	if ((GetAsyncKeyState(0x41) & 0x8000))    // a
	{
		z = 5;
		x_pluze2 -= step;
		map[y_pluze2][x_pluze2 + step] = 0;
		rotateimage(&imgmanblue, &imgmanblue1, PI, WHITE);
		rotateimage(&imgmanblue_M, &imgmanblue1_M, PI, WHITE);
		rotateimage(&imgpluze4shot, &imgpluze3shot, PI, WHITE);
		rotateimage(&imgpluze4shot_M, &imgpluze3shot_M, PI, WHITE);
	}
	if ((GetAsyncKeyState(0x44) & 0x8000))  // d
	{
		z = 6;
		x_pluze2 += step;
		map[y_pluze2][x_pluze2 - step] = 0;
		rotateimage(&imgmanblue, &imgmanblue1, 0, WHITE);
		rotateimage(&imgmanblue_M, &imgmanblue1_M, 0, WHITE);
		rotateimage(&imgpluze4shot, &imgpluze3shot, 0, WHITE);
		rotateimage(&imgpluze4shot_M, &imgpluze3shot_M, 0, WHITE);
	}
	if ((GetAsyncKeyState(0x57) & 0x8000))     // w
	{
		z = 7;
		y_pluze2 -= step;
		map[y_pluze2 + step][x_pluze2] = 0;
		rotateimage(&imgmanblue, &imgmanblue1, PI / 2, WHITE);
		rotateimage(&imgmanblue_M, &imgmanblue1_M, PI / 2, WHITE);
		rotateimage(&imgpluze4shot, &imgpluze3shot, PI / 2, WHITE);
		rotateimage(&imgpluze4shot_M, &imgpluze3shot_M, PI / 2, WHITE);
	}
	if ((GetAsyncKeyState(0x53) & 0x8000))  // s
	{
		z = 8;
		y_pluze2 += step;
		map[y_pluze2 - step][x_pluze2] = 0;
		rotateimage(&imgmanblue, &imgmanblue1, PI *1.5, WHITE);
		rotateimage(&imgmanblue_M, &imgmanblue1_M, PI *1.5, WHITE);
		rotateimage(&imgpluze4shot, &imgpluze3shot, PI*1.5, WHITE);
		rotateimage(&imgpluze4shot_M, &imgpluze3shot_M, PI*1.5, WHITE);
	}
	if ((GetAsyncKeyState(0x20) & 0x8000))    //  发射子弹
	{
		state = pluzeshot2;
		kind = 0;
		if (touch % 5 == 0)
		{
			if (p_gun2 == 1)
			{
				mciSendString(_T("close gun2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\py.mp3 alias gun2"), NULL, 0, NULL);
				mciSendString(_T("play gun2 "), NULL, 0, NULL);
				p_gun2 = 2;
			}
			else if (p_gun2 == 2)
			{
				mciSendString(_T("close gun2_2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\py.mp3 alias gun2_2"), NULL, 0, NULL);
				mciSendString(_T("play gun2_2 "), NULL, 0, NULL);
				p_gun2 = 1;
			}
			if (z == 5)
			{
				map[y_pluze2 + 25][x_pluze2 - 23] = 5;
			}
			else if (z == 6)
			{
				bullet_x2[clip] = x_pluze2 + 62;
				bullet_y2[clip] = y_pluze2 + 15;
				map[bullet_y2[clip]][bullet_x2[clip]] = 6;
				clip++;
			}
			else if (z == 7)
				map[y_pluze2 - 23][x_pluze2 + 15] = 7;
			else if (z == 8)
			{
				bullet_x3[clip1] = x_pluze2 + 15;
				bullet_y3[clip1] = y_pluze2 + 43;
				map[bullet_y3[clip1]][bullet_x3[clip1]] = 8;
				clip1++;
			}
		}
	}
	if ((GetAsyncKeyState(0x4B) & 0x8000)) //发射手榴弹
	{
		kind = 1;
		if (shoulei_buck > 0)
		{
			if (touch % 5 == 0)
			{
				if (p_shoulei == 1)
				{
					mciSendString(_T("close shoulei "), NULL, 0, NULL);
					mciSendString(_T("open .\\多声爆炸.mp3 alias shoulei"), NULL, 0, NULL);
					mciSendString(_T("play shoulei "), NULL, 0, NULL);
					p_shoulei = 2;
				}
				else if (p_shoulei == 2)
				{
					mciSendString(_T("close shoueli_2 "), NULL, 0, NULL);
					mciSendString(_T("open .\\多声爆炸.mp3 alias shoulei_2"), NULL, 0, NULL);
					mciSendString(_T("play shoulei_2 "), NULL, 0, NULL);
					p_shoulei = 1;
				}
				shoulei_buck--;
				if (z == 5)
				{
					map[y_pluze2 + 25][x_pluze2 - 23] = 5;
					boom = x_pluze2 - 273;
				}
				else if (z == 6)
				{
					bullet_x2[clip] = x_pluze2 + 62;
					bullet_y2[clip] = y_pluze2 + 15;
					map[bullet_y2[clip]][bullet_x2[clip]] = 6;
					boom = x_pluze2 + 312;
					clip++;
				}
				else if (z == 7)
				{
					map[y_pluze2 - 23][x_pluze2 + 15] = 7;
					boom = y_pluze2 - 273;
				}
				else if (z == 8)
				{
					bullet_x3[clip1] = x_pluze2 + 15;
					bullet_y3[clip1] = y_pluze2 + 43;
					map[bullet_y3[clip1]][bullet_x3[clip1]] = 8;
					clip1++;
					boom = y_pluze2 + 293;
				}
			}
		}
	}
}

void main()
{
	char c;
	char a[20][200]={"真是隐蔽的地方,适合养老度假呢。","呀呀呀，过来了不得了的人物呢！","伊默頭......，应该是我书上的下一个名字。","你这个样子是死神吗，正好我也受人雇佣要干掉你呢。","是嘛，杀掉死神可是有严重的后果。","一位富商的女儿将要病死，杀掉你就能得到一大笔钱。","哼，你之所以是个杀手而不是一个挤奶工都是多亏了我。","那是我凭自己的本事做的和你有什么关系？","如果我死了，你就再也杀不了人了,可是会失业的。","杀掉你后我得到的钱足够用了。","那么，让我看看你的本事吧。","能干掉死神可真是刺激啊！"};
	initgraph(1600, 800);//存储剧情台词
	startup();
	putimage(0, 0, &imgbk);   //显示开始封面图
    c=getch();
	if(c=='0') 
	{ putimage(0,0,&imgabout);
	  _getch();
	  settextstyle(30, 0, _T("宋体"));
	 setbkcolor(BLACK);
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[0]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[1]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[2]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[3]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[4]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[5]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[6]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[7]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[8]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[9]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[10]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[11]);
	 _getch();
     cleardevice();
	 putimage(0,0,&imgvs);
	 _getch();
	 cleardevice();
	 putimage(0,0,&imgb);
	 _getch();
	while (1)  // 游戏循环执行
	{
		show();  // 控制人物
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();  // 与用户输入有关的更新
	}
	}// 数据初始化	
	else 
	{
	 settextstyle(30, 0, _T("宋体"));
	 setbkcolor(BLACK);
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[0]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[1]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[2]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[3]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[4]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[5]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[6]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[7]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[8]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[9]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //加载死神台词画面
	 outtextxy(450, 560, a[10]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //加载杀手台词画面
     outtextxy(450, 560, a[11]);
	 _getch();
     cleardevice();
	 putimage(0,0,&imgvs);
	 _getch();
	 cleardevice();
	 putimage(0,0,&imgb);
	 _getch();
	
	while (1)  // 游戏循环执行
	{
		show();  // 控制人物
		updateWithoutInput();  // 与用户输入无关的更新
		updateWithInput();  // 与用户输入有关的更新
	}
	}
}