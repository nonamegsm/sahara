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
* @file about_dialog.h
* @class AboutDialog
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#pragma once

#include <QDialog>

namespace Ui {
	class AboutDialog;
}

namespace OpenPST{
	namespace GUI {

		class AboutDialog : public QDialog
		{

			Q_OBJECT

			public:
				explicit AboutDialog(QWidget *parent = 0);
				~AboutDialog();


			public slots:

			private:
				Ui::AboutDialog* ui;

			};
	}
}
