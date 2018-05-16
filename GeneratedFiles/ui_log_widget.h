/********************************************************************************
** Form generated from reading UI file 'log_widget.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOG_WIDGET_H
#define UI_LOG_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Log_widget
{
public:
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;

    void setupUi(QWidget *Log_widget)
    {
        if (Log_widget->objectName().isEmpty())
            Log_widget->setObjectName(QStringLiteral("Log_widget"));
        Log_widget->resize(877, 580);
        verticalLayout = new QVBoxLayout(Log_widget);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        verticalLayout->setContentsMargins(0, 0, 0, 0);
        textBrowser = new QTextBrowser(Log_widget);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));

        verticalLayout->addWidget(textBrowser);


        retranslateUi(Log_widget);

        QMetaObject::connectSlotsByName(Log_widget);
    } // setupUi

    void retranslateUi(QWidget *Log_widget)
    {
        Log_widget->setWindowTitle(QApplication::translate("Log_widget", "Form", 0));
    } // retranslateUi

};

namespace Ui {
    class Log_widget: public Ui_Log_widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOG_WIDGET_H
