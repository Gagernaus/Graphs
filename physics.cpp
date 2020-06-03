#include <iostream>
#include <stdio.h>
#include <cmath>
#include <QtCharts>

#include "physics.h"



double calcAccXRR(double airResistance, double mass, double xVelocity, double yVelocity) {
    double result = -airResistance * (xVelocity * sqrt(xVelocity * xVelocity + yVelocity * yVelocity)) / mass;
    return result;
}

double calcAccYRR(double airResistance, double g, double mass, double xVelocity, double yVelocity) {
    double result = -g - airResistance * (yVelocity * sqrt(xVelocity * xVelocity + yVelocity * yVelocity)) / mass;
    return result;
}

void flightWithResR(double *time, double *mh, double *dist,double x, double y, double mass, double airResistance, double g, double deltaT,
                    double xVelocity, double yVelocity, QLineSeries *series) {
    do {
        series->append(x,y);
        *time = *time + deltaT;
        double k1 = 0;
        double k2 = 0;
        double k3 = 0;
        double k4 = 0;
        double l1 = 0;
        double l2 = 0;
        double l3 = 0;
        double l4 = 0;
        k1 = deltaT * calcAccXRR(airResistance, mass, xVelocity, yVelocity);
        l1 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity, yVelocity);
        k2 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k1 / 2, yVelocity + l1 / 2);
        l2 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k1 / 2, yVelocity + l1 / 2);
        k3 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k2 / 2, yVelocity + l2 / 2);
        l3 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k2 / 2, yVelocity + l2 / 2);
        k4 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k3, yVelocity + l3);
        l4 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k3, yVelocity + l3);
        xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        x = x + xVelocity * deltaT;
        y = y + yVelocity * deltaT;
        if (y>*mh)
            *mh=y;
    } while (y > 0);
    *dist = x;
}

double calcAccXReactiveRR(double airResistance, double mass, double xVelocity, double yVelocity, double xFuelVelocity,
                        //double deltaT,
                         double fuelLoss) {
    double result = -airResistance * (xVelocity * sqrt(xVelocity * xVelocity + yVelocity * yVelocity)) / mass +
                    xFuelVelocity * fuelLoss / mass; // * deltaT;
    return result;
}

double
calcAccYReactiveRR(double airResistance, double g, double mass, double xVelocity, double yVelocity,
                  double yFuelVelocity,
                  //double deltaT,
                  double fuelLoss) {
    double result = -g - airResistance * (yVelocity * sqrt(xVelocity * xVelocity + yVelocity * yVelocity)) / mass +
                    yFuelVelocity * fuelLoss / mass; //* deltaT;
    return result;
}

void
flightReactiveWithResR(double *time, double *mh, double *dist, double x, double y, double mass, double airResistance, double g,
                       double deltaT, double xVelocity, double yVelocity, double fuelMass,
                       double fuelLoss, double xFuelVelocity,double yFuelVelocity,
                       QLineSeries* series) {

    do {
        *time = *time + deltaT;
        series->append(x,y);
        double c = 299792458;
        double k1 = 0;
        double k2 = 0;
        double k3 = 0;
        double k4 = 0;
        double l1 = 0;
        double l2 = 0;
        double l3 = 0;
        double l4 = 0;
        if (fuelMass > 0) {
            k1 = deltaT *
                 calcAccXReactiveRR(airResistance, mass + fuelMass, xVelocity, yVelocity, xFuelVelocity,
                                  fuelLoss);
            l1 = deltaT * calcAccYReactiveRR(airResistance, g, mass + fuelMass, xVelocity, yVelocity, yFuelVelocity,
                                           fuelLoss);
            k2 = deltaT *
                 calcAccXReactiveRR(airResistance, mass + fuelMass, xVelocity + k1 / 2, yVelocity + l1 / 2, xFuelVelocity,
                                  fuelLoss);
            l2 = deltaT * calcAccYReactiveRR(airResistance, g, mass + fuelMass, xVelocity + k1 / 2, yVelocity + l1 / 2,
                                           yFuelVelocity, fuelLoss);
            k3 = deltaT *
                 calcAccXReactiveRR(airResistance, mass + fuelMass, xVelocity + k2 / 2, yVelocity + l2 / 2, xFuelVelocity,
                                  fuelLoss);
            l3 = deltaT * calcAccYReactiveRR(airResistance, g, mass + fuelMass, xVelocity + k2 / 2, yVelocity + l2 / 2,
                                           yFuelVelocity, fuelLoss);
            k4 = deltaT *
                 calcAccXReactiveRR(airResistance, mass + fuelMass, xVelocity + k3, yVelocity + l3, xFuelVelocity,
                                  fuelLoss);
            l4 = deltaT * calcAccYReactiveRR(airResistance, g, mass + fuelMass, xVelocity + k3, yVelocity + l3,
                                           yFuelVelocity, fuelLoss);
            xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
            fuelMass = fuelMass - fuelLoss * deltaT;
        } else {
            k1 = deltaT * calcAccXRR(airResistance, mass, xVelocity, yVelocity);
            l1 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity, yVelocity);
            k2 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k1 / 2, yVelocity + l1 / 2);
            l2 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k1 / 2, yVelocity + l1 / 2);
            k3 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k2 / 2, yVelocity + l2 / 2);
            l3 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k2 / 2, yVelocity + l2 / 2);
            k4 = deltaT * calcAccXRR(airResistance, mass, xVelocity + k3, yVelocity + l3);
            l4 = deltaT * calcAccYRR(airResistance, g, mass, xVelocity + k3, yVelocity + l3);
            xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        }
        if(sqrt(xVelocity*xVelocity+yVelocity*yVelocity)>=c){
            break;
        }
        x = x + xVelocity * deltaT;
        y = y + yVelocity * deltaT;
        if (y>*mh)
            *mh=y;
    } while (y > 0);
    *dist = x;
}


