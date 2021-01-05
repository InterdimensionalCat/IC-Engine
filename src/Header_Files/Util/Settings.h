#pragma once
#include <variant>
#include <string>
#include "TimeStepType.h"

using SettingType = std::variant<int, float, bool, ic::TimeStepType, std::string>;

namespace ic {
	class Settings {
	public:
		virtual SettingType getSetting(const std::string& settingname) const = 0;
		virtual void setSetting(const std::string& settingName, const SettingType settingVal) = 0;
	};
}


