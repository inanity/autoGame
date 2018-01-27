#ifndef OTHER_H
#define OTHER_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

#include <QDebug>
#include <Qtime>
#include <QtGlobal>

#include <calladb.h>
#include "globalnum.h"
#include "choosecard.h"

const int f_x=10;
const int f_y=340;
const int f_width=20;
const int f_height=20;

const std::string f_path="modelother/modelvs.png";
const int f_threshold=10;

//确认按钮
const int ok_x=480;
const int ok_y=390;
const int ok_width=60;
const int ok_height=35;

//得到卡退出
const int return_x=50;
const int return_y=520;
const int return_width=25;
const int return_height=30;

//200血条
const int bosshp_x=740;
const int bosshp_y=148;
const int bosshp_width=275;
const int bosshp_height=30;
const int bosshp_pic_threshold=150;
const std::string bosshp_path="modelother/bosshp.png";
const int booshp_threshold=10;


//200 ok确认
const int ok200_x=490;
const int ok200_y=385;
const int ok200_width=45;
const int ok200_height=25;
const int ok200_pic_threshold=160;
const std::string ok200_path="modelother/model_200_ok.png";
const int ok200_threshold=10;

//200 通过确认
const int comfirm_x=450;
const int comfirm_y=415;
const int comfirm_width=110;
const int comfirm_height=30;
const int comfirm_pic_threshold=160;
const std::string comfirm_choose_path="modelother/model_200_choose.png";
const std::string comfirm_layer_path="modelother/model_200_layer.png";
const int comfirm_threshold=10;

const int comfirm_y_other=340;

int compareFing();
int comprebosshp();

int compare200ok();
int compare200choose();
int compare200layer();

int wait200ok();
int wait200choose();
int wait200layer();


#endif // OTHER_H
