#include "mainHeader.h"
#include "cmath"
QString outp;
calc::calc(QWidget *parent) : QWidget(parent)
{
    this->setStyleSheet("background-color: black");
    setWindowTitle("Calculator");
    vlayout=new QVBoxLayout(this);
    layout=new QGridLayout();
    vlayout->addLayout(layout);
    index=0;
    QSignalMapper *signalMapper=new QSignalMapper(this);
    QSignalMapper *signalOperations=new QSignalMapper(this);
    QSignalMapper *signalBoolean=new QSignalMapper(this);
    connect(signalMapper,SIGNAL(mapped(int)),this,SLOT(onclick(int)));
    connect(signalOperations,SIGNAL(mapped(int)),this,SLOT(doOperation(int)));
    connect(signalBoolean,SIGNAL(mapped(int)),this,SLOT(doBoolean(int)));

    graphic_l=new QLabel("Graphics");

    output=new QLabel("0");
    //setbuttons();
    int lastCol,i,j;
    const QSize btnSize = QSize(50, 50);
    QRect rect=QRect(0,0,50,50);
    QRegion reg=QRegion(rect,QRegion::Ellipse);
    for(i=0;i<12;++i){
        buttons[i]=new QPushButton(static_cast<QString>(i+48));
        buttons[i]->setFixedSize(btnSize);
        buttons[i]->setStyleSheet("QPushButton { font-size:17px;color:white;background-color: grey;border:2px; border-style:solid; border-color: black }");
        buttons[i]->setMask(reg);
        signalMapper->setMapping(buttons[i],i);
        connect(buttons[i],SIGNAL(clicked()),signalMapper,SLOT(map()));
        vlayout->addWidget(buttons[i]);
    }
    for(i=0;i<4;++i)
        for(j=0;j<3;j++)
        {
            layout->addWidget(buttons[j+i*3], 4-i, j+5);
            layout->setSpacing(10);
        }
    buttons[10]->setText("Rome");
    buttons[11]->setText("=");
    buttons[11]->setStyleSheet("QPushButton { font-size:17px;color:white;background-color:orange ;border:2px; border-style:solid; border-color: orange }");

    for(i=0;i<16;++i){
        boolean[i]=new QPushButton("");
        boolean[i]->setFixedSize(btnSize);
        boolean[i]->setStyleSheet("QPushButton { font-size:14px;color:white;background-color: dimgrey;border:2px; border-style:solid; border-color: black }");
        boolean[i]->setMask(reg);
        signalBoolean->setMapping(boolean[i],i);
        connect(boolean[i],SIGNAL(clicked()),signalBoolean,SLOT(map()));
        vlayout->addWidget(boolean[i]);
    }
    for(i=0;i<4;++i)
        for(j=0;j<4;j++)
        {
            layout->addWidget(boolean[j+i*4], 4-i, j+1);
            layout->setSpacing(10);
        }
    lastCol=j;
    boolean[0]->setText("const 0");
    boolean[1]->setText("xy");
    boolean[2]->setText("x(!y)");
    boolean[3]->setText("x");
    boolean[4]->setText("(!x)y");
    boolean[5]->setText("y");
    boolean[6]->setText("x^y");
    boolean[7]->setText("x v y");
    boolean[8]->setText("!(x v y)");
    boolean[9]->setText("x~y");
    boolean[10]->setText("!y");
    boolean[11]->setText("x v !y");
    boolean[12]->setText("!x");
    boolean[13]->setText("(!x) v y");
    boolean[14]->setText("!(xy)");
    boolean[15]->setText("const 1");

    for(i=0;i<4;++i){
        operation[i]=new QPushButton("");
        operation[i]->setFixedSize(btnSize);
        operation[i]->setStyleSheet("QPushButton { font-size:17px;color:white;background-color:orange;border:2px; border-style:solid; border-color: orange }");
        operation[i]->setMask(reg);
        signalOperations->setMapping(operation[i],i);
        connect(operation[i],SIGNAL(clicked()),signalOperations,SLOT(map()));
        vlayout->addWidget(operation[i]);
    }
    for(i=0;i<4;i++)
    {
        layout->addWidget(operation[i], 4-i, 8);
        layout->setSpacing(lastCol++);
    }
    operation[0]->setText("+");
    operation[1]->setText("-");
    operation[2]->setText("x");
    operation[3]->setText("/");

    graphic=new QCheckBox();
    graphic_l->setStyleSheet("color:white");
    layout->addWidget(output,0,0,1,8);
    layout->addWidget(graphic_l,6,1);
    layout->addWidget(graphic,6,2);
    output->setStyleSheet("color:white;font-size:30px;float:right");
    romeIsActive=0;
}

