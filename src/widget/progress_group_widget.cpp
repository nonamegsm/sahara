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
* @file progress_group_widget.cpp
* @class LogWidget
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "widget/progress_group_widget.h"
#include "ui_progress_group_widget.h"

using namespace OpenPST::GUI;

ProgressGroupWidget::ProgressGroupWidget(QWidget *parent) :
	QGroupBox(parent),
	ui(new Ui::ProgressGroupWidget)
{
	ui->setupUi(this);

	cancelButton = ui->cancelButton;
	cancelAllButton = ui->cancelAllButton;
}

ProgressGroupWidget::~ProgressGroupWidget()
{
	delete ui;
}

void ProgressGroupWidget::setProgress(int value)
{
	ui->progressBar->setValue(value);
}

void ProgressGroupWidget::setProgress(int min, int max, int value)
{
	ui->progressBar->setMinimum(min);
	ui->progressBar->setMaximum(max);
	ui->progressBar->setValue(value);
}

void ProgressGroupWidget::setTaskCount(int count)
{
	QString tmp;
	ui->taskCountLabel->setText(tmp.sprintf("%d Tasks", count));
}

void ProgressGroupWidget::setTextLeft(QString text)
{
	ui->textLeft->setText(text);
}

void ProgressGroupWidget::setTextRight(QString text)
{
	ui->textRight->setText(text);
}

void ProgressGroupWidget::reset()
{
	setProgress(0, 100, 0);
	setTextLeft("");
	setTextRight("");
	disableCancel();
	disableCancelAll();
}

void ProgressGroupWidget::enableCancel()
{
	ui->cancelButton->setEnabled(true);
}

void ProgressGroupWidget::disableCancel()
{
	ui->cancelButton->setEnabled(false);
}

void ProgressGroupWidget::enableCancelAll()
{
	ui->cancelAllButton->setEnabled(true);
}

void ProgressGroupWidget::disableCancelAll()
{
	ui->cancelAllButton->setEnabled(false);

}
