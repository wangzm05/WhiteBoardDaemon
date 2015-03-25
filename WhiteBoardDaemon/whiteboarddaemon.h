#ifndef WHITEBOARDDAEMON_H
#define WHITEBOARDDAEMON_H

#include <QtWidgets>
#include "ui_whiteboarddaemon.h"
#include "configdialog.h"
#include <QMessageBox>

#include <QImage>  
#include <QTimer>
#include "opencv2/opencv.hpp"

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
	//Mat  frame;// frame struct
	Mat takePicture();  // take photo
	void poly2quad(const vector<Point> poly, vector<Point> &quad);

private Q_SLOTS:
	void configure();
	void startCamara();      // open camera 
	void readFarme();       // read a frame  
	void stopCamara();     // stop camera
	void autoCalibration();
};

#endif // WHITEBOARDDAEMON_H
