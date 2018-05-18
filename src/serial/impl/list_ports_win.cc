#if defined(_WIN32)

/*
 * Copyright (c) 2014 Craig Lilley <cralilley@gmail.com>
 * This software is made available under the terms of the MIT licence.
 * A copy of the licence can be obtained from:
 * http://opensource.org/licenses/MIT
 */



#include "serial/serial.h"
#include <tchar.h>
#include <windows.h>
#include <setupapi.h>
#include <initguid.h>
#include <devguid.h>
#include <cstring>
#include <SetupAPI.h>


using serial::PortInfo;
using std::vector;
using std::string;

static const DWORD port_name_max_length = 256;
static const DWORD friendly_name_max_length = 256;
static const DWORD hardware_id_max_length = 256;

// Convert a wide Unicode string to an UTF8 string
std::string utf8_encode(const std::wstring &wstr)
{
	int size_needed = WideCharToMultiByte(CP_UTF8, 0, &wstr[0], (int)wstr.size(), NULL, 0, NULL, NULL);
	std::string strTo( size_needed, 0 );
	WideCharToMultiByte                  (CP_UTF8, 0, &wstr[0], (int)wstr.size(), &strTo[0], size_needed, NULL, NULL);
	return strTo;
}

vector<PortInfo>
serial::list_ports()
{
	vector<PortInfo> devices_found;

	HDEVINFO device_info_set = SetupDiGetClassDevs(
		(const GUID *) &GUID_DEVCLASS_PORTS,
		NULL,
		NULL,
		DIGCF_PRESENT);

	unsigned int device_info_set_index = 0;
	SP_DEVINFO_DATA device_info_data;

	device_info_data.cbSize = sizeof(SP_DEVINFO_DATA);

	while(SetupDiEnumDeviceInfo(device_info_set, device_info_set_index, &device_info_data))
	{
		device_info_set_index++;

		// Get port name

		HKEY hkey = SetupDiOpenDevRegKey(
			device_info_set,
			&device_info_data,
			DICS_FLAG_GLOBAL,
			0,
			DIREG_DEV,
			KEY_READ);


		DWORD port_name_length = port_name_max_length;

		#ifdef UNICODE
		wchar_t port_name[port_name_max_length];
		#else
		TCHAR port_name[port_name_max_length];
		#endif

		LONG return_code = RegQueryValueEx(     //NONAME ( ANSI VER )
					hkey,
					L"PortName",
					NULL,
					NULL,
					(LPBYTE)port_name,
					&port_name_length);

		RegCloseKey(hkey);

		if(return_code != EXIT_SUCCESS)
			continue;

		if(port_name_length > 0 && port_name_length <= port_name_max_length)
			port_name[port_name_length-1] = '\0';
		else
			port_name[0] = '\0';

		// Ignore parallel ports
		#ifdef UNICODE
		if(wcsstr(port_name, L"LPT") != NULL)
			continue;
		#else
		if(_tcsstr(port_name, _T("LPT")) != NULL)
			continue;
		#endif


		// Get port friendly name
		#ifdef UNICODE
		wchar_t friendly_name[friendly_name_max_length];
		#else
		TCHAR friendly_name[friendly_name_max_length];
		#endif
		
		DWORD friendly_name_actual_length = 0;

		BOOL got_friendly_name = SetupDiGetDeviceRegistryProperty(
					device_info_set,
					&device_info_data,
					SPDRP_FRIENDLYNAME,
					NULL,
					(PBYTE)friendly_name,
					friendly_name_max_length,
					&friendly_name_actual_length);

		if(got_friendly_name == TRUE && friendly_name_actual_length > 0)
			friendly_name[friendly_name_actual_length-1] = '\0';
		else
			friendly_name[0] = '\0';

		// Get hardware ID
		#ifdef UNICODE
		wchar_t hardware_id[hardware_id_max_length];
		#else
		TCHAR hardware_id[hardware_id_max_length];
		#endif
		
		DWORD hardware_id_actual_length = 0;

		BOOL got_hardware_id = SetupDiGetDeviceRegistryProperty(
					device_info_set,
					&device_info_data,
					SPDRP_HARDWAREID,
					NULL,
					(PBYTE)hardware_id,
					hardware_id_max_length,
					&hardware_id_actual_length);

		if(got_hardware_id == TRUE && hardware_id_actual_length > 0)
			hardware_id[hardware_id_actual_length-1] = '\0';
		else
			hardware_id[0] = '\0';

		#ifdef UNICODE
			std::string portName = utf8_encode(std::wstring(&port_name[0]));
			std::string friendlyName = utf8_encode(friendly_name);
			std::string hardwareId = utf8_encode(hardware_id);
			//std::string portName = port_name;
			//std::string friendlyName = friendly_name;
			//std::string hardwareId = hardware_id;
		#else
			std::string portName = port_name;
			std::string friendlyName = friendly_name;
			std::string hardwareId = hardware_id;
		#endif

		PortInfo port_entry;
		port_entry.port = portName;
		port_entry.description = friendlyName;
		port_entry.hardware_id = hardwareId;

		devices_found.push_back(port_entry);
	}

	SetupDiDestroyDeviceInfoList(device_info_set);

	return devices_found;
}

#endif // #if defined(_WIN32)
