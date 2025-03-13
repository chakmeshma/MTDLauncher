#define WIN32_LEAN_AND_MEAN


#include <string>
#include <map>
#include <Windows.h>
#include <shellapi.h>
#include <fstream>
#include "resource.h"
#include "ini.h"

static std::map<int, std::string> mapEditID_StrKey{};
static std::map<std::string, float> mapStrKey_Value{};
static std::map<std::string, float> mapStrKey_DefaultValue{};
static std::string settingsFileName = "";
static std::string launcheeFileName = "";

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

	void* iniReader = iniReaderInstantiate(settingsFileName.c_str());

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


	mapStrKey_DefaultValue["JetAltitude"] = 98050.0f;
	mapStrKey_DefaultValue["JetSpeed"] = 600000.0f;
	mapStrKey_DefaultValue["MissileSpeedFactor"] = 1.5f;
	mapStrKey_DefaultValue["PropelForce"] = 900001.0f;
	mapStrKey_DefaultValue["StickDistance"] = 11000.0f;
	mapStrKey_DefaultValue["ShakeValue"] = 19000000.0f;
	mapStrKey_DefaultValue["RotationAngleLimit"] = 60.0f;
	mapStrKey_DefaultValue["DetectionRectMinArea"] = 75.0f;
	//mapStrKey_DefaultValue
	mapStrKey_DefaultValue["ColorSaturation;R"] = 1.0f;
	mapStrKey_DefaultValue["ColorSaturation;G"] = 1.0f;
	mapStrKey_DefaultValue["ColorSaturation;B"] = 1.0f;
	mapStrKey_DefaultValue["ColorSaturation;A"] = 1.0f;
	//mapStrKey_DefaultValue
	mapStrKey_DefaultValue["ColorContrast;R"] = 1.0f;
	mapStrKey_DefaultValue["ColorContrast;G"] = 1.0f;
	mapStrKey_DefaultValue["ColorContrast;B"] = 1.0f;
	mapStrKey_DefaultValue["ColorContrast;A"] = 1.0f;
	//mapStrKey_DefaultValue
	mapStrKey_DefaultValue["FilmGrainIntensity"] = 0.0f;
	mapStrKey_DefaultValue["CameraFOV"] = 60.0f;
}

void AppendFloatLine(const std::string& key, std::string& strData) {
	strData += key;
	strData += " = ";
	strData += std::to_string(mapStrKey_Value[key]);
	strData += "\n";
}

void AppendVectorLine(const std::string& key, std::string& strData) {
	strData += key;
	strData += " = ";

	strData += std::to_string(mapStrKey_Value[key + ";R"]);
	strData += " ";
	strData += std::to_string(mapStrKey_Value[key + ";G"]);
	strData += " ";
	strData += std::to_string(mapStrKey_Value[key + ";B"]);
	strData += " ";
	strData += std::to_string(mapStrKey_Value[key + ";A"]);

	strData += "\n";
}

bool Save() {
	std::string newFileData = "";
	newFileData += "[Geometry]\n";

	AppendFloatLine("JetAltitude", newFileData);
	AppendFloatLine("JetSpeed", newFileData);
	AppendFloatLine("MissileSpeedFactor", newFileData);
	AppendFloatLine("PropelForce", newFileData);
	AppendFloatLine("StickDistance", newFileData);
	AppendFloatLine("ShakeValue", newFileData);
	AppendFloatLine("RotationAngleLimit", newFileData);
	AppendFloatLine("DetectionRectMinArea", newFileData);

	newFileData += "\n[Rendering]\n";
	AppendVectorLine("ColorSaturation", newFileData);
	AppendVectorLine("ColorContrast", newFileData);
	AppendFloatLine("FilmGrainIntensity", newFileData);
	AppendFloatLine("CameraFOV", newFileData);

	std::ofstream saveFile(settingsFileName.c_str());

	if (saveFile.is_open()) {
		saveFile << newFileData;

		saveFile.close();

		return true;
	}

	return false;
}

std::string removeTrailingZeros(const std::string& number) {
	std::string result = number;
	while (!result.empty() && result.back() == '0') {
		result.pop_back(); // Remove the last character if it is '0'
	}

	if (result.back() == '.')
		result.pop_back();

	return result;
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

	SetDlgItemText(hwnd, ID, removeTrailingZeros(std::to_string(newValue)).c_str());
}

void ValidateAllEdit(HWND hwnd) {
	for (auto it = mapEditID_StrKey.begin(); it != mapEditID_StrKey.end(); ++it) {
		ValidateEdit(hwnd, it->first);
	}
}

LRESULT CALLBACK DlgProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam)
{
	switch (Message)
	{
	case WM_INITDIALOG:
		ValidateAllEdit(hwnd);
		break;
	case WM_COMMAND:
		if (HIWORD(wParam) == EN_KILLFOCUS) {
			ValidateEdit(hwnd, LOWORD(wParam));
			break;
		}

		if (HIWORD(wParam) == EN_CHANGE) {
			if (mapEditID_StrKey.find(LOWORD(wParam)) != mapEditID_StrKey.end())
				EnableWindow(GetDlgItem(hwnd, IDOK2), TRUE);

			break;
		}

		switch (LOWORD(wParam))
		{
		case IDOK:
			ValidateAllEdit(hwnd);

			if (!Save()) {
				MessageBox(hwnd, "Couldn't open settings.ini file for saving!", "Error", MB_OK);
			}
			else
			{
				ShellExecute(0, "open", launcheeFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
				EndDialog(hwnd, 0);
			}

			break;
		case IDOK2:
			ValidateAllEdit(hwnd);

			if (!Save()) {
				MessageBox(hwnd, "Couldn't open settings.ini file for saving!", "Error", MB_OK);
			}
			else
			{
				EnableWindow(GetDlgItem(hwnd, IDOK2), FALSE);
				//ShellExecute(0, "open", launcheeFileName.c_str(), NULL, NULL, SW_SHOWNORMAL);
				//EndDialog(hwnd, 0);
			}

			break;
		case IDOK3:
			for (auto it = mapEditID_StrKey.begin(); it != mapEditID_StrKey.end(); ++it) {
				SetDlgItemText(hwnd, it->first, "");
			}

			for (auto it = mapStrKey_Value.begin(); it != mapStrKey_Value.end(); ++it) {
				mapStrKey_Value[it->first] = mapStrKey_DefaultValue[it->first];
			}

			ValidateAllEdit(hwnd);

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
	char currDir[MAX_PATH];
	GetCurrentDirectory(MAX_PATH, currDir);

	settingsFileName = "";
	settingsFileName += currDir;
	settingsFileName += "\\settings.ini";

	launcheeFileName = "";
	launcheeFileName += currDir;
	launcheeFileName += "\\MissileTrackingDemo.exe";

	//launcheeFileName = "C:\\Users\\chakm\\OneDrive\\Desktop\\Windows\\MissileTrackingDemo.exe";

	try
	{
		InitLoad();
	}
	catch (...) {
		MessageBox(NULL, "Couldn't open/load settings.ini file!", "Error", MB_OK);

		return EXIT_FAILURE;
	}

	return DialogBox(hInstance, MAKEINTRESOURCE(IDD_DIALOG1), NULL, DlgProc);
}