/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include <cmath>
#include "gwindow.h"
#include "simpio.h"
using namespace std;

double const sq = sqrt(3.0);
GWindow* gw;

void drawTriangle(GPoint& point, double length){
	double centerX = point.getX();
	double centerY = point.getY();

	GPoint m1(centerX-length, centerY+sq/3*length);
	GPoint m2(centerX+length, centerY+sq/3*length);
	GPoint m3(centerX, centerY-2*sq/3*length);
	gw->drawLine(m1, m2);
	gw->drawLine(m2, m3);
	gw->drawLine(m3, m1); 
}

void drawCenterTriangle(GPoint &point, double length){
	double centerX = point.getX();
	double centerY = point.getY();
	GPoint a(centerX-length/2, centerY-sq/6*length);
	GPoint b(centerX+length/2, centerY-sq/6*length);
	GPoint c(centerX, centerY+sq/3*length);
	gw->drawLine(a, b);
	gw->drawLine(b, c);
	gw->drawLine(c, a); 
	drawTriangle(point, length);

}

void drawTriangles(GPoint& point, double length, int degree){
	double centerX = point.getX();
	double centerY = point.getY();
	
	if(degree>0){
		int newDegree = degree-1;
		drawCenterTriangle(point, length);
		GPoint a(centerX-length/2, centerY+sq/6*length);
		GPoint b(centerX+length/2, centerY+sq/6*length);
		GPoint c(centerX, centerY-sq/3*length);
		drawTriangles(a, length/2, newDegree);
		drawTriangles(b, length/2, newDegree);
		drawTriangles(c, length/2, newDegree);
	};
};

int main() {
	gw = new GWindow(600, 400);
	GPoint point(300, 200);
	double length = getReal("enter triangle length: ");
	int degree = getInteger("enter degree number: ");
	if(degree == 0){
		drawTriangle(point, length/2);
	}
	drawTriangles(point, length/2, degree);
    return 0;
}