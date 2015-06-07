#include "whiteboarddaemon.h"

WhiteBoardDaemon::WhiteBoardDaemon(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  
	connect(ui.actionStart, SIGNAL(triggered()), this, SLOT(startCamara()));
	connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(stopCamara()));
	connect(ui.actionCamera_Debug_Mode,SIGNAL(triggered()), this, SLOT(setCameraMode()));
	connect(ui.actionLaser_Debug_Mode, SIGNAL(triggered()), this, SLOT(setLaserMode()));
	connect(ui.actionIn_use_Mode, SIGNAL(triggered()), this, SLOT(setUseMode()));

	mode = CAMERA_MODE;
	preview = STOP_PREVIEW;
	status = BEFORE_CALIBRATION;
}

WhiteBoardDaemon::~WhiteBoardDaemon()
{

}

void WhiteBoardDaemon::configure()
{
	ConfigDialog dialog(this);
	if (dialog.exec()) {
		
	}
}

void WhiteBoardDaemon::startCamara()
{
	QList<QCameraInfo> cameras = QCameraInfo::availableCameras();
	int deviceID = -1, i=0;
	foreach(const QCameraInfo &cameraInfo, cameras) {
		if (cameraInfo.deviceName().contains(DEVICE_NAME)) {
			deviceID = i;
			break;
		}
		i++;
	}

	if (deviceID == -1){
		QMessageBox msgBox;
		msgBox.setText("Our camera is not found.");
		msgBox.exec();
		return;
	}

	cam.open(deviceID); // open a specific camera
	if (!cam.isOpened())
	{
		QMessageBox msgBox;
		msgBox.setText("Camera device cannot be opened.");
		msgBox.exec();
		return;
	}
	
	if (mode == LASER_MODE) {
		// ALC_Initialize
		int nRet = ALC_Initialize();

		if (nRet == 0){
			QMessageBox msgBox;
			msgBox.setText("Initialization Error");
			msgBox.exec();
			return;
		}

		int bRet = ALC_WriteASICRegister(0xB70, 1);

		//display error message or flash data
		if (!bRet){
			QMessageBox msgBox;
			msgBox.setText("Initialization Error");
			msgBox.exec();
			return;
		}
	}

	timer->start(30);
	ui.actionStart->setChecked(true);
	ui.actionStop->setChecked(false);
	preview = START_PREVIEW;
}

void WhiteBoardDaemon::readFarme()
{
	if (!cam.isOpened()) // check if we succeeded
		return;

	Mat frame, rgb;
	cam >> frame; // get a new frame from camera
	// Mat to QImage 
	cvtColor(frame, rgb, COLOR_BGR2RGB);
	QImage image(rgb.data, rgb.cols, rgb.rows, QImage::Format_RGB888);
	ui.CamView->setPixmap(QPixmap::fromImage(image));  // Display image onto label 
}

void WhiteBoardDaemon::stopCamara()
{
	timer->stop(); 
	ui.actionStart->setChecked(false);
	ui.actionStop->setChecked(true);
	preview = STOP_PREVIEW;
}

Mat WhiteBoardDaemon::takePicture()
{
	Mat frame;
	if (!cam.isOpened()) // check if we succeeded
		return frame;

	cam >> frame; // get a new frame from camera
	return frame;
}

