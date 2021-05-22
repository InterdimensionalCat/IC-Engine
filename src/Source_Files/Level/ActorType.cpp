#include "ActorType.h"
#include <string>

using namespace ic;

ActorType::ActorType(const std::string& typeName, const std::string& variantName) : typeName(typeName), variantName(variantName) {

}

const std::string& ActorType::getType() const {
	return typeName;
}
const std::string& ActorType::getVariant() const {
	return variantName;
}
bool ActorType::isSameTypeAs(const ActorType& other) const {
	return typeName == other.typeName;
}
std::string ActorType::toString() const {
	return std::string("ActorType{typeName=" + typeName + ", variantName=" + variantName + "}");
}