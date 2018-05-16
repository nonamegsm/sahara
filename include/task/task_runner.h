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
* @file task_runner.h
* @class TaskRunner
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#pragma once

#include <QThreadPool>
#include "task/task.h"

class TaskRunner
{	
	
	private:
		QThreadPool pool;
		volatile bool* canceller;
	public:
		TaskRunner(volatile bool* canceller = 0);
		~TaskRunner();
		void clearQueue();
		void cancelCurrent();
		void cancelAll();
		bool waitForDone();
		bool isRunning();
		int queue(Task* task, int priority = 0);
};