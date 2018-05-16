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
* @file task.h
* @class Task
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#pragma once

#include <QObject>
#include <QRunnable>

class Task : public QObject, public QRunnable
{
	Q_OBJECT

	public:
		~Task() {
			if (canceller) {
				*canceller = false;
			}
		}
		virtual void run() = 0;

		bool cancelled() {
			return canceller ? *canceller : false;
		}
		void setCanceller(volatile bool* cancelController) {
			canceller = cancelController;
		}

	protected:
		//volatile bool* canceller = 0; NONAME
		volatile bool* canceller;
	signals:
		void started();
		void aborted();
		void complete();
		void error(QString msg);
		void log(QString msg);
};