/**
*
* (c) Gassan Idriss <ghassani@gmail.com>
* 
* This file is part of gui-common.
* 
* gui-common is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* (at your option) any later version.
* 
* gui-common is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
* 
* You should have received a copy of the GNU General Public License
* along with gui-common. If not, see <http://www.gnu.org/licenses/>.
*
* @file log_widget.cpp
* @class LogWidget
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/


#include "widget/log_widget.h"
#include "ui_log_widget.h"


using namespace OpenPST::GUI;


LogWidget::LogWidget(QWidget *parent) :QGroupBox(parent),
	ui(new Ui::LogWidget)
{
	ui->setupUi(this);

	//QObject::connect(ui->clearLogButton, SIGNAL(clicked()), this, SLOT(clear()));
	//QObject::connect(ui->saveLogButton,	SIGNAL(clicked()), this, SLOT(save()));
}

LogWidget::~LogWidget()
{
	delete ui;
}


void LogWidget::clear()
{
	ui->log->clear();
}

void LogWidget::save()
{

	QString fileName = QFileDialog::getSaveFileName(this, tr("Save Log"), "", tr("Log Files (*.log)"));

	if (!fileName.length()) {
		return;
	}

	std::ofstream file(fileName.toStdString().c_str(), std::ios::out | std::ios::trunc);

	if (!file.is_open()) {
		log("Error opening file for writing");
		return;
	}

	QString content = ui->log->toPlainText();

	file.write(content.toStdString().c_str(), content.size());
	file.close();
}


void LogWidget::log(const char* message)
{
	//ui->log->appendPlainText(message);
}


void LogWidget::log(std::string message)
{
	//ui->log->appendPlainText(message.c_str());
}


void LogWidget::log(QString message)
{
	//ui->log->appendPlainText(message);
}

