#pragma once
#include "Settings.h"
#include <map>

using SettingType = std::variant<int, float, bool, TimeStepType, std::string>;

class GameSettings : public Settings {
public:
	GameSettings();
	SettingType getSetting(const std::string& settingname) const override;
	void setSetting(const std::string& settingName, const SettingType settingVal) override;
	std::map<std::string, SettingType> settingsmap;
};