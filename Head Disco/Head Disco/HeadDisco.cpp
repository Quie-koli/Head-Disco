#include "HeadDisco.h"
using namespace cv;
using namespace std;/*����δ����ʹ�������������ռ䵼�����õ�opencv�Ŀ⺯���Ҳ����������������ʹ�������������ռ�*/
HeadDisco::HeadDisco(QWidget *parent)
    : QMainWindow(parent)
{
    ui.setupUi(this);
	initgame();//�ڴ��崴��ʱ���ʼ����Ϸ
}
QImage Mat2QImage(const cv::Mat& mat)/*��opencv��ȡ������ͷͼ��ת��ΪQImage*/
{
	if (mat.type() == CV_8UC1 || mat.type() == CV_8U)
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_Grayscale8);
		return image;
	}
	else if (mat.type() == CV_8UC3)
	{
		QImage image((const uchar*)mat.data, mat.cols, mat.rows, mat.step, QImage::Format_RGB888);
		return image.rgbSwapped();  //r��b����
	}
}
int lerp(int a, int b, float t) /*������ֵ֮����һ����ֵ��ʱ�ڵ����ƶ�ʱ��������*/
{
	a = a + (b - a) * t;
	return a;

}
void HeadDisco::initgame() //��ʼ����Ϸ
{
	running = true;
	points = 0;
	uilayer = 0;
	tipui = 0;
	tipui = 0;
	startbk.load("./st1.png"); /*��������Ŀ¼����Ϸʹ�õ�ͼƬ�ز�*/
	starttiltle.load("./st2.png");
	background.load("./2333.png");
	blue.load("./b1.png");
	red.load("./b2.png");
	perf.load("./p1.png");
	bad.load("./p2.png");
	resg.load("./res.png");
	tipg.load("./tip.png");
	camerapos = QRectF(0, 300, 1000, 750);/*����ui�����꼰��С*/
	backpos = QRectF(0, 0, 1000, 470);
	hidepos = QRectF(0, 0, 5, 5);
	mpos = QRectF(30, 90, 134, 38);
	anspos = QRectF(0, 0, 1000, 818);
	anpos2 = QRectF(0, 130, 1000, 569);
	tippos = QRectF(20, 0, 648, 200);
	aupl.AddAudioclip("bgm.mp3","bgm");/*������Ϸ��Ч*/
	aupl.AddAudioclip("hit.mp3", "hit");
	aupl.AddAudioclip("gameover.wav", "gameover");
	aupl.Playaudiocliploop("bgm");/*ѭ�����ű�������*/
	update();/*ˢ��һ���ÿ�ʼ��Ϸ������Ⱦ����*/
}

