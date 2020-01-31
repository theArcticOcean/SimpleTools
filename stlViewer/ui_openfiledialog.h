/********************************************************************************
** Form generated from reading UI file 'openfiledialog.ui'
**
** Created by: Qt User Interface Compiler version 5.9.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_OPENFILEDIALOG_H
#define UI_OPENFILEDIALOG_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QDialog>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_OpenFileDialog
{
public:
    QVBoxLayout *verticalLayout;
    QLabel *pictureLabel;
    QHBoxLayout *horizontalLayout;
    QLabel *noticeLabel;
    QLineEdit *lineEdit;
    QPushButton *browseButton;
    QPushButton *displayButton;

    void setupUi(QDialog *OpenFileDialog)
    {
        if (OpenFileDialog->objectName().isEmpty())
            OpenFileDialog->setObjectName(QStringLiteral("OpenFileDialog"));
        OpenFileDialog->resize(647, 455);
        verticalLayout = new QVBoxLayout(OpenFileDialog);
        verticalLayout->setSpacing(6);
        verticalLayout->setContentsMargins(11, 11, 11, 11);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        pictureLabel = new QLabel(OpenFileDialog);
        pictureLabel->setObjectName(QStringLiteral("pictureLabel"));
        pictureLabel->setPixmap(QPixmap(QString::fromUtf8(":/Earth.png")));
        pictureLabel->setScaledContents(true);
        pictureLabel->setAlignment(Qt::AlignCenter);
        pictureLabel->setWordWrap(false);

        verticalLayout->addWidget(pictureLabel);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        noticeLabel = new QLabel(OpenFileDialog);
        noticeLabel->setObjectName(QStringLiteral("noticeLabel"));

        horizontalLayout->addWidget(noticeLabel);

        lineEdit = new QLineEdit(OpenFileDialog);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));

        horizontalLayout->addWidget(lineEdit);

        browseButton = new QPushButton(OpenFileDialog);
        browseButton->setObjectName(QStringLiteral("browseButton"));

        horizontalLayout->addWidget(browseButton);

        displayButton = new QPushButton(OpenFileDialog);
        displayButton->setObjectName(QStringLiteral("displayButton"));

        horizontalLayout->addWidget(displayButton);


        verticalLayout->addLayout(horizontalLayout);


        retranslateUi(OpenFileDialog);

        QMetaObject::connectSlotsByName(OpenFileDialog);
    } // setupUi

    void retranslateUi(QDialog *OpenFileDialog)
    {
        OpenFileDialog->setWindowTitle(QApplication::translate("OpenFileDialog", "OpenFileDialog", Q_NULLPTR));
        pictureLabel->setText(QString());
        noticeLabel->setText(QApplication::translate("OpenFileDialog", "File:", Q_NULLPTR));
        browseButton->setText(QApplication::translate("OpenFileDialog", "Browse", Q_NULLPTR));
        displayButton->setText(QApplication::translate("OpenFileDialog", "Display", Q_NULLPTR));
    } // retranslateUi

};

namespace Ui {
    class OpenFileDialog: public Ui_OpenFileDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_OPENFILEDIALOG_H
