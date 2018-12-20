#include "mainHeader.h"
#include <QApplication>
int main(int argc,char *argv[]){
    QApplication app(argc,argv);
    calc widget;
    widget.show();
    return app.exec();
}
