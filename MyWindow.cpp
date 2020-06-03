#include "MyWindow.h"

MyWindow::MyWindow(QWidget *parent): QDialog(parent)
{
    this->setWindowTitle("Menu");

    x = new QLabel("Starting X");
    y = new QLabel("Starting Y");
    mass = new QLabel("Mass");
    velocity = new QLabel("Velocity");
    angle = new QLabel("Angle");
    airRes = new QLabel("Radius");
    fuelM = new QLabel("Fuel mass");
    fuelV = new QLabel("Fuel velocity / detachment velocity");
    fuelLoss = new QLabel("Fuel loss per sec / detachment mass");
    dT = new QLabel("Delta T");
    detT = new QLabel("Detachment time");
    dA = new QLabel("Detachment angle");
    type = new QLabel("Choose flight type");


    leX = new QLineEdit;
    leY = new QLineEdit;
    leM =  new QLineEdit;
    leV = new QLineEdit;
    leA = new QLineEdit;
    leR = new QLineEdit;
    leFM = new QLineEdit;
    leFV = new QLineEdit;
    leFL = new QLineEdit;
    leDT = new QLineEdit;
    leDetT = new QLineEdit;
    leDa = new QLineEdit;

    options = new QComboBox();
    options->insertItem(0,"-");
    options->insertItem(1,"Simple Flight");
    options->insertItem(2,"Flight with resistance");
    options->insertItem(3,"Flight with relative resistance");
    options->insertItem(4,"Reactive flight");
    options->insertItem(5,"Reactive flight with resistance");
    options->insertItem(6,"Reactive flight with relative resistance");
    options->insertItem(7,"Sudden mass change");


    leX->setText("0");
    leY->setText("0");
    leM->setText("0");
    leV->setText("0");
    leA->setText("0");
    leR->setText("0");
    leFM->setText("0");
    leFV->setText("0");
    leFL->setText("0");
    leDT->setText("0.001");
    leDetT->setText("0");
    leDa->setText("0");
    confirm = new QPushButton("Confirm");
    confirm->setEnabled(false);
    //confirm->setDefault(true);//enter = нажатие на кнопку
    quit = new QPushButton("Quit");

    QGridLayout *grid = new QGridLayout;

    grid->addWidget(x,0,0);
    grid->addWidget(leX,0,1);
    grid->addWidget(y,1,0);
    grid->addWidget(leY,1,1);
    grid->addWidget(dT,2,0);
    grid->addWidget(leDT,2,1);
    grid->addWidget(mass,3,0);
    grid->addWidget(leM,3,1);
    grid->addWidget(velocity,4,0);
    grid->addWidget(leV,4,1);
    grid->addWidget(angle,5,0);
    grid->addWidget(leA,5,1);
    grid->addWidget(airRes,6,0);
    grid->addWidget(leR,6,1);
    grid->addWidget(fuelM,7,0);
    grid->addWidget(leFM,7,1);
    grid->addWidget(fuelLoss,8,0);
    grid->addWidget(leFL,8,1);
    grid->addWidget(fuelV,9,0);
    grid->addWidget(leFV,9,1);    
    grid->addWidget(detT,10,0);
    grid->addWidget(leDetT,10,1);
    grid->addWidget(dA,11,0);
    grid->addWidget(leDa,11,1);
    grid->addWidget(confirm,8,2);
    grid->addWidget(quit,9,2);
    grid->addWidget(type,0,2);
    grid->addWidget(options,1,2);


    connect(confirm,SIGNAL(clicked()),this,SLOT(slt1()));
    connect(quit,SIGNAL(clicked()),this,SLOT(close()));
    connect(options,SIGNAL(activated(int)),this,SLOT(optionChosen(int)));


    setLayout(grid);
}


void MyWindow::slt1(){
    qWarning()<<"signal sent";
    double P = 1.29;    // (кг/м^3)
    double S = leR->text().toFloat()*leR->text().toFloat()*3.1415926535;  // S = M_PI*r^2
    double C = 0.47;    // безразмерный коэффициент сопротивлениЯ формы
    double k = C*S*P/2;
    emit(sgnl(choice, leX->text().toFloat(), leY->text().toFloat(), leM->text().toFloat(),
              leA->text().toFloat(),leV->text().toFloat(),k,
              leFM->text().toFloat(),leFV->text().toFloat(),leFL->text().toFloat(),leDT->text().toFloat(),leDetT->text().toFloat(),leDa->text().toFloat()));
}

void MyWindow::optionChosen(int chosen){
    if(chosen==0){
        confirm->setEnabled(false);
    }
    else{
        choice=chosen;
        confirm->setEnabled(true);
        qWarning()<<""<<choice;
    }
}


//leM->text().toFloat,leA->text().toFloat,leV->text().toFloat,
//leAR->text().toFloat,leFM->text().toFloat,leFV->text().toFloat,
//leFL->text().toFloat,leDT->text().toFloat
