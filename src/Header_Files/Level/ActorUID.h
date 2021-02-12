#pragma once
#include <map>
#include <memory>
#include <exception>
#include <vector>

namespace ic {
	class ActorUID {

	public:
		static void registerNewActor(const std::string& actorname) {
			auto idnum = nametoidmap.find(actorname);
			if (idnum != nametoidmap.end()) {
				//actor already exists
				throw std::exception();
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
				throw std::exception();
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
		static ActorUID createNewInstance(const std::string& actorname) {
			auto idnum = nametoidmap.find(actorname);
			if (idnum == nametoidmap.end()) {
				//actor does not exist/not registered
				throw std::exception();
			}
			else {
				//else create the instance
				return createNewInstance(idnum->second);
			}
		}

		bool operator==(const ActorUID& rhs) const {
			return compare(rhs) == 0;
		}
		bool operator<(const ActorUID& rhs) const {
			return compare(rhs) < 0;
		}
		bool operator>(const ActorUID& rhs) const {
			return compare(rhs) > 0;
		}



	private:
		ActorUID(std::shared_ptr<int> actorID, std::shared_ptr<int> instancenum) : actorID(actorID), instancenum(instancenum) {}

		int compare(const ActorUID& other) const {
			if (actorID == other.actorID) {
				if (*instancenum == *other.instancenum) return 0;
				return *instancenum > *other.instancenum ? 1 : -1;
			}
			else {
				return *actorID > *other.actorID ? 1 : -1;
			}
		}

		static ActorUID createNewInstance(const int actorID) {
			auto instancecount = instances.at(actorID).size();
			auto& actorIDinstances = instances.at(actorID);
			for (auto i = 0; i < instancecount; i++) {
				if ((int)actorIDinstances.at(i).use_count() == 1) {
					//instancenum not in use, can overrite
					return ActorUID(actorIDs.at(actorID), actorIDinstances.at(i));
				}
			}

			actorIDinstances.push_back(std::make_shared<int>((int)instancecount));
			return ActorUID(actorIDs.at(actorID), actorIDinstances.at(instancecount));
		}

		std::shared_ptr<int> actorID;
		std::shared_ptr<int> instancenum;

		static inline std::map<std::string, int> nametoidmap;

		//original location of the actorID shared pointer in each ActorUID instance
		static inline std::vector<std::shared_ptr<int>> actorIDs;

		//original location of the instancenum shared pointer in each ActorUID instance
		static inline std::vector<std::vector<std::shared_ptr<int>>> instances;
		
		//counter that garuntees each actorID being unique
		static inline int idcounter = 0;
	};
}
