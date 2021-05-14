#pragma once
#include <map>
#include <memory>
#include <exception>
#include <vector>
#include <string>
#include "LoggerProvider.h"

//NEED TO MOVE THIS OUT OF HEADERS HOLY SHIT
class boost::uuids::uuid;
using UUID = boost::uuids::uuid;

namespace ic {

	/**
	 * @brief                         The ActorUID class is the way that different parts of an
	 *                                actor reference eachother and know that they belong to the same object,
	 *                                since different parts are decoupled into different objects this is necessasary
	*/
	class ActorUID {

	public:

		ActorUID(const std::string& actorTypeName) : actorTypeName(actorTypeName) {
			auto foundActorName = instancesMap.find(actorTypeName);
			if (foundActorName == instancesMap.end()) {
				//allcoate space for instances and
				//create this ActorUID as the first instance if
				//data for this actorTypeName is not found
				instancesMap.insert(actorTypeName, 
					std::vector<std::shared_ptr<int>>(1, std::make_unique<int>(1))
				);
			}
			else {

				//add a new instance off the end of the array that is one larger
				auto& actorNameInstances = foundActorName->second;
				int newInstanceNum = (int)actorNameInstances.size();
				actorNameInstances.push_back(
					std::make_unique_unique<int>(newInstanceNum)
						);
			}
		}

		//copy works in the way we want, no need to redefine

		~ActorUID() {
			try {
				auto foundActorName = instancesMap.find(actorTypeName);
				if (foundActorName == instancesMap.end()) {

				}
				else {
					//check if the shared instanceNum is going to be the last one out
					//and if it is remove from the instancesmap
					//then if no more instances for this actorTypeName are in the instancesmap
					//then remove the whole actorTypeName entry from the instancemap
				}
			}
			catch (exception e) {
				//log this cus we in some bad shit
			}
		}


		static void registerNewActor(const std::string& actorname) {
			auto idnum = nametoidmap.find(actorname);
			if (idnum != nametoidmap.end()) {
				//actor already exists
				LoggerProvider::log("actor " + actorname + " is already loaded!", LogSeverity::Warning, LogType::General);
				return;
			}
			else {
				nametoidmap.insert(std::pair<std::string, int>(actorname, idcounter));
				actorIDs.push_back(std::make_shared<int>(idcounter));
				instances.push_back(std::vector<std::shared_ptr<int>>());
				idcounter++;
			}
		}

		static void removeActor(const std::string& actorname) {
			auto actorentry = nametoidmap.find(actorname);

			if (actorentry == nametoidmap.end()) {
				//log the error: name doesnt exist
				LoggerProvider::log("actor " + actorname + " doesnt exist!", LogSeverity::Warning, LogType::General);
				return;
			}
			else {

				//remove from id list
				int actorID = actorentry->second;
				actorIDs.erase(std::remove_if(actorIDs.begin(), actorIDs.end(), [actorID](std::shared_ptr<int>& id) {
					return *id == actorID;
					}), actorIDs.end());

				//update actorids
				for (size_t i = 0; i < actorIDs.size(); i++) {
					if (*actorIDs.at(i) > actorID) {
						*actorIDs.at(i) -= 1;
					}
				}

				//remove from nametoidmap
				nametoidmap.erase(actorname);

				//update nametoidmap
				for (auto& nameMapPair : nametoidmap) {
					if (nameMapPair.second > actorID) {
						nameMapPair.second--;
					}
				}


				//remove all instances from the instancemap
				instances.erase(instances.begin() + actorID);
		

			}
		}

		//creates a new ActorUID number and garuntees that the instancenum for each
        //actor is unique
        //this also removes instances currently being unused

		/**
		 * @brief                     Creates and returns a new ActorUID instance of the supplied actor
		 *                            this will register the actor if the supplied actorname has not been
		 *                            registered before, and will clean up instancenums that are now unused.
		 *		                      calls an internal version of createNewInstance that takes the id num for
		 *                            the actor as opposed to the actor name
		 * @param actorname           Name of the actor to create a new instance of
		 * @return                    The new ActorUID instance
		*/
		static ActorUID createNewInstance(const std::string& actorname) {
			auto idnum = nametoidmap.find(actorname);
			if (idnum == nametoidmap.end()) {
				//actor does not exist/not registered
				LoggerProvider::log("actor " + actorname + " is not loaded!", LogSeverity::Warning, LogType::General);
				registerNewActor(actorname);
				return createNewInstance(actorname);
			}
			else {
				//else create the instance
				return createNewInstance(idnum->second);
			}
		}

		/**
		 * @brief                     Get the name of associated actor type
		 * @return                    The name
		*/
		std::string getActorName() const {
			return idtonamemap.at(*actorID);
		}

		/**
		 * @brief                     Comparison operators
		 * @param rhs 
		 * @return 
		*/
		bool operator==(const ActorUID& rhs) const {
			return compare(rhs) == 0;
		}
		bool operator<(const ActorUID& rhs) const {
			return compare(rhs) < 0;
		}
		bool operator>(const ActorUID& rhs) const {
			return compare(rhs) > 0;
		}


		/**
		 * @brief                     Converts the information of an ActorUID to a string that reads nicely for printing
		 * @return                    The printable string in the format:
		 *                            "ActorUID(ActorID=[ActorName], InstanceID=[InstanceNumber])"
		*/
		std::string toString() const {
			return "ActorUID(ActorID=" + std::to_string(*actorID) +
				", InstanceID=" + std::to_string(*instancenum) + ")";
		}

	private:

		/**
		 * @brief                     ActorUID's cannot be freely created
		 * @param actorID 
		 * @param instancenum 
		*/
		//ActorUID(std::shared_ptr<int> actorID, std::shared_ptr<int> instancenum) : actorID(actorID), instancenum(instancenum) {}

		int compare(const ActorUID& other) const {
			if (actorTypeName == other.actorTypeName) {
				if (*instanceNum == *other.instanceNum) return 0;
				return *instanceNum > *other.instanceNum ? 1 : -1;
			}
			else {
				return actorTypeName > other.actorTypeName ? 1 : -1;
			}
		}

		//static ActorUID createNewInstance(const int actorID) {
		//	auto instancecount = instances.at(actorID).size();
		//	auto& actorIDinstances = instances.at(actorID);
		//	for (auto i = 0; i < instancecount; i++) {
		//		if ((int)actorIDinstances.at(i).use_count() == 1) {
		//			//instancenum not in use, can overrite
		//			return ActorUID(actorIDs.at(actorID), actorIDinstances.at(i));
		//		}
		//	}

		//	actorIDinstances.push_back(std::make_shared<int>((int)instancecount));
		//	return ActorUID(actorIDs.at(actorID), actorIDinstances.at(instancecount));
		//}

		//std::shared_ptr<int> actorID;
		//std::shared_ptr<int> instancenum;

		//static inline std::map<std::string, int> nametoidmap;
		//static inline std::map<int, std::string> idtonamemap;

		//original location of the actorID shared pointer in each ActorUID instance
		//static inline std::vector<std::shared_ptr<int>> actorIDs;

		//original location of the instancenum shared pointer in each ActorUID instance
		//static inline std::vector<std::vector<std::shared_ptr<int>>> instances;
		
		//counter that garuntees each actorID being unique
		//static inline int idcounter = 0;

		static inline std::map<std::string, std::vector<std::shared_ptr<int>>> instancesMap;

		std::string actorTypeName;
		//std::shared_ptr<int> instanceNum;
		std::shared_ptr<UUID> instanceNum;
	};
}
