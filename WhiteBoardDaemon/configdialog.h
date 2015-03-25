#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include "ui_configdialog.h"

class ConfigDialog : public QDialog
{
	Q_OBJECT

public:
	ConfigDialog(QWidget *parent = 0);
	~ConfigDialog();

private:
	Ui::Dialog ui;
};

#endif // CONFIGDIALOG_H
