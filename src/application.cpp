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
* @file application.cpp
* @class Application
* @package openpst/gui-common
* @brief
*
* @author Gassan Idriss <ghassani@gmail.com>
*/

#include "application.h"

using namespace OpenPST::GUI;

Application::Application(int& argc, char** argv, const char* translatorPrefix) :
	QApplication(argc, argv)
{

#if defined (_WIN32) && defined (DEBUG)
	AllocConsole();
	freopen_s(&sout, "CONOUT$", "w", stdout);
	freopen_s(&serr, "CONOUT$", "w", stderr);
#endif

	qtTranslator.load("qt_" + QLocale::system().name(), QLibraryInfo::location(QLibraryInfo::TranslationsPath));
	translator.load(translatorPrefix + QLocale::system().name(), "languages");

	this->installTranslator(&qtTranslator);
	this->installTranslator(&translator);
		
#if (QT_VERSION >= QT_VERSION_CHECK(5, 6, 0))
    	setAttribute( Qt::AA_EnableHighDpiScaling );
#endif	

}


Application::~Application()
{
#if defined (_WIN32) && defined (DEBUG)
	fclose(sout);
	fclose(serr);
	FreeConsole();
#endif
}
