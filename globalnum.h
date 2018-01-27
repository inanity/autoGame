#ifndef GLOBALNUM_H
#define GLOBALNUM_H

#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>
#include <string>

#include <Qtime>
#include <QtGlobal>
#include <windows.h>

const std::string screencapName="screencap.png";

const std::string seekGame="adb shell \"ps | grep dmqmx\"";
const std::string killGame="adb shell kill ";
const std::string startservice_cmd="adb start-server";
const std::string connect_cmd="adb connect 127.0.0.1:6555";
const std::string screencap_cmd="adb shell screencap -p /sdcard/"+screencapName;
const std::string getscreencap_cmd="adb pull /sdcard/"+screencapName+" .";
const std::string clickf_cmd="adb shell input tap ";
const std::string dragf_cmd="adb shell input swipe ";

const int compartMax=20;
const int sleepMax=2000;
const int loopNum=15;
const int layerChallengeMax=30;

int bSums(cv::Mat &src);
int sleepRand();



#endif // GLOBALNUM_H
