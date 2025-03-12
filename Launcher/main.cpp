#define WIN32_LEAN_AND_MEAN


#include <string>
#include <map>
#include <Windows.h>
#include "resource.h"
#include "ini.h"

std::map<int, std::string> mapEditID_StrKey{};

void InitLoad() {
	iniReaderInstantiate("C:\\settings.ini");
}

void ValidateEdit(HWND hwnd, int ID) {

	//char buf[1024];
	//GetDlgItemText(hwnd, ID, buf, 1024);

	//float newValue = lastValue;

	//try {
	//	float canNewValue = std::stof(buf);
	//	newValue = canNewValue;
	//}
	//catch (...) {

	//}

	//lastValue = newValue;

	//SetDlgItemText(hwnd, ID, std::to_string(newValue).c_str());
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