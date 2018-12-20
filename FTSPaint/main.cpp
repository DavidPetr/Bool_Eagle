#include "mypaint.h"
#include <windows.h>
#include <stdio.h>
#include <QApplication>

int main(int argc,char* argv[]){
    QApplication app(argc,NULL);
    mypaint window;
    WCHAR buffer[10];
    GetEnvironmentVariableW(L"Combination",buffer,10);
    window.combination= _wtoi(buffer);
    qDebug()<<window.combination<<"\n";
    window.show();
    return app.exec();
}
