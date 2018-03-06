#include "readlayer.h"

void init()
{
//    std::string temp;
//    for(int i=0;i<MODELSIZE;i++)
//    {
//        temp.clear();
//        temp=modelpath_head+std::to_string(i)+modelpath_tail;
//        numModel[i]=cv::imread(temp,0);
//    }
}

int readlayer()
{
    int count=0;
    int layerNum=0;

    while(1)
    {
        if(count>compartMax)
        {
            qDebug("readlayer compare num more than %d",compartMax);
            return -1;
        }
        count++;

        layerNum=readlayer_unwait();
        if(-1==layerNum)
        {
            qDebug()<<"readlayer readlayer_unwait fail";
        }
        else
        {
            return layerNum;
        }
    }
}
int readlayer_unwait()
{
    int layerNum=0;

    if(-1==getpicture())
    {
        qDebug("readlayer_unwait getpicture fail");
        return -1;
    }


    layerNum=readTriNum();
    if(-1==layerNum)
    {
        qDebug()<<"readlayer_unwait readTriNum fail";
    }
    else
    {
        return layerNum;
    }

    layerNum=readDoubleNum();
    if(-1==layerNum)
    {
        qDebug()<<"readlayer_unwait readDoubleNum fail";
    }
    else
    {
        return layerNum;
    }

    layerNum=readSingleNum();
    if(-1==layerNum)
    {
        qDebug()<<"readlayer readSingleNum fail";
    }
    else
    {
        return layerNum;
    }
    return -1;
}



int readhundred()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(hundred_x, hundred_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

//    imwrite("getnum.png", TempImgRes);
//    TempImgRes= cv::imread("getnum.png",0);
//    if(!TempImgRes.data)
//    {
//        qDebug("read getnum.png fail\n");
//        return -1;
//    }

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readhundred fail");
        return -1;
    }
    return num;
}

int readdecad()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(decade_x, decade_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readdecad fail");
        return -1;
    }
    return num;
}

int readunit()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(unit_x, unit_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readhundred fail");
        return -1;
    }
    return num;
}

int readTriNum()
{
    int layerNum=0;
    int numtemp;

//    if(-1==getpicture())
//    {
//        qDebug("readlayer getpicture fail");
//        return -1;
//    }

    //获取百位数值
    numtemp=readhundred();
    if(-1==numtemp)
    {
        qDebug("readTriNum readhundred fail");
        return -1;
    }
    layerNum=layerNum*10+numtemp;

    //获取十位数值
    numtemp=readdecad();
    if(-1==numtemp)
    {
        qDebug("readTriNum readdecad fail");
        return -1;
    }
    layerNum=layerNum*10+numtemp;

    //获取个位数值
    numtemp=readunit();
    if(-1==numtemp)
    {
        qDebug("readTriNum readunit fail");
        return -1;
    }
    layerNum=layerNum*10+numtemp;

    return layerNum;
}

int readDoubleDecad()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(double_decade_x, double_decade_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readDoubleDecad fail");
        return -1;
    }
    return num;
}

int readDoubleUnit()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(double_unit_x, double_unit_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readSingleUnit fail");
        return -1;
    }
    return num;
}
int readDoubleNum()
{
    int layerNum=0;
    int numtemp;

//    if(-1==getpicture())
//    {
//        qDebug("readDoubleNum getpicture fail");
//        return -1;
//    }

    //获取十位数值
    numtemp=readDoubleDecad();
    if(-1==numtemp)
    {
        qDebug("readDoubleNum readDoubleDecad fail");
        return -1;
    }
    layerNum=layerNum*10+numtemp;

    //获取个位数值
    numtemp=readDoubleUnit();
    if(-1==numtemp)
    {
        qDebug("readDoubleNum readDoubleUnit fail");
        return -1;
    }
    layerNum=layerNum*10+numtemp;

    return layerNum;
}


int readSingleUnit()
{
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg,TempImgRes;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(single_unit_x, single_unit_y, width, height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

    int num;
    num=getnum(TempImgRes);
    if(-1==num)
    {
        qDebug("readSingleUnit fail");
        return -1;
    }
    return num;
}

int readSingleNum()
{
    int layerNum=0;

//    if(-1==getpicture())
//    {
//        qDebug("readSingleNum getpicture fail");
//        return -1;
//    }

    //获取个位数值
    layerNum=readSingleUnit();
    if(-1==layerNum)
    {
        qDebug("readSingleNum readSingleUnit fail");
        return -1;
    }

    return layerNum;
}


int getnum(cv::Mat &src)
{
    cv::Mat numModel[MODELSIZE];
    std::string temp;
    for(int i=0;i<MODELSIZE;i++)
    {
        temp.clear();
        temp=modelpath_head+std::to_string(i)+modelpath_tail;
        numModel[i]=cv::imread(temp,0);
    }

    cv::Mat matResTemp;
    int numResTemp;
    for(int i=0;i<MODELSIZE;i++)
    {
        cv::bitwise_xor(src,numModel[i],matResTemp);
        numResTemp=bSums(matResTemp);
//        qDebug()<<"i"<<i<<" "<<numResTemp;
        if(numResTemp<=NUM_THRESHOLD)
        {
            return i;
        }
    }
    return -1;
}


