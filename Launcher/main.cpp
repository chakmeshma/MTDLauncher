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
	mapEditID_StrKey[IDC_EDIT2] = "JetSpeed";
	mapEditID_StrKey[IDC_EDIT3] = "MissileSpeedFactor";
	mapEditID_StrKey[IDC_EDIT4] = "PropelForce";
	mapEditID_StrKey[IDC_EDIT5] = "StickDistance";
	mapEditID_StrKey[IDC_EDIT6] = "ShakeValue";
	mapEditID_StrKey[IDC_EDIT7] = "RotationAngleLimit";
	mapEditID_StrKey[IDC_EDIT8] = "DetectionRectMinArea";
	mapEditID_StrKey[IDC_EDIT9] = "ColorSaturation;R";
	mapEditID_StrKey[IDC_EDIT10] = "ColorSaturation;G";
	mapEditID_StrKey[IDC_EDIT11] = "ColorSaturation;B";
	mapEditID_StrKey[IDC_EDIT12] = "ColorSaturation;A";
	mapEditID_StrKey[IDC_EDIT13] = "ColorContrast;R";
	mapEditID_StrKey[IDC_EDIT14] = "ColorContrast;G";
	mapEditID_StrKey[IDC_EDIT15] = "ColorContrast;B";
	mapEditID_StrKey[IDC_EDIT16] = "ColorContrast;A";
	mapEditID_StrKey[IDC_EDIT17] = "FilmGrainIntensity";
	mapEditID_StrKey[IDC_EDIT18] = "CameraFOV";

	void* iniReader = iniReaderInstantiate("C:\\settings.ini");

	mapStrKey_Value["JetAltitude"] = iniReaderGetFloat(iniReader, "Geometry", "JetAltitude");
	mapStrKey_Value["JetSpeed"] = iniReaderGetFloat(iniReader, "Geometry", "JetSpeed");
	mapStrKey_Value["MissileSpeedFactor"] = iniReaderGetFloat(iniReader, "Geometry", "MissileSpeedFactor");
	mapStrKey_Value["PropelForce"] = iniReaderGetFloat(iniReader, "Geometry", "PropelForce");
	mapStrKey_Value["StickDistance"] = iniReaderGetFloat(iniReader, "Geometry", "StickDistance");
	mapStrKey_Value["ShakeValue"] = iniReaderGetFloat(iniReader, "Geometry", "ShakeValue");
	mapStrKey_Value["RotationAngleLimit"] = iniReaderGetFloat(iniReader, "Geometry", "RotationAngleLimit");
	mapStrKey_Value["DetectionRectMinArea"] = iniReaderGetFloat(iniReader, "Geometry", "DetectionRectMinArea");

	mapStrKey_Value["ColorSaturation;R"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorSaturation")[0];
	mapStrKey_Value["ColorSaturation;G"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorSaturation")[1];
	mapStrKey_Value["ColorSaturation;B"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorSaturation")[2];
	mapStrKey_Value["ColorSaturation;A"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorSaturation")[3];

	mapStrKey_Value["ColorContrast;R"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorContrast")[0];
	mapStrKey_Value["ColorContrast;G"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorContrast")[1];
	mapStrKey_Value["ColorContrast;B"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorContrast")[2];
	mapStrKey_Value["ColorContrast;A"] = iniReaderGetFloatVector(iniReader, "Rendering", "ColorContrast")[3];

	mapStrKey_Value["FilmGrainIntensity"] = iniReaderGetFloat(iniReader, "Rendering", "FilmGrainIntensity");
	mapStrKey_Value["CameraFOV"] = iniReaderGetFloat(iniReader, "Rendering", "CameraFOV");


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