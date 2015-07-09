#ifndef WHITEBOARDDAEMON_H
#define WHITEBOARDDAEMON_H

#include <QtWidgets>
#include "ui_whiteboarddaemon.h"
#include "configdialog.h"
#include <QMessageBox>

#include <QImage>  
#include <QTimer>
#include <QtMultimedia/Qcamerainfo.h>
#include <QtMultimedia/Qcamera.h>
#include "opencv2/opencv.hpp"
#include "utility.h"
#include "ACamDll.h"
#include <algorithm>

using namespace cv;
using namespace std;

class Spot
{
	friend bool operator==(const Spot & a, const Spot & b);
public:
	Spot(int x, int y, double area) {
		this->x = x;
		this->y = y;
		this->area = area;
		this->count = 1;
	}

	void revisit() { this->count++; }
	bool isAbnormal() { if (count >= MAX_COUNT) return true; else return false; };
private:
	double x, y;
	double area;
	int count;

};

inline bool operator==(const Spot & a, const Spot & b)
{
	double distance = fabs(a.x - b.x) + fabs(a.y - b.y);
	double diffArea = fabs(a.area - b.area);

	if (distance < EPSILON && diffArea < EPSILON)
		return true;
	else
		return false;
}

class WhiteBoardDaemon : public QMainWindow
{
	Q_OBJECT

public:
	WhiteBoardDaemon(QWidget *parent = 0);
	~WhiteBoardDaemon();

private:
	Ui::WhiteBoardDaemonClass ui;
	QSystemTrayIcon* trayIcon;
	QTimer    *timer;
	VideoCapture cam;// camera device
	vector<Point> quad; // project area: a quadrangle
	Mat mask; // to mask the area of interest
	Mat warpMatrix; // Perspective transformation
	//Mat  frame;// frame struct
	Mat takePicture();  // take photo
	int status;
	int mode; // 1: Camera; 2: Laser; 3: normal
	int preview; // 1: start; 0: stop;
	vector<Spot> cursorSpots; // light spots from fingers
	vector<Spot> shieldedSpots; // shilded spots
	double sampleVertexesArea[9]; // [x,y]: [0,0] [0.5,0] [1,0] [0,0.5] [0.5,0.5] [0.5, 1] [1,0] [1,0.5] [1,1]

	double getBilinearArea(double x, double y);
	void poly2quad(const vector<Point> poly, vector<Point> &quad);
	vector<Point> getOrderedScreenVerticles(vector<Point> quad, int w, int h);

private Q_SLOTS:
	void configure();
	void startCamara();      // open camera 
	void readFarme();       // read a frame  
	void stopCamara();     // stop camera
	void spotMeasurement();
	void autoCalibration();
	void setCameraMode();
	void setLaserMode();
	void setUseMode();
	void updateSpots(Mat frame);
	void iconActivated(QSystemTrayIcon::ActivationReason reason);
};


#endif // WHITEBOARDDAEMON_H
