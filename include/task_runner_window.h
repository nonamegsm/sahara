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
* @file task_runner_window.h
* @class TaskRunnerWindow
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#pragma once

#include <QObject>
#include <QMainWindow>
#include "task/task.h"
#include "task/task_runner.h"

namespace OpenPST {
	namespace GUI {
	
		class TaskRunnerWindow : public QMainWindow
		{
			
			Q_OBJECT

			public:
				explicit TaskRunnerWindow(QWidget *parent = 0);
				~TaskRunnerWindow();

			protected:
				TaskRunner taskRunner;
				//volatile bool cancelTask = false; NONAME
				volatile bool cancelTask;

			protected:
				virtual void addTask(Task* task) = 0;

			public slots:
				virtual void cancelCurrentTask() = 0;
				virtual void cancelAllTasks() = 0;
				virtual void onTaskStarted() = 0;
				virtual void onTaskComplete() = 0;
				virtual void onTaskError(QString msg) = 0;
				virtual void onTaskLog(QString msg) = 0;
		};
	}
}
