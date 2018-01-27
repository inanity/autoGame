#ifndef READLAYER_H
#define READLAYER_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

#include <globalnum.h>
#include <QDebug>
#include <calladb.h>


const std::string modelpath_head="modelnum/model";
const std::string modelpath_tail=".png";

const int MODELSIZE=10;

const int NUM_THRESHOLD=40;

void init();
int readlayer();
int readlayer_unwait();

const int hundred_x = 176;
const int hundred_y = 25;
const int decade_x  = 194;
const int decade_y  = 25;
const int unit_x    = 212;
const int unit_y    = 25;
const int width     = 20;
const int height    = 28;
int readhundred();
int readdecad();
int readunit();
int readTriNum();

const int double_decade_x   = 183;
const int double_decade_y   = 25;
const int double_unit_x     = 202;
const int double_unit_y     = 25;
int readDoubleDecad();
int readDoubleUnit();
int readDoubleNum();

const int single_unit_x = 193;
const int single_unit_y = 25;
int readSingleUnit();
int readSingleNum();

int getnum(cv::Mat &src);


#endif // READLAYER_H
