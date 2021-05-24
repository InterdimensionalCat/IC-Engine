#include"ActorUID.h"
#include "ActorType.h"
#include "LoggerProvider.h"
#include <sstream>

using namespace ic;

ActorUID::ActorUID(const ActorType& type) : type(std::make_shared<ActorType>(type.getType(), type.getVariant())) {}

ActorUID::ActorUID(const std::string& typeName, const std::string& variantName) : type(std::make_shared<ActorType>(typeName, variantName)) {}

ActorType ActorUID::getActorType() const {
	return *type;
}

std::string ActorUID::toString() const {

	const void* address = static_cast<const void*>(type.get());
	std::stringstream ss;
	ss << address;
	std::string addressStr = ss.str();

	return std::string("ActorUID{type=" + type->toString() + ", instance=" + addressStr + "}");
}

bool ActorUID::operator==(const ActorUID& rhs) const {
	return *type == *rhs.type && type.get() == rhs.type.get();
}
bool ActorUID::operator!=(const ActorUID& rhs) const {
	return !(*this == rhs);
}
bool ActorUID::operator<(const ActorUID& rhs) const {
	return (*type < *rhs.type) ? true : (type.get() < rhs.type.get());
}
bool ActorUID::operator>(const ActorUID& rhs) const {
	return (*type > *rhs.type) ? true : (type.get() > rhs.type.get());
}
bool ActorUID::operator<=(const ActorUID& rhs) const {
	return (*this == rhs) || (*this < rhs);
}
bool ActorUID::operator>=(const ActorUID& rhs) const {
	return (*this == rhs) || (*this > rhs);
}