void HeadDisco::mousePressEvent(QMouseEvent* event)//�����ĸ����¼�����
{
	aupl.Playaudiocliponce("hit");
	if (event->button() == Qt::LeftButton)/*�ж�Ϊ���*/
	{
		switch (uilayer)/*uilayer�ǵ�ǰ�����id��*/
		{
			case 0:/*��Ϊ��ʼ��Ϸ����ʱ�����������ѡ���ڵ������*/
				uilayer = 1;
				anpos2 = QRectF(139, 260, 721, 268);
				starttiltle.load("./st3.png"); 
				break;
			case 1:/*��Ϊѡ���ڵ������ʱ��������ж��Ƿ�����λ����ѡ����ڵ���ķ�Χ�ڣ��Ǽ�ѡ����ڵ��￪ʼ��Ϸ*/
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
			case 2:/*��Ϊ���¿�ʼ��Ϸ����ʱ�������������������������¿�ʼ��Ϸ*/
				uilayer = 4;
				points = 0;//�������ball�͹���points
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
void HeadDisco::createaball(int tp, int r, int xm, int ym, QImage& im) /*�������򲢼���balls������*/
{
	ball pp(tp, r, xm, ym, im);
	balls.push_back(pp);
}
void HeadDisco::startgame() {
	CascadeClassifier faceDetector("haarcascade_frontalface_default.xml");/*��������ʶ��ģ��*/
	running = true;
	VideoCapture cap(0);/*��������ͷ*/
	vector<Rect> objects;
	Size pp = cv::Size(100, 100);
	QRectF r(50, 50, 300, 200);
	int sies, ddp = 25;
	faceisu = false;
	gaming = true;
	hp = 5;
	while (running)/*Ϊwhile (0)ʱѭ�������洰��رն��������³�������ʱѭ���޷��رգ�����취:����һ��bool�ͱ����ڴ��屻�ر�ʱ�������ñ�������Ϊfalse����ѭ��*/
	{
		
			Mat cam;
			cap >> cam;/*��������ͷ��ȡ������*/
			flip(cam, cam, 1);/*����ͷ���澵������Ӧ����˶�����*/
			Cameracanvas = Mat2QImage(cam);/*����ͷ����תΪqimage*/
			objects.clear();
			cv::resize(cam, cam, Size(200, 150));/*��������ͷ��ȡ��ͼ��ϴ�ʵʱ��������ʶ���������Ĺ������Խ�ͼ����С��תΪ�Ҷ�ͼ������ʶ��ȷ�Ⱥ����Ч��*/
			cvtColor(cam, cam, COLOR_BGR2GRAY);
			if (gaming) {
			faceDetector.detectMultiScale(cam, objects);
			if (objects.size() > 0) {
				sies = objects[0].width * objects[0].height;
				if (sies > 3000 && sies < 6000) {/*��������ʶ��ģ�;��Ȳ����������ṩһЩ��������ݣ���������������������һ������ķ�Χ���Ӷ��ṩ����ʶ�𾫶�*/
					role_x = lerp(role_x, objects[0].x * 5, 0.6);
					role_y = lerp(hidepos.y(), objects[0].y * 3.75 + 290, 0.6);
					hidepos.setX(role_x);
					hidepos.setY(role_y);/*������λ���������ڵ���λ������ֵ�ڴ�����ڵ���λ��*/
				}
				else faceisu = 0;
				facesize = sies;
				faceisu = 1;
			}
			else faceisu = 0;/*����޷������������ݾͲ������µĹ���*/
			if (faceisu) {/*һ����ʱ����ʱ�䵽��ʱ�����������������һ�ֹ���*/
				if (ddp == 0) {
					if (rand() % 2 == 0)
						createaball(1, 170, 200 + (rand() % 3) * 300, -100, blue);
					else
						createaball(2, 170, 200 + (rand() % 3) * 300, -100, red);
					ddp = 5 + rand() % 30;
				}
				else ddp--;
			}
			update();/*�����Ϸ���濨ס������������������������update��Ϊupdate�����Զ�����Ҳ���޷���Ⱦ��Ϸ����*/
		}
		waitKey(30);
	}
}
void HeadDisco::drawrestartgameui() {
	QPainter painter(this);/*���������������ڿؼ��ϣ�����ʵ��Ч�����ѣ��������Ϊֱ�ӻ����ڴ�����*/
	painter.drawImage(anspos, startbk);
	painter.drawImage(anpos2, resg);
	QFont font("Microsoft YaHei", 12, QFont::Bold, false);
	painter.setPen(Qt::white);
	painter.setFont(font);
	painter.drawText(QRectF(465, 400, 200, 20), QString::fromStdString("Points:" + std::to_string(points)));
}

void HeadDisco::drawgamestartui() {//���ƽ�����Ϸui��ѡ���ڵ���ui
	QPainter painter(this);
	painter.drawImage(anspos, startbk);
	painter.drawImage(anpos2, starttiltle);
	if((uilayer)==1)
	painter.drawImage(tippos,tipg);
}
void HeadDisco::drawgameui() {//������Ϸ��������ui
	QPainter painter(this);
	QFont font("Microsoft YaHei", 9, QFont::Bold, false);
	painter.drawImage(camerapos, Cameracanvas);
	painter.drawImage(backpos, background);
	painter.drawImage(hidepos, hideimg);
	list<ball>::iterator b2 = balls.begin();
	int temp;
	while (b2 != balls.end())/*����balls���ж�ÿ��ball������Ⱦ*/
	{

		temp = b2->update(role_x, role_y);/*�ж��ڵ����Ƿ��������ײ�����򷵻�1������2������ײ0*/

		painter.drawImage(QRectF(b2->px, b2->py, 100, 100), b2->img);
		if (temp != 0) {/*��������ײ*/
			aupl.Playaudiocliponce("hit");
			if (temp == 1) {
				tipui = 15;/*��ʾ�ӷ�����*/
				points++;
			}
			else {
				tipui = -15;/*��ʾ��Ѫ����*/
				hp--; 
				if (hp <= 0) { /*��ѪС����ʱ��Ϸ���������ؿ�����*/
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

	painter.setFont(font);/*��ʾ������ֵ*/
	painter.drawText(QRectF(60, 765, 200, 20), QString::fromStdString("Face Size:" + std::to_string(facesize)));
	painter.drawText(QRectF(60, 30, 200, 20), QString::fromStdString("Points:" + std::to_string(points)));
	painter.drawText(QRectF(60, 60, 200, 20), QString::fromStdString("Hp:" + std::to_string(hp)));
	if (tipui > 0) {/*tipui > 0ʱ��Ⱦ�ӷ�ui*/
		tipui--;/*��һ������ʱʱ�䵽uiֹͣ��ʾ*/
		painter.drawImage(mpos, perf);

	}
	if (tipui < 0) {/*tipui< 0ʱ��Ⱦ����ui*/
		tipui++;
		painter.drawImage(mpos, bad);

	}

}
void  HeadDisco::paintEvent(QPaintEvent*)/*��Ⱦ��Ϸ����*/ {

	switch (uilayer)
	{
	case 0://���ƽ�����Ϸui
		drawgamestartui(); break;
	case 1://����ѡ���ڵ���ui
		drawgamestartui(); break;
	case 2://�������¿�ʼ��Ϸui
		drawrestartgameui(); break;
	case 4: //������Ϸ����ui
		drawgameui(); break;
		break;
	}

}
void HeadDisco::closeEvent(QCloseEvent*)/*�����ڽ���ʱ������ȡ����ͷ��ѭ��*/ {
	running = false;
}
HeadDisco::~HeadDisco()
{}