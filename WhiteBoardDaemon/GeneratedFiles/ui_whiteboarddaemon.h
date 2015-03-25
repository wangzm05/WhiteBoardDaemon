/********************************************************************************
** Form generated from reading UI file 'whiteboarddaemon.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WHITEBOARDDAEMON_H
#define UI_WHITEBOARDDAEMON_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WhiteBoardDaemonClass
{
public:
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionConfiguration;
    QAction *actionAutomatic_blocking_noise;
    QAction *actionAutomatical_Calibration;
    QAction *actionProhibit_light_pen_control;
    QAction *actionExit;
    QAction *actionAdd;
    QAction *actionErase;
    QAction *action25_points;
    QAction *action36_points;
    QAction *actionCamera_Debug_Mode;
    QAction *actionLaser_Debug_Mode;
    QAction *actionIn_use_Mode;
    QAction *actionLanguage;
    QAction *actionAbout;
    QWidget *centralWidget;
    QLabel *CamView;
    QMenuBar *menuBar;
    QMenu *menuActions;
    QMenu *menuManual_covering_area;
    QMenu *menuManual_Calibration;
    QMenu *menuSet_up;
    QMenu *menuAbout;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *WhiteBoardDaemonClass)
    {
        if (WhiteBoardDaemonClass->objectName().isEmpty())
            WhiteBoardDaemonClass->setObjectName(QStringLiteral("WhiteBoardDaemonClass"));
        WhiteBoardDaemonClass->resize(651, 564);
        actionStart = new QAction(WhiteBoardDaemonClass);
        actionStart->setObjectName(QStringLiteral("actionStart"));
        actionStop = new QAction(WhiteBoardDaemonClass);
        actionStop->setObjectName(QStringLiteral("actionStop"));
        actionConfiguration = new QAction(WhiteBoardDaemonClass);
        actionConfiguration->setObjectName(QStringLiteral("actionConfiguration"));
        actionAutomatic_blocking_noise = new QAction(WhiteBoardDaemonClass);
        actionAutomatic_blocking_noise->setObjectName(QStringLiteral("actionAutomatic_blocking_noise"));
        actionAutomatical_Calibration = new QAction(WhiteBoardDaemonClass);
        actionAutomatical_Calibration->setObjectName(QStringLiteral("actionAutomatical_Calibration"));
        actionProhibit_light_pen_control = new QAction(WhiteBoardDaemonClass);
        actionProhibit_light_pen_control->setObjectName(QStringLiteral("actionProhibit_light_pen_control"));
        actionExit = new QAction(WhiteBoardDaemonClass);
        actionExit->setObjectName(QStringLiteral("actionExit"));
        actionAdd = new QAction(WhiteBoardDaemonClass);
        actionAdd->setObjectName(QStringLiteral("actionAdd"));
        actionErase = new QAction(WhiteBoardDaemonClass);
        actionErase->setObjectName(QStringLiteral("actionErase"));
        action25_points = new QAction(WhiteBoardDaemonClass);
        action25_points->setObjectName(QStringLiteral("action25_points"));
        action36_points = new QAction(WhiteBoardDaemonClass);
        action36_points->setObjectName(QStringLiteral("action36_points"));
        actionCamera_Debug_Mode = new QAction(WhiteBoardDaemonClass);
        actionCamera_Debug_Mode->setObjectName(QStringLiteral("actionCamera_Debug_Mode"));
        actionLaser_Debug_Mode = new QAction(WhiteBoardDaemonClass);
        actionLaser_Debug_Mode->setObjectName(QStringLiteral("actionLaser_Debug_Mode"));
        actionIn_use_Mode = new QAction(WhiteBoardDaemonClass);
        actionIn_use_Mode->setObjectName(QStringLiteral("actionIn_use_Mode"));
        actionLanguage = new QAction(WhiteBoardDaemonClass);
        actionLanguage->setObjectName(QStringLiteral("actionLanguage"));
        actionAbout = new QAction(WhiteBoardDaemonClass);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        centralWidget = new QWidget(WhiteBoardDaemonClass);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        CamView = new QLabel(centralWidget);
        CamView->setObjectName(QStringLiteral("CamView"));
        CamView->setGeometry(QRect(0, 0, 651, 531));
        CamView->setAlignment(Qt::AlignCenter);
        WhiteBoardDaemonClass->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(WhiteBoardDaemonClass);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 651, 23));
        menuActions = new QMenu(menuBar);
        menuActions->setObjectName(QStringLiteral("menuActions"));
        menuManual_covering_area = new QMenu(menuActions);
        menuManual_covering_area->setObjectName(QStringLiteral("menuManual_covering_area"));
        menuManual_Calibration = new QMenu(menuActions);
        menuManual_Calibration->setObjectName(QStringLiteral("menuManual_Calibration"));
        menuSet_up = new QMenu(menuBar);
        menuSet_up->setObjectName(QStringLiteral("menuSet_up"));
        menuAbout = new QMenu(menuBar);
        menuAbout->setObjectName(QStringLiteral("menuAbout"));
        WhiteBoardDaemonClass->setMenuBar(menuBar);
        mainToolBar = new QToolBar(WhiteBoardDaemonClass);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        WhiteBoardDaemonClass->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(WhiteBoardDaemonClass);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        WhiteBoardDaemonClass->setStatusBar(statusBar);

        menuBar->addAction(menuActions->menuAction());
        menuBar->addAction(menuSet_up->menuAction());
        menuBar->addAction(menuAbout->menuAction());
        menuActions->addAction(actionStart);
        menuActions->addAction(actionStop);
        menuActions->addSeparator();
        menuActions->addAction(actionConfiguration);
        menuActions->addAction(actionAutomatic_blocking_noise);
        menuActions->addAction(menuManual_covering_area->menuAction());
        menuActions->addAction(menuManual_Calibration->menuAction());
        menuActions->addAction(actionAutomatical_Calibration);
        menuActions->addSeparator();
        menuActions->addAction(actionProhibit_light_pen_control);
        menuActions->addAction(actionExit);
        menuManual_covering_area->addAction(actionAdd);
        menuManual_covering_area->addAction(actionErase);
        menuManual_Calibration->addAction(action25_points);
        menuManual_Calibration->addAction(action36_points);
        menuSet_up->addAction(actionCamera_Debug_Mode);
        menuSet_up->addAction(actionLaser_Debug_Mode);
        menuSet_up->addAction(actionIn_use_Mode);
        menuAbout->addAction(actionLanguage);
        menuAbout->addAction(actionAbout);

        retranslateUi(WhiteBoardDaemonClass);
        QObject::connect(actionConfiguration, SIGNAL(triggered()), WhiteBoardDaemonClass, SLOT(configure()));
        QObject::connect(actionAutomatical_Calibration, SIGNAL(triggered()), WhiteBoardDaemonClass, SLOT(autoCalibration()));
        QObject::connect(actionExit, SIGNAL(triggered()), WhiteBoardDaemonClass, SLOT(close()));

        QMetaObject::connectSlotsByName(WhiteBoardDaemonClass);
    } // setupUi

    void retranslateUi(QMainWindow *WhiteBoardDaemonClass)
    {
        WhiteBoardDaemonClass->setWindowTitle(QApplication::translate("WhiteBoardDaemonClass", "WhiteBoardDaemon", 0));
        actionStart->setText(QApplication::translate("WhiteBoardDaemonClass", "Start", 0));
        actionStop->setText(QApplication::translate("WhiteBoardDaemonClass", "Stop", 0));
        actionConfiguration->setText(QApplication::translate("WhiteBoardDaemonClass", "Configuration", 0));
        actionAutomatic_blocking_noise->setText(QApplication::translate("WhiteBoardDaemonClass", "Automatical blocking noise", 0));
        actionAutomatical_Calibration->setText(QApplication::translate("WhiteBoardDaemonClass", "Automatical Calibration", 0));
        actionProhibit_light_pen_control->setText(QApplication::translate("WhiteBoardDaemonClass", "Prohibit light-pen control", 0));
        actionExit->setText(QApplication::translate("WhiteBoardDaemonClass", "Exit", 0));
        actionAdd->setText(QApplication::translate("WhiteBoardDaemonClass", "Add", 0));
        actionErase->setText(QApplication::translate("WhiteBoardDaemonClass", "Erase", 0));
        action25_points->setText(QApplication::translate("WhiteBoardDaemonClass", "25 points", 0));
        action36_points->setText(QApplication::translate("WhiteBoardDaemonClass", "36 points", 0));
        actionCamera_Debug_Mode->setText(QApplication::translate("WhiteBoardDaemonClass", "Camera Debug Mode", 0));
        actionLaser_Debug_Mode->setText(QApplication::translate("WhiteBoardDaemonClass", "Laser Debug Mode", 0));
        actionIn_use_Mode->setText(QApplication::translate("WhiteBoardDaemonClass", "Normal Service Mode", 0));
        actionLanguage->setText(QApplication::translate("WhiteBoardDaemonClass", "Language", 0));
        actionAbout->setText(QApplication::translate("WhiteBoardDaemonClass", "About", 0));
        CamView->setText(QString());
        menuActions->setTitle(QApplication::translate("WhiteBoardDaemonClass", "Actions", 0));
        menuManual_covering_area->setTitle(QApplication::translate("WhiteBoardDaemonClass", "Manual covering area", 0));
        menuManual_Calibration->setTitle(QApplication::translate("WhiteBoardDaemonClass", "Manual Calibration", 0));
        menuSet_up->setTitle(QApplication::translate("WhiteBoardDaemonClass", "Setup", 0));
        menuAbout->setTitle(QApplication::translate("WhiteBoardDaemonClass", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class WhiteBoardDaemonClass: public Ui_WhiteBoardDaemonClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WHITEBOARDDAEMON_H
