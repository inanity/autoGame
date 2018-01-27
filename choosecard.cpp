#include <choosecard.h>

int dragItem()
{
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x1_add=qrand()%drag_width;
    int x2_add=qrand()%drag_width;
    int y_add=qrand()%10;
    if(-1==drag(drag_x+x1_add,drag_start_y-y_add,drag_x+x2_add,drag_end_y+y_add))
    {
        qDebug("dragItem fail\n");
        return -1;
    }
    return 0;
}

int partpicture(int x,int y,int width,int height,cv::Mat &partMat,int thresholdValue)
{
    getpicture();
    cv::Mat src,image_src;
    cv::Mat imageROI;
    cv::Mat TempImg;
    src= cv::imread(screencapName,0);
    if(!src.data)
    {
        qDebug("partpicture read %s fail\n",screencapName.c_str());
        return -1;
    }
    image_src = src.clone();            //备份原图
    imageROI = image_src(cv::Rect(x,y,width,height));    //设置待裁取ROI
    imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
    threshold(TempImg,partMat,thresholdValue,255,CV_THRESH_BINARY);

    return 0;
}

int choose_go()
{
    cv::Mat matTemp;
    cv::Mat goMat;
    cv::Mat res;
    int res_num;
    goMat= cv::imread(go_path,0);
    if(!goMat.data)
    {
        qDebug("choose_go read %s fail\n",go_path.c_str());
        return -1;
    }

    int count=0;
    while(1)
    {
        if(count>compartMax)
        {
            qDebug("choose_go compare go.png error");
            return -1;
        }
        count++;

        //sleepRand();
        if(-1==dragItem())
        {
            qDebug("choose_go dragItem fail\n");
            return -1;
        }
        //sleepRand();
        if(-1==partpicture(go_x,go_y,go_width,go_height,matTemp))
        {
            qDebug("choose_go partpicture fail\n");
            return -1;
        }
        cv::bitwise_xor(matTemp,goMat,res);
        res_num=bSums(res);
        if(res_num<go_threshold)
        {
            qDebug()<<"compare go.png ok";
            break;
        }
        qDebug()<<"compare go.png fail res_num:"<<res_num;

    }

    //sleepRand();
    int x_add=qrand()%go_width;
    int y_add=qrand()%go_height;
    if(-1==click(go_x+x_add,go_y+y_add))
    {
        qDebug("choose_go click(%d,%d) fail",go_x+x_add,go_y+y_add);
        return -1;
    }

    return 0;
}

int choose_card()
{
    cv::Mat matTemp;
    cv::Mat cardMat;
    cv::Mat res;
    int res_num;
    cardMat= cv::imread(card_path,0);
    if(!cardMat.data)
    {
        qDebug("choose_card read %s fail\n",card_path.c_str());
        return -1;
    }

    int count=0;
    while(1)
    {
        if(count>compartMax)
        {
            qDebug("choose_card compare go.png error");
            return -1;
        }
        count++;

        //sleepRand();
        if(-1==dragItem())
        {
            qDebug("choose_card dragItem fail\n");
            return -1;
        }
        //sleepRand();
        if(-1==partpicture(card_x,card_y,card_width,card_height,matTemp))
        {
            qDebug("choose_card partpicture fail\n");
            return -1;
        }
        cv::bitwise_xor(matTemp,cardMat,res);
        res_num=bSums(res);
        if(res_num<card_threshold)
        {
            qDebug()<<"compare card.png ok";
            break;
        }
        qDebug()<<"compare card.png fail";
    }

    //sleepRand();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int x_add=qrand()%card_width;
    int y_add=qrand()%card_height;
    if(-1==click(card_x+x_add,card_y+y_add))
    {
        qDebug("choose_card click(%d,%d) fail",card_x+x_add,card_y+y_add);
        return -1;
    }

    return 0;
}

