#include <stdio.h>
#include <stdlib.h>
#pragma comment(lib,"Winmm.lib") 
#include <conio.h>
#include <windows.h>
#include<graphics.h>
#include<math.h>
#include <time.h>
#define pluze 10//10Ϊpluze
#define pluzeshot 11//11Ϊɱ�����
#define pluzeshot2 12//12Ϊ�������
#define PI 3.1415926535
float mouse_x, mouse_y;
int x_pluze, y_pluze;       //ɱ�ֵ�����
int x_pluze2, y_pluze2;		//���������
int map[1600][3200];//��ͼ����
int map_x, map_y;//��ͼ�ϵ�x��y
int clip = 0;
int game = 1;
int clip1 = 0;
int p;//����
int temp;//����ɱ�ֵ�״̬
int state;//���������״̬
int touch = 0;
int v = 10;//ɱ���ӵ��ٶ�
int v_s = 6;//ɱ�������ٶ�
int boom;
double v_x[1000];//�ӵ�ˮƽ�����ٶ�
double v_y[1000];//�ӵ���ֱ�����ٶ�
int i_bullet = 0;//ɱ���ӵ����
int bullet_x[1000], bullet_y[1000];//�����ӵ�λ��
int bullet_x2[1000], bullet_y2[1000];//�������ӵ�λ��
int bullet_x3[1000], bullet_y3[1000];//�������ӵ�λ��
int kind;
int v2 = 20;                   //�����ӵ��ٶ�
float hp_pluze = 100;           //ɱ������ֵ
float hp_buck = 100;           //��������ֵ
int z, shoot;                 //1�ӵ��ķ���
int shoulei_pluze = 2;
int shoulei_buck = 2;//��������
double vs_x[50];
double vs_y[50];//�����ٶ�
int shoulei_x[50];
int shoulei_y[50];//���׵�ǰλ��
int i_shoulei = 0;//���ױ��
int x_pr[50], y_pr[50];//���׳�ʼλ��
int p_gun1 = 1;//��¼ǹ��1
int p_gun2 = 1;//��¼ǹ��2
int p_shoulei = 1;//��¼������
IMAGE imgpluze1, imgpluze2;    //ǹ��1
IMAGE imgpluze1_M, imgpluze2_M;
IMAGE imgmanblue1, imgmanblue;    //ǹ��2
IMAGE imgmanblue1_M, imgmanblue_M;
IMAGE imgbullet1;  //���ӵ�
IMAGE imgbullet_M1;
IMAGE img_wall;
IMAGE imgbullet2;  //���ӵ�
IMAGE imgbullet_M2;
IMAGE imgbullet3;  //���ӵ�
IMAGE imgbullet_M3;
IMAGE imgbullet4;  //���ӵ�
IMAGE imgbullet_M4;
IMAGE imgpluze1shot, imgpluze1shot_M;
IMAGE imgpluze2shot, imgpluze2shot_M;
IMAGE imgpluze3shot, imgpluze3shot_M;
IMAGE imgpluze4shot, imgpluze4shot_M;   //��ͬ�������ͼ������ͼ
IMAGE imgbullet, imgbullet_M;      //�ӵ�ͼ������ͼ
IMAGE imgpluzeui;
IMAGE imgbuckui;                 //uiͼƬ
IMAGE imghp;                    //Ѫ��
IMAGE imggun;                  //ǹ
IMAGE imgshoulei, imgshoulei_m;//����ͼƬ
IMAGE imgboom, imgboom_mask;//��ըͼƬ
IMAGE imgbk;                //��ʼ���汳��ͼ
IMAGE imgwin1, imgwin2;     //��βʤ��ͼ
IMAGE imgvs,imgb;
IMAGE imgsishen,imgshashou,imgkuang;//���ؾ�������ɱ�ֶԻ���
IMAGE imgabout;//������������Ϣ
MOUSEMSG m;	// ���������Ϣ
int speed;
time_t start, stop;//��ʱ��
void startup()                       // ���ݳ�ʼ������ʾ����
{
	speed = 4;//�ٶ�
	temp = pluze;                    //ɱ��һ��ʼ����ǹ״̬
	state = pluze - 1;
	x_pluze = 1450;
	y_pluze = 700;                   //ɱ�ֳ�ʼλ��
	x_pluze2 = 100;
	y_pluze2 = 100;                  //�����ʼλ��
	map[y_pluze][x_pluze] = pluze;   //ɱ��λ��
	map[x_pluze2][y_pluze2] = 9;     //����λ��
	loadimage(&img_wall, _T("demon.jpg"));        //�����ϰ���ͼƬ
	loadimage(&imgpluze1, _T("ɱ����ǹ.jpg"));    //����ɱ����ǹͼ
	loadimage(&imgpluze1_M, _T("ɱ����ǹ_mask.jpg"));//����ɱ����ǹ������ͼ
	loadimage(&imgmanblue1, _T("������ǹ.jpg"));//����������ǹͼ
	loadimage(&imgmanblue1_M, _T("������ǹ_mask.jpg"));//����������ǹ������ͼ
	loadimage(&imgbullet1, _T("zidanl.jpg"));//�����ӵ�ͼ�������
	loadimage(&imgbullet_M1, _T("zidanl_mask.jpg"));//�����ӵ�ͼ�������������ͼ
	loadimage(&imgbullet2, _T("zidanr.jpg"));//�����ӵ�ͼ�ҷ������
	loadimage(&imgbullet_M2, _T("zidanr_mask.jpg"));//�����ӵ�ͼ�ҷ������������ͼ
	loadimage(&imgbullet3, _T("zidanu.jpg"));//�����ӵ�ͼ�Ϸ������
	loadimage(&imgbullet_M3, _T("zidanu_mask.jpg"));//�����ӵ�ͼ�Ϸ������������ͼ
	loadimage(&imgbullet4, _T("zidand.jpg"));//�����ӵ�ͼ�·������
	loadimage(&imgbullet_M4, _T("zidand_mask.jpg"));//�����ӵ�ͼ�·������������ͼ
	loadimage(&imgbullet, _T("���ӵ�.jpg"));//����ɱ���ӵ�ͼ
	loadimage(&imgbullet_M, _T("���ӵ�_mask1.jpg"));//����ɱ���ӵ�ͼ������ͼ
	loadimage(&imgpluze1shot, _T("ɱ����ǹ.jpg"));//����ɱ����ǹͼ
	loadimage(&imgpluze1shot_M, _T("ɱ����ǹ_mask.jpg"));//����ɱ����ǹͼ������ͼ
	loadimage(&imgpluze3shot, _T("������ǹ.jpg"));//����������ǹͼ
	loadimage(&imgpluze3shot_M, _T("������ǹ_mask.jpg"));//����������ǹͼ������ͼ
	loadimage(&imgpluzeui, _T("ɱ��Ѫ��.jpg"));//����ɱ�ֵ�Ѫ��ͼ
	loadimage(&imgbuckui, _T("����Ѫ��.jpg"));//���������Ѫ��ͼ
	loadimage(&imghp, _T("С��ƿ.jpg"));//���ز�Ѫ����ͼ
	loadimage(&imggun, _T("С��ƿ.jpg"));//�����������׵���ͼ
	loadimage(&imgshoulei, _T("Ұ�����.jpg"));//��������ͼ
	loadimage(&imgshoulei_m, _T("Ұ�����_mask.jpg"));//��������ͼ������ͼ
	loadimage(&imgboom, _T("boom.jpg"));//���ر�ը��Чͼ
	loadimage(&imgboom_mask, _T("boom_mask.jpg"));//���ر�ը��Чͼ������ͼ
	loadimage(&imgbk, _T("bk1.jpg"));//���ؿ�ʼ���汳��ͼ
	loadimage(&imgwin1, _T("����final.jpg"));//��������ʤ��ͼ
	loadimage(&imgwin2, _T("ɱ��final.jpg"));//����ɱ��ʤ��ͼ 
	loadimage(&imgsishen,_T("����win1.jpg"));//���ؾ�������ͼ
	loadimage(&imgshashou,_T("ɱ��win1.jpg"));//���ؾ���ɱ��ͼ
	loadimage(&imgkuang,_T("�Ի���.jpg"));//���ضԻ���
	loadimage(&imgvs,_T("�����ǹ.jpg"));
	loadimage(&imgb,_T("ǹ.jpg"));
	loadimage(&imgabout,_T("about.jpg"));//������������Ϣͼ
	mciSendString(_T("open ��ʿbgm.mp3 alias bgm"),NULL,0,NULL);
	mciSendString(_T("open py.mp3 alias gun1"), NULL, 0, NULL);
	mciSendString(_T("open py.mp3 alias gun2"), NULL, 0, NULL);
	mciSendString(_T("open ǹ��2.mp3 alias gun1_2"), NULL, 0, NULL);
	mciSendString(_T("open ǹ��2.mp3 alias gun2_2"), NULL, 0, NULL);
	mciSendString(_T("open ������ը.mp3 alias shoulei"), NULL, 0, NULL);
	mciSendString(_T("open ������ը.mp3 alias shoulei_2"), NULL, 0, NULL);   //���ر������ֺ���Ч
	mciSendString(_T("play bgm repeat"), NULL, 0, NULL);
	time_t t;//��ʱ��
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
		}                                          //����������������ϰ���ը����Ѫƿ����
	for (map_y = 100; map_y <= 700; map_y = map_y + 50)
		for (map_x = 100; map_x <= 1400; map_x = map_x + 50)
		{
			if ((map[map_y - 50][map_x] == 1) && (map[map_y][map_x - 50] == 1))
				map[map_y][map_x] = 1;
		}                                           //��ֹ����bug����
}

