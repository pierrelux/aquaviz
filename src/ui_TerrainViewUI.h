/********************************************************************************
** Form generated from reading UI file 'TerrainViewUI.ui'
**
** Created: Sun Apr 24 21:05:21 2011
**      by: Qt User Interface Compiler version 4.7.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TERRAINVIEWUI_H
#define UI_TERRAINVIEWUI_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QHeaderView>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QStatusBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>
#include "QVTKWidget.h"

QT_BEGIN_NAMESPACE

class Ui_TerrainView
{
public:
    QAction *actionOpenFile;
    QAction *actionExit;
    QAction *actionPrint;
    QAction *actionHelp;
    QAction *actionSave;
    QAction *actionConnect;
    QAction *actionQuit;
    QAction *actionAbout;
    QAction *actionAttitude;
    QAction *actionTerrain;
    QAction *actionFrame;
    QAction *actionGroundPlane;
    QAction *actionOrigin;
    QAction *actionScreenshot;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout_2;
    QVBoxLayout *verticalLayout;
    QVTKWidget *qvtkWidget;
    QMenuBar *menuBar;
    QMenu *menuFile;
    QMenu *menuHelp;
    QMenu *menuView;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *TerrainView)
    {
        if (TerrainView->objectName().isEmpty())
            TerrainView->setObjectName(QString::fromUtf8("TerrainView"));
        TerrainView->resize(1024, 768);
        actionOpenFile = new QAction(TerrainView);
        actionOpenFile->setObjectName(QString::fromUtf8("actionOpenFile"));
        actionOpenFile->setEnabled(true);
        actionExit = new QAction(TerrainView);
        actionExit->setObjectName(QString::fromUtf8("actionExit"));
        actionPrint = new QAction(TerrainView);
        actionPrint->setObjectName(QString::fromUtf8("actionPrint"));
        actionHelp = new QAction(TerrainView);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        actionSave = new QAction(TerrainView);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionConnect = new QAction(TerrainView);
        actionConnect->setObjectName(QString::fromUtf8("actionConnect"));
        actionConnect->setVisible(false);
        actionQuit = new QAction(TerrainView);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        actionAbout = new QAction(TerrainView);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAttitude = new QAction(TerrainView);
        actionAttitude->setObjectName(QString::fromUtf8("actionAttitude"));
        actionAttitude->setCheckable(true);
        actionAttitude->setChecked(true);
        actionTerrain = new QAction(TerrainView);
        actionTerrain->setObjectName(QString::fromUtf8("actionTerrain"));
        actionTerrain->setCheckable(true);
        actionFrame = new QAction(TerrainView);
        actionFrame->setObjectName(QString::fromUtf8("actionFrame"));
        actionFrame->setCheckable(true);
        actionGroundPlane = new QAction(TerrainView);
        actionGroundPlane->setObjectName(QString::fromUtf8("actionGroundPlane"));
        actionGroundPlane->setCheckable(true);
        actionGroundPlane->setChecked(true);
        actionOrigin = new QAction(TerrainView);
        actionOrigin->setObjectName(QString::fromUtf8("actionOrigin"));
        actionOrigin->setCheckable(true);
        actionScreenshot = new QAction(TerrainView);
        actionScreenshot->setObjectName(QString::fromUtf8("actionScreenshot"));
        centralwidget = new QWidget(TerrainView);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout_2 = new QVBoxLayout(centralwidget);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setSizeConstraint(QLayout::SetMaximumSize);
        qvtkWidget = new QVTKWidget(centralwidget);
        qvtkWidget->setObjectName(QString::fromUtf8("qvtkWidget"));
        qvtkWidget->setEnabled(true);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(qvtkWidget->sizePolicy().hasHeightForWidth());
        qvtkWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(qvtkWidget);


        verticalLayout_2->addLayout(verticalLayout);

        TerrainView->setCentralWidget(centralwidget);
        menuBar = new QMenuBar(TerrainView);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1024, 25));
        menuFile = new QMenu(menuBar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuView = new QMenu(menuBar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        TerrainView->setMenuBar(menuBar);
        statusBar = new QStatusBar(TerrainView);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        TerrainView->setStatusBar(statusBar);

        menuBar->addAction(menuFile->menuAction());
        menuBar->addAction(menuView->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFile->addAction(actionConnect);
        menuFile->addAction(actionScreenshot);
        menuFile->addAction(actionQuit);
        menuHelp->addAction(actionAbout);
        menuView->addAction(actionAttitude);
        menuView->addAction(actionFrame);
        menuView->addAction(actionGroundPlane);
        menuView->addAction(actionOrigin);
        menuView->addAction(actionTerrain);

        retranslateUi(TerrainView);

        QMetaObject::connectSlotsByName(TerrainView);
    } // setupUi

    void retranslateUi(QMainWindow *TerrainView)
    {
        TerrainView->setWindowTitle(QApplication::translate("TerrainView", "Ocean Floor Visualization", 0, QApplication::UnicodeUTF8));
        actionOpenFile->setText(QApplication::translate("TerrainView", "Open File...", 0, QApplication::UnicodeUTF8));
        actionExit->setText(QApplication::translate("TerrainView", "Exit", 0, QApplication::UnicodeUTF8));
        actionPrint->setText(QApplication::translate("TerrainView", "Print", 0, QApplication::UnicodeUTF8));
        actionHelp->setText(QApplication::translate("TerrainView", "Help", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("TerrainView", "Save", 0, QApplication::UnicodeUTF8));
        actionConnect->setText(QApplication::translate("TerrainView", "&Connect", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("TerrainView", "&Quit", 0, QApplication::UnicodeUTF8));
        actionAbout->setText(QApplication::translate("TerrainView", "&About", 0, QApplication::UnicodeUTF8));
        actionAttitude->setText(QApplication::translate("TerrainView", "&Attitude", 0, QApplication::UnicodeUTF8));
        actionTerrain->setText(QApplication::translate("TerrainView", "&Terrain", 0, QApplication::UnicodeUTF8));
        actionFrame->setText(QApplication::translate("TerrainView", "&Frames Trace", 0, QApplication::UnicodeUTF8));
        actionGroundPlane->setText(QApplication::translate("TerrainView", "&Ground Plane", 0, QApplication::UnicodeUTF8));
        actionOrigin->setText(QApplication::translate("TerrainView", "&Origin", 0, QApplication::UnicodeUTF8));
        actionScreenshot->setText(QApplication::translate("TerrainView", "&Take a screenshot", 0, QApplication::UnicodeUTF8));
        menuFile->setTitle(QApplication::translate("TerrainView", "&File", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("TerrainView", "&Help", 0, QApplication::UnicodeUTF8));
        menuView->setTitle(QApplication::translate("TerrainView", "&View", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TerrainView: public Ui_TerrainView {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TERRAINVIEWUI_H