void normalFlight(double *time, double *mh, double *dist, double x,double y,double xV, double yV, double g, double dT, QLineSeries* series){
    do{
        series->append(x,y);
       *time = *time + dT;
        x = x + xV*dT;
        y = y + yV*dT;
        yV = yV - g*dT;
        if (y>*mh)
            *mh=y;
    } while (y>0);
    *dist = x;
}


double calcAccXR(double airRes, double mass, double xVelocity){
    double result = -airRes*xVelocity/mass;
    return result;
}

double calcAccYR(double airRes, double g, double mass, double yVelocity){
    double result = -g -airRes*yVelocity/mass;
    return result;
}

void flightWithRes(double *time, double *mh, double *dist, double x, double y, double mass, double airResistance, double g,
                   double deltaT, double xVelocity, double yVelocity, QLineSeries *series) {
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double l1 = 0;
    double l2 = 0;
    double l3 = 0;
    double l4 = 0;
    do {
        series->append(x,y);
        *time = *time + deltaT;
        k1 = deltaT * calcAccXR(airResistance, mass, xVelocity);
        l1 = deltaT * calcAccYR(airResistance, g, mass, yVelocity);
        k2 = deltaT * calcAccXR(airResistance, mass, xVelocity + k1 / 2);
        l2 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l1 / 2);
        k3 = deltaT * calcAccXR(airResistance, mass, xVelocity + k2 / 2);
        l3 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l2 / 2);
        k4 = deltaT * calcAccXR(airResistance, mass, xVelocity + k3);
        l4 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l3);
        xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
        yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        x = x + xVelocity * deltaT;
        y = y + yVelocity * deltaT;
        if (y>*mh)
            *mh=y;
    } while (y > 0);
    *dist = x;
}


double calcAccXReactive(double xFuelV, double fuelLoss, double totalMass){
    double result = xFuelV*fuelLoss/(totalMass);
    return result;
}

double calcAccYReactive(double g, double yFuelV, double fuelLoss, double totalMass){
    double result = yFuelV*fuelLoss/(totalMass) - g;
    return result;
}

void flightReactive(double *time, double *mh, double *dist, double x, double y, double mass, double xVelocity, double yVelocity, double g, double fuelMass,
                    double fuelLoss, double xfuelVelocity,double yfuelVelocity, double dT, QLineSeries *series){
    do{
        series->append(x,y);
        *time = *time + dT;
        if (fuelMass>0){
        xVelocity = xVelocity + dT*calcAccXReactive(xfuelVelocity, fuelLoss, mass+fuelMass);
        yVelocity = yVelocity + dT*calcAccYReactive(g, yfuelVelocity, fuelLoss, mass+fuelMass);
        fuelMass = fuelMass - fuelLoss*dT;
        }
        else{
            yVelocity = yVelocity - g*dT;
        }
        x = x + xVelocity*dT;
        y = y+ yVelocity*dT;
        if (y>*mh)
            *mh=y;
     } while (y>0);
    *dist = x;
}

double calcAccXReactiveR(double airRes, double xVelocity,double xFuelV,
                         double fuelLoss, double totalMass){
    double result = -airRes*xVelocity/totalMass+xFuelV*fuelLoss/(totalMass);
    return result;
}

