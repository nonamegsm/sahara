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
* @file table_dialog.cpp
* @class TableDialog
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "table_dialog.h"
#include "ui_table_dialog.h"

using namespace OpenPST::GUI;

TableDialog::TableDialog(QWidget *parent) :
	QDialog(parent),
	ui(new Ui::TableDialog)
{
	ui->setupUi(this);
}

TableDialog::~TableDialog()
{
	delete ui;
}


void TableDialog::setTitle(const QString& text)
{
	ui->tableTitle->setText(text);
}

QTableWidget* TableDialog::getTableWidget()
{
	return ui->tableWidget;
}
