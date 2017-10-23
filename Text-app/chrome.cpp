#include <Windows.h>
#include <Oleacc.h>
#include <stdio.h>
#include <iostream>
#include <windows.h>
using namespace std;
/*tracking URL changes in Chrome, have not integrated this with main code yet */

string chrome::get_location(HWND hwnd){
	HWINEVENTHOOK LHook = 0; 
	void CALLBACK WinEventProc(HWINEVENTHOOK hWinEventHook, DWORD event, HWND hwnd, LONG idObject, LONG idChild, DWORD dwEventThread, DWORD dwmsEventTime){
		IAccessible* pAcc = NULL; 
		VARIANT varChild; 
		HRESULT hr = AccessibleObjectFromEvent(hwnd, idObject, idChild, &pAcc, &varChild); 
		if((hr == S_OK) && (pAcc != NULL)){
			BSTR bstrName, bstrValue; 
			pAcc -> get_accValue(varChild, &bstrValue); 
			pAcc -> get_accName(varChild, &bstrName); 
			char classname[50]; 
			GetClassName(hwnd, className, 50); 
			if(string(className) == "Chrome_WidgetWin_1")
				printf("URL Change: %ls\n", bstrValue); 
			pAcc -> Release(); 
		}
	}

	void Hook(){ 
		if(LHook != 0) return; 
		CoInitialize(NULL); 
		LHook = SetWinEventHook(EVENT_MIN, EVENT_MAX, NULL, WinEventProc, 0, 0, WINEVENT_SKIPOWNPROCESS); 
	}

	void Unhook(){
		if(!LHook) return
		UnhookWinEvent(LHook); 
		CoUninitialize(); 
	}

	MSG msg; 
	Hook(); 
	/* to distribute workload amongst multiple CPU Cores */ 

	#pragma omp parallel for

	if(GetMessage(&msg, NULL, 0, 0)) { 
		TranslateMessage(&msg); 
		DispatchMessage(&msg); 
	}
	Unhook(); 
}
