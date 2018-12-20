#ifndef HEADER_H
#define HEADER_H

#include <Windows.h>
#include <stdio.h>
#include <QMainWindow>
#include <QtWidgets>
#include <iostream>
//QString boolExpr[4]={"!(xy)","!(x)y","x!(y)","(xy)"};

class calc : public QWidget
{
    Q_OBJECT
private:
    bool romeIsActive;
    QSignalMapper *signalMapper,*signalOperations,*signalBoolean;
    QVBoxLayout *vlayout;
    QGridLayout *layout;
    QLabel *output,*graphic_l;
    QPushButton *zero,*one, *two, *three,*four,*five,*six,*seven,*eight,*nine,*rome,*equal;
    QPushButton *buttons[12]={zero,one, two, three,four,five,six,seven,eight,nine,rome,equal};
    QPushButton *const0_,*and_,*x_and_not_y,*x_,
                *not_x_and_y,*y_,*xor_,*or_,*nor_,
                *equ_,*not_y_,*if_y_then_x_,*not_x_,
                *if_x_then_y_,*nand_,*const1_;

    QPushButton *boolean[16]={
                    const0_,and_,x_and_not_y,x_,
                    not_x_and_y,y_,xor_,or_,nor_,
                    equ_,not_y_,if_y_then_x_,not_x_,
                    if_x_then_y_,nand_,const1_ };
    QPushButton *add,*sub,*mul,*div;
    QPushButton *operation[4]={mul,add,div,sub};
    int numbers[2],index,operationType,operationBoolType;
    bool writingNumber,boolfunc,numfunc,operationTypeGraphic;
    QCheckBox *graphic;

    int count;
    int size;
    std::string *p;    // 0	  1	  2	  3    4   5    6   7    8    9  10   11  12
    std::string s[13] = {"I","IV","V","IX","X","XL","L","XC","C","CD","D","CM","M"};
public:
    explicit calc(QWidget *parent = nullptr);

    QString toSTR(int);
    void calculation();
    void boolcalc();
    int calcul(int,int,int,int);
    int not__(int);
    int or__(int,int);
    int and__(int,int);
    void GraphicFTS(int);

    void rome_convert(int);
    int length(int);
signals:

public slots:
    void keyPressEvent(QKeyEvent *event);
    void onclick(int);
    void doOperation(int);
    void doBoolean(int);

};


#endif // HEADER_H
