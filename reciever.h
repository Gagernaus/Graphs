#ifndef RECIEVER_H
#define RECIEVER_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsItem>
#include <QtCharts>
#include <QWidget>

#include <physics.h>

class reciever: public QDialog
{
    Q_OBJECT

private:
    QChartView *charView;
    QGridLayout *grid;
    int choice;
    QPushButton *quit;
    QLabel *time;
    QLabel *distance;
    QLabel *maxHigth;
    double t;
    double d;
    double h;
    QLineEdit *et;
    QLineEdit *ed;
    QLineEdit *eh;

public:
    reciever(QWidget *parent = 0);
public slots:
    void qwert(int,double,double,double,double,double,double,double,double,double,double,double,double);
    void newChart(QChart *);
signals:
    void testsig(QChart *);

};


#endif // RECIEVER_H
