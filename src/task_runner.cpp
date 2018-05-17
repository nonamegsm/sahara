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
* @file task_runner.cpp
* @class TaskRunner
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "task/task_runner.h"

TaskRunner::TaskRunner(volatile bool* canceller) : canceller(canceller)
{
	pool.setExpiryTimeout(-1);
	pool.setMaxThreadCount(1);
}

TaskRunner::~TaskRunner()
{
	cancelAll();
	if (pool.activeThreadCount() > 0) {
		pool.waitForDone();
	}
}

int TaskRunner::queue(Task* task, int priority)
{
	if (canceller) {
		task->setCanceller(canceller);
	}

	pool.start(task, priority);

	return 0;
}


void TaskRunner::clearQueue()
{
	//pool.clear(); NONAME
}

void TaskRunner::cancelCurrent()
{
	if (canceller) {
		*canceller = true;
	}
}

void TaskRunner::cancelAll()
{
	clearQueue();
	cancelCurrent();
}

bool TaskRunner::isRunning()
{
	return pool.activeThreadCount() > 0;
}



bool TaskRunner::waitForDone()
{
	if (isRunning()) {
		return pool.waitForDone();
	}
	return true;
}