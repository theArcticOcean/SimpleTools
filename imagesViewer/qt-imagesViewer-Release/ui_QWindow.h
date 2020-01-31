/********************************************************************************
** Form generated from reading UI file 'QWindow.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_QWINDOW_H
#define UI_QWINDOW_H

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

class Ui_QWindow
{
public:
    QAction *actionOpen_Files;
    QAction *actionClose_All;
    QWidget *centralWidget;
    QLabel *addLabel;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *QWindow)
    {
        if (QWindow->objectName().isEmpty())
            QWindow->setObjectName(QStringLiteral("QWindow"));
        QWindow->resize(400, 300);
        QWindow->setAcceptDrops(true);
        QWindow->setStyleSheet(QStringLiteral(""));
        actionOpen_Files = new QAction(QWindow);
        actionOpen_Files->setObjectName(QStringLiteral("actionOpen_Files"));
        actionClose_All = new QAction(QWindow);
        actionClose_All->setObjectName(QStringLiteral("actionClose_All"));
        centralWidget = new QWidget(QWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        addLabel = new QLabel(centralWidget);
        addLabel->setObjectName(QStringLiteral("addLabel"));
        addLabel->setGeometry(QRect(110, 70, 171, 101));
        addLabel->setLayoutDirection(Qt::LeftToRight);
        addLabel->setAutoFillBackground(false);
        addLabel->setScaledContents(true);
        addLabel->setAlignment(Qt::AlignCenter);
        QWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(QWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 400, 23));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QStringLiteral("menuFiles"));
        QWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(QWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        QWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(QWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        QWindow->setStatusBar(statusBar);

        menuBar->addAction(menuFiles->menuAction());
        menuFiles->addAction(actionOpen_Files);
        menuFiles->addAction(actionClose_All);

        retranslateUi(QWindow);

        QMetaObject::connectSlotsByName(QWindow);
    } // setupUi

    void retranslateUi(QMainWindow *QWindow)
    {
        QWindow->setWindowTitle(QApplication::translate("QWindow", "StartWindow", Q_NULLPTR));
        actionOpen_Files->setText(QApplication::translate("QWindow", "Open Files", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionOpen_Files->setShortcut(QApplication::translate("QWindow", "Ctrl+O", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        actionClose_All->setText(QApplication::translate("QWindow", "Close All", Q_NULLPTR));
#ifndef QT_NO_SHORTCUT
        actionClose_All->setShortcut(QApplication::translate("QWindow", "Ctrl+Shift+C", Q_NULLPTR));
#endif // QT_NO_SHORTCUT
        addLabel->setText(QString());
        menuFiles->setTitle(QApplication::translate("QWindow", "Files", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class QWindow: public Ui_QWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_QWINDOW_H
