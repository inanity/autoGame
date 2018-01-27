#ifndef CALLADB_H
#define CALLADB_H

#include <fstream>
#include <string>
#include <QDebug>
#include <Qtime>
#include <QtGlobal>
#include <globalnum.h>

#include <algorithm>

const int BUFFSIZE=128;

int connectgame();
int killgame();
int getpicture();
int click(const int x,const int y);
int drag(int s_x,int s_y,int d_x,int d_y);

int execmd(const std::string& cmd,std::string& result);

#endif // CALLADB_H