double calcAccYReactiveR(double airRes, double yVelocity, double g,
                         double yFuelV,double fuelLoss, double totalMass){
    double result = -g -airRes*yVelocity/totalMass + yFuelV*fuelLoss/(totalMass);
    return result;
}

void flightReactiveR(double *time, double *mh, double *dist, double x, double y, double mass, double airResistance, double g,
                     double deltaT, double xVelocity, double yVelocity, double fuelMass,
                     double fuelLoss, double xFuelVelocity,double yFuelVelocity,
                     QLineSeries* series){
    double k1 = 0;
    double k2 = 0;
    double k3 = 0;
    double k4 = 0;
    double l1 = 0;
    double l2 = 0;
    double l3 = 0;
    double l4 = 0;
    do {
        series->append(x,y);
        *time = *time + deltaT;
        if(fuelMass>0){
            k1 = deltaT * calcAccXReactiveR(airResistance,xVelocity,xFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            l1 = deltaT * calcAccYReactiveR(airResistance, yVelocity, g, yFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            k2 = deltaT * calcAccXReactiveR(airResistance,xVelocity+k1/2,xFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            l2 = deltaT * calcAccYReactiveR(airResistance, yVelocity+l1/2, g, yFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            k3 = deltaT * calcAccXReactiveR(airResistance,xVelocity+k2/2,xFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            l3 = deltaT * calcAccYReactiveR(airResistance, yVelocity+l2/2, g, yFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            k4 = deltaT * calcAccXReactiveR(airResistance,xVelocity+k3,xFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            l4 = deltaT * calcAccYReactiveR(airResistance, yVelocity+l3, g, yFuelVelocity, fuelLoss,
                                            mass+fuelMass);
            xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
            fuelMass = fuelMass - fuelLoss * deltaT;
        } else {
            k1 = deltaT * calcAccXR(airResistance, mass, xVelocity);
            l1 = deltaT * calcAccYR(airResistance, g, mass, yVelocity);
            k2 = deltaT * calcAccXR(airResistance, mass, xVelocity + k1 / 2);
            l2 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l1 / 2);
            k3 = deltaT * calcAccXR(airResistance, mass, xVelocity + k2 / 2);
            l3 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l2 / 2);
            k4 = deltaT * calcAccXR(airResistance, mass, xVelocity + k3);
            l4 = deltaT * calcAccYR(airResistance, g, mass, yVelocity + l3);
            xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
        }
        x = x + xVelocity * deltaT;
        y = y + yVelocity * deltaT;
        if (y>*mh)
            *mh=y;
    } while (y > 0);
    *dist = x;
}

void flightWithSuddenMassChange(double *time, double *mh, double *dist,double x, double y, double mass, double airResistance, double g, double deltaT,
                                double xVelocity, double yVelocity, double detMass, double detT, double detVx, double detVy, QLineSeries *series){
    double m = mass;
    bool det=false;
    do {
        series->append(x,y);
        *time = *time + deltaT;
            double k1 = 0;
            double k2 = 0;
            double k3 = 0;
            double k4 = 0;
            double l1 = 0;
            double l2 = 0;
            double l3 = 0;
            double l4 = 0;
            k1 = deltaT * calcAccXR(airResistance, m, xVelocity);
            l1 = deltaT * calcAccYR(airResistance, g, m, yVelocity);
            k2 = deltaT * calcAccXR(airResistance, m, xVelocity + k1 / 2);
            l2 = deltaT * calcAccYR(airResistance, g, m, yVelocity + l1 / 2);
            k3 = deltaT * calcAccXR(airResistance, m, xVelocity + k2 / 2);
            l3 = deltaT * calcAccYR(airResistance, g, m, yVelocity + l2 / 2);
            k4 = deltaT * calcAccXR(airResistance, m, xVelocity + k3);
            l4 = deltaT * calcAccYR(airResistance, g, m, yVelocity + l3);
            xVelocity = xVelocity + (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            yVelocity = yVelocity + (l1 + 2 * l2 + 2 * l3 + l4) / 6;
            x = x + xVelocity * deltaT;
            y = y + yVelocity * deltaT;
            if(*time>=detT&&!det){
                xVelocity = (mass*xVelocity-detMass*detVx)/(mass-detMass);
                yVelocity = (mass*yVelocity-detMass*detVy)/(mass-detMass);
                x = x+ xVelocity*deltaT;
                y = y + yVelocity*deltaT;
                m = mass - detMass;
                det=true;
            }
        if (y>*mh)
            *mh=y;
    } while (y > 0);
    *dist = x;
}