int choosing(int layer)
{
    int x_add;
    int y_add;


    if(-1==choose_card())
    {
        qDebug("choosing choose_card fail");
        return -1;
    }

    //选卡策略
    int cardlocal[21][5];
    std::ifstream fcard(cardlocl_path);
    if(!fcard.is_open())
    {
        qDebug("cannot open %s",cardlocl_path.c_str());
        return -1;
    }
    for(int i=0;i<21;i++)
    {
        int num;
        fcard>>num;
        if(i!=num)
        {
            qDebug("%s %d layer error",cardlocl_path.c_str(),i);
            return -1;
        }
        for(int j=0;j<5;j++)
        {
            fcard>>num;
            if(num/10<1 || num/10>PAGESIZE || num%10<1 || num%10>5)
            {
                if(0!=num)
                {
                    qDebug("layer:%d num:%d error",i,num);
                    return -1;
                }
            }
            cardlocal[i][j]=num;
        }
    }
    qDebug()<<"load cardlocal completed";

    //选择卡组下标
    int layernum;
    if(layer%10)
    {
        layernum=0;
        //小层选卡策略
        int cardlocallittlelayer[20][5];
        std::ifstream fcard_little(cardlocallittlelayer_path);
        if(!fcard_little.is_open())
        {
            qDebug("cannot open %s",cardlocallittlelayer_path.c_str());
            return -1;
        }
        for(int i=0;i<20;i++)
        {
            int num;
            fcard_little>>num;
            if(i!=num)
            {
                qDebug("%s %d layer error",cardlocallittlelayer_path.c_str(),i);
                return -1;
            }
            for(int j=0;j<5;j++)
            {
                fcard_little>>num;
                if(num/10<1 || num/10>PAGESIZE || num%10<1 || num%10>5)
                {
                    if(0!=num)
                    {
                        qDebug("layer:%d num:%d error",i,num);
                        return -1;
                    }
                }
                cardlocallittlelayer[i][j]=num;
            }
        }
        qDebug()<<"load cardlocallittlelayer completed1";

        for(int j=0;j<5;j++)
        {
            cardlocal[0][j]=cardlocallittlelayer[layer/10][j];
        }
        qDebug()<<"load cardlocallittlelayer completed2";
    }
    else
    {
        layernum=layer/10;
    }
    qDebug()<<"choose layernum:"<<layernum;

    int count;
    int currentPageNum;
    int pageNum;
    int cardNum;
    for(int i=0;i<5;i++)
    {
        if(0==cardlocal[layernum][i])
        {
            qDebug()<<"choose card num less than 5";
            break;
        }
        pageNum=cardlocal[layernum][i]/10;
        count=0;
        while(1)
        {
            count++;
            if(count>compartMax)
            {
                qDebug("choosing change page error");
                return -1;
            }

            //sleepRand();
            currentPageNum=getPageNum();
            if(-1==currentPageNum)
            {
                qDebug("choosing getPageNum error");
                return -1;
            }

            qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
            x_add=qrand()%page_button_width;
            y_add=qrand()%page_height_height;
            if(currentPageNum==pageNum)
            {
               qDebug()<<"choose page: "<<currentPageNum;
               break;
            }
            else if(currentPageNum<pageNum)
            {
                if(-1==click(next_page_button_x+x_add,page_button_y+y_add))
                {
                    qDebug("choosing click(%d %d) previous page error");
                    return -1;
                }
            }
            else
            {
                if(-1==click(previous_page_button_x+x_add,page_button_y+y_add))
                {
                    qDebug("choosing click(%d %d) next page error");
                    return -1;
                }
            }
        }//while change page

        cardNum=cardlocal[layernum][i]%10;
        //sleepRand();
        qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
        x_add=qrand()%choose_width;
        y_add=qrand()%choose_height;
        switch (cardNum) {
        case 1:
            if(-1==click(oneChoose_x+x_add,choose_y+y_add))
            {
                qDebug("choosing cardNum:%d click(%d,%d) fail",cardNum,oneChoose_x+x_add,choose_y+y_add);
                return -1;
            }
            break;
        case 2:
            if(-1==click(twoChoose_x+x_add,choose_y+y_add))
            {
                qDebug("choosing cardNum:%d click(%d,%d) fail",cardNum,twoChoose_x+x_add,choose_y+y_add);
                return -1;
            }
            break;
        case 3:
            if(-1==click(threeChoose_x+x_add,choose_y+y_add))
            {
                qDebug("choosing cardNum:%d click(%d,%d) fail",cardNum,threeChoose_x+x_add,choose_y+y_add);
                return -1;
            }
            break;
        case 4:
            if(-1==click(fourChoose_x+x_add,choose_y+y_add))
            {
                qDebug("choosing cardNum:%d click(%d,%d) fail",cardNum,fourChoose_x+x_add,choose_y+y_add);
                return -1;
            }
            break;
        case 5:
            if(-1==click(fiveChoose_x+x_add,choose_y+y_add))
            {
                qDebug("choosing cardNum:%d click(%d,%d) fail",cardNum,fiveChoose_x+x_add,choose_y+y_add);
                return -1;
            }
            break;
        default:
            qDebug("choosing layer:%d cardnum:%d err",layernum,cardlocal[layernum][i]);
            return -1;
            break;
        }
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    x_add=qrand()%challenge_button_width;
    y_add=qrand()%challenge_button_height;
    if(-1==click(challenge_button_x+x_add,challenge_button_y+y_add))
    {
        qDebug("choosing click(%d %d) challenge_button fail",challenge_button_x+x_add,challenge_button_y+y_add);
        return -1;
    }

    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    x_add=qrand()%challenge_ok_width;
    y_add=qrand()%challenge_ok_height;
    if(-1==click(challenge_ok_x+x_add,challenge_ok_y+y_add))
    {
        qDebug("choosing click(%d %d) challenge_ok_button fail",challenge_ok_x+x_add,challenge_ok_y+y_add);
        return -1;
    }

    return 0;
}

int getPageNum()
{
    cv::Mat pageMat[PAGESIZE+1];
    std::string pagepath;
    for(int i=1;i<PAGESIZE+1;i++)
    {
        pagepath.clear();
        pagepath=page_head+std::to_string(i)+page_tail;
        pageMat[i]= cv::imread(pagepath,0);
        if(!pageMat[i].data)
        {
            qDebug("choosing read %s fail\n",pagepath.c_str());
            return -1;
        }
    }

    cv::Mat currentPageMat;
    cv::Mat pageRes;
    int res_num;
    for(int j=0;j<compartMax;j++)
    {

        if(-1==partpicture(pagenum_x,pagenum_y,pagenum_width,pagenum_height,currentPageMat))
        {
            qDebug("choosing partpicture fail\n");
            return -1;
        }
        for(int i=1;i<PAGESIZE+1;i++)
        {

//            if(-1==partpicture(pagenum_x,pagenum_y,pagenum_width,pagenum_height,currentPageMat))
//            {
//                qDebug("choosing partpicture fail\n");
//                return -1;
//            }
            cv::bitwise_xor(pageMat[i],currentPageMat,pageRes);
            res_num=bSums(pageRes);
            if(res_num<page_threshold)
            {
                qDebug()<<"compare page "<<i<<".png ok";
                return i;
            }
            qDebug()<<"compare page "<<i<<".png fail";
        }
    }

    qDebug("getPageNum fail");
    return -1;
}







void getmodel()
{
    for(int i=1;i<9;i++)
    {
        char srcpath[]="choosenum/0.png";
        srcpath[10]=i+'0';
        cv::Mat src,image_src;
        cv::Mat imageROI;
        cv::Mat TempImg,TempImgRes;
        src= cv::imread(srcpath,0);
        if(!src.data)
        {
            qDebug("read %s fail\n",srcpath);
        }
        image_src = src.clone();            //备份原图
        imageROI = image_src(cv::Rect(536, 536, 22, 20));    //设置待裁取ROI
        imageROI.convertTo(TempImg, TempImg.type());        //将ROI区域拷贝至dst
        threshold(TempImg,TempImgRes,90,255,CV_THRESH_BINARY);

        char depath[]="0.png";
        depath[0]=i+'0';
        cv::imwrite(depath,TempImgRes);
        qDebug()<<i;
    }
}