void calc::onclick(int i)
{
    setWindowTitle("Works!");
    if(index!=0 || romeIsActive)output->clear();
    if(i<10 && writingNumber){
        romeIsActive=0;
        writingNumber=true;
        outp+=static_cast<QString>(i+48);
        numbers[index]=outp.toInt();
        output->setText(outp);
    }
    else if(i==10){
        outp.clear();
        romeIsActive=1;
        rome_convert(numbers[0]);
        QString Rome;// = QString::fromStdString(*p);
        for(int j=0;j<size;j++)
            Rome.append(QString::fromStdString(p[j]));
        output->setText(Rome);
        delete[]p;
        index=0;
    }
    else if(i==11 && index!=0){
        romeIsActive=0;
        if(numfunc)calculation();
        else if(boolfunc)boolcalc();
    }
}

void calc::doOperation(int sign)
{
    operationTypeGraphic=false;
    setWindowTitle("Number");
    numfunc=true;
    boolfunc=false;
    index++;
    if(index==2)
    {
        calculation();
        index=1;
    }
    outp.clear();
    operationType=sign;
}

void calc::doBoolean(int funcNumber)
{
    operationTypeGraphic=true;
    setWindowTitle("Bool");
    boolfunc=true;
    numfunc=false;
    index++;
    if(index==2)
    {
        boolcalc();
        index=1;
    }
    outp.clear();
    operationBoolType=funcNumber;
}

QString calc::toSTR(int dec)
{
    QString s;
    int var=dec,count=0,count1,current;
    if(var<0)var*=-1;
    while(var){
        var/=10;
        count++;
    }
    int *array;
    array=new int[count];
    count1=count;
    var=dec;
    if(var<0)var*=-1;
    while(var){
        current=var%10;
        var/=10;
        array[--count1]=current;
    }
    while(count--)
        s.push_front(static_cast<QChar>(array[count]+48));
    if(dec<0)s.push_front("-");
    return s;
}

void calc::calculation()
{
    int result;
    switch (operationType){
        case 0:{result=numbers[0]+numbers[1];break;}
        case 1:{result=numbers[0]-numbers[1];break;}
        case 2:{result=numbers[0]*numbers[1];break;}
        case 3:{result=numbers[0]/numbers[1];break;}
    }
    numbers[0]=result;
    outp=toSTR(result);
    index=0;
    setWindowTitle("All Worked Number");
    if(result==0)output->setText("0");
    else output->setText(toSTR(result));
    outp.clear();
    numfunc=false;
}

void calc::boolcalc()
{
    int result,combinationINT;
    switch (operationBoolType){
        case 0:{result=calcul(0,0,0,0);combinationINT=0;break;}
        case 1:{result=calcul(0,0,0,1);combinationINT=1;break;}
        case 2:{result=calcul(0,0,1,0);combinationINT=2;break;}
        case 3:{result=calcul(0,0,1,1);combinationINT=3;break;}
        case 4:{result=calcul(0,1,0,0);combinationINT=4;break;}
        case 5:{result=calcul(0,1,0,1);combinationINT=5;break;}
        case 6:{result=calcul(0,1,1,0);combinationINT=6;break;}
        case 7:{result=calcul(0,1,1,1);combinationINT=7;break;}
        case 8:{result=calcul(1,0,0,0);combinationINT=8;break;}
        case 9:{result=calcul(1,0,0,1);combinationINT=9;break;}
        case 10:{result=calcul(1,0,1,0);combinationINT=10;break;}
        case 11:{result=calcul(1,0,1,1);combinationINT=11;break;}
        case 12:{result=calcul(1,1,0,0);combinationINT=12;break;}
        case 13:{result=calcul(1,1,0,1);combinationINT=13;break;}
        case 14:{result=calcul(1,1,1,0);combinationINT=14;break;}
        case 15:{result=calcul(1,1,1,1);combinationINT=15;break;}
    }
    numbers[0]=result;
    outp=toSTR(result);
    index=0;
    setWindowTitle("All Worked Boolean");
    QString s="0";
    if(result==0)output->setText(s);
    else output->setText(toSTR(result));
    outp.clear();
    boolfunc=false;
    if(graphic->checkState())GraphicFTS(combinationINT);
}

int calc::calcul(int i1, int i2, int i3, int i4)
{
    int result;
    int max=(numbers[0]>numbers[1])?numbers[0]:numbers[1];
    if(i1==1 && i2+i3+i4==0)
        result=and__(not__(numbers[0]),not__(numbers[1]));
    else if(i2==1 && i1+i3+i4==0)
        result=and__(not__(numbers[0]),numbers[1]);
    else if(i3==1 && i1+i2+i4==0)
        result=and__(numbers[1],not__(numbers[1]));
    else if(i4==1 && i1+i2+i3==0)
        result=and__(numbers[0],numbers[1]);
    else if(i1==1 && i2==1 && i3+i4==0)
        result=not__(numbers[0]);
    else if(i1==1 && i3==1 && i2+i4==0)
        result=not__(numbers[1]);
    else if(i1==1 && i4==1 && i2+i3==0)
        result=or__(
                    and__(not__(numbers[0]),not__(numbers[1])),
                    and__(numbers[0],numbers[1])
                );
    else if(i2==1 && i3==1 && i1+i4==0)
        result=or__(
                    and__(not__(numbers[0]),numbers[1]),
                    and__(numbers[0],not__(numbers[1]))
                );
    else if(i2==1 && i4==1 && i1+i3==0)result=numbers[1];
    else if(i3==1 && i4==1 && i1+i2==0)result=numbers[1];
    else if(i1+i2+i3==3 && i4==0)result=not__(and__(numbers[0],numbers[1]));
    else if(i1+i2+i4==3 && i3==0)result=or__(not__(numbers[0]),numbers[1]);
    else if(i1+i3+i4==3 && i2==0)result=or__(numbers[0],not__(numbers[1]));
    else if(i2+i3+i4==3 && i1==0)result=or__(numbers[0],numbers[1]);
    else if(i1+i2+i3+i4==4)result=or__(max,not__(max));
    else if(i1+i2+i3+i4==0)result=and__(max,not__(max));

    return result;
}

int calc::not__(int a)
{
    int var=a,count=0;
    while(var){
        var/=2;
        count++;
    }
    var=pow(2,count)-1;
    return a^var;
}

int calc::or__(int a, int b)
{
    int var=a,count0=0;
    while(var){
        var/=2;
        count0++;
    }
    int count1=0;
    var=b;
    while(var){
        var/=2;
        count1++;
    }
    if(count0==count1)return a|b;
    else if(count0>count1){
        var=pow(2,count0-1)+b;
        return a|var;
    }
    else{
        var=pow(2,count1-1)+a;
        return var|b;
    }
}

int calc::and__(int a, int b)
{
    return a&b;
}

void calc::GraphicFTS(int comb)
{
    STARTUPINFO s;
    PROCESS_INFORMATION p;
    ZeroMemory(&s, sizeof(s));
    s.cb = sizeof(s);
    ZeroMemory(&p, sizeof(p));
    WCHAR cmd[] = L"FTSPaint.exe";
    WCHAR buffer[12];
    _itow((DWORD)comb, buffer, 10);
    SetEnvironmentVariableW(L"Combination",buffer);
    if(!CreateProcess(
            NULL,
            cmd,
            NULL,
            NULL,
            FALSE,
            0,
            NULL,
            NULL,
            &s,
            &p
            ))
        {
            wprintf(L"Error %d \n", GetLastError());
            exit(1);
        }
    CloseHandle(p.hProcess);
    CloseHandle(p.hThread);
}

int calc::length(int a)
{
    int i = 0;
    while (a) {
        a /= 10;
        i++;
    }
    return i;
}


void calc::rome_convert(int n)
{
   if (n < 0) {
           qDebug() << "Negative Number \n";
           return;
       }
   count = length(n);
   int i = 0, patik = 4 * (count - 1), l;
   size = count * 4;
   p = new std::string[size];
   if (count < 1) {
       return;
   }
   else if (count > 3) {
       if (n / 1000 > size) {
           delete[]p;
           size = n / 250;
           p = new std::string[size];
       }
       int cont = n / 1000;
       for (; cont; cont--)
           p[i++] = s[12];
       n %= 1000;
   }
   for (int j = 0; j < count; j++) {
       if (patik < 0)break;
       if (n < 10)l = n % 10;
       else  l = n / pow(10, length(n) - 1);
       if (n == 0)break;
       patik = 4 * (length(n) - 1);
       switch (l) {
          case 1: {p[i++] = s[patik]; break; }
          case 2: {p[i] = p[i + 1] = s[patik]; i += 2;  break; }
          case 3: {p[i] = p[i + 1] = p[i + 2] = s[patik]; i += 3; break; }
          case 4: {p[i++] = s[patik + 1]; break; }
          case 5: {p[i++] = s[patik + 2]; break; }
          case 6: {p[i] = s[patik + 2]; p[i + 1] = s[patik]; i += 2; break; }
          case 7: {p[i] = s[patik + 2]; p[i + 1] = p[i + 2] = s[patik]; i += 3; break; }
          case 8: {p[i] = s[patik + 2]; p[i + 1] = p[i + 2] = p[i + 3] = s[patik]; i += 4; break; }
          case 9: {p[i++] = s[patik + 3]; break; }
        }
      patik -= 4;
      n %= (int)pow(10, length(n) - 1);
  }
}

void calc::keyPressEvent(QKeyEvent *event)
{
    if(index!=0)output->clear();
    if((Qt::Key_0<=event->key()) && (event->key() <= Qt::Key_9))
    {
        onclick(event->key()-48);
    }
    else if(event->key()==Qt::Key_Equal || event->key()==Qt::Key_Return)
    {
        if(numfunc)calculation();
        else if(boolfunc)boolcalc();
    }
    else if(event->key()==Qt::Key_Plus)doOperation(0);
    else if(event->key()==Qt::Key_Minus)doOperation(1);
    else if(event->key()==Qt::Key_Asterisk)doOperation(2);
    else if(event->key()==Qt::Key_Slash)doOperation(3);
}


