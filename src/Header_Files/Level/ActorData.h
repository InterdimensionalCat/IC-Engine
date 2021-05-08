#pragma once
#include <memory>
#include <optional>
#include "LoggerProvider.h"
#include "json.hpp"
#include "ActorUID.h"
#include <filesystem>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

namespace ic {
	class ActorData {
	public:
        ActorData(const std::string& actorname, const std::string& variantname = "", std::unique_ptr<json> mapdata = std::make_unique<json>())
			: actorname(actorname), mapCharacteristics(std::move(mapdata)), actor(ActorUID::createNewInstance(actorname)) {


			std::filesystem::path staticJson(std::filesystem::current_path());
			staticJson /= "resources";
			staticJson /= "actor";
			staticJson /= "static";
			staticJson /= actorname;
			staticJson += ".json";

			std::ifstream st(staticJson.string().c_str());
			if (st.is_open()) {
				staticData = std::make_unique<json>();
				st >> *staticData;
			}
			else {
				LoggerProvider::logAndThrowLogicError("JSON Files not found for actor " + actorname + "!", LogSeverity::Fatal, LogType::General);
			}

			if (variantname != "") {
				std::filesystem::path dynamicJson(std::filesystem::current_path());
				dynamicJson /= "resources";
				dynamicJson /= "actor";
				dynamicJson /= "dynamic";
				dynamicJson /= variantname;
				dynamicJson += ".json";

				std::ifstream dyn(dynamicJson.string().c_str());
				if (dyn.is_open()) {
					dynamicData = std::make_unique<json>();
					dyn >> *dynamicData.value();
				}
				else {
					LoggerProvider::logAndThrowLogicError("JSON Files not found for actor " + variantname + "!", LogSeverity::Fatal, LogType::General);
				}
			}
        }


		//WARNING: NO TWO KEYS CAN HAVE THE SAME NAME IN AN ACTOR DATA OBJECT, FINDER WILL STOP AFTER THE FIRST FOUND INSTANCE
        template<typename SearchType>
        SearchType findKey(const std::string& keyval) const {
            std::optional<SearchType> foundVal;

            foundVal = findKey<SearchType>(*mapCharacteristics, keyval);

            if (!foundVal.has_value()) {
                foundVal = findKey<SearchType>(*staticData, keyval);
            }

            if (!foundVal.has_value() && dynamicData.has_value()) {
                foundVal = findKey<SearchType>(*dynamicData.value(), keyval);
            }

            return foundVal.value();
        }

		ActorUID getActorUID() const { return actor; }
		std::string getActorName() const { return actorname; }

		bool hasVariant() {
			return dynamicData.has_value();
		}

    private:
        template<typename SearchType>
        std::optional<SearchType> findKey(const json& j, const std::string& keyval) const {
			std::optional<SearchType> returnval{};

			for (auto& [key, val] : j.items()) {
				if (val.is_object()) {
					returnval = findKey<SearchType>(val, keyval);
				}
				else {
					if (keyval == key) {
						returnval = val.get<SearchType>();
					}
				}

				if (returnval.has_value()) break;
			}

			return returnval;
        }

		std::unique_ptr<json> staticData;
		std::optional<std::unique_ptr<json>> dynamicData;
		std::unique_ptr<json> mapCharacteristics;
		ActorUID actor;
		std::string actorname;
	};
}