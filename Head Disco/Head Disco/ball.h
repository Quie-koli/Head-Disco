#pragma once
#include <QPainter>
#include <list>
#include "Gameobject.h"
class ball : public Gameobject//为Gameobject的派生
{
public:
	ball(int tp,int r,int xs,int ys, QImage& im);
	~ball();
	int update(int x, int y);
	int update();
	QImage& img;/*渲染的该球的图像，起初选用的并非引用型但经过思考认为使用引用对内存占用更小*/
private:
	int type;
	int radius;
	
};

