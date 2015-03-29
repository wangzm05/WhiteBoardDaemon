#ifndef WHITEBOARDDAEMON_H
#define WHITEBOARDDAEMON_H

#include <QtWidgets>
#include "ui_whiteboarddaemon.h"
#include "configdialog.h"
#include <QMessageBox>

#include <QImage>  
#include <QTimer>
#include "opencv2/opencv.hpp"
#include "utility.h"

using namespace cv;
using namespace std;

class WhiteBoardDaemon : public QMainWindow
{
	Q_OBJECT

public:
	WhiteBoardDaemon(QWidget *parent = 0);
	~WhiteBoardDaemon();

private:
	Ui::WhiteBoardDaemonClass ui;
	QTimer    *timer;
	VideoCapture cam;// camera device
	vector<Point> quad; // project area: a quadrangle
	Mat mask; // to mask the area of interest
	Mat warpMatrix; // Perspective transformation
	//Mat  frame;// frame struct
	Mat takePicture();  // take photo
	int status;
	void poly2quad(const vector<Point> poly, vector<Point> &quad);
	vector<Point> getOrderedScreenVerticles(vector<Point> quad, int w, int h);

private Q_SLOTS:
	void configure();
	void startCamara();      // open camera 
	void readFarme();       // read a frame  
	void stopCamara();     // stop camera
	void autoCalibration();
};

#endif // WHITEBOARDDAEMON_H
