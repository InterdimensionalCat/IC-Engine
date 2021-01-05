#include "GameSettings.h"
#include <map>
#include <variant>
#include <string>

using namespace ic;

GameSettings::GameSettings() {
	setSetting("Title", std::string("Game Engine 2020"));
	setSetting("Width", 1920);
	setSetting("Height", 1080);
	setSetting("targetFPS", 60.0f);
	setSetting("targetDT", 1.0f / 60.0f);
	setSetting("debug", false);
	setSetting("paused", false);
	setSetting("vsync", false);
	setSetting("running", true);
	setSetting("TimeStepType", TimeStepType::Fixed);
}

SettingType GameSettings::getSetting(const std::string& settingname) const {
#ifndef debug_mode
	cout << "setting " << settingname " accessed with value " << settingsmap[settingname] << "\n";
#endif
	return settingsmap.at(settingname);
}

void GameSettings::setSetting(const std::string& settingName, const SettingType settingVal) {
#ifndef debug_mode
	cout << "setting " << settingname " created with value " << settingVal << "\n";
#endif
	settingsmap.insert_or_assign(settingName, settingVal);
}