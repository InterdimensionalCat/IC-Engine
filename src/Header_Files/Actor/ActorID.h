#pragma once

namespace ic {

	class ActorEntry;

	/**
	 * @brief classification level identification information for actors
	 * @details contains the variant name and actor type name of the actor,
	 * can also represent an invalid actor when an ActorEntry is empty or expired
	 * exclusively managed by the ActorEntry class
	*/
	class ActorID
	{
	public:
		ActorID(const ActorID&) = default;
		ActorID& operator=(const ActorID&) = default;

		bool isIdValid() const;

		std::string getActorName() const { return typeName; }
		std::string getVariantName() const { return variantName; }

		bool operator==(const ActorID& rhs) const;
		bool operator!=(const ActorID& rhs) const;
		bool operator<(const ActorID& rhs) const;
		bool operator>(const ActorID& rhs) const;
		bool operator<=(const ActorID& rhs) const;
		bool operator>=(const ActorID& rhs) const;
	private:
		friend class ActorEntry;

		int compare(const ActorID& other) const;
		ActorID(const std::string& typeName, const std::string& variantName);
		ActorID();
		std::string typeName;
		std::string variantName;
	};
}

