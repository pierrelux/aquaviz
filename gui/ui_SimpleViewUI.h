/********************************************************************************
** Form generated from reading UI file 'SimpleViewUI.ui'
**
** Created: Sun Feb 20 14:05:34 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIMPLEVIEWUI_H
#define UI_SIMPLEVIEWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_SimpleView
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QAction *action_Connect;
    QAction *action_Quit;
    QAction *action_About;
    QWidget *centralwidget;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menu_Help;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SimpleView)
    {
        if (SimpleView->objectName().isEmpty())
            SimpleView->setObjectName(QString::fromUtf8("SimpleView"));
        SimpleView->resize(794, 600);
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SimpleView->sizePolicy().hasHeightForWidth());
        SimpleView->setSizePolicy(sizePolicy);
        actionOpenFile = new QAction(SimpleView);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        actionExit = new QAction(SimpleView);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionPrint = new QAction(SimpleView);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionHelp = new QAction(SimpleView);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionSave = new QAction(SimpleView);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        action_Connect = new QAction(SimpleView);
        action_Connect->setObjectName(QString::fromUtf8("action_Connect"));
        action_Quit = new QAction(SimpleView);
        action_Quit->setObjectName(QString::fromUtf8("action_Quit"));
        action_About = new QAction(SimpleView);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        centralwidget = new QWidget(SimpleView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setGeometry(QRect(0, 0, 800, 600));
        SimpleView->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(SimpleView);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 794, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        SimpleView->setMenuBar(menuBar);
        statusBar = new QStatusBar(SimpleView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        SimpleView->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_Connect);
        menu_File->addAction(action_Quit);
        menu_Help->addAction(action_About);

        retranslateUi(SimpleView);

        QMetaObject::connectSlotsByName(SimpleView);
    } // setupUi

    void retranslateUi(QMainWindow *SimpleView)
    {
        SimpleView->setWindowTitle(QApplication::translate("SimpleView", "Ocean Floor Visualizer", 0, QApplication::UnicodeUTF8));
        actionOpenFile->setText(QApplication::translate("SimpleView", "Open File...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("SimpleView", "Exit", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("SimpleView", "Print", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("SimpleView", "Help", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("SimpleView", "Save", 0, QApplication::UnicodeUTF8));
        action_Connect->setText(QApplication::translate("SimpleView", "&Connect", 0, QApplication::UnicodeUTF8));
        action_Quit->setText(QApplication::translate("SimpleView", "&Quit", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("SimpleView", "&About", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("SimpleView", "&File", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("SimpleView", "&Help", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SimpleView: public Ui_SimpleView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIMPLEVIEWUI_H
