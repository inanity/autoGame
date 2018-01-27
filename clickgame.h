#ifndef CLICKGAME_H
#define CLICKGAME_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

#include <QDebug>
#include <Qtime>
#include <QtGlobal>

#include "calladb.h"
#include "globalnum.h"
#include "choosecard.h"
#include "readlayer.h"


const int screen1_x=530;
const int screen1_y=90;
const int screen1_width=115;
const int screen1_height=115;
const std::string screen1_path="modelclickgame/model_screen1.png";
const int screen1_threshold=10;

const int screen2_ok_x=490;
const int screen2_ok_y=390;
const int screen2_ok_width=40;
const int screen2_ok_height=15;
const std::string screen2_ok_path="modelclickgame/model_screen2.png";
const int screen2_ok_pic_threshold=200;
const int screen2_ok_threshold=10;

const int screen3_x=620;
const int screen3_y=505;
const int screen3_width=35;
const int screen3_height=40;
const std::string screen3_path="modelclickgame/model_screen3.png";
const int screen3_pic_threshold=200;
const int screen3_threshold=10;

int isScreen1();
int isScreen2();
int isScreen3();

int go_gamescreen();

#endif // CLICKGAME_H
