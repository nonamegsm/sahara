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
* @file log_widget.h
* @class LogWidget
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/


#pragma once


#include <QObject>
#include <fstream>

#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QFileDialog>
#include <QtWidgets/QWidget>

#include "ui_log_widget.h"


//using OpenPST::GUI;


namespace Ui {
	class LogWidget;
}

namespace OpenPST{ 
	namespace GUI{
		class LogWidget : public QGroupBox
		{

			Q_OBJECT

			public:
	
				explicit LogWidget(QWidget *parent = 0);
				~LogWidget();

				
				void log(const char* message);
				void log(std::string message);
				void log(QString message);

			public slots:
				void clear();
				void save();

			private:
				Ui::LogWidget *ui;


		};
	}
}


