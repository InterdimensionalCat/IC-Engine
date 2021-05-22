#include"ActorUID.h"
#include <boost/uuid/uuid.hpp>            // uuid class
#include <boost/uuid/uuid_generators.hpp> // generators
#include <boost/uuid/uuid_io.hpp>         // streaming operators etc.
#include "ActorType.h"
#include "LoggerProvider.h"
#include <string>
#include <sstream>

using UUID = boost::uuids::uuid;

static std::unique_ptr<boost::uuids::random_generator> internalGenerator = std::make_unique<boost::uuids::random_generator>();

using namespace ic;

ActorUID::ActorUID(const ActorType& type) : type(type) {
	instanceNum = std::make_shared<UUID>((*internalGenerator)());
}
ActorUID::ActorUID(const std::string& typeName, const std::string& variantName) : type(typeName, variantName) {}
const ActorType& ActorUID::getActorType() const {
	return type;
}
//auto ActorUID::operator<=>(const ActorUID& other) const {
//	if (type == other.type) {
//		if (*instanceNum == *other.instanceNum) return 0;
//		return *instanceNum > *other.instanceNum ? 1 : -1;
//	}
//	else {
//		return type > other.type ? 1 : -1;
//	}
//}
std::string ActorUID::toString() const {
	std::stringstream uuidOutput;
	uuidOutput << *instanceNum;
	return std::string("ActorUID{type=" + type.toString() + ", UUID=" + uuidOutput.str());
}