#ifndef MYPAINT_H
#define MYPAINT_H

#include <QMainWindow>
#include <QtWidgets>

class mypaint : public QMainWindow
{
    Q_OBJECT
private:
   QPainter *paint;
   QPen *pen;
   QBrush *brush;
public:
    int combination;
    explicit mypaint(QWidget *parent = nullptr);
    virtual void paintEvent(QPaintEvent *);
    virtual void mousePressEvent(QMouseEvent *event);
    virtual void resizeEvent(QResizeEvent* event);
signals:

public slots:
   void paintFTS();
   void paintNode(int,int,QString,QPoint&,QPoint&,QPoint&,QPoint&);
   void paintInit(int,int,QString,QPoint&);
   void paintEnd(QPoint);
};

#endif // MYPAINT_H