void show()  // ����������ӵ�״̬
{
	int i, j;
	while (MouseHit())    //�Զ���ǹ
	{
		m = GetMouseMsg();
		if (m.uMsg == WM_LBUTTONDOWN)  //����������
		{

			if (p_gun1 == 1)
			{
				mciSendString(_T("close gun1 "), NULL, 0, NULL);
				mciSendString(_T("open .\\ɱ��ǹ��.mp3 alias gun1"), NULL, 0, NULL);
				mciSendString(_T("play gun1 "), NULL, 0, NULL);
				p_gun1 = 2;
			}
			else if (p_gun1 == 2)
			{
				mciSendString(_T("close gun1_2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\ɱ��ǹ��.mp3 alias gun1_2"), NULL, 0, NULL);
				mciSendString(_T("play gun1_2 "), NULL, 0, NULL);
				p_gun1 = 1;
			}                          //�������ʱǹ������
			temp = pluzeshot;          //ɱ�ָı�״̬����Ϊ��ǹ
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
		}                             //�������λ�ö����ӵ�x��y�ٶ�
		if (m.uMsg != WM_LBUTTONDOWN)
			stop = time(NULL);
		if (stop - start >= 1)
			temp = pluze;
		if (m.uMsg == WM_MOUSEMOVE)
		{
			mouse_x = m.x;
			mouse_y = m.y;            //��ȡ�������
		}
		if ((m.uMsg == WM_RBUTTONDOWN) && (shoulei_pluze>0))
		{
			if (p_shoulei == 1)
			{
			
				mciSendString(_T("close shoulei "), NULL, 0, NULL);
				mciSendString(_T("open .\\������ը.mp3 alias shoulei"), NULL, 0, NULL);
				mciSendString(_T("play shoulei "), NULL, 0, NULL);
				p_shoulei = 2;
			}
			else if (p_shoulei == 2)
			{
				mciSendString(_T("close shoueli_2 "), NULL, 0, NULL);
				mciSendString(_T("open .\\������ը.mp3 alias shoulei_2"), NULL, 0, NULL);
				mciSendString(_T("play shoulei_2 "), NULL, 0, NULL);
				p_shoulei = 1;
			}                         //����������Ч
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
	}                                  //���Ʋ�ͬ�����ӵ����ٶ�һ��


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
	}                                      // ��תͼ�� ʹ����ָ�����λ��
	BeginBatchDraw();
	setbkcolor(WHITE);
	cleardevice();
	map[y_pluze2][x_pluze2] = state;
	for (map_y = 0; map_y <= 800; map_y++)     //���ݵ�ͼ�������ͼƬ
		for (map_x = 0; map_x <= 1600; map_x++)
		{
			touch++;
			if (map[map_y][map_x] == 1)
				putimage(map_x, map_y, &img_wall);   //1Ϊǽ
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
					putimage(map_x, map_y, &imgshoulei, SRCERASE);     //����
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
					putimage(map_x, map_y, &imgshoulei, SRCERASE);    //����
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
					putimage(map_x, map_y, &imgshoulei, SRCERASE);    //����
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
					putimage(map_x, map_y, &imgshoulei, SRCERASE);   //����

				}

			}
			else if (map[map_y][map_x] == 100)
			{
				putimage(map_x, map_y, &imgpluzeui);//ɱ��  ui
			}
			else if (map[map_y][map_x] == 101)
			{
				putimage(map_x, map_y, &imgbuckui);//����  ui
			}
			else if (map[map_y][map_x] == 103)
			{
				putimage(map_x, map_y, &imghp);//Ѫ��
			}
			else if (map[map_y][map_x] == 104)
			{
				putimage(map_x, map_y, &imggun);//ǹ
			}
			else if (map[map_y][map_x] == 105)
			{
				putimage(map_x, map_y, &imgshoulei_m, NOTSRCERASE);
				putimage(map_x, map_y, &imgshoulei, SRCERASE);//����
			}
			else if (map[map_y][map_x] == 106)
			{
				putimage(map_x, map_y, &imgboom_mask, NOTSRCERASE);
				putimage(map_x, map_y, &imgboom, SRCERASE);//���ױ�ը
				if (touch % 10 == 0)
					map[map_y][map_x] = 0;
			}
		}
	setfillcolor(RED);
	fillroundrect(188, 20, 540 - 340 * (1 - hp_buck / 100), 65,20,20);
	fillroundrect(1010 + 340 * (1 - hp_pluze / 100), 20,1350, 65,20,20);//����Ѫ���ĳ��̣��յ��˺����ߵõ�ѪƿѪ������Ӧ�ķ����ϱ䳤����
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
}                         //��Ϸ��β�ж�ʤ���߳���ͼ��

