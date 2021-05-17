#pragma once
#include <string>

namespace ic {

	/**
	 * @brief                         Identification class that denotes what
	 *                                kind of actor the object is, does not take into
	 *                                account which instance the object is
	*/
	class ActorType {
	public:

		ActorType();
		const std::string& getType() const;

	private:

		/**
		 * @brief                     The name of the actor type this identifier represents
		*/
		std::string actorTypeName;

		/**
		 * @brief                     ActorType also supports variants; classes
		*/
		std::string variantName;
	};
}