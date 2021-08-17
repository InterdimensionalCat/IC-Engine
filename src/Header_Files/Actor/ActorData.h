#pragma once

namespace ic {


	/**
	 * @brief class that loads and manages combined actor json data
	 * @details there are potentially 3 sources of actor data;
	 * the map data, the variant json, and the actor json, data is 
	 * prioritized in that order; so a transform specified in the map data
	 * will overrwrite any transform specified in the variant or actor json files
	 * 
	*/
	class ActorData {
	public:

		/**
		 * @brief construct an ActorData json from an actor and variant name
		 * @param actorname the actor json name
		 * @param variantname the variant json name
		*/
		ActorData(const std::string& actorname, const std::string& variantname);

		/**
		 * @brief construct an Actordata json from an actor, variant name, and map data
		 * @param actorname the actor json name
		 * @param variantname the variant json name
		 * @param mapdata pointer to the map data associated with this
		*/
		ActorData(const std::string& actorname, const std::string& variantname, const tmx::Object& mapdata);

		/**
		 * @brief get a read only reference to the underlying json data
		 * @return the underlying json data
		*/
		const std::shared_ptr<json> get() const;

	private:

		/**
		 * @brief the combined json data of the actor
		*/
		std::shared_ptr<json> data;
	};
}