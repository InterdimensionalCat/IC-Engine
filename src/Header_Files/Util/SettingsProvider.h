#include "Settings.h"
#include "GameSettings.h"
#include <memory>
#include <string>
#include "TimeStepType.h"

using SettingType = std::variant<int, float, bool, TimeStepType, std::string>;

class SettingsProvider {
public:
	template<typename T>
	static T getSetting(const std::string& settingname) {
		static_assert(
			std::is_same<T, int>::value 
			|| std::is_same<T, float>::value
			|| std::is_same<T, bool>::value
			|| std::is_same<T, TimeStepType>::value
			|| std::is_same<T, std::string>::value
		);

		if (!settings) {
			settings = std::make_unique<GameSettings>();
		}
		try {
			return std::get<T>(settings->getSetting(settingname));
		}
		catch(const std::bad_variant_access&) {
#ifdef debug_mode
			std::cout << "setting " + settingname + " is not of type " + typeid(T).name() + "!\n";
#endif
			return T();
		}
		catch (const std::out_of_range&) {
#ifdef debug_mode
			std::cout << "setting " + settingname + " does not exist!\n";
#endif
			return T();
		}
	}

	template<typename T>
	static void setSetting(const std::string& settingName, const T settingVal) {
		static_assert(
			std::is_same<T, int>::value
			|| std::is_same<T, float>::value
			|| std::is_same<T, bool>::value
			|| std::is_same<T, TimeStepType>::value
			|| std::is_same<T, std::string>::value
			);

		if (!settings) {
			settings = std::make_unique<GameSettings>();
		}
		settings->setSetting(settingName, settingVal);
	}
private:
	inline static std::unique_ptr<Settings> settings;
};