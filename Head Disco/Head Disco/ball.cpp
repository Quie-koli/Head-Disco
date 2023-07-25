#include "ball.h"

ball::ball(int tp, int r, int xs, int ys,QImage &im):type(tp),radius(r*r),img(im)/*ball的构造函数*/ {
	px = xs;
	py = ys;
}
ball::~ball() /*本来想在ball被析构时删除自身在balls的位置，但是实际上直接删除balls对应位置不用手动删除ball*/ {
	
}
int ball::update(int x, int y) {//重载update
	py += 20;/*每次移动一下*/
	int temp = (x+100 - px)* (x+100 - px) + (y+100 - py)* (y + 100 - py);
	if (temp < radius) return type ;/*并计算是否与遮挡物碰撞，是的话返回自身类型值*/
	else return 0;
}
int ball::update() {
	//已经重载了
	return 0;
}
