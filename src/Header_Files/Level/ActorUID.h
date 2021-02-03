#pragma once
#include <unordered_map>
#include <memory>

namespace ic {
	struct ActorUID {


		static void registerNewActor(const std::string& actorname) {
			int actorCount = (int)instanceMap.size();
			nametoidmap.emplace(actorname, actorCount);
			instanceMap.emplace(actorCount, std::vector<std::shared_ptr<ActorUID>>(0));
		}

		static void removeActor(const std::string& actorname) {
			auto actorentry = nametoidmap.find(actorname);
			if (actorentry == nametoidmap.end()) {
				//log the error
				throw exception();
			}
			else {
				return id->second;
			}
		}

		static int nameToID(const std::string& actorname) {
			auto id = nametoidmap.find(actorname);
			if (id == nametoidmap.end()) {
				//log the error
				throw exception();
			}
			else {
				return id->second;
			}
		}

		//creates a new ActorUID number and garuntees that the instancenum for each
		//actor is unique
		static std::shared_ptr<ActorUID> makeNewInstance(const int actorID) {
			auto actorInstances = instanceMap.find(actorID);
			if (actorInstances == instanceMap.end()) {
				//log the error
				throw exception();
			}
			else {
				auto& instancesVec = actorInstances->second;
				int newinstancenum = instancesVec.size();
				for (size_t i = 0; i < newinstancenum; i++) {
					if (instancesVec.at(i).use_count() == 1) {
						//this instance value is free to use
						instancesVec.at(i)->actorID = actorID;
						return instancesVec.at(i);
					}
				}

				//no existing instance value is free
				instancesVec.push_back(std::make_shared<ActorUID>(actorID, newinstancenum));
			}

			auto count = instanceCount.find(actorID);
			if (count == instanceCount.end()) {
				instanceCount.insert(std::pair<int, int>(actorID, 0));
				instanceCount.at(actorID) += 1;
				return ActorUID(actorID, 0);
			}
			else {
				auto instNum = count->second;
				count->second++;
				return ActorUID(actorID, instNum);
			}
		}
		static int getInstanceCount(const int actorID) const {
			auto count = instanceCount.find(actorID);
			return count == instanceCount.end() ? 0 : count->second + 1;
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
		ActorUID(int actorID, int instancenum) : actorID(actorID), instancenum(instancenum) {}
		int compare(const ActorUID& rhs) const {
			if (actorID == other.actorID) {
				if (instancenum == other.instancenum) return 0;
				return instancenum > other.instancenum ? 1 : -1;
			}
			else {
				return actorID > other.actorID ? 1 : -1;
			}
		}
		int actorID;
		int instancenum;

		//key is actorID, value is the next inscancenum avalible
		static std::unordered_map<std::string, int> nametoidmap;
		//static std::unordered_map<int, int> instanceCount;

		//first row is actor id, second row is pointer to instanceNum
		static std::unordered_map<int, std::vector<std::shared_ptr<ActorUID>>> instanceMap;
	};
}
