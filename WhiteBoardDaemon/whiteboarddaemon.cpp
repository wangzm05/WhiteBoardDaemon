#include "whiteboarddaemon.h"

WhiteBoardDaemon::WhiteBoardDaemon(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	QIcon icon = QIcon("./Resources/icon.png");
	setWindowIcon(icon);
	trayIcon = new QSystemTrayIcon(this);
	trayIcon->setIcon(icon);
	trayIcon->setToolTip("White Board Moniter");
	trayIcon->show();
	connect(trayIcon, SIGNAL(activated(QSystemTrayIcon::ActivationReason)), this, SLOT(iconActivated(QSystemTrayIcon::ActivationReason)));
	
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

void WhiteBoardDaemon::iconActivated(QSystemTrayIcon::ActivationReason reason)
{
	switch (reason)
	{
	case QSystemTrayIcon::Trigger:
	case QSystemTrayIcon::DoubleClick:
		this->show();
		break;
	case QSystemTrayIcon::MiddleClick:
		// TODO: show menu ?
		break;
	default:
		break;
	}
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
	//cam.open(0);
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

void WhiteBoardDaemon::spotMeasurement()
{
	// 1. Get desktop width and height:
	QLabel *label = new QLabel(0, Qt::WindowStaysOnTopHint | Qt::FramelessWindowHint);
	int w = (QApplication::desktop())->width();
	int h = QApplication::desktop()->height();
	label->setGeometry(0, 0, w, h);

	// 2. Show black in full screen mode, and take picture:
	label->setPalette(Qt::blue);
	label->show();
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

	//if (status == AFTER_CALIBRATION && mode == LASER_MODE)
	if (mode == LASER_MODE)
		updateSpots(frame);
}

void WhiteBoardDaemon::updateSpots(Mat frame)
{
	//Mat rotated;
	//warpPerspective(frame, rotated, warpMatrix, rotated.size(), INTER_LINEAR, BORDER_CONSTANT);
	
	Mat frame_gray;
	//cvtColor(rotated, frame_gray, COLOR_BGR2GRAY);
	cvtColor(frame, frame_gray, COLOR_BGR2GRAY);
	Mat binframe;
	// 1. Binary picture
	threshold(frame_gray, binframe, 0, 255, THRESH_BINARY | THRESH_OTSU);
	// focus on interest area (if no rotation)
	//binframe.copyTo(binframe, mask);
	// 2. Find contours
	// erode + dilate
	Mat kernel(5, 5, CV_8U, Scalar(1));
	morphologyEx(binframe, binframe, MORPH_OPEN, kernel);
	morphologyEx(binframe, binframe, MORPH_CLOSE, kernel);
	//imshow("binframe", binframe);
	// find contours
	vector<vector<Point>> contours;
	findContours(binframe, contours, RETR_EXTERNAL, CHAIN_APPROX_NONE);
	//imshow("binframe", binframe);
	// 3. Find the spots in the range [min, max]
	vector<Spot> newSpots;
	vector<vector<Point>>::const_iterator it = contours.begin();
	namedWindow("spots", 1);
	int i = 0;
	for (; it != contours.end(); it++, i++)
	{
		// Get mass center:
		Moments mu = moments(*it, false);
		Point2f mc = Point2f(mu.m10 / mu.m00, mu.m01 / mu.m00);

		double preCalcArea = getBilinearArea(mc.x / binframe.rows, mc.y / binframe.cols);
		double max = 100;// ALPHA*preCalcArea*binframe.rows*binframe.cols;
		double min = 5;// BETA*preCalcArea*binframe.rows*binframe.cols;

		double area = contourArea(*it);
		if (area > min && area < max)
		{
			Spot newSpot(mc.x, mc.y, area);
			vector<Spot>::iterator oldSpotIt = std::find(cursorSpots.begin(), cursorSpots.end(), newSpot);
			if (oldSpotIt == cursorSpots.end()) {
				if (std::find(shieldedSpots.begin(), shieldedSpots.end(), newSpot) == shieldedSpots.end())
				{
					newSpots.push_back(newSpot);
					//drawContours(rotated, contours, i, Scalar(255,0,0), 2);
					//imshow("spots", rotated);
					drawContours(frame, contours, i, Scalar(255, 0, 0), 2);
					imshow("spots", frame);
				}
			}
			else
			{
				oldSpotIt->revisit();
				if (oldSpotIt->isAbnormal())
					shieldedSpots.push_back(*oldSpotIt);
				else
					newSpots.push_back(*oldSpotIt);
			}

		}
	}

	cursorSpots = newSpots;
}

double WhiteBoardDaemon::getBilinearArea(double x, double y)
{
	double x1, x2, y1, y2;
	double q11, q12, q21, q22;

	if (x < 0.5 && y < 0.5) {
		x1 = 0, x2 = 0.5, y1 = 0, y2 = 0.5;
		q11 = sampleVertexesArea[0], q21 = sampleVertexesArea[1], q12 = sampleVertexesArea[3], q22 = sampleVertexesArea[4];			
	}
	else if (x < 0.5 && y >= 0.5) {
		x1 = 0, x2 = 0.5, y1 = 0.5, y2 = 1;
		q11 = sampleVertexesArea[3], q21 = sampleVertexesArea[4], q12 = sampleVertexesArea[6], q22 = sampleVertexesArea[7];
	}
	else if (x >= 0.5 && y < 0.5) {
		x1 = 0.5, x2 = 1, y1 = 0, y2 = 0.5;
		q11 = sampleVertexesArea[1], q21 = sampleVertexesArea[2], q12 = sampleVertexesArea[4], q22 = sampleVertexesArea[5];
	}
	else {
		x1 = 0.5, x2 = 1, y1 = 0.5, y2 = 1;
		q11 = sampleVertexesArea[4], q21 = sampleVertexesArea[5], q12 = sampleVertexesArea[7], q22 = sampleVertexesArea[8];
	}

	return (q11*(x2 - x)*(y2 - y) + q21*(x - x1)*(y2 - y) + q12*(x2 - x)*(y - y1) + q22*(x - x1)*(y - y1)) / (x2 - x1) / (y2 - y1);;
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

	namedWindow("binframe", 1);

	// 4. Gray pictures
	Mat aframe_gray, bframe_gray;
	cvtColor(aframe, aframe_gray, COLOR_BGR2GRAY);
	cvtColor(bframe, bframe_gray, COLOR_BGR2GRAY);
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
	//imshow("binframe", binframe);
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
	int cnt = 0;
	while (nlines != 4 && cnt < 100)//Adjust this 
	{
		approxPolyDP(projectArea, poly, simplicity, true);
		nlines = poly.size();
		simplicity += 5;
		cnt++;
	}

	if (cnt >= 100) {
		QMessageBox msgBox;
		msgBox.setText("Cannot find a quadrange contour.");
		msgBox.exec();
		return;
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


	imshow("binframe", bframe);

	mask = Mat::zeros(binframe.size(), CV_8U);
	vector<vector<Point>> result(1, quad); 
	drawContours(mask, result, -1, Scalar(255), FILLED);

	vector<Point> screen = getOrderedScreenVerticles(quad, w, h);
	Point2f src[4], dst[4];
	src[0] = quad[0];
	src[1] = quad[1];
	src[2] = quad[2];
	src[3] = quad[3];
	dst[0] = screen[0];
	dst[1] = screen[1];
	dst[2] = screen[2];
	dst[3] = screen[3];

	//warpMatrix = getPerspectiveTransform(quad, screen);
	warpMatrix = getPerspectiveTransform(src, dst);

	status = AFTER_CALIBRATION;

	this->hide();
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
			screen.push_back(Point(0, h-1));
		else if (quad[i].x >= meanX && quad[i].y < meanY)
			screen.push_back(Point(w-1, 0));
		else if (quad[i].x >= meanX && quad[i].y >= meanY)
			screen.push_back(Point(w-1, h-1));
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