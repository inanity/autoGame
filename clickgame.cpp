#include <clickgame.h>

int isScreen1()
{
    cv::Mat screen1modelmat;
    cv::Mat screen1mat;
    cv::Mat res;
    int res_num;
    screen1modelmat=cv::imread(screen1_path,0);
    if(!screen1modelmat.data)
    {
        qDebug("isScreen1 read %s fail",screen1_path.c_str());
        return -1;
    }

    if(-1==partpicture(screen1_x,screen1_y,screen1_width,screen1_height,screen1mat))
    {
        qDebug("isScreen1 partpicture fail");
        return -1;
    }
    cv::bitwise_xor(screen1mat,screen1modelmat,res);
    res_num=bSums(res);
    if(res_num<screen1_threshold)
    {
        qDebug()<<"isScreen1 ok ";
        return 0;
    }
    else
    {
        qDebug()<<"isScreen1 fail ";
        return 1;
    }
}

int isScreen2()
{
    cv::Mat screen2modelmat;
    cv::Mat screen2mat;
    cv::Mat res;
    int res_num;
    screen2modelmat=cv::imread(screen2_ok_path,0);
    if(!screen2modelmat.data)
    {
        qDebug("isScreen3 read %s fail",screen2_ok_path.c_str());
        return -1;
    }

    if(-1==partpicture(screen2_ok_x,screen2_ok_y,screen2_ok_width,screen2_ok_height,screen2mat,screen2_ok_pic_threshold))
    {
        qDebug("isScreen2 partpicture fail");
        return -1;
    }
    cv::bitwise_xor(screen2mat,screen2modelmat,res);
    res_num=bSums(res);
    if(res_num<screen2_ok_threshold)
    {
        qDebug()<<"isScreen2 ok ";
        return 0;
    }
    else
    {
        qDebug()<<"isScreen2 fail ";
        return 1;
    }
}

int isScreen3()
{
    cv::Mat screen3modelmat;
    cv::Mat screen3mat;
    cv::Mat res;
    int res_num;
    screen3modelmat=cv::imread(screen3_path,0);
    if(!screen3modelmat.data)
    {
        qDebug("isScreen3 read %s fail",screen3_path.c_str());
        return -1;
    }

    if(-1==partpicture(screen3_x,screen3_y,screen3_width,screen3_height,screen3mat,screen3_pic_threshold))
    {
        qDebug("isScreen3 partpicture fail");
        return -1;
    }
    cv::bitwise_xor(screen3mat,screen3modelmat,res);
    res_num=bSums(res);
    if(res_num<screen3_threshold)
    {
        qDebug()<<"isScreen3 ok ";
        return 0;
    }
    else
    {
        qDebug()<<"isScreen3 fail ";
        return 1;
    }
}

int go_gamescreen()
{
    int count;
    int temp;
    int x_add;
    int y_add;

    count=0;
    while(1)
    {
        temp=isScreen1();
        if(-1==temp)
        {
            qDebug("go_gamescreenp isScreen1 error");
            return -1;
        }
        if(0==temp)
        {
            qDebug()<<"go_gamescreen isScreen1 ok";
            break;
        }
        qDebug()<<"go_gamescreen isScreen1 fail";

        if(count>compartMax/4)
        {
            qDebug()<<"go_gamescreen compare isScreen1 more than "<<compartMax;
            return -1;
        }
        count++;
    }

//    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
//    x_add=qrand()%screen1_width;
//    y_add=qrand()%screen1_height;
//    if(-1==click(screen1_x+x_add,screen1_y+y_add))
    if(-1==click(585,145))
    {
        qDebug("choosing click(%d %d) 200 Screen1 fail",585,145);
        return -1;
    }

    count=0;
    while(1)
    {
        Sleep(3000);
        temp=isScreen2();
        if(-1==temp)
        {
            qDebug("go_gamescreenp isScreen2 error");
            return -1;
        }
        if(0==temp)
        {
            qDebug()<<"go_gamescreen isScreen2 ok";
            break;
        }
        qDebug()<<"go_gamescreen isScreen2 fail";

        if(count>compartMax)
        {
            qDebug("go_gamescreen compare isScreen2 more than %d",compartMax);
            return -1;
        }
        count++;
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    x_add=qrand()%screen2_ok_width;
    y_add=qrand()%screen2_ok_height;
    if(-1==click(screen2_ok_x+x_add,screen2_ok_y+y_add))
    {
        qDebug("choosing click(%d %d) screen2_ok fail",screen2_ok_x+x_add,screen2_ok_y+y_add);
        return -1;
    }


    count=0;
    while(1)
    {
        temp=isScreen3();
        if(-1==temp)
        {
            qDebug("go_gamescreenp isScreen3 error");
            return -1;
        }
        if(0==temp)
        {
            qDebug()<<"go_gamescreen isScreen3 ok";
            break;
        }
        qDebug()<<"go_gamescreen isScreen3 fail";

        if(count>compartMax)
        {
            qDebug("go_gamescreen compare isScreen3 more than %d",compartMax);
            return -1;
        }
        count++;
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    x_add=qrand()%screen3_width;
    y_add=qrand()%screen3_height;
    if(-1==click(screen3_x+x_add,screen3_y+y_add))
    {
        qDebug("choosing click(%d %d) screen3 fail",screen3_x+x_add,screen3_y+y_add);
        return -1;
    }

    count=0;
    while(1)
    {
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        x_add=qrand()%200;
        y_add=qrand()%200;
        if(-1==drag(900-x_add,200+y_add,100+x_add,200+y_add))
        {
            qDebug("Hdrag fail\n");
            return -1;
        }

        if(-1!=readlayer_unwait())
        {
            qDebug("go_gamescreen ok");
            break;
        }
        else
        {
            qDebug()<<"go_gamescreen fail";
        }

        if(count>compartMax/4)
        {
            qDebug("go_gamescreen drag more than %d",compartMax);
            return -1;
        }
        count++;
    }

    return 0;
}

