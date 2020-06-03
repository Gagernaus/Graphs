#ifndef MYWINDOW_H
#define MYWINDOW_H

#include <QDialog>
#include <QLabel>
#include <QLineEdit>
#include <QGridLayout>
#include <QPushButton>
#include <QDebug>
#include <QGraphicsItem>
#include <QtCharts>
#include <QWidget>
#include <QComboBox>

class MyWindow : public QDialog
{
    Q_OBJECT

public:
    MyWindow(QWidget *parent = 0);

private:
    QLabel *mass;
    QLabel *velocity;
    QLabel *angle;
    QLabel *airRes;
    QLabel *fuelM;
    QLabel *fuelV;
    QLabel *fuelLoss;
    QLabel *dT;
    QLabel *type;
    QLabel *x;
    QLabel *y;
    QLabel *detT;
    QLabel *dA;
    QLineEdit *leX;
    QLineEdit *leY;
    QLineEdit *leM;
    QLineEdit *leV;
    QLineEdit *leA;
    QLineEdit *leR;
    QLineEdit *leFM;
    QLineEdit *leFV;
    QLineEdit *leFL;
    QLineEdit *leDT;
    QLineEdit *leDetT;
    QLineEdit *leDa;
    QPushButton *confirm;
    QPushButton *quit;
    QComboBox *options;
    int choice;

public slots:
    void slt1();
    void optionChosen(int);
signals:
    void sgnl(int,double,double,double,double,double,double,double,double,double,double,double,double);
};

/*class sqsqsq: public QObject {
    Q_OBJECT
public slots:
    void qwert(double mass,double angle,double velocity,double airRes,double fuelM,double fuelV,double fuelL
               ,double dT){
        double PI=3.1415926535;
        double g=9.81;
        double xVelocity=velocity*cos(angle*PI/180);
        double yVelocity=velocity*sin(angle*PI/180);
        double xFuelVelocity=fuelV*cos(angle*PI/180);
        double yFuelVelocity=fuelV*sin(angle*PI/180);
        QLineSeries *series = new QLineSeries();
        flightReactiveWithRes(mass,airRes,g,dT,xVelocity,yVelocity,fuelM,fuelL,xFuelVelocity,
                                   yFuelVelocity,series);
        QChart *chart= new QChart();
        chart->legend()->hide();
        chart->addSeries(series);
        chart->createDefaultAxes();
        chart->setTitle("Reactive flight");

        emit(testsig(chart));
    }
signals:
    void testsig(QChart *);

};*/

#endif // MYWINDOW_H
