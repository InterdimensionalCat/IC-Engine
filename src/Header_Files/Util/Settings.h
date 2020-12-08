#pragma once
#include <variant>
#include <string>
#include "TimeStepType.h"

using SettingType = std::variant<int, float, bool, TimeStepType, std::string>;

class Settings {
public:
	virtual SettingType getSetting(const std::string& settingname) const = 0;
	virtual void setSetting(const std::string& settingName, const SettingType settingVal) = 0;
};