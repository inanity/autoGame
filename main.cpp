#include <QCoreApplication>
#include <QDebug>
#include <iostream>
#include <opencv2/core/mat.hpp>
#include <opencv2/core/mat.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv/cv.hpp>

#include "clickgame.h"
#include "choosecard.h"
#include "readlayer.h"
#include "other.h"

int startgame();


int main(int argc, char *argv[])
{
//    cv::Mat src,image_src;
//    cv::Mat imageROI;
//    cv::Mat TempImg,TempImgRes;
//    src= cv::imread("screen2.png",0);
//    if(!src.data)
//    {
//        qFatal("read  fail\n");
//    }
//    image_src = src.clone();            //备份原图
//    imageROI = image_src(cv::Rect(screen2_ok_x, screen2_ok_y, screen2_ok_width, screen2_ok_height));    //设置待裁取ROI
//    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
//    threshold(TempImg,TempImgRes,200,255,CV_THRESH_BINARY);

//    cv::imwrite("model_screen2.png",TempImgRes);
//    return 0;

    QCoreApplication a(argc, argv);
    if(-1==connectgame())
    {
        qFatal("main connectgame faile");
        return -1;
    }

    int count=0;
    while(1)
    {
        if(-1==go_gamescreen())
        {
            qDebug()<<"go_gamescreen error";
        }
        else
        {
            if(-1==startgame())
            {
                qDebug()<<"startgame fail";
            }
        }

        if(-1==killgame())
        {
            qDebug("killgame error");
        }

        if(count>compartMax*2)
        {
            qFatal("main count more than %d",compartMax*2);
            return -1;
        }
        count++;
    }

    return a.exec();
}


int startgame()
{
    int x_add;
    int y_add;
    int currentLayer;
    int currentLayerTemp;
    int layerChallengeNum;
    for(int i=0;i<loopNum;i++)
    {
        currentLayer=0;
        currentLayerTemp=0;
        layerChallengeNum=0;
        while(1)
        {
            currentLayerTemp=readlayer();
            qDebug()<<"current layer:"<<currentLayerTemp;
            if(-1==currentLayerTemp)
            {
                qDebug("main readlayer fail");
                return -1;
            }
            if(200==currentLayerTemp)
            {
                int bosshp_res=comprebosshp();
                if(-1==bosshp_res)
                {
                    qDebug("main comprebosshp error");
                    return -1;
                }
                else if(0==bosshp_res)
                {
                    qDebug()<<"200 ok";

                    if(-1==choose_go())
                    {
                        qDebug("wait200ok choose_go fail");
                        return -1;
                    }

                    //等待200OK 出现
                    if(-1==wait200ok())
                    {
                        qDebug("main wait200ok error");
                        return -1;
                    }
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                    x_add=qrand()%ok200_width;
                    y_add=qrand()%ok200_height;
                    if(-1==click(ok200_x+x_add,ok200_y+y_add))
                    {
                        qDebug("choosing click(%d %d) 200 ok_button fail",ok200_x+x_add,ok200_y+y_add);
                        return -1;
                    }

                    //等待200choose 出现
                    if(-1==wait200choose())
                    {
                        qDebug("main wait200choose error");
                        return -1;
                    }
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                    x_add=qrand()%comfirm_width;
                    y_add=qrand()%comfirm_height;
                    if(-1==click(comfirm_x+x_add,comfirm_y+y_add))
                    {
                        qDebug("choosing click(%d %d) card ok_button fail",comfirm_x+x_add,comfirm_y+y_add);
                        return -1;
                    }

                    //等待200choose 出现
                    if(-1==wait200layer())
                    {
                        qDebug("main wait200layer error");
                        return -1;
                    }
                    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                    x_add=qrand()%comfirm_width;
                    y_add=qrand()%comfirm_height;
                    if(-1==click(comfirm_x+x_add,comfirm_y_other+y_add))
                    {
                        qDebug("choosing click(%d %d) layer ok_button fail",comfirm_x+x_add,comfirm_y+y_add);
                        return -1;
                    }

                    break;
                }
                //return 0;
            }

            if(currentLayerTemp!=currentLayer)
            {
                currentLayer=currentLayerTemp;
                layerChallengeNum=0;
                if(1!=currentLayer%10 && currentLayer%10)
                {
                    continue;
                }
                if(-1==choosing(currentLayer))
                {
                    qDebug("main choose_card1 faile");
                    return -1;
                }
                if(-1==choose_go())
                {
                    qDebug("main choose_go1 faile");
                    return -1;
                }
            }
            else
            {
                layerChallengeNum++;
                if(layerChallengeNum>layerChallengeMax)
                {
                    qDebug("challenge layer:%d num more than %d",currentLayer,layerChallengeMax);
                    return -1;
                }
                if(0==layerChallengeNum%5 && layerChallengeNum>1)
                {
                    if(0==currentLayer%10 && layerChallengeNum>11)
                    {
                        if(-1==choosing(currentLayer))
                        {
                            qDebug("main choose_card2 faile");
                            return -1;
                        }
                    }
                }
                if(-1==choose_go())
                {
                    qDebug("main choose_go2 faile");
                    return -1;
                }
            }


            sleepRand();
            if(-1==compareFing())
            {
                qDebug("main compareFing error");
                return -1;
            }

            int count=0;
            while(1)
            {
                getpicture();
                if(-1!=readlayer_unwait())
                {
                    qDebug("fight over");
                    break;
                }
                else
                {
                    qDebug()<<"fight tail";
                }
                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                x_add=qrand()%ok_width;
                y_add=qrand()%ok_height;
                if(-1==click(ok_x+x_add,ok_y+y_add+30))
                {
                    qDebug("choosing click(%d %d) challenge_ok_button fail",ok_x+x_add,ok_y+y_add);
                    return -1;
                }

                qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
                x_add=qrand()%return_width;
                y_add=qrand()%return_height;
                if(-1==click(return_x+x_add,return_y+y_add))
                {
                    qDebug("choosing click(%d %d) return_button fail",return_x+x_add,return_y+y_add);
                    return -1;
                }

                //sleepRand();
                qDebug()<<"----------";

                if(count>compartMax)
                {
                    qDebug("fight error");
                    return -1;
                }
                count++;

            }
        }
    }
    return 0;
}

