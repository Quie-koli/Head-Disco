#include "ball.h"

ball::ball(int tp, int r, int xs, int ys,QImage &im):type(tp),radius(r*r),img(im)/*ball�Ĺ��캯��*/ {
	px = xs;
	py = ys;
}
ball::~ball() /*��������ball������ʱɾ��������balls��λ�ã�����ʵ����ֱ��ɾ��balls��Ӧλ�ò����ֶ�ɾ��ball*/ {
	
}
int ball::update(int x, int y) {//����update
	py += 20;/*ÿ���ƶ�һ��*/
	int temp = (x+100 - px)* (x+100 - px) + (y+100 - py)* (y + 100 - py);
	if (temp < radius) return type ;/*�������Ƿ����ڵ�����ײ���ǵĻ�������������ֵ*/
	else return 0;
}
int ball::update() {
	//�Ѿ�������
	return 0;
}