void WhiteBoardDaemon::autoCalibration()
{
	if (!cam.isOpened())
	{
		QMessageBox msgBox;
		msgBox.setText("Camera device has not be opened.");
		msgBox.exec();
		return;
	}
	// 1. Get desktop width and height:
	QLabel *label = new QLabel(0, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	int w = (QApplication::desktop())->width();
	int h = QApplication::desktop()->height();
	label->setGeometry(0, 0, w, h);

	// 2. Show black in full screen mode, and take picture:
	label->setPalette(Qt::black);
	label->show();
	// wait a moment
	QTime t;
	t.start();
	while (t.elapsed()<1000)
		QCoreApplication::processEvents();
	// take a picture
	Mat aframe = takePicture();

	// 3. Show white in full screen mode, and take picture:
	label->setPalette(Qt::white);
	// wait a moment
	t.restart();
	while (t.elapsed()<2000)
		QCoreApplication::processEvents();
	// take a picture
	Mat bframe = takePicture();
	label->close();

	//namedWindow("a", 1);
	//namedWindow("b", 1);
	namedWindow("area", 1);
	//namedWindow("allcontours", 1);
	namedWindow("binframe", 1);

	// 4. Gray pictures
	Mat aframe_gray, bframe_gray;
	cvtColor(aframe, aframe_gray, COLOR_RGB2GRAY);
	cvtColor(bframe, bframe_gray, COLOR_RGB2GRAY);
	// 5. Diff pictures
	Mat diff, binframe;
	absdiff(aframe_gray, bframe_gray, diff);
	// 6. Binary picture
	threshold(diff, binframe, 0, 255, THRESH_BINARY | THRESH_OTSU);
	// 7. Find contours
	// erode + dilate
	Mat kernel(5, 5, CV_8U, Scalar(1));
	morphologyEx(binframe, binframe, MORPH_OPEN, kernel);
	morphologyEx(binframe, binframe, MORPH_CLOSE, kernel);
	imshow("binframe", binframe);
	// find contours
	vector<vector<Point>> contours;
	findContours(binframe, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//imshow("binframe", binframe);
	// find the biggest contour
	int max = 0;
	vector<Point> projectArea; // project area
	vector<vector<Point>>::const_iterator it = contours.begin();
	for (; it != contours.end(); it++)
	{
		if (it->size() > max)
		{
			projectArea = *it;
			max = it->size();
		}
	}

	// Poly Approximate
	vector<Point> poly;
	int nlines = 0;//Edge counter
	double simplicity = 5;//Increment of adjustment.
	while (nlines != 4)//Adjust this 
	{
		approxPolyDP(projectArea, poly, simplicity, true);
		nlines = poly.size();
		simplicity += 5;
	}
	quad = poly;
	//approxPolyDP(projectArea, poly, 5, true);
	//poly2quad(poly, quad); // from a polygon to a quadrange
	// Draw quadrangle line
	vector<Point>::const_iterator itp = quad.begin();
	for (; itp != quad.end(); itp++)
	{
		if (itp != (quad.end()-1))
			line(bframe, *itp, *(itp + 1), Scalar(0,255,0), 2);
		else
			line(bframe, *itp, *(quad.begin()), Scalar(0,255,0), 2);
	}
	/*vector<Point>::const_iterator itp2 = poly.begin();
	for (; itp2 != poly.end(); itp2++)
	{
		if (itp2 != (poly.end() - 1))
			//line(result, *itp, *(itp+1), Scalar(0), 2);
			line(bframe, *itp2, *(itp2 + 1), Scalar(0, 0, 255), 2);
		else
			//line(result, *itp, *(poly.begin()), Scalar(0), 2);
			line(bframe, *itp2, *(poly.begin()), Scalar(0, 0, 255), 2);
	}*/


	//imshow("a", aframe_gray);
	//imshow("b", bframe_gray);

	//imshow("binframe", binframe);

	mask = Mat::zeros(binframe.size(), CV_8U);
	vector<vector<Point>> result(1, quad); 
	drawContours(mask, result, -1, Scalar(255), FILLED);

	vector<Point> screen = getOrderedScreenVerticles(quad, w, h); 
	warpMatrix = getPerspectiveTransform(quad, screen);

	status = AFTER_CALIBRATION;

	imshow("area", bframe);
}

void WhiteBoardDaemon::poly2quad(const vector<Point> poly, vector<Point> &quad)
{
	quad = poly;

	int n = poly.size() - 4;

	for (int i = 0; i < n; i++) {
		vector<Point>::const_iterator cur = quad.begin();
		vector<Point>::const_iterator maxAngle;
		double minValue = 1;

		for (; cur != quad.end(); cur++)
		{
			vector<Point>::const_iterator pre, post;
			if (cur == quad.begin()) {
				pre = quad.end() - 1;
				post = cur + 1;
			}
			else if (cur == (quad.end() - 1)) {
				pre = cur - 1;
				post = quad.begin();
			}
			else {
				pre = cur - 1;
				post = cur + 1;
			}
			double cosValue = ((pre->x - cur->x)*(post->x - cur->x) + (pre->y - cur->y)*(post->y - cur->y))/
				sqrt((pre->x - cur->x)*(pre->x - cur->x) + (pre->y - cur->y)*(pre->y - cur->y))/
				sqrt((post->x - cur->x)*(post->x - cur->x) + (post->y - cur->y)*(post->y - cur->y));
			if (cosValue < minValue) {
				maxAngle = cur;
				minValue = cosValue;
			}
		}

		quad.erase(maxAngle);
	}
}

vector<Point> WhiteBoardDaemon::getOrderedScreenVerticles(vector<Point> quad, int w, int h)
{
	int sumX = 0, sumY = 0;
	double meanX, meanY;
	for (int i = 0; i < 4; i++)
	{
		sumX += quad[i].x;
		sumY += quad[i].y;
	}
	meanX = sumX / 4.0f;
	meanY = sumY / 4.0f;

	vector<Point> screen;
	for (int i = 0; i < 4; i++)
	{
		if (quad[i].x < meanX && quad[i].y < meanY)
			screen.push_back(Point(0,0));
		else if (quad[i].x < meanX && quad[i].y >= meanY)
			screen.push_back(Point(0, h));
		else if (quad[i].x >= meanX && quad[i].y < meanY)
			screen.push_back(Point(w, 0));
		else if (quad[i].x >= meanX && quad[i].y >= meanY)
			screen.push_back(Point(w, h));
	}
	return screen;
}

void WhiteBoardDaemon::setCameraMode()
{
	if (mode == CAMERA_MODE) return;

	ui.actionCamera_Debug_Mode->setChecked(true);
	ui.actionLaser_Debug_Mode->setChecked(false);
	ui.actionIn_use_Mode->setChecked(false);

	mode = CAMERA_MODE;
	if (preview == START_PREVIEW) {
		startCamara();
	}
}

void WhiteBoardDaemon::setLaserMode()
{
	if (mode == LASER_MODE) return;

	ui.actionCamera_Debug_Mode->setChecked(false);
	ui.actionLaser_Debug_Mode->setChecked(true);
	ui.actionIn_use_Mode->setChecked(false);

	mode = LASER_MODE;
	if (preview == START_PREVIEW) {
		startCamara();
	}
}

void WhiteBoardDaemon::setUseMode()
{
	if (mode == NORMAL_MODE) return;

	ui.actionCamera_Debug_Mode->setChecked(false);
	ui.actionLaser_Debug_Mode->setChecked(false);
	ui.actionIn_use_Mode->setChecked(true);

	mode = NORMAL_MODE;
	if (preview == START_PREVIEW) {
		startCamara();
	}
}