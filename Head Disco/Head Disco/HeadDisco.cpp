#include "HeadDisco.h"
using namespace cv;
using namespace std;/*由于未声明使用这两个命名空间导致引用的opencv的库函数找不到，解决增加声明使用这两个命名空间*/
HeadDisco::HeadDisco(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	initgame();//在窗体创建时候初始化游戏
}
QImage Mat2QImage(const cv::Mat& mat)/*将opencv获取的摄像头图像转换为QImage*/
{
	if (mat.type() == CV_8UC1 || mat.type() == CV_8U)
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();  //r与b调换
	}
}
int lerp(int a, int b, float t) /*对两个值之间做一个插值来时遮挡物移动时更加流畅*/
{
	a = a + (b - a) * t;
	return a;

}
void HeadDisco::initgame() //初始化游戏
{
	running = true;
	points = 0;
	uilayer = 0;
	tipui = 0;
	tipui = 0;
	startbk.load("./st1.png"); /*加载运行目录下游戏使用的图片素材*/
	starttiltle.load("./st2.png");
	background.load("./2333.png");
	blue.load("./b1.png");
	red.load("./b2.png");
	perf.load("./p1.png");
	bad.load("./p2.png");
	resg.load("./res.png");
	tipg.load("./tip.png");
	camerapos = QRectF(0, 300, 1000, 750);/*设置ui的坐标及大小*/
	backpos = QRectF(0, 0, 1000, 470);
	hidepos = QRectF(0, 0, 5, 5);
	mpos = QRectF(30, 90, 134, 38);
	anspos = QRectF(0, 0, 1000, 818);
	anpos2 = QRectF(0, 130, 1000, 569);
	tippos = QRectF(20, 0, 648, 200);
	aupl.AddAudioclip("bgm.mp3","bgm");/*加载游戏音效*/
	aupl.AddAudioclip("hit.mp3", "hit");
	aupl.AddAudioclip("gameover.wav", "gameover");
	aupl.Playaudiocliploop("bgm");/*循环播放背景音乐*/
	update();/*刷新一次让开始游戏界面渲染出来*/
}

void HeadDisco::mousePressEvent(QMouseEvent* event)//对鼠标的各种事件处理
{
	aupl.Playaudiocliponce("hit");
	if (event->button() == Qt::LeftButton)/*判断为左键*/
	{
		switch (uilayer)/*uilayer是当前界面的id号*/
		{
			case 0:/*当为开始游戏界面时按下左键进入选择遮挡物界面*/
				uilayer = 1;
				anpos2 = QRectF(139, 260, 721, 268);
				starttiltle.load("./st3.png"); 
				break;
			case 1:/*当为选择遮挡物界面时按下左键判断是否点击的位置在选择的遮挡物的范围内，是即选择该遮挡物开始游戏*/
				if (event->y() > 300 && event->y() < 500)
				{
					if (event->x() > 139 && event->x() < 317)
					{
						hideimg.load("./120.png");
						uilayer = 4;
						startgame();
					}
					if (event->x() > 317 && event->x() < 495)
					{
						hideimg.load("./121.png");
						uilayer = 4;
						startgame();
					}
					if (event->x() > 495 && event->x() < 673)
					{
						hideimg.load("./122.png");
						uilayer = 4;
						startgame();
					}if (event->x() > 673 && event->x() < 851)
					{
						hideimg.load("./123.png");
						uilayer = 4;
						startgame();
					}

				}
			break;
			case 2:/*当为重新开始游戏界面时按下左键进入清空所有数据重新开始游戏*/
				uilayer = 4;
				points = 0;//清空所有ball和归零points
				list<ball>::iterator b2 = balls.begin();
				while (b2 != balls.end())
				{	
					balls.erase(b2);
					b2++;
				}hp = 5;
				gaming = true;
				break;
				
		}
		
		update();
	}
}
void HeadDisco::createaball(int tp, int r, int xm, int ym, QImage& im) /*创建滚球并加入balls数组中*/
{
	ball pp(tp, r, xm, ym, im);
	balls.push_back(pp);
}
void HeadDisco::startgame() {
	CascadeClassifier faceDetector("haarcascade_frontalface_default.xml");/*加载人脸识别模型*/
	running = true;
	VideoCapture cap(0);/*开启摄像头*/
	vector<Rect> objects;
	Size pp = cv::Size(100, 100);
	QRectF r(50, 50, 300, 200);
	int sies, ddp = 25;
	faceisu = false;
	gaming = true;
	hp = 5;
	while (running)/*为while (0)时循环不会随窗体关闭而结束导致程序陷入时循环无法关闭，解决办法:声明一个bool型变量在窗体被关闭时触发将该变量设置为false结束循环*/
	{
		
			Mat cam;
			cap >> cam;/*输入摄像头获取的数据*/
			flip(cam, cam, 1);/*将镜头画面镜像以适应玩家运动方向*/
			Cameracanvas = Mat2QImage(cam);/*将镜头数据转为qimage*/
			objects.clear();
			cv::resize(cam, cam, Size(200, 150));/*由于摄像头获取的图像较大实时进行人脸识别性能消耗过大，所以将图像缩小并转为灰度图以增加识别精确度和提高效率*/
			cvtColor(cam, cam, COLOR_BGR2GRAY);
			if (gaming) {
			faceDetector.detectMultiScale(cam, objects);
			if (objects.size() > 0) {
				sies = objects[0].width * objects[0].height;
				if (sies > 3000 && sies < 6000) {/*由于人脸识别模型精度不够经常会提供一些错误的数据，所以在这里限制人脸在一个合理的范围，从而提供人脸识别精度*/
					role_x = lerp(role_x, objects[0].x * 5, 0.6);
					role_y = lerp(hidepos.y(), objects[0].y * 3.75 + 290, 0.6);
					hidepos.setX(role_x);
					hidepos.setY(role_y);/*将人脸位置数据与遮挡物位置做插值在传入给遮挡物位置*/
				}
				else faceisu = 0;
				facesize = sies;
				faceisu = 1;
			}
			else faceisu = 0;/*如果无法捕获到人脸数据就不产生新的滚球*/
			if (faceisu) {/*一个计时器在时间到的时候随机产生红蓝其中一种滚球*/
				if (ddp == 0) {
					if (rand() % 2 == 0)
						createaball(1, 170, 200 + (rand() % 3) * 300, -100, blue);
					else
						createaball(2, 170, 200 + (rand() % 3) * 300, -100, red);
					ddp = 5 + rand() % 30;
				}
				else ddp--;
			}
			update();/*起初游戏画面卡住不动，解决方法是在这里加上update因为update不会自动调用也就无法渲染游戏画面*/
		}
		waitKey(30);
	}
}
void HeadDisco::drawrestartgameui() {
	QPainter painter(this);/*起初本来画板绘制在控件上，但是实际效果不佳，所以设计为直接绘制在窗体上*/
	painter.drawImage(anspos, startbk);
	painter.drawImage(anpos2, resg);
	QFont font("Microsoft YaHei", 12, QFont::Bold, false);
	painter.setPen(Qt::white);
	painter.setFont(font);
	painter.drawText(QRectF(465, 400, 200, 20), QString::fromStdString("Points:" + std::to_string(points)));
}

