/********************************************************************************
** Form generated from reading UI file 'configdialog.ui'
**
** Created by: Qt User Interface Compiler version 5.4.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CONFIGDIALOG_H
#define UI_CONFIGDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>
#include <QtWidgets/QFormLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Dialog
{
public:
    QWidget *formLayoutWidget;
    QFormLayout *formLayout;
    QLabel *label;
    QLabel *label_2;
    QSpinBox *spinBox_2;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QLabel *label_4;
    QSpinBox *spinBox_4;
    QLabel *label_5;
    QSpinBox *spinBox_5;
    QSpinBox *spinBox;
    QCheckBox *checkBox;
    QRadioButton *radioButton;
    QRadioButton *radioButton_2;
    QCheckBox *checkBox_2;
    QWidget *layoutWidget;
    QHBoxLayout *horizontalLayout;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Dialog)
    {
        if (Dialog->objectName().isEmpty())
            Dialog->setObjectName(QStringLiteral("Dialog"));
        Dialog->resize(400, 265);
        formLayoutWidget = new QWidget(Dialog);
        formLayoutWidget->setObjectName(QStringLiteral("formLayoutWidget"));
        formLayoutWidget->setGeometry(QRect(30, 20, 341, 144));
        formLayout = new QFormLayout(formLayoutWidget);
        formLayout->setObjectName(QStringLiteral("formLayout"));
        formLayout->setHorizontalSpacing(80);
        formLayout->setContentsMargins(0, 0, 0, 0);
        label = new QLabel(formLayoutWidget);
        label->setObjectName(QStringLiteral("label"));

        formLayout->setWidget(0, QFormLayout::LabelRole, label);

        label_2 = new QLabel(formLayoutWidget);
        label_2->setObjectName(QStringLiteral("label_2"));

        formLayout->setWidget(1, QFormLayout::LabelRole, label_2);

        spinBox_2 = new QSpinBox(formLayoutWidget);
        spinBox_2->setObjectName(QStringLiteral("spinBox_2"));
        spinBox_2->setMinimum(3);
        spinBox_2->setMaximum(7);
        spinBox_2->setValue(4);

        formLayout->setWidget(1, QFormLayout::FieldRole, spinBox_2);

        label_3 = new QLabel(formLayoutWidget);
        label_3->setObjectName(QStringLiteral("label_3"));

        formLayout->setWidget(2, QFormLayout::LabelRole, label_3);

        spinBox_3 = new QSpinBox(formLayoutWidget);
        spinBox_3->setObjectName(QStringLiteral("spinBox_3"));
        spinBox_3->setMaximum(255);
        spinBox_3->setValue(25);

        formLayout->setWidget(2, QFormLayout::FieldRole, spinBox_3);

        label_4 = new QLabel(formLayoutWidget);
        label_4->setObjectName(QStringLiteral("label_4"));

        formLayout->setWidget(3, QFormLayout::LabelRole, label_4);

        spinBox_4 = new QSpinBox(formLayoutWidget);
        spinBox_4->setObjectName(QStringLiteral("spinBox_4"));
        spinBox_4->setMaximum(255);
        spinBox_4->setValue(90);

        formLayout->setWidget(3, QFormLayout::FieldRole, spinBox_4);

        label_5 = new QLabel(formLayoutWidget);
        label_5->setObjectName(QStringLiteral("label_5"));

        formLayout->setWidget(4, QFormLayout::LabelRole, label_5);

        spinBox_5 = new QSpinBox(formLayoutWidget);
        spinBox_5->setObjectName(QStringLiteral("spinBox_5"));
        spinBox_5->setMaximum(255);
        spinBox_5->setValue(180);

        formLayout->setWidget(4, QFormLayout::FieldRole, spinBox_5);

        spinBox = new QSpinBox(formLayoutWidget);
        spinBox->setObjectName(QStringLiteral("spinBox"));
        spinBox->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        spinBox->setMinimum(20);
        spinBox->setMaximum(80);

        formLayout->setWidget(0, QFormLayout::FieldRole, spinBox);

        checkBox = new QCheckBox(Dialog);
        checkBox->setObjectName(QStringLiteral("checkBox"));
        checkBox->setGeometry(QRect(30, 160, 101, 16));
        radioButton = new QRadioButton(Dialog);
        radioButton->setObjectName(QStringLiteral("radioButton"));
        radioButton->setGeometry(QRect(40, 180, 89, 16));
        radioButton_2 = new QRadioButton(Dialog);
        radioButton_2->setObjectName(QStringLiteral("radioButton_2"));
        radioButton_2->setGeometry(QRect(150, 180, 89, 16));
        checkBox_2 = new QCheckBox(Dialog);
        checkBox_2->setObjectName(QStringLiteral("checkBox_2"));
        checkBox_2->setGeometry(QRect(30, 200, 71, 16));
        layoutWidget = new QWidget(Dialog);
        layoutWidget->setObjectName(QStringLiteral("layoutWidget"));
        layoutWidget->setGeometry(QRect(30, 230, 341, 25));
        horizontalLayout = new QHBoxLayout(layoutWidget);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        pushButton = new QPushButton(layoutWidget);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout->addWidget(pushButton);

        pushButton_2 = new QPushButton(layoutWidget);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout->addWidget(pushButton_2);

        buttonBox = new QDialogButtonBox(layoutWidget);
        buttonBox->setObjectName(QStringLiteral("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        horizontalLayout->addWidget(buttonBox);


        retranslateUi(Dialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), Dialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Dialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(Dialog);
    } // setupUi

    void retranslateUi(QDialog *Dialog)
    {
        Dialog->setWindowTitle(QApplication::translate("Dialog", "Configuration", 0));
        label->setText(QApplication::translate("Dialog", "\345\223\215\345\272\224\345\205\211\346\226\221\345\244\247\345\260\217\346\257\224\344\276\213\357\274\21020%~80%\357\274\211", 0));
        label_2->setText(QApplication::translate("Dialog", "\346\235\277\346\223\246\344\270\216\345\205\211\346\226\221\347\232\204\345\200\215\346\225\260\357\274\2103~7\357\274\211", 0));
        label_3->setText(QApplication::translate("Dialog", "\346\255\243\345\270\270\344\275\277\347\224\250\346\227\266\347\232\204\344\272\256\345\272\246\347\263\273\346\225\260\357\274\2100~255\357\274\211", 0));
        label_4->setText(QApplication::translate("Dialog", "\350\207\252\345\212\250\346\240\241\346\255\243\346\227\266\347\232\204\345\271\263\345\235\207\347\224\273\351\235\242\344\272\256\345\272\246\357\274\2100~255\357\274\211", 0));
        label_5->setText(QApplication::translate("Dialog", "\350\207\252\345\212\250\346\240\241\346\255\243\344\270\255\347\201\260\345\272\246\345\200\274\357\274\2100~255\357\274\211", 0));
        checkBox->setText(QApplication::translate("Dialog", "\345\220\257\345\212\250\345\275\225\345\210\266\345\275\225\345\203\217", 0));
        radioButton->setText(QApplication::translate("Dialog", "\347\254\224\350\247\246\346\216\247", 0));
        radioButton_2->setText(QApplication::translate("Dialog", "\346\211\213\346\214\207\350\247\246\346\216\247", 0));
        checkBox_2->setText(QApplication::translate("Dialog", "\350\203\214\346\212\225\346\250\241\345\274\217", 0));
        pushButton->setText(QApplication::translate("Dialog", "\346\211\213\345\212\250\345\205\211\346\226\221\351\207\207\351\233\206", 0));
        pushButton_2->setText(QApplication::translate("Dialog", "Reset", 0));
    } // retranslateUi

};

namespace Ui {
    class Dialog: public Ui_Dialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CONFIGDIALOG_H
