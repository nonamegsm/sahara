/********************************************************************************
** Form generated from reading UI file 'sahara_window.ui'
**
** Created by: Qt User Interface Compiler version 5.1.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SAHARA_WINDOW_H
#define UI_SAHARA_WINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTabWidget>
#include <QtWidgets/QTableWidget>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QWidget>
#include "widget/log_widget.h"
#include "widget/progress_group_widget.h"

QT_BEGIN_NAMESPACE

class Ui_SaharaWindow
{
public:
    QAction *actionTest;
    QAction *actionAbout;
    QAction *actionClose;
    QWidget *centralWidget;
    QTabWidget *mainTabSet;
    QWidget *tab;
    QGroupBox *sendImageGroupBox;
    QPushButton *sendImageButton;
    QLineEdit *sendImageFileValue;
    QToolButton *sendImageFileBrowseButton;
    QPushButton *sendImageCheckButton;
    QLabel *sendImageFileLabel;
    QGroupBox *sendImageXmlGroupBox;
    QLineEdit *sendImageXmlPathValue;
    QToolButton *sendImageXmlBrowseButton;
    QPushButton *sendImageXmlCheckButton;
    QLabel *sendImageFileLabel_2;
    QPushButton *sendImageXmlButton;
    QWidget *saharaMemoryTab;
    QGroupBox *memoryReadGroupBox;
    QLineEdit *memoryReadAddressValue;
    QLabel *memoryReadAddressLabel;
    QLabel *memoryReadSizeLabel;
    QLineEdit *memoryReadSizeValue;
    QPushButton *memoryReadButton;
    QCheckBox *memoryReadIs64bit;
    QGroupBox *debugMemoryLocationsGroupBox;
    QTableWidget *debugMemoryLocationsTable;
    QWidget *saharaCommandTab;
    QGroupBox *clientCommandGroupBox;
    QComboBox *clientCommandValue;
    QPushButton *clientCommandButton;
    QGroupBox *clientCommandGroupBox_2;
    QPushButton *switchModeButton;
    QComboBox *switchModeValue;
    QWidget *deviceContainer;
    QPushButton *portDisconnectButton;
    QPushButton *portRefreshButton;
    QPushButton *portConnectButton;
    QComboBox *portList;
    QLabel *portListLabel;
    QCheckBox *autoHelloCheckbox;
    QCheckBox *DMSScheckBox;
    QGroupBox *miscGroupBox;
    QPushButton *resetButton;
    QPushButton *doneButton;
    QPushButton *readHelloButton;
    QGroupBox *helloGroupBox;
    QPushButton *writeHelloButton;
    QLabel *writeHelloMinimumVersionLabel;
    QLineEdit *writeHelloVersionValue;
    QLineEdit *writeHelloMinimumVersionValue;
    QComboBox *writeHelloSwitchModeValue;
    QLabel *writeHelloVersionLabel;
    QLabel *writeHelloModeLabel;
    QGroupBox *deviceStateGroupBox;
    QLabel *deviceStateText;
    QLabel *deviceVersionText;
    QLabel *deviceMinVersionText;
    OpenPST::GUI::ProgressGroupWidget *progressGroupBox;
    OpenPST::GUI::LogWidget *logWidget;
    QMenuBar *menuBar;
    QMenu *menuHelp;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *SaharaWindow)
    {
        if (SaharaWindow->objectName().isEmpty())
            SaharaWindow->setObjectName(QStringLiteral("SaharaWindow"));
        SaharaWindow->resize(881, 734);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(SaharaWindow->sizePolicy().hasHeightForWidth());
        SaharaWindow->setSizePolicy(sizePolicy);
        SaharaWindow->setMinimumSize(QSize(881, 734));
        SaharaWindow->setMaximumSize(QSize(881, 734));
        actionTest = new QAction(SaharaWindow);
        actionTest->setObjectName(QStringLiteral("actionTest"));
        actionAbout = new QAction(SaharaWindow);
        actionAbout->setObjectName(QStringLiteral("actionAbout"));
        actionClose = new QAction(SaharaWindow);
        actionClose->setObjectName(QStringLiteral("actionClose"));
        centralWidget = new QWidget(SaharaWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        mainTabSet = new QTabWidget(centralWidget);
        mainTabSet->setObjectName(QStringLiteral("mainTabSet"));
        mainTabSet->setEnabled(true);
        mainTabSet->setGeometry(QRect(10, 210, 861, 241));
        QFont font;
        font.setPointSize(10);
        mainTabSet->setFont(font);
        mainTabSet->setDocumentMode(false);
        tab = new QWidget();
        tab->setObjectName(QStringLiteral("tab"));
        sendImageGroupBox = new QGroupBox(tab);
        sendImageGroupBox->setObjectName(QStringLiteral("sendImageGroupBox"));
        sendImageGroupBox->setGeometry(QRect(10, 10, 831, 101));
        QFont font1;
        font1.setBold(true);
        font1.setWeight(75);
        sendImageGroupBox->setFont(font1);
        sendImageButton = new QPushButton(sendImageGroupBox);
        sendImageButton->setObjectName(QStringLiteral("sendImageButton"));
        sendImageButton->setGeometry(QRect(760, 55, 61, 27));
        QFont font2;
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setWeight(50);
        sendImageButton->setFont(font2);
        sendImageFileValue = new QLineEdit(sendImageGroupBox);
        sendImageFileValue->setObjectName(QStringLiteral("sendImageFileValue"));
        sendImageFileValue->setGeometry(QRect(10, 55, 631, 27));
        sendImageFileValue->setFont(font2);
        sendImageFileBrowseButton = new QToolButton(sendImageGroupBox);
        sendImageFileBrowseButton->setObjectName(QStringLiteral("sendImageFileBrowseButton"));
        sendImageFileBrowseButton->setGeometry(QRect(650, 55, 25, 27));
        sendImageFileBrowseButton->setFont(font2);
        sendImageCheckButton = new QPushButton(sendImageGroupBox);
        sendImageCheckButton->setObjectName(QStringLiteral("sendImageCheckButton"));
        sendImageCheckButton->setGeometry(QRect(690, 55, 61, 27));
        sendImageCheckButton->setFont(font2);
        sendImageFileLabel = new QLabel(sendImageGroupBox);
        sendImageFileLabel->setObjectName(QStringLiteral("sendImageFileLabel"));
        sendImageFileLabel->setGeometry(QRect(10, 30, 121, 21));
        QFont font3;
        font3.setBold(false);
        font3.setWeight(50);
        sendImageFileLabel->setFont(font3);
        sendImageXmlGroupBox = new QGroupBox(tab);
        sendImageXmlGroupBox->setObjectName(QStringLiteral("sendImageXmlGroupBox"));
        sendImageXmlGroupBox->setGeometry(QRect(10, 120, 831, 81));
        sendImageXmlGroupBox->setFont(font1);
        sendImageXmlGroupBox->setAcceptDrops(false);
        sendImageXmlPathValue = new QLineEdit(sendImageXmlGroupBox);
        sendImageXmlPathValue->setObjectName(QStringLiteral("sendImageXmlPathValue"));
        sendImageXmlPathValue->setGeometry(QRect(10, 50, 631, 27));
        sendImageXmlPathValue->setFont(font2);
        sendImageXmlBrowseButton = new QToolButton(sendImageXmlGroupBox);
        sendImageXmlBrowseButton->setObjectName(QStringLiteral("sendImageXmlBrowseButton"));
        sendImageXmlBrowseButton->setGeometry(QRect(654, 50, 25, 27));
        sendImageXmlBrowseButton->setFont(font2);
        sendImageXmlCheckButton = new QPushButton(sendImageXmlGroupBox);
        sendImageXmlCheckButton->setObjectName(QStringLiteral("sendImageXmlCheckButton"));
        sendImageXmlCheckButton->setGeometry(QRect(690, 50, 61, 27));
        sendImageXmlCheckButton->setFont(font2);
        sendImageFileLabel_2 = new QLabel(sendImageXmlGroupBox);
        sendImageFileLabel_2->setObjectName(QStringLiteral("sendImageFileLabel_2"));
        sendImageFileLabel_2->setGeometry(QRect(10, 20, 361, 21));
        sendImageFileLabel_2->setFont(font3);
        sendImageXmlButton = new QPushButton(sendImageXmlGroupBox);
        sendImageXmlButton->setObjectName(QStringLiteral("sendImageXmlButton"));
        sendImageXmlButton->setGeometry(QRect(760, 50, 61, 27));
        sendImageXmlButton->setFont(font2);
        mainTabSet->addTab(tab, QString());
        saharaMemoryTab = new QWidget();
        saharaMemoryTab->setObjectName(QStringLiteral("saharaMemoryTab"));
        memoryReadGroupBox = new QGroupBox(saharaMemoryTab);
        memoryReadGroupBox->setObjectName(QStringLiteral("memoryReadGroupBox"));
        memoryReadGroupBox->setGeometry(QRect(10, 10, 241, 191));
        memoryReadGroupBox->setFont(font1);
        memoryReadAddressValue = new QLineEdit(memoryReadGroupBox);
        memoryReadAddressValue->setObjectName(QStringLiteral("memoryReadAddressValue"));
        memoryReadAddressValue->setGeometry(QRect(80, 25, 140, 27));
        memoryReadAddressValue->setFont(font3);
        memoryReadAddressLabel = new QLabel(memoryReadGroupBox);
        memoryReadAddressLabel->setObjectName(QStringLiteral("memoryReadAddressLabel"));
        memoryReadAddressLabel->setGeometry(QRect(10, 25, 71, 27));
        memoryReadAddressLabel->setFont(font3);
        memoryReadSizeLabel = new QLabel(memoryReadGroupBox);
        memoryReadSizeLabel->setObjectName(QStringLiteral("memoryReadSizeLabel"));
        memoryReadSizeLabel->setGeometry(QRect(10, 60, 71, 27));
        memoryReadSizeLabel->setFont(font3);
        memoryReadSizeValue = new QLineEdit(memoryReadGroupBox);
        memoryReadSizeValue->setObjectName(QStringLiteral("memoryReadSizeValue"));
        memoryReadSizeValue->setGeometry(QRect(80, 60, 141, 27));
        memoryReadSizeValue->setFont(font3);
        memoryReadButton = new QPushButton(memoryReadGroupBox);
        memoryReadButton->setObjectName(QStringLiteral("memoryReadButton"));
        memoryReadButton->setGeometry(QRect(130, 110, 71, 27));
        memoryReadButton->setFont(font3);
        memoryReadIs64bit = new QCheckBox(memoryReadGroupBox);
        memoryReadIs64bit->setObjectName(QStringLiteral("memoryReadIs64bit"));
        memoryReadIs64bit->setEnabled(false);
        memoryReadIs64bit->setGeometry(QRect(30, 110, 71, 21));
        memoryReadIs64bit->setFont(font3);
        debugMemoryLocationsGroupBox = new QGroupBox(saharaMemoryTab);
        debugMemoryLocationsGroupBox->setObjectName(QStringLiteral("debugMemoryLocationsGroupBox"));
        debugMemoryLocationsGroupBox->setGeometry(QRect(260, 10, 591, 191));
        debugMemoryLocationsGroupBox->setFont(font1);
        debugMemoryLocationsTable = new QTableWidget(debugMemoryLocationsGroupBox);
        if (debugMemoryLocationsTable->columnCount() < 4)
            debugMemoryLocationsTable->setColumnCount(4);
        QTableWidgetItem *__qtablewidgetitem = new QTableWidgetItem();
        debugMemoryLocationsTable->setHorizontalHeaderItem(0, __qtablewidgetitem);
        QTableWidgetItem *__qtablewidgetitem1 = new QTableWidgetItem();
        debugMemoryLocationsTable->setHorizontalHeaderItem(1, __qtablewidgetitem1);
        QTableWidgetItem *__qtablewidgetitem2 = new QTableWidgetItem();
        debugMemoryLocationsTable->setHorizontalHeaderItem(2, __qtablewidgetitem2);
        QTableWidgetItem *__qtablewidgetitem3 = new QTableWidgetItem();
        debugMemoryLocationsTable->setHorizontalHeaderItem(3, __qtablewidgetitem3);
        debugMemoryLocationsTable->setObjectName(QStringLiteral("debugMemoryLocationsTable"));
        debugMemoryLocationsTable->setEnabled(true);
        debugMemoryLocationsTable->setGeometry(QRect(10, 20, 571, 161));
        debugMemoryLocationsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
        debugMemoryLocationsTable->setWordWrap(true);
        debugMemoryLocationsTable->horizontalHeader()->setStretchLastSection(false);
        debugMemoryLocationsTable->verticalHeader()->setHighlightSections(true);
        debugMemoryLocationsTable->verticalHeader()->setProperty("showSortIndicator", QVariant(false));
        debugMemoryLocationsTable->verticalHeader()->setStretchLastSection(false);
        mainTabSet->addTab(saharaMemoryTab, QString());
        saharaCommandTab = new QWidget();
        saharaCommandTab->setObjectName(QStringLiteral("saharaCommandTab"));
        clientCommandGroupBox = new QGroupBox(saharaCommandTab);
        clientCommandGroupBox->setObjectName(QStringLiteral("clientCommandGroupBox"));
        clientCommandGroupBox->setGeometry(QRect(10, 10, 401, 91));
        clientCommandGroupBox->setFont(font1);
        clientCommandValue = new QComboBox(clientCommandGroupBox);
        clientCommandValue->setObjectName(QStringLiteral("clientCommandValue"));
        clientCommandValue->setEnabled(true);
        clientCommandValue->setGeometry(QRect(10, 40, 291, 27));
        clientCommandValue->setFont(font2);
        clientCommandValue->setEditable(false);
        clientCommandButton = new QPushButton(clientCommandGroupBox);
        clientCommandButton->setObjectName(QStringLiteral("clientCommandButton"));
        clientCommandButton->setGeometry(QRect(310, 40, 81, 27));
        clientCommandButton->setFont(font2);
        clientCommandGroupBox_2 = new QGroupBox(saharaCommandTab);
        clientCommandGroupBox_2->setObjectName(QStringLiteral("clientCommandGroupBox_2"));
        clientCommandGroupBox_2->setGeometry(QRect(420, 10, 421, 91));
        clientCommandGroupBox_2->setFont(font1);
        switchModeButton = new QPushButton(clientCommandGroupBox_2);
        switchModeButton->setObjectName(QStringLiteral("switchModeButton"));
        switchModeButton->setGeometry(QRect(310, 40, 101, 27));
        switchModeButton->setFont(font2);
        switchModeValue = new QComboBox(clientCommandGroupBox_2);
        switchModeValue->setObjectName(QStringLiteral("switchModeValue"));
        switchModeValue->setEnabled(true);
        switchModeValue->setGeometry(QRect(10, 40, 291, 27));
        switchModeValue->setFont(font2);
        switchModeValue->setEditable(false);
        mainTabSet->addTab(saharaCommandTab, QString());
        deviceContainer = new QWidget(centralWidget);
        deviceContainer->setObjectName(QStringLiteral("deviceContainer"));
        deviceContainer->setGeometry(QRect(10, 10, 861, 75));
        portDisconnectButton = new QPushButton(deviceContainer);
        portDisconnectButton->setObjectName(QStringLiteral("portDisconnectButton"));
        portDisconnectButton->setEnabled(false);
        portDisconnectButton->setGeometry(QRect(760, 10, 91, 25));
        portDisconnectButton->setFont(font);
        portRefreshButton = new QPushButton(deviceContainer);
        portRefreshButton->setObjectName(QStringLiteral("portRefreshButton"));
        portRefreshButton->setGeometry(QRect(660, 40, 91, 27));
        portRefreshButton->setFont(font);
        portConnectButton = new QPushButton(deviceContainer);
        portConnectButton->setObjectName(QStringLiteral("portConnectButton"));
        portConnectButton->setGeometry(QRect(660, 10, 91, 25));
        portConnectButton->setFont(font);
        portList = new QComboBox(deviceContainer);
        portList->setObjectName(QStringLiteral("portList"));
        portList->setGeometry(QRect(90, 10, 561, 29));
        portList->setFont(font);
        portList->setEditable(false);
        portListLabel = new QLabel(deviceContainer);
        portListLabel->setObjectName(QStringLiteral("portListLabel"));
        portListLabel->setGeometry(QRect(20, 6, 64, 31));
        portListLabel->setFont(font);
        autoHelloCheckbox = new QCheckBox(deviceContainer);
        autoHelloCheckbox->setObjectName(QStringLiteral("autoHelloCheckbox"));
        autoHelloCheckbox->setGeometry(QRect(760, 40, 91, 21));
        autoHelloCheckbox->setChecked(true);
        DMSScheckBox = new QCheckBox(deviceContainer);
        DMSScheckBox->setObjectName(QStringLiteral("DMSScheckBox"));
        DMSScheckBox->setGeometry(QRect(760, 60, 70, 17));
        miscGroupBox = new QGroupBox(centralWidget);
        miscGroupBox->setObjectName(QStringLiteral("miscGroupBox"));
        miscGroupBox->setGeometry(QRect(690, 100, 181, 111));
        miscGroupBox->setFont(font1);
        resetButton = new QPushButton(miscGroupBox);
        resetButton->setObjectName(QStringLiteral("resetButton"));
        resetButton->setGeometry(QRect(10, 50, 91, 27));
        resetButton->setFont(font2);
        doneButton = new QPushButton(miscGroupBox);
        doneButton->setObjectName(QStringLiteral("doneButton"));
        doneButton->setGeometry(QRect(10, 20, 91, 27));
        doneButton->setFont(font2);
        readHelloButton = new QPushButton(miscGroupBox);
        readHelloButton->setObjectName(QStringLiteral("readHelloButton"));
        readHelloButton->setGeometry(QRect(10, 80, 91, 27));
        readHelloButton->setFont(font2);
        helloGroupBox = new QGroupBox(centralWidget);
        helloGroupBox->setObjectName(QStringLiteral("helloGroupBox"));
        helloGroupBox->setGeometry(QRect(250, 100, 431, 91));
        QFont font4;
        font4.setPointSize(10);
        font4.setBold(true);
        font4.setWeight(75);
        helloGroupBox->setFont(font4);
        helloGroupBox->setStyleSheet(QStringLiteral(""));
        writeHelloButton = new QPushButton(helloGroupBox);
        writeHelloButton->setObjectName(QStringLiteral("writeHelloButton"));
        writeHelloButton->setGeometry(QRect(350, 50, 75, 27));
        writeHelloButton->setFont(font2);
        writeHelloMinimumVersionLabel = new QLabel(helloGroupBox);
        writeHelloMinimumVersionLabel->setObjectName(QStringLiteral("writeHelloMinimumVersionLabel"));
        writeHelloMinimumVersionLabel->setGeometry(QRect(290, 20, 101, 20));
        writeHelloMinimumVersionLabel->setFont(font3);
        writeHelloVersionValue = new QLineEdit(helloGroupBox);
        writeHelloVersionValue->setObjectName(QStringLiteral("writeHelloVersionValue"));
        writeHelloVersionValue->setGeometry(QRect(230, 50, 51, 27));
        writeHelloVersionValue->setFont(font3);
        writeHelloMinimumVersionValue = new QLineEdit(helloGroupBox);
        writeHelloMinimumVersionValue->setObjectName(QStringLiteral("writeHelloMinimumVersionValue"));
        writeHelloMinimumVersionValue->setGeometry(QRect(290, 50, 51, 27));
        writeHelloMinimumVersionValue->setFont(font3);
        writeHelloSwitchModeValue = new QComboBox(helloGroupBox);
        writeHelloSwitchModeValue->setObjectName(QStringLiteral("writeHelloSwitchModeValue"));
        writeHelloSwitchModeValue->setGeometry(QRect(10, 50, 211, 27));
        writeHelloSwitchModeValue->setFont(font2);
        writeHelloSwitchModeValue->setEditable(false);
        writeHelloVersionLabel = new QLabel(helloGroupBox);
        writeHelloVersionLabel->setObjectName(QStringLiteral("writeHelloVersionLabel"));
        writeHelloVersionLabel->setGeometry(QRect(230, 20, 51, 20));
        writeHelloVersionLabel->setFont(font3);
        writeHelloModeLabel = new QLabel(helloGroupBox);
        writeHelloModeLabel->setObjectName(QStringLiteral("writeHelloModeLabel"));
        writeHelloModeLabel->setGeometry(QRect(10, 20, 47, 20));
        writeHelloModeLabel->setFont(font3);
        deviceStateGroupBox = new QGroupBox(centralWidget);
        deviceStateGroupBox->setObjectName(QStringLiteral("deviceStateGroupBox"));
        deviceStateGroupBox->setGeometry(QRect(10, 100, 231, 91));
        deviceStateGroupBox->setFont(font4);
        deviceStateText = new QLabel(deviceStateGroupBox);
        deviceStateText->setObjectName(QStringLiteral("deviceStateText"));
        deviceStateText->setGeometry(QRect(20, 20, 201, 31));
        deviceStateText->setFont(font2);
        deviceVersionText = new QLabel(deviceStateGroupBox);
        deviceVersionText->setObjectName(QStringLiteral("deviceVersionText"));
        deviceVersionText->setGeometry(QRect(20, 50, 91, 31));
        deviceVersionText->setFont(font2);
        deviceMinVersionText = new QLabel(deviceStateGroupBox);
        deviceMinVersionText->setObjectName(QStringLiteral("deviceMinVersionText"));
        deviceMinVersionText->setGeometry(QRect(120, 50, 101, 31));
        deviceMinVersionText->setFont(font2);
        progressGroupBox = new OpenPST::GUI::ProgressGroupWidget(centralWidget);
        progressGroupBox->setObjectName(QStringLiteral("progressGroupBox"));
        progressGroupBox->setGeometry(QRect(10, 440, 861, 71));
        logWidget = new OpenPST::GUI::LogWidget(centralWidget);
        logWidget->setObjectName(QStringLiteral("logWidget"));
        logWidget->setGeometry(QRect(10, 520, 861, 151));
        SaharaWindow->setCentralWidget(centralWidget);
        deviceContainer->raise();
        mainTabSet->raise();
        miscGroupBox->raise();
        helloGroupBox->raise();
        deviceStateGroupBox->raise();
        progressGroupBox->raise();
        logWidget->raise();
        menuBar = new QMenuBar(SaharaWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 881, 21));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QStringLiteral("menuHelp"));
        SaharaWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(SaharaWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        SaharaWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(SaharaWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        SaharaWindow->setStatusBar(statusBar);

        menuBar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(SaharaWindow);

        mainTabSet->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(SaharaWindow);
    } // setupUi

    void retranslateUi(QMainWindow *SaharaWindow)
    {
        SaharaWindow->setWindowTitle(QApplication::translate("SaharaWindow", "Sahara - OpenPST", 0));
        actionTest->setText(QApplication::translate("SaharaWindow", "test", 0));
        actionAbout->setText(QApplication::translate("SaharaWindow", "About", 0));
        actionClose->setText(QApplication::translate("SaharaWindow", "Close", 0));
        sendImageGroupBox->setTitle(QApplication::translate("SaharaWindow", "Send Image", 0));
        sendImageButton->setText(QApplication::translate("SaharaWindow", "Send", 0));
        sendImageFileBrowseButton->setText(QApplication::translate("SaharaWindow", "...", 0));
        sendImageCheckButton->setText(QApplication::translate("SaharaWindow", "Check", 0));
        sendImageFileLabel->setText(QApplication::translate("SaharaWindow", "Image File Path", 0));
        sendImageXmlGroupBox->setTitle(QApplication::translate("SaharaWindow", "Specify XML ", 0));
        sendImageXmlBrowseButton->setText(QApplication::translate("SaharaWindow", "...", 0));
        sendImageXmlCheckButton->setText(QApplication::translate("SaharaWindow", "Check", 0));
        sendImageFileLabel_2->setText(QApplication::translate("SaharaWindow", "Images XML Path (sahara.xml)", 0));
        sendImageXmlButton->setText(QApplication::translate("SaharaWindow", "Send", 0));
        mainTabSet->setTabText(mainTabSet->indexOf(tab), QApplication::translate("SaharaWindow", "Image Transfer", 0));
        memoryReadGroupBox->setTitle(QApplication::translate("SaharaWindow", "Memory Read", 0));
        memoryReadAddressValue->setText(QApplication::translate("SaharaWindow", "0x00000000", 0));
        memoryReadAddressLabel->setText(QApplication::translate("SaharaWindow", "Address", 0));
        memoryReadSizeLabel->setText(QApplication::translate("SaharaWindow", "Size", 0));
        memoryReadSizeValue->setText(QApplication::translate("SaharaWindow", "0", 0));
        memoryReadButton->setText(QApplication::translate("SaharaWindow", "Read", 0));
        memoryReadIs64bit->setText(QApplication::translate("SaharaWindow", "64bit", 0));
        debugMemoryLocationsGroupBox->setTitle(QApplication::translate("SaharaWindow", "Debug Memory Locations", 0));
        QTableWidgetItem *___qtablewidgetitem = debugMemoryLocationsTable->horizontalHeaderItem(0);
        ___qtablewidgetitem->setText(QApplication::translate("SaharaWindow", "Name", 0));
        QTableWidgetItem *___qtablewidgetitem1 = debugMemoryLocationsTable->horizontalHeaderItem(1);
        ___qtablewidgetitem1->setText(QApplication::translate("SaharaWindow", "File Name", 0));
        QTableWidgetItem *___qtablewidgetitem2 = debugMemoryLocationsTable->horizontalHeaderItem(2);
        ___qtablewidgetitem2->setText(QApplication::translate("SaharaWindow", "Address", 0));
        QTableWidgetItem *___qtablewidgetitem3 = debugMemoryLocationsTable->horizontalHeaderItem(3);
        ___qtablewidgetitem3->setText(QApplication::translate("SaharaWindow", "Size", 0));
        mainTabSet->setTabText(mainTabSet->indexOf(saharaMemoryTab), QApplication::translate("SaharaWindow", "Memory Debug", 0));
        clientCommandGroupBox->setTitle(QApplication::translate("SaharaWindow", "Command", 0));
        clientCommandButton->setText(QApplication::translate("SaharaWindow", "Send", 0));
        clientCommandGroupBox_2->setTitle(QApplication::translate("SaharaWindow", "Switch Mode", 0));
        switchModeButton->setText(QApplication::translate("SaharaWindow", "Switch Mode", 0));
        mainTabSet->setTabText(mainTabSet->indexOf(saharaCommandTab), QApplication::translate("SaharaWindow", "Command", 0));
        portDisconnectButton->setText(QApplication::translate("SaharaWindow", "Disconnect", 0));
        portRefreshButton->setText(QApplication::translate("SaharaWindow", "Refresh", 0));
        portConnectButton->setText(QApplication::translate("SaharaWindow", "Connect", 0));
        portListLabel->setText(QApplication::translate("SaharaWindow", "Device", 0));
        autoHelloCheckbox->setText(QApplication::translate("SaharaWindow", "Auto Hello", 0));
        DMSScheckBox->setText(QApplication::translate("SaharaWindow", "DMSS Cmd", 0));
        miscGroupBox->setTitle(QApplication::translate("SaharaWindow", "Misc", 0));
        resetButton->setText(QApplication::translate("SaharaWindow", "Reset", 0));
        doneButton->setText(QApplication::translate("SaharaWindow", "Done", 0));
        readHelloButton->setText(QApplication::translate("SaharaWindow", "Read Hello", 0));
        helloGroupBox->setTitle(QApplication::translate("SaharaWindow", "Hello Handshake", 0));
        writeHelloButton->setText(QApplication::translate("SaharaWindow", "Respond", 0));
        writeHelloMinimumVersionLabel->setText(QApplication::translate("SaharaWindow", "Min. Version", 0));
        writeHelloVersionValue->setText(QApplication::translate("SaharaWindow", "2", 0));
        writeHelloMinimumVersionValue->setText(QApplication::translate("SaharaWindow", "1", 0));
        writeHelloVersionLabel->setText(QApplication::translate("SaharaWindow", "Version", 0));
        writeHelloModeLabel->setText(QApplication::translate("SaharaWindow", "Mode", 0));
        deviceStateGroupBox->setTitle(QApplication::translate("SaharaWindow", "Device State:", 0));
        deviceStateText->setText(QApplication::translate("SaharaWindow", "Disconnected", 0));
        deviceVersionText->setText(QApplication::translate("SaharaWindow", "Ver: -", 0));
        deviceMinVersionText->setText(QApplication::translate("SaharaWindow", "Min. Ver: -", 0));
        progressGroupBox->setTitle(QString());
        logWidget->setTitle(QString());
        menuHelp->setTitle(QApplication::translate("SaharaWindow", "Help", 0));
    } // retranslateUi

};

namespace Ui {
    class SaharaWindow: public Ui_SaharaWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SAHARA_WINDOW_H