void HeadDisco::drawgamestartui() {//绘制进入游戏ui和选择遮挡物ui
	QPainter painter(this);
	painter.drawImage(anspos, startbk);
	painter.drawImage(anpos2, starttiltle);
	if((uilayer)==1)
	painter.drawImage(tippos,tipg);
}
void HeadDisco::drawgameui() {//绘制游戏核心内容ui
	QPainter painter(this);
	QFont font("Microsoft YaHei", 9, QFont::Bold, false);
	painter.drawImage(camerapos, Cameracanvas);
	painter.drawImage(backpos, background);
	painter.drawImage(hidepos, hideimg);
	list<ball>::iterator b2 = balls.begin();
	int temp;
	while (b2 != balls.end())/*遍历balls数列对每个ball进行渲染*/
	{

		temp = b2->update(role_x, role_y);/*判断遮挡物是否与滚球碰撞，蓝球返回1，红球2，无碰撞0*/

		painter.drawImage(QRectF(b2->px, b2->py, 100, 100), b2->img);
		if (temp != 0) {/*发生了碰撞*/
			aupl.Playaudiocliponce("hit");
			if (temp == 1) {
				tipui = 15;/*显示加分提醒*/
				points++;
			}
			else {
				tipui = -15;/*显示掉血提醒*/
				hp--; 
				if (hp <= 0) { /*当血小于零时游戏结束跳到重开界面*/
					gaming = false; 
					uilayer = 2;
					anpos2 = QRectF(350, 460, 300, 95); 
					aupl.Playaudiocliponce("gameover");
					update();
				}
			}
			balls.erase(b2);

		}
		else {
			if (b2->py > 800)  balls.erase(b2);

		}
		b2++;

	}
	painter.setPen(Qt::white);

	painter.setFont(font);/*显示各种数值*/
	painter.drawText(QRectF(60, 765, 200, 20), QString::fromStdString("Face Size:" + std::to_string(facesize)));
	painter.drawText(QRectF(60, 30, 200, 20), QString::fromStdString("Points:" + std::to_string(points)));
	painter.drawText(QRectF(60, 60, 200, 20), QString::fromStdString("Hp:" + std::to_string(hp)));
	if (tipui > 0) {/*tipui > 0时渲染加分ui*/
		tipui--;/*做一个倒计时时间到ui停止显示*/
		painter.drawImage(mpos, perf);

	}
	if (tipui < 0) {/*tipui< 0时渲染减分ui*/
		tipui++;
		painter.drawImage(mpos, bad);

	}

}
void  HeadDisco::paintEvent(QPaintEvent*)/*渲染游戏画面*/ {

	switch (uilayer)
	{
	case 0://绘制进入游戏ui
		drawgamestartui(); break;
	case 1://绘制选择遮挡物ui
		drawgamestartui(); break;
	case 2://绘制重新开始游戏ui
		drawrestartgameui(); break;
	case 4: //绘制游戏内容ui
		drawgameui(); break;
		break;
	}

}
void HeadDisco::closeEvent(QCloseEvent*)/*当窗口结束时结束获取摄像头的循环*/ {
	running = false;
}
HeadDisco::~HeadDisco()
{}