#include "mypaint.h"

mypaint::mypaint(QWidget *parent) : QMainWindow(parent)
{
    setWindowTitle("Functional Elements Scheme ՖՏՍ");

    pen=new QPen(Qt::black);
    pen->setWidth(2);
    brush=new QBrush(Qt::white);
    this->setFixedSize(400,400);
}

void mypaint::paintEvent(QPaintEvent *event)
{
    QMainWindow::paintEvent(event);
    if(Qt::WA_Resized)setAttribute(Qt::WA_OpaquePaintEvent);
    paint=new QPainter(this);
    paint->setPen(*pen);
    paint->setBrush(*brush);
    paintFTS();
    delete paint;
}

void mypaint::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<event->x()<<" "<<event->y()<<"\n";
    update();
}
void mypaint::resizeEvent(QResizeEvent* event)
{
   QMainWindow::resizeEvent(event);
   setAttribute(Qt::WA_OpaquePaintEvent , false);
}

void mypaint::paintFTS()
{
    QPoint null,end;
    QPoint x,y;
    QPoint start_l_1,start_r_1,start_c_1,end_1;
    QPoint start_l_2,start_r_2,start_c_2,end_2;
    if(combination==0/*i1+i2+i3+i4==0*/){
            paintInit(40,10,"0",x);
            paintEnd(x);
        }
    else if(combination==1/*i4==1 && i1+i2+i3==0*/){
        paintInit(40,10,"x",x);
        paintInit(54,10,"y",y);
        paintNode(17,70,"&",start_l_2,start_r_2,null,end_2);
        paint->drawLine(x,start_l_2);
        paint->drawLine(y,start_r_2);
        paintEnd(end_2);
    }
    else if(combination==2/*i3==1 && i1+i2+i4==0*/){
        paintInit(40,10,"x",x);
        paintInit(187,10,"y",y);
        paintNode(10,100,"!",null,null,start_c_1,end_1);
        paintNode(150,170,"V",start_l_2,start_r_2,null,end_2);
        paint->drawLine(end_1,start_l_2);
        paint->drawLine(x,start_c_1);
        paint->drawLine(y,start_r_2);
        paintEnd(end_2);
    }
    else if(combination==3/*i3+i4==2 && i1+i2==0*/){
        paintInit(40,10,"x",x);
        paintEnd(x);
    }
    else if(combination==4/*i2==1 && i1+i3+i4==0*/){
        paintInit(40,10,"x",x);
        paintInit(187,10,"y",y);
        paintNode(x.x()-30,x.y()+50,"!",null,null,start_c_1,end_1);
        paintNode(150,end_1.y()+20,"&",start_l_2,start_r_2,null,end_2);
        paint->drawLine(x,start_c_1);
        paint->drawLine(y,start_r_2);
        paint->drawLine(end_1,start_l_2);
        paintEnd(end_2);
    }
    else if(combination==5/*i2+i4==2 && i1+i3==0*/){
        paintInit(40,10,"y",y);
        paintEnd(y);
    }
    else if(combination==6/*i2+i3==2 && i1+i4==0*/){
        paintInit(40,10,"x",x);
        paintInit(147,10,"y",y);
        paintNode(x.x()-30,x.y()+50,"!",null,null,start_c_1,end_1);
        paintNode(110,end_1.y()+20,"&",start_l_1,start_r_1,null,end_2);
        paint->drawLine(x,start_c_1);
        paint->drawLine(y,start_r_1);
        paint->drawLine(end_1,start_l_1);
        end=end_2;

        paintInit(230,10,"x",x);
        paintInit(337,10,"y",y);
        paintNode(y.x()-30,y.y()+50,"!",null,null,start_c_2,end_1);
        paintNode(207,end_1.y()+20,"&",start_l_2,start_r_2,null,end_2);


        paint->drawLine(x,start_l_2);
        paint->drawLine(y,start_c_2);
        paint->drawLine(end_1,start_r_2);

        paintNode(end.x()+20,end.y()+20,"V",start_l_1,start_r_1,null,end_1);
        paint->drawLine(end,start_l_1);
        paint->drawLine(start_r_1,end_2);
        paintEnd(end_1);
    }
    else if(combination==7/*i2+i3+i4==3 && i1==0*/){
        paintInit(40,10,"x",x);
        paintInit(54,10,"y",y);
        paintNode(17,x.y()+70,"V",start_l_1,start_r_1,null,end_1);
        paint->drawLine(x,start_l_1);
        paint->drawLine(y,start_r_1);
        paintEnd(end_1);
    }
    else if(combination==8/*i1==1 && i2+i3+i4==0*/){
        paintInit(40,10,"x",x);
        paintInit(54,10,"y",y);
        paintNode(17,x.y()+70,"V",start_l_1,start_r_1,null,end_1);
        paintNode(end_1.x()-30,end_1.y()+20,"!",null,null,start_c_1,end_2);
        paint->drawLine(x,start_l_1);
        paint->drawLine(y,start_r_1);
        paintEnd(end_2);
    }
    else if(combination==9/*i1+i4==2 && i2+i3==0*/){
        paintInit(40,10,"x",x);
        paintInit(54,10,"y",y);
        paintNode(17,x.y()+70,"V",start_l_1,start_r_1,null,end_1);
        paintNode(end_1.x()-30,end_1.y()+20,"!",null,null,start_c_1,end_1);
        paint->drawLine(x,start_l_1);
        paint->drawLine(y,start_r_1);

        paintInit(230,10,"x",x);
        paintInit(244,10,"y",y);
        paintNode(207,x.y()+70,"&",start_l_2,start_r_2,null,end_2);
        paint->drawLine(x,start_l_2);
        paint->drawLine(y,start_r_2);
        paint->drawLine(end_2.x(),end_2.y(),end_2.x(),end_1.y());
        paintNode((end_1.x()+end_2.x())/2.5,end_1.y()+20,"V",start_l_1,start_r_1,null,end);
        paint->drawLine(end_1,start_l_1);
        paint->drawLine(end_2.x(),end_1.y(),start_r_1.x(),start_r_1.y());
        paintEnd(end);
    }
    else if(combination==10/*i1+i3==2 && i2+i4==0*/){
        paintInit(40,10,"y",y);
        paintNode(y.x()-30,y.y()+20,"!",null,null,start_c_1,end_1);
        paintEnd(end_1);
    }
    else if(combination==11/*i1+i3+i4==3 && i2==0*/){
        paintInit(40,10,"x",x);
        paintInit(187,10,"y",y);
        paintNode(y.x()-30,y.y()+20,"!",null,null,start_c_1,end_1);

        paintNode((end_1.x()+x.x())/2,end_1.y()+20,"V",start_l_2,start_r_2,null,end_2);
        paint->drawLine(x.x(),x.y(),x.x(),end_1.y());
        paint->drawLine(x.x(),end_1.y(),start_l_2.x(),start_l_2.y());
        paint->drawLine(end_1,start_r_2);
        paintEnd(end_2);
    }
    else if(combination==12/*i1+i2==2 && i3+i4==0*/){
        paintInit(40,10,"x",x);
        paintNode(x.x()-30,x.y()+20,"!",null,null,start_c_1,end_1);
        paintEnd(end_1);
    }
    else if(combination==13/*i1+i2+i4==3 && i3==0*/){
        paintInit(40,10,"x",x);
        paintInit(187,10,"y",y);
        paintNode(x.x()-30,x.y()+20,"!",null,null,start_c_1,end_1);

        paintNode((end_1.x()+y.x())/2,end_1.y()+20,"V",start_l_2,start_r_2,null,end_2);
        paint->drawLine(y.x(),y.y(),y.x(),end_1.y());
        paint->drawLine(y.x(),end_1.y(),start_r_2.x(),start_r_2.y());
        paint->drawLine(end_1,start_l_2);
        paintEnd(end_2);
    }
    else if(combination==14/*i1+i2+i3==3 && i4==0*/){
        paintInit(40,10,"x",x);
        paintInit(54,10,"y",y);
        paintNode(17,70,"&",start_l_2,start_r_2,null,end_2);
        paint->drawLine(x,start_l_2);
        paint->drawLine(y,start_r_2);
        paintNode(end_2.x()-30,end_2.y()+20,"!",null,null,start_c_1,end_1);
        paintEnd(end_1);
    }
    else if(combination==15/*i1+i2+i3+i4==4*/){
        paintInit(40,10,"1",x);
        paintEnd(x);
    }
}

void mypaint::paintNode(int x,int y,QString type,QPoint& start_l,QPoint& start_r,QPoint& start_c,QPoint& end)
{
    int x2=x+60,x_down=x+30,y_down=y+30,space=20,
            text_x=x_down-3,text_y=(y_down+y)/2;
    QPointF points1[3] = {
         QPointF(x_down, y_down),
         QPointF(x, y),
         QPointF(x2, y),
     };
    QPoint  cord1_1(text_x,text_y);
    QPoint  l11(x_down,y-space),
            l21(x_down,y),
            l31(x_down,y_down),
            l41(x_down,y_down+space),
            l12(x_down-7,y-space),
            l22(x_down-7,y),
            l32(x_down+7,y-space),
            l42(x_down+7,y),
            l52(x_down,y_down),
            l62(x_down,y_down+space);
    paint->drawPolygon(points1,3);
    paint->drawText(cord1_1,type);
    if(type=="!"){
        paint->drawLine(l11,l21);
        paint->drawLine(l31,l41);
        end=l41;
        start_c=l11;
    }
    else if(type=="V" || type=="&"){
        paint->drawLine(l12,l22);
        paint->drawLine(l32,l42);
        paint->drawLine(l52,l62);
        end=l62;
        start_l=l12;
        start_r=l32;
    }
}

void mypaint::paintInit(int x, int y, QString s, QPoint &p)
{
    paint->drawText(x,y,s);
    p.setX(x);
    p.setY(y+10);
}

void mypaint::paintEnd(QPoint p)
{
    p.setY(p.y()+20);
    paint->drawEllipse(p,40,10);
    paint->drawLine(p.x(),p.y()-20,p.x(),p.y()-10);
}

