#define WIN32_LEAN_AND_MEAN


#include <string>
#include <map>
#include <Windows.h>
#include "resource.h"
#include "ini.h"

std::map<int, std::string> mapEditID_StrKey{};
std::map<std::string, float> mapStrKey_Value{};

void InitLoad() {
	mapEditID_StrKey[IDC_EDIT1] = "JetAltitude";

	void* iniReader = iniReaderInstantiate("C:\\settings.ini");

	mapStrKey_Value["JetAltitude"] = iniReaderGetFloat(iniReader, "Geometry", "JetAltitude");

	iniReaderDestroy(iniReader);
}

void ValidateEdit(HWND hwnd, int ID) {

	if (mapEditID_StrKey.find(ID) == mapEditID_StrKey.end())
		return;

	char buf[1024];
	GetDlgItemText(hwnd, ID, buf, 1024);

	float newValue = mapStrKey_Value[mapEditID_StrKey[ID]];

	try {
		float canNewValue = std::stof(buf);
		newValue = canNewValue;
	}
	catch (...) {

	}

	mapStrKey_Value[mapEditID_StrKey[ID]] = newValue;

	SetDlgItemText(hwnd, ID, std::to_string(newValue).c_str());
}


LRESULT CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_COMMAND:
		if (HIWORD(wParam) == EN_KILLFOCUS) {
			ValidateEdit(hwnd, LOWORD(wParam));
			break;
		}

		switch (LOWORD(wParam))
		{
		case IDCANCEL:
			//char txt[1024];

			//GetDlgItemText(hwnd, IDC_EDIT1, txt, 1024);

			//MessageBoxA(NULL, txt, "SDFDSF", MB_OK);
			break;
		}
		break;
	case WM_CLOSE:
		EndDialog(hwnd, 0);
		break;
	default:
		return FALSE;
	}
	return TRUE;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	InitLoad();

	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}