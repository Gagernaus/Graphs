#ifndef UNTITLED_PHYSICS_H
#define UNTITLED_PHYSICS_H
#include <QtCharts>

void normalFlight(double *, double *, double *, double, double, double, double, double, double, QLineSeries*);

double calcAccXR(double, double, double);

double calcAccYR(double, double, double, double);

void flightWithRes(double *, double *, double *, double, double, double, double, double, double, double, double, QLineSeries*);

double calcAccXRR(double, double, double, double);

double calcAccYRR(double, double, double, double, double);

void flightWithResR(double *, double *, double *, double, double, double, double, double, double, double, double, QLineSeries*);

double calcAccXReactive(double, double, double);

double calcAccYReactive(double, double, double, double);

void flightReactive(double *, double *, double *, double, double, double, double, double, double, double, double, double, double, double, QLineSeries*);

double calcAccXReactiveRR(double, double, double, double, double, double);

double calcAccYReactiveRR(double, double, double, double, double, double, double);

void flightReactiveWithResR(double *, double *, double *, double, double, double, double, double, double, double, double, double, double, double, double,QLineSeries*);

double calcAccXReactiveR(double, double, double, double, double);

double calcAccYReactiveR(double, double, double, double, double, double);

void flightReactiveR(double *, double *, double *, double,double,double,double,double,double,double,double,double,double,
                     double,double, QLineSeries*);

void flightWithSuddenMassChange(double *, double *, double *,double , double , double , double , double , double , double , double , double , double , double ,double, QLineSeries *);

#endif //UNTITLED_PHYSICS_H
