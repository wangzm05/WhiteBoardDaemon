#include "whiteboarddaemon.h"
#include <QtWidgets/QApplication>

int main(int argc, char *argv[])
{
	QApplication a(argc, argv);
	WhiteBoardDaemon w;
	w.show();
	return a.exec();
}
