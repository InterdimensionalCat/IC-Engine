#pragma once
#include <string>
#include <compare>

namespace ic {

	/**
	 * @brief                         Identification class that denotes what
	 *                                kind of actor the object is, does not take into
	 *                                account which instance the object is
	 *                                typeName indicates the base actor type, while
	 *                                variantName indicates the variant
	*/
	class ActorType {
	public:

		/**
		 * @brief                     Constructs an ActorType with the given type and variant names
		 * @param typeName            type name of the new ActorType
		 * @param variantName         variant name of the new ActorType
		*/
		ActorType(const std::string& typeName, const std::string& variantName);

		/**
		 * @brief                    Default implemented copy constructor, use this instead of
		 *                           the explicit constructor when possible to minimize using raw identifier
		 *                           information
		 * @param other 
		*/
		ActorType(const ActorType& other) = default;

		/**
		 * @brief                   Const ref getters, dont use unless you have to
		 * @return 
		*/
		const std::string& getType() const;
		const std::string& getVariant() const;

		/**
		 * @brief                  Checks if two ActorTypes have the same base type identifier,
		 *                         regardless of the variant type they are
		 * @param other 
		 * @return 
		*/
		bool isSameTypeAs(const ActorType& other) const;

		/**
		 * @brief                     Comparison operator(spaceshipftw), the ordering of ActorTypes is based on string comparisons,
		 *                            so it is somewhat arbitrary and equality is really the only useful operator unless
		 *                            you are dealing with a map
		 * @return 
		*/
		//auto operator<=>(const ActorType&) const = default;
		bool operator==(const ActorType& rhs) const;
		bool operator!=(const ActorType& rhs) const;
		bool operator<(const ActorType& rhs) const;
		bool operator>(const ActorType& rhs) const;
		bool operator<=(const ActorType& rhs) const;
		bool operator>=(const ActorType& rhs) const;

		/**
		 * @brief                     Converts the ActorType to a readable string value
		 * @return 
		*/
		std::string toString() const;

	private:

		/**
		 * @brief                     The name of the actor type this identifier represents
		*/
		std::string typeName;

		/**
		 * @brief                     ActorType also supports variants, storing the variant name here
		*/
		std::string variantName;
	};
}