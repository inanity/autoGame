#include <other.h>

int compareFing()
{
    cv::Mat fmodelmat;
    cv::Mat fmat;
    cv::Mat res;
    int res_num;
    fmodelmat=cv::imread(f_path,0);
    if(!fmodelmat.data)
    {
        qDebug("vsing read %s fail",f_path.c_str());
        return -1;
    }

    int count=0;
    while(1)
    {
        if(count>compartMax)
        {
            qDebug("compareFing error");
            return -1;
        }
        count++;

        sleepRand();
//        if(-1==getpicture())
//        {
//            qDebug("vsing getpicture fail");
//            return -1;
//        }
        if(-1==partpicture(f_x,f_y,f_width,f_height,fmat))
        {
            qDebug("vsing partpicture fail");
            return -1;
        }
        cv::bitwise_xor(fmat,fmodelmat,res);
        res_num=bSums(res);
        if(res_num<f_threshold)
        {
            qDebug()<<"compare f ok continue res_num:"<<res_num;
            continue;
        }
        else
        {
            qDebug()<<"compare f fail res_num:"<<res_num;
            return 0;
        }
    }
}


int comprebosshp()
{
    cv::Mat booshpmodelmat;
    cv::Mat bosshpmat;
    cv::Mat res;
    int res_num;
    booshpmodelmat=cv::imread(bosshp_path,0);
    if(!booshpmodelmat.data)
    {
        qDebug("comprebosshp read %s fail",bosshp_path.c_str());
        return -1;
    }

    if(-1==partpicture(bosshp_x,bosshp_y,bosshp_width,bosshp_height,bosshpmat,bosshp_pic_threshold))
    {
        qDebug("comprebosshp partpicture fail");
        return -1;
    }
    cv::bitwise_xor(bosshpmat,booshpmodelmat,res);
    res_num=bSums(res);
    if(res_num<booshp_threshold)
    {
        qDebug()<<"compare boss ok ";
        return 0;
    }
    else
    {
        qDebug()<<"compare boss fail ";
        return 1;
    }
}

int compare200ok()
{
    cv::Mat ok200modelmat;
    cv::Mat ok200hpmat;
    cv::Mat res;
    int res_num;
    ok200modelmat=cv::imread(ok200_path,0);
    if(!ok200modelmat.data)
    {
        qDebug("compare200ok read %s fail",ok200_path.c_str());
        return -1;
    }

    if(-1==partpicture(ok200_x,ok200_y,ok200_width,ok200_height,ok200hpmat,ok200_pic_threshold))
    {
        qDebug("compare200ok partpicture fail");
        return -1;
    }
    cv::bitwise_xor(ok200hpmat,ok200modelmat,res);
    res_num=bSums(res);
    if(res_num<ok200_threshold)
    {
        qDebug()<<"compare ok200 ok ";
        return 0;
    }
    else
    {
        qDebug()<<"compare ok200 fail ";
        return 1;
    }
}

int compare200choose()
{
    cv::Mat choose200modelmat;
    cv::Mat choose200hpmat;
    cv::Mat res;
    int res_num;
    choose200modelmat=cv::imread(comfirm_choose_path,0);
    if(!choose200modelmat.data)
    {
        qDebug("compare200choose read %s fail",comfirm_choose_path.c_str());
        return -1;
    }

    if(-1==partpicture(comfirm_x,comfirm_y,comfirm_width,comfirm_height,choose200hpmat,comfirm_pic_threshold))
    {
        qDebug("compare200choose partpicture fail");
        return -1;
    }
    cv::bitwise_xor(choose200hpmat,choose200modelmat,res);
    res_num=bSums(res);
    if(res_num<comfirm_threshold)
    {
        qDebug()<<"compare 200choose ok ";
        return 0;
    }
    else
    {
        qDebug()<<"compare 200choose fail ";
        return 1;
    }
}

int compare200layer()
{
    cv::Mat layer200modelmat;
    cv::Mat layer200hpmat;
    cv::Mat res;
    int res_num;
    layer200modelmat=cv::imread(comfirm_layer_path,0);
    if(!layer200modelmat.data)
    {
        qDebug("compare200layer read %s fail",comfirm_layer_path.c_str());
        return -1;
    }

    if(-1==partpicture(comfirm_x,comfirm_y,comfirm_width,comfirm_height,layer200hpmat,comfirm_pic_threshold))
    {
        qDebug("compare200layer partpicture fail");
        return -1;
    }
    cv::bitwise_xor(layer200hpmat,layer200modelmat,res);
    res_num=bSums(res);
    if(res_num<comfirm_threshold)
    {
        qDebug()<<"compare 200layer ok ";
        return 0;
    }
    else
    {
        qDebug()<<"compare 200layer fail ";
        return 1;
    }
}

int wait200ok()
{
    int count=0;
    int resTemp;
    while(1)
    {
        resTemp=compare200ok();
        if(-1==resTemp)
        {
            qDebug("wait200ok compare200ok error");
            return -1;
        }
        if(0==resTemp)
        {
            qDebug()<<"wait200ok compare 200ok ok";
            return 0;
        }
        else
        {
            qDebug()<<"wait200ok compare 200ok fail";
        }

        if(count>compartMax)
        {
            qDebug("wait200ok error");
            return -1;
        }
    }
}

int wait200choose()
{
    int count=0;
    int resTemp;
    while(1)
    {
        resTemp=compare200choose();
        if(-1==resTemp)
        {
            qDebug("wait200choose compare200choose error");
            return -1;
        }
        if(0==resTemp)
        {
            qDebug()<<"wait200choose compare 200choose ok";
            return 0;
        }
        else
        {
            qDebug()<<"wait200choose compare 200choose fail";
        }

        if(count>compartMax)
        {
            qDebug("wait200choose error");
            return -1;
        }
    }
}

int wait200layer()
{
    int count=0;
    int resTemp;
    while(1)
    {
        resTemp=compare200layer();
        if(-1==resTemp)
        {
            qDebug("wait200layer compare200layer error");
            return -1;
        }
        if(0==resTemp)
        {
            qDebug()<<"wait200layer compare 200layer ok";
            return 0;
        }
        else
        {
            qDebug()<<"wait200layer compare 200layer fail";
        }

        if(count>compartMax)
        {
            qDebug("wait200layer error");
            return -1;
        }
    }
}


