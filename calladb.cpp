#include "calladb.h"

int connectgame()
{
    std::string result;
    if(0!=execmd(startservice_cmd,result))
    {
        qDebug("startservice fail\n");
        return 0;
    }
    qDebug()<<result.c_str();

    if(0!=execmd(connect_cmd,result))
    {
        qDebug("connectgame fail\n");
        return 0;
    }
    qDebug()<<result.c_str();
    return 0;
}

int killgame()
{
    std::string result;
    if(0!=execmd(seekGame,result))
    {
        qDebug("seek game fail\n");
        return -1;
    }
    qDebug()<<result.c_str();

    if(result.empty())
    {
        qDebug("seekGame empty");
        return -1;
    }

    int space1=result.find_first_of(' ',0);
    while(' '==result[space1])
        space1++;
    int space2=result.find_first_of(' ',space1);
    std::string gamepid=result.substr(space1,space2-space1);
    qDebug()<<"gamepid:"<<gamepid.c_str();

    result.clear();
    if(0!=execmd(killGame+gamepid,result))
    {
        qDebug("seek game fail\n");
        return 0;
    }
    qDebug()<<result.c_str();

    return 0;
}

int getpicture()
{
    std::string result;
    if(0!=execmd(screencap_cmd,result))
    {
        qDebug("screencap fail\n");
        return -1;
    }
    qDebug()<<result.c_str();
    result.clear();
    if(0!=execmd(getscreencap_cmd,result))
    {
        qDebug("getscreencap fail\n");
        return -1;
    }
    qDebug()<<result.c_str();
    return 0;
}

int click(const int x,const int y)
{
    sleepRand();
    std::string click_cmd=clickf_cmd+
            std::to_string(x)+" "+std::to_string(y);
    std::string result;
    if(0!=execmd(click_cmd,result))
    {
        qDebug("click (%s) fail\n",click_cmd.c_str());
        return 0;
    }
    qDebug()<<result.c_str();
    return 0;
}

int drag(int s_x,int s_y,int d_x,int d_y)
{
    sleepRand();
    qsrand(QTime(0,0,0).secsTo(QTime::currentTime()));
    int delay=qrand()%1000+100;
    std::string drag_cmd=dragf_cmd+
            std::to_string(s_x)+" "+std::to_string(s_y)+" "+
            std::to_string(d_x)+" "+std::to_string(d_y)+" "+
             std::to_string(delay);
    std::string result;
    qDebug()<<drag_cmd.c_str();
    if(0!=execmd(drag_cmd,result))
    {
        qDebug("drag (%s) fail\n",drag_cmd.c_str());
        return 0;
    }
    qDebug()<<result.c_str();
    return 0;
}

int execmd(const std::string& cmd,std::string& result)
{
    char buffer[BUFFSIZE];
    FILE* pipe = _popen(cmd.c_str(),"r");
    if(!pipe)
    {
        qDebug("cmd %s fail\n",cmd.c_str());
        return -1;
    }

    while(!feof(pipe))
    {
        if(fgets(buffer, BUFFSIZE, pipe)){
            result.append(std::string(buffer));
        }
    }

    _pclose(pipe);
    return 0;
}
