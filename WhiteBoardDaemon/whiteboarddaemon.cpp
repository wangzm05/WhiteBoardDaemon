#include "whiteboarddaemon.h"

WhiteBoardDaemon::WhiteBoardDaemon(QWidget *parent)
	: QMainWindow(parent)
{
	ui.setupUi(this);

	timer = new QTimer(this);

	connect(timer, SIGNAL(timeout()), this, SLOT(readFarme()));  
	connect(ui.actionStart, SIGNAL(triggered()), this, SLOT(startCamara()));
	connect(ui.actionStop, SIGNAL(triggered()), this, SLOT(stopCamara()));
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
	cam.open(0); // open the default camera
	if (!cam.isOpened())
	{
		QMessageBox msgBox;
		msgBox.setText("Camera device cannot be opened.");
		msgBox.exec();
		return;
	}
	timer->start(30);
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
	//vector<vector<Point>> maxContour;
	//maxContour.push_back(projectArea);
	Mat result(binframe.size(), CV_8U, Scalar(255));
	//drawContours(result, maxContour, -1, Scalar(0), 2);

	// Poly Approximate
	vector<Point> poly, quad;
	int nlines = 0;//PolyPoly counter
	double simplicity = 5;//Increment of adjustment, lower numbers may be more precise vs. high numbers being faster to cycle.
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
			//line(result, *itp, *(itp+1), Scalar(0), 2);
			line(bframe, *itp, *(itp + 1), Scalar(0,255,0), 2);
		else
			//line(result, *itp, *(poly.begin()), Scalar(0), 2);
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
	//imshow("area", result);
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
