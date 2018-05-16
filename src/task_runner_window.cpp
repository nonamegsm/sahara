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
* @file task_runner_window.cpp
* @class TaskRunnerWindow
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include <QObject>
#include "task_runner_window.h"

using namespace OpenPST::GUI;

TaskRunnerWindow::TaskRunnerWindow(QWidget *parent) :
	QMainWindow(parent),
	taskRunner(&cancelTask)
{
}

TaskRunnerWindow::~TaskRunnerWindow()
{

}

void TaskRunnerWindow::addTask(Task* task)
{
	connect(task, &Task::started,   this, &TaskRunnerWindow::onTaskStarted);
	connect(task, &Task::complete,  this, &TaskRunnerWindow::onTaskComplete);
	connect(task, &Task::error,		this, &TaskRunnerWindow::onTaskError);
	connect(task, &Task::log,		this, &TaskRunnerWindow::onTaskLog);

	taskRunner.queue(task);
}

void TaskRunnerWindow::cancelCurrentTask()
{
	cancelTask = true;

}

void TaskRunnerWindow::cancelAllTasks()
{
	taskRunner.clearQueue();
	cancelTask = true;
}

void TaskRunnerWindow::onTaskStarted()
{
	printf("TaskRunnerWindow::onTaskStarted\n");

}

void TaskRunnerWindow::onTaskComplete()
{
	printf("TaskRunnerWindow::onTaskComplete\n");
}

void TaskRunnerWindow::onTaskError(QString msg)
{
	printf("TaskRunnerWindow::onTaskError\n");
}

void TaskRunnerWindow::onTaskLog(QString msg)
{
	printf("TaskRunnerWindow::onTaskLog\n");
}