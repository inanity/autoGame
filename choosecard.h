#ifndef CHOOSECARD_H
#define CHOOSECARD_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

#include <QDebug>
#include <Qtime>
#include <QtGlobal>

#include <calladb.h>
#include "globalnum.h"

#include <fstream>


//拖动
const int drag_x=940;
const int drag_width=40;
const int drag_start_y=580;
const int drag_end_y=20;

//进军
const int go_x=940;
const int go_y=55;
const int go_width=40;
const int go_height=60;
const std::string go_path="modellocal/go.png";
const int go_threshold=10;

//探索
const int card_x=940;
const int card_y=385;//278;
const int card_width=40;
const int card_height=60;
const std::string card_path="modellocal/card.png";
const int card_threshold=10;

//页数
const int pagenum_x=536;
const int pagenum_y=536;
const int pagenum_width=22;
const int pagenum_height=20;

const int PAGESIZE=8;
const std::string page_head="modelchoosenum/";
const std::string page_tail=".png";
const int page_threshold=10;

const int page_button_width=90;
const int page_height_height=20;
const int page_button_y=530;
const int previous_page_button_x=390;
const int next_page_button_x=625;



//选择卡片
const int choose_width=50;
const int choose_height=50;
const int choose_y=300;

const int oneChoose_x=310;
const int twoChoose_x=oneChoose_x+150;
const int threeChoose_x=twoChoose_x+150;
const int fourChoose_x=threeChoose_x+150;
const int fiveChoose_x=fourChoose_x+150;

const std::string cardlocl_path="cardlocal.txt";
const std::string cardlocallittlelayer_path="cardlocallittlelayer.txt";

//开始挑战按钮
const int challenge_button_x=860;
const int challenge_button_y=530;
const int challenge_button_width=100;
const int challenge_button_height=30;

//确认卡组按钮
const int challenge_ok_x=480;
const int challenge_ok_y=390;
const int challenge_ok_width=60;
const int challenge_ok_height=35;

int dragItem();
int partpicture(int x,int y,int width,int height,cv::Mat &partMat,int thresholdValue=90);
int choose_go();
int choose_card();
int choosing(int layer,bool flag=true);
int getPageNum();



//获取模板
void getmodel();
#endif // CHOOSECARD_H
