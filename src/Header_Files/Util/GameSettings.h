#pragma once
#include"IcLogger.h"

#ifndef IC_SETTING
#define IC_SETTING(settingname) \
    static auto get##settingname() {\
        return settings->settingname;\
	}\
    static void set##settingname(const auto& settingval) {\
	    settings->settingname = settingval;\
	}
#endif

#ifndef IC_WRITE_SETTING_ARG
#define IC_WRITE_SETTING_ARG(arg) \
try {\
     (*file)["settings"][#arg] = arg;\
}\
catch (std::exception e) {\
    Logger::error("exception occured while writing setting {}, skipping. Error msg: {}", #arg, e.what());\
}
#define IC_READ_SETTING_ARG(arg) \
try {\
       arg = (*file)["settings"][#arg];\
}\
catch (std::exception e) {\
    Logger::error("exception occured while reading setting {}, skipping. Error msg: {}", #arg, e.what());\
}
#endif

namespace ic {
	enum class TimeStepType { Fixed, Variable };

	class Settings
	{
	public:

		static void start() {
			settings = std::make_unique<StandardSettings>();
		}

		static void stop() {
			settings.reset();
		}

		class StandardSettings {
		public:

			StandardSettings() {
				Logger::info("Initalizing standard settings.");
				fs::path filepath(fs::current_path());
				filepath /= "settings";
				filepath /= "settings";
				filepath += ".json";

				std::shared_ptr<json> olddata = std::make_shared<json>();

				if (fs::exists(filepath)) {
					std::ifstream readfile(filepath);
					Logger::info("Existing settings file found!");

					try {
						readfile >> (*olddata);
						fromJson(olddata);
					}
					catch (json::parse_error& e)
					{
						Logger::warn("existing settings file does not appear to have json data.");
					}


					readfile.close();
					Logger::info("Existing settings file loaded successfully!");
				}
				else {
					Logger::warn("existing settings file not found, intializing settings from default values");
				}
			}

			void toJson(std::shared_ptr<json> file) const {
				IC_WRITE_SETTING_ARG(Width);
				IC_WRITE_SETTING_ARG(Height);
				IC_WRITE_SETTING_ARG(TargetFPS);
				IC_WRITE_SETTING_ARG(Title);
				IC_WRITE_SETTING_ARG(Vsync);
			}

			void fromJson(const std::shared_ptr<json> file) {
				IC_READ_SETTING_ARG(Width);
				IC_READ_SETTING_ARG(Height);
				IC_READ_SETTING_ARG(TargetFPS);
				IC_READ_SETTING_ARG(Title);
				IC_WRITE_SETTING_ARG(Vsync);
			}

			~StandardSettings() {

				Logger::info("Saving standard settings.");

				try {
					std::shared_ptr<json> newdata = std::make_shared<json>();
					toJson(newdata);

					fs::path filepath(fs::current_path());
					filepath /= "settings";

					if (!fs::exists(filepath)) {
						Logger::warn("Directory {} does not exist, "
							"creating...", filepath.string());
						fs::create_directories(filepath);
					}

					filepath /= "settings";
					filepath += ".json";

					std::fstream writefile;
					writefile.open(filepath, std::fstream::out);

;

					writefile << newdata->dump(2);

					writefile.close();
					Logger::info("Settings save successful at path {}", filepath.string());
				}
				catch (std::exception e) {
					//log this
					Logger::error("Settings save unsuccessful!");
				}
			}

		private:

			friend class Settings;

			bool Debug   = false;
			bool Paused  = false;
			bool Running = true;
			TimeStepType StepType = TimeStepType::Fixed;

			float Width     = 1920;
			float Height    = 1080;
			float TargetFPS = 60.0f;
			std::string Title = "GameEngine2020";
			bool Vsync = false;

		};

		IC_SETTING(Debug);
		IC_SETTING(Paused);
		IC_SETTING(Running);
		IC_SETTING(StepType);

		IC_SETTING(Width);
		IC_SETTING(Height);
		IC_SETTING(TargetFPS);
		IC_SETTING(Title);
		IC_SETTING(Vsync);

		static auto getTargetDT() {
			if (!settings) {
				settings = std::make_unique<StandardSettings>();
			}
			return (1.0f / settings->TargetFPS);
		}

	private:
		inline static std::unique_ptr<StandardSettings> settings;
	};
}

#undef IC_SETTING
#undef IC_WRITE_SETTING_ARG
#undef IC_READ_SETTING_ARG