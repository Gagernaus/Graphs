#include "MyWindow.h"
#include "reciever.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MyWindow *inputWindow = new MyWindow();
    inputWindow->show();
    reciever* graphWindow = new reciever();
    graphWindow->show();
    QObject::connect(inputWindow,SIGNAL(sgnl(int,double,double,double,
                                             double,double,double,double,
                                             double,double,double,double,double))
                     ,graphWindow,SLOT(qwert(int,double,double,double,
                                             double,double,double,double,
                                             double,double,double,double,double)));
    return a.exec();
}
