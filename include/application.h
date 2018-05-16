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
* @file application.h
* @class Application
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#pragma once

#include <QApplication>
#include <QMetaType>
#include <QLibraryInfo>
#include <QTranslator>
//#include <QCommandLineParser>
#ifdef _WIN32
#include <windows.h>
#endif

namespace OpenPST {
	namespace GUI {
		class Application : public QApplication {
			public:
				Application(int& argc, char** argv, const char* translationPrefix);
				~Application();
			private:
				QTranslator qtTranslator;
				QTranslator translator;
			
#if defined (_WIN32) && defined (DEBUG)
				FILE* sout;
				FILE* serr;
#endif
		};
	}
}