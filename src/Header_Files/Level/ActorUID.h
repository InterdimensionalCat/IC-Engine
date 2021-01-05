#pragma once
#include <unordered_map>

namespace ic {
	struct ActorUID {

		//creates a new ActorUID number and garuntees that the instancenum for each
		//actor is both unique and serialized
		static ActorUID makeNewInstance(const int actorID) {
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
		static std::unordered_map<int, int> instanceCount;
	};
}
