#pragma once
#include <memory>
#include "ActorType.h"

namespace boost {
	namespace uuids {
		struct uuid;
		class random_generator_pure;
		typedef random_generator_pure random_generator;
	}
}

namespace ic {


	class ic::ActorType;
	using UUID = boost::uuids::uuid;

	/**
	 * @brief                         The ActorUID class is the way that different parts of an
	 *                                actor reference eachother and know that they belong to the same object,
	 *                                since different parts are decoupled into different objects this is necessasary
	*/
	class ActorUID {

	public:

		/**
		 * @brief	                  Constructs a new ActorUID of the given type, creates a unique instance number
		 *                            automatically
		 * @param type                The type of the new actor
		*/
		ActorUID(const ActorType& type);

		/**
		 * @brief                     Constructs a new ActorUID and corrosponding ActorType with the given parameters
		 * @param typeName            The type name of the actortype
		 * @param variantName         The variant name of the actortype
		*/
		ActorUID(const std::string& typeName, const std::string& variantName);

		/**
		 * @brief                    The copy constructor's default handling of smart pointers is what we want here,
		 *                           this allows us to make copies of the ActorUID that point to the same instance num
		 * @param  
		*/
		ActorUID(const ActorUID&) = default;

		/**
		 * @brief                     Get the name of associated actor type
		 * @return                    The name
		*/
		const ActorType& getActorType() const;

		/**
		 * @brief                     Comparison operator(spaceship ftw)
		 * @return 
		*/
		auto operator<=>(const ActorUID&) const = default;

		/**
		 * @brief                     Converts the ActorUID into a printable
		 *                            string format
		 * @return 
		*/
		std::string toString() const;

	private:


		ActorType type;
		std::shared_ptr<UUID> instanceNum;
	};
}
