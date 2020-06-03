#include "reciever.h"

reciever::reciever(QWidget *parent): QDialog(parent)
{
    this->setWindowTitle("Graph");

    time = new QLabel("Flight time:");
    distance = new QLabel("Distance:");
    maxHigth = new QLabel("Maximum higth:");

    et = new QLineEdit;
    et->setEnabled(false);
    ed = new QLineEdit;
    ed->setEnabled(false);
    eh = new QLineEdit;
    eh->setEnabled(false);

    t = 0;
    d = 0;
    h = 0;

    quit = new QPushButton("Quit");

    grid = new QGridLayout;

    grid->addWidget(quit,7,0);

    setLayout(grid);


    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    connect(this,SIGNAL(testsig(QChart *)),this,SLOT(newChart(QChart *)));
}

void reciever::qwert(int choice,double x,double y,double mass,double angle,double velocity,
                     double airRes,double fuelM,double fuelV,double fuelL,double dT, double detT, double detA){
    qWarning()<<"signal recieved";
    double PI=3.1415926535;
    double g=9.81;
    double xVelocity=velocity*cos(angle*PI/180);
    double yVelocity=velocity*sin(angle*PI/180);
    double xFuelVelocity=fuelV*cos(angle*PI/180);
    double yFuelVelocity=fuelV*sin(angle*PI/180);
    double xDetV = fuelV*cos(detA*PI/180);
    double yDetv = fuelV*sin(detA*PI/180);
    QLineSeries *series = new QLineSeries();
    QChart *chart= new QChart();
    chart->legend()->hide();
    chart->createDefaultAxes();
    switch(choice){
    case 1:{
        normalFlight(&t,&h,&d,x,y,xVelocity,yVelocity,g,dT,series);
        chart->setTitle("Simple flight");
        qWarning()<<"Simple flight";
        break;
    }
    case 2:{
        flightWithRes(&t,&h,&d,x,y,mass,airRes,g,dT,xVelocity,yVelocity,series);
        chart->setTitle("Flight with resistance");
        qWarning()<<"Flight with resistance";
        break;
    }
    case 3:{
        flightWithResR(&t,&h,&d,x,y,mass,airRes,g,dT,xVelocity,yVelocity,series);
        chart->setTitle("Flight whith relative resistance");
        qWarning()<<"Flight with relative resistance";
        break;
    }
    case 4:{
        flightReactive(&t,&h,&d,x, y, mass, xVelocity, yVelocity, g, fuelM,
                       fuelL, xFuelVelocity, yFuelVelocity, dT, series);
        chart->setTitle("Reactive flight");
        qWarning()<<"Reactive flight";
        break;

    }
    case 5:{
        flightReactiveR(&t,&h,&d,x, y, mass, airRes, g, dT, xVelocity, yVelocity, fuelM, fuelL, xFuelVelocity, yFuelVelocity, series);
        chart->setTitle("Reactive flight with resistance");
        qWarning()<<"Reactive flight with resistance";
        break;
    }
    case 6:{
        flightReactiveWithResR(&t,&h,&d,x,y,mass,airRes,g,dT,xVelocity,yVelocity,fuelM,fuelL,xFuelVelocity,
                               yFuelVelocity,series);
        chart->setTitle("Reactive flight with relative resistance");
        qWarning()<<"Reactive flight with relative resistance";
        break;
    case 7:{
            flightWithSuddenMassChange(&t,&h,&d,x,y,mass,airRes,g,dT,xVelocity,yVelocity,fuelL,detT,xDetV,yDetv,series);
            chart->setTitle("Sudden mass change");
            qWarning()<<"Flight with sudden mass change";
            break;
        }
    default:
            qWarning()<<"error";
    }
    }
    chart->addSeries(series);
    QString a = QString::number(t);
    QString b =  QString::number(h);
    QString c =  QString::number(d);
    et->setText(a);
    eh->setText(b);
    ed->setText(c);
    t=0;
    h=0;
    emit(testsig(chart));
}


void reciever::newChart(QChart *chart){
    charView = new QChartView(chart);
    grid->addWidget(time,1,0);
    grid->addWidget(et,2,0);
    grid->addWidget(distance,3,0);
    grid->addWidget(ed,4,0);
    grid->addWidget(maxHigth,5,0);
    grid->addWidget(eh,6,0);
    grid->addWidget(charView,0,0);
    repaint();

}