void updateWithoutInput()  // ���û������޹صĸ���
{
	map[0][50] = 101;
	map[0][1000] = 100;//���ui
	map[y_pluze][x_pluze] = temp;
	map[y_pluze2][x_pluze2] = state;
	int i, j, back, l;//�ж���ײ�ñ���
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
		}//����ǽ����
	for (l = 0; l < 1000; l++)//�ӵ��ƶ�
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
	for (l = 0; l < 50; l++)//�����ƶ�
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
	for (i = 100; i <= 700; i = i + 50)//�ӵ�����ǽ��ǽ��ʧ
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
		}//�ӵ�����wall 
	for (i = y_pluze2 - 25; i<y_pluze2 + 25; i++)
		for (j = x_pluze2 - 25; j < x_pluze2 + 25; j++)
		{
			if (map[i][j] == 20)
			{
				hp_buck = hp_buck - 10;
				map[i][j] = 0;
			}
		}//�ӵ�����buck
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
	if (x_pluze > 1500)//��ֹ���߽�
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
	if (x_pluze2 > 1500)//��ֹ���߽�
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

void updateWithInput()  // ���û������йصĸ���
{
	int step = speed;
	if ((GetAsyncKeyState(VK_LEFT) & 0x8000))    // �����
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze -= step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze][x_pluze - step] = 0;
	}
	if ((GetAsyncKeyState(VK_RIGHT) & 0x8000))  // �ҷ����
	{
		map[y_pluze][x_pluze] = 0;
		x_pluze += step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze][x_pluze - step] = 0;
	}
	if ((GetAsyncKeyState(VK_UP) & 0x8000))     // �Ϸ����
	{
		map[y_pluze][x_pluze] = 0;
		y_pluze -= step;
		map[y_pluze][x_pluze] = temp;
		map[y_pluze + step][x_pluze] = 0;
	}
	if ((GetAsyncKeyState(VK_DOWN) & 0x8000))  // �·����
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
	if ((GetAsyncKeyState(0x20) & 0x8000))    //  �����ӵ�
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
	if ((GetAsyncKeyState(0x4B) & 0x8000)) //��������
	{
		kind = 1;
		if (shoulei_buck > 0)
		{
			if (touch % 5 == 0)
			{
				if (p_shoulei == 1)
				{
					mciSendString(_T("close shoulei "), NULL, 0, NULL);
					mciSendString(_T("open .\\������ը.mp3 alias shoulei"), NULL, 0, NULL);
					mciSendString(_T("play shoulei "), NULL, 0, NULL);
					p_shoulei = 2;
				}
				else if (p_shoulei == 2)
				{
					mciSendString(_T("close shoueli_2 "), NULL, 0, NULL);
					mciSendString(_T("open .\\������ը.mp3 alias shoulei_2"), NULL, 0, NULL);
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
	char a[20][200]={"�������εĵط�,�ʺ����϶ȼ��ء�","ѽѽѽ�������˲����˵������أ�","��Ĭ�^......��Ӧ���������ϵ���һ�����֡�","�����������������������Ҳ���˹�ӶҪ�ɵ����ء�","���ɱ��������������صĺ����","һλ���̵�Ů����Ҫ������ɱ������ܵõ�һ���Ǯ��","�ߣ���֮�����Ǹ�ɱ�ֶ�����һ�����̹����Ƕ�����ҡ�","������ƾ�Լ��ı������ĺ�����ʲô��ϵ��","��������ˣ������Ҳɱ��������,���ǻ�ʧҵ�ġ�","ɱ������ҵõ���Ǯ�㹻���ˡ�","��ô�����ҿ�����ı��°ɡ�","�ܸɵ���������Ǵ̼�����"};
	initgraph(1600, 800);//�洢����̨��
	startup();
	putimage(0, 0, &imgbk);   //��ʾ��ʼ����ͼ
    c=getch();
	if(c=='0') 
	{ putimage(0,0,&imgabout);
	  _getch();
	  settextstyle(30, 0, _T("����"));
	 setbkcolor(BLACK);
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[0]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[1]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[2]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[3]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[4]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[5]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[6]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[7]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[8]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[9]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[10]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[11]);
	 _getch();
     cleardevice();
	 putimage(0,0,&imgvs);
	 _getch();
	 cleardevice();
	 putimage(0,0,&imgb);
	 _getch();
	while (1)  // ��Ϸѭ��ִ��
	{
		show();  // ��������
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	}// ���ݳ�ʼ��	
	else 
	{
	 settextstyle(30, 0, _T("����"));
	 setbkcolor(BLACK);
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[0]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[1]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[2]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[3]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[4]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[5]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[6]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[7]);
	 _getch();
     cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[8]);
	 _getch();
     cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[9]);
	 _getch();
	 cleardevice();
	 setbkmode(TRANSPARENT);
	 putimage(0,200,&imgsishen);
	 putimage(400,500,&imgkuang);       //��������̨�ʻ���
	 outtextxy(450, 560, a[10]);
	 _getch();
	 cleardevice();
	 putimage(1150,200,&imgshashou);
	 putimage(400,500,&imgkuang);      //����ɱ��̨�ʻ���
     outtextxy(450, 560, a[11]);
	 _getch();
     cleardevice();
	 putimage(0,0,&imgvs);
	 _getch();
	 cleardevice();
	 putimage(0,0,&imgb);
	 _getch();
	
	while (1)  // ��Ϸѭ��ִ��
	{
		show();  // ��������
		updateWithoutInput();  // ���û������޹صĸ���
		updateWithInput();  // ���û������йصĸ���
	}
	}
}