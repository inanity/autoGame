#include "globalnum.h"

int bSums(cv::Mat &src)
{
    int counter = 0;
    //迭代器访问像素点
    cv::Mat_<uchar>::iterator it = src.begin<uchar>();
    cv::Mat_<uchar>::iterator itend = src.end<uchar>();
    for (; it!=itend; ++it)
    {
        if((*it)>0) counter+=1;//二值化后，像素点是0或者255
    }
    return counter;
}

int sleepRand()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int num=qrand()%sleepMax+1000;
    Sleep(num);
}
