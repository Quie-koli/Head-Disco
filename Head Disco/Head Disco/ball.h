#pragma once
#include <QPainter>
#include <list>
#include "Gameobject.h"
class ball : public Gameobject//ΪGameobject������
{
public:
	ball(int tp,int r,int xs,int ys, QImage& im);
	~ball();
	int update(int x, int y);
	int update();
	QImage& img;/*��Ⱦ�ĸ����ͼ�����ѡ�õĲ��������͵�����˼����Ϊʹ�����ö��ڴ�ռ�ø�С*/
private:
	int type;
	int radius;
	
};

