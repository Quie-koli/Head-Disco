#pragma once
#include <QtWidgets/QMainWindow>
#include "ui_HeadDisco.h"
#include<QCloseEvent>
#include <QPaintEvent>
#include <QPainter>
#include<opencv2/opencv.hpp>
#include<opencv2/highgui/highgui_c.h>
#include <opencv2/gapi/ocl/core.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <vector> 
#include<Windows.h>
#include <iostream> 
#include "ball.h"
#include "Audioplayer.h"
class HeadDisco : public QMainWindow
{
    Q_OBJECT

public:
    HeadDisco(QWidget *parent = nullptr);
    ~HeadDisco();
    void closeEvent(QCloseEvent*);
    void paintEvent(QPaintEvent*);
    QImage Cameracanvas, hideimg, background, blue, red,startbk,starttiltle,perf,bad,resg,tipg;
    QRectF hidepos, camerapos, backpos,anspos,anpos2,mpos,tippos;
    int role_x, role_y;
private slots:

private:
    Ui::HeadDiscoClass ui;
    int facesize;
    int points;
    int tipui;
    int uilayer,hp;
    void createaball(int tp, int r, int xm, int ym, QImage& im);
    void drawgameui();
    void drawgamestartui();
    void mousePressEvent(QMouseEvent* event);
    void startgame();
    void initgame();
    void drawrestartgameui();
    bool running;
    bool faceisu;
    bool gaming;
    Audioplayer aupl;
    std::list<ball> balls;/*普通数组无法很方便的进行增加减少成员，所以使用list类来更便于开发*/
};
