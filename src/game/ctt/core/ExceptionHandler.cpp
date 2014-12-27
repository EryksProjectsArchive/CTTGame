//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/ExceptionHandler.cpp
// Author	: Eryk Dwornicki
// NOTE:	: Remember to use only low-level operating-system methods here.
//
//////////////////////////////////////////////

#include "ExceptionHandler.h"

#ifdef _WIN32
#include <Windows.h>
#include <ShlObj.h>
#include <stdio.h>
#include <time.h>

void getAdditionalInfoAboutAddr(uint32 address, uint32 * addressWithoutBase, char * fileName)
{
	_MEMORY_BASIC_INFORMATION Buffer;
	int iResult = VirtualQuery((LPCVOID)address, &Buffer, MAX_PATH);
	if (!iResult)
	{
		*addressWithoutBase = 0xBEEF0001;
		return;
	}
	iResult = IsBadCodePtr((FARPROC)Buffer.AllocationBase);
	if (!iResult)
	{
		*addressWithoutBase = 0xBEEF0002;
		return;
	}
	iResult = GetModuleFileNameA((HMODULE)Buffer.AllocationBase, fileName, MAX_PATH);
	if (!iResult)
	{
		*addressWithoutBase = 0xBEEF0003;
		return;
	}
	*addressWithoutBase = address - (DWORD)Buffer.AllocationBase;
	/*if (*addressWithoutBase < 0) unsigned musn't be smaller than false :)
	{
		*addressWithoutBase = 0xBEEF0004;
		return;
	}*/
}

LONG WINAPI exceptionFilter(LPEXCEPTION_POINTERS exceptionPointers)
{
	// Get MyDocuments
	char path[MAX_PATH] = { 0 }, tmpPath[MAX_PATH] = { 0 };
	HRESULT hResult = SHGetFolderPath(NULL, CSIDL_PERSONAL, NULL, SHGFP_TYPE_CURRENT, (LPSTR)tmpPath);
	sprintf(path, "%s\\%s\\crash.log", tmpPath, GAME_NAME);

	FILE *fp = fopen(path, "a+");
	if (fp)
	{
		fputs("-----------------------------------------------\n", fp);

		time_t timer;
		struct tm* t;
		time(&timer);
		t = localtime(&timer);

		fprintf(fp, "Crash log %02d.%02d.%d, %02d:%02d:%02d\n", t->tm_mday, t->tm_mon, 1970+t->tm_year, t->tm_hour, t->tm_min, t->tm_sec);
		fprintf(fp, "Game name: %s, Version: %d.%d.%d/%d\n", GAME_NAME, GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVISION, GAME_VERSION_INT);
		
		OSVERSIONINFOEX info;
		memset(&info, 0, sizeof(OSVERSIONINFOEX));
		info.dwOSVersionInfoSize = sizeof(OSVERSIONINFOEX);
		GetVersionEx((OSVERSIONINFO *)&info);
		char *windows = "Unknown";

		if (info.dwMajorVersion == 6 && info.dwMinorVersion == 3 && info.wProductType == VER_NT_WORKSTATION)
		{
			windows = "Windows 8.1";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 3 && info.wProductType != VER_NT_WORKSTATION)
		{
			windows = "Windows Server 2012 R2";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 2 && info.wProductType == VER_NT_WORKSTATION)
		{
			windows = "Windows 8";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 2 && info.wProductType != VER_NT_WORKSTATION)
		{
			windows = "Windows Server 2012";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 1 && info.wProductType == VER_NT_WORKSTATION)
		{
			windows = "Windows 7";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 1 && info.wProductType != VER_NT_WORKSTATION)
		{
			windows = "Windows Server 2008 R2";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 0 && info.wProductType != VER_NT_WORKSTATION)
		{
			windows = "Windows Server 2008";
		}
		else if (info.dwMajorVersion == 6 && info.dwMinorVersion == 0 && info.wProductType == VER_NT_WORKSTATION)
		{
			windows = "Windows Vista";
		}
		else if (info.dwMajorVersion == 5 && info.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) != 0)
		{
			windows = "Windows Server 2003 R2";
		}
		else if (info.dwMajorVersion == 5 && info.dwMinorVersion == 2 && GetSystemMetrics(SM_SERVERR2) == 0)
		{
			windows = "Windows Server 2003";
		}
		else if (info.dwMajorVersion == 5 && info.dwMinorVersion == 1)
		{
			windows = "Windows XP";
		}
		else if (info.dwMajorVersion == 5 && info.dwMinorVersion == 0)
		{
			windows = "Windows 2000";
		}

		fprintf(fp, "OS: %s, NT: %d.%d", windows, info.dwMajorVersion, info.dwMinorVersion);

		uint32 baseAddress = (uint32)GetModuleHandle(NULL) - 0x401000;
		fprintf(fp, "\n\nExe base address: %p\nException address: %p\nException code: %p\n", baseAddress, exceptionPointers->ExceptionRecord->ExceptionAddress, exceptionPointers->ExceptionRecord->ExceptionCode);

		uint32 addressWithoutBase = 0;
		char fileName[MAX_PATH] = { 0 };
		getAdditionalInfoAboutAddr(baseAddress, &addressWithoutBase, fileName);

		fprintf(fp, "Module file name: %s\nAddress without base: %p", fileName, addressWithoutBase);

		fputs("\n\n", fp);
		fprintf(fp, "EAX: %p, EBP: %p, EBX: %p, ECX: %p\nEDI %p, EDX: %p EFlags: %p, EIP: %p\nESI: %p, ESP: %p\n\n",
			exceptionPointers->ContextRecord->Eax, exceptionPointers->ContextRecord->Ebp, exceptionPointers->ContextRecord->Ebx,
			exceptionPointers->ContextRecord->Ecx, exceptionPointers->ContextRecord->Edi, exceptionPointers->ContextRecord->Edx,
			exceptionPointers->ContextRecord->EFlags, exceptionPointers->ContextRecord->Eip, exceptionPointers->ContextRecord->Esi, exceptionPointers->ContextRecord->Esp);

		fputs("Extended registers:\n", fp);
		for (unsigned int i = 0; i < 512; ++i)
		{
			if (i>1 && !(i%32))
				fputs("\n", fp);
			
			fprintf(fp, "%02X ", exceptionPointers->ContextRecord->ExtendedRegisters[i]);
		}
		fputs("\n", fp);

		fputs("\n\n", fp);

		fflush(fp);
		fclose(fp);

	}
	else
	{
		MessageBox(NULL, "Cannot create crash log file!", "Fatal error", MB_ICONERROR);
	}


	return EXCEPTION_EXECUTE_HANDLER;
}

void __forceinline initWin32ExceptionHandler()
{
	SetUnhandledExceptionFilter(exceptionFilter);
}
#endif

void ExceptionHandler::init()
{
#if defined(_WIN32) && !defined(_WIN64)
	initWin32ExceptionHandler();
#endif
}