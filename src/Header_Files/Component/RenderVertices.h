#pragma once
#include "RenderComponent.h"
#include "SFML\Graphics.hpp"
#include <vector>
#include <string>

namespace ic {
	class RenderVertices : public RenderComponent {
	public:



		/*RenderVertices(const ActorData& dat) : RenderComponent(const ActorData& dat) {
			auto xcoords = variantData["RenderVertices"]["vertex"]["xcoords"].get<std::vector<float>>();
			auto ycoords = variantData["RenderVertices"]["vertex"]["ycoords"].get<std::vector<float>>();

			auto red = variantData["RenderVertices"]["color"]["color_r"].get<std::vector<int>>();
			auto blue = variantData["RenderVertices"]["color"]["color_g"].get<std::vector<int>>();
			auto green = variantData["RenderVertices"]["color"]["color_b"].get<std::vector<int>>();
			auto alpha = variantData["RenderVertices"]["color"]["color_a"].get<std::vector<int>>();

			auto texcoordsx = variantData["RenderVertices"]["texture"]["texcoordsx"].get<std::vector<float>>();
			auto texcoordsy = variantData["RenderVertices"]["texture"]["texcoordsy"].get<std::vector<float>>();

			for (size_t i = 0; i < xcoords.size(); i++) {
				auto x = xcoords.at(i);
				auto y = xcoords.at(i);

				auto r = red.at(i);
				auto g = green.at(i);
				auto b = blue.at(i);
				auto a = alpha.at(i);

				auto tx = texcoordsx.at(i);
				auto ty = texcoordsy.at(i);
				vertices.push_back(sf::Vector2f(x, y));
				vertices.at(vertices.size() - 1).color = sf::Color(r, g, b, a);
				vertices.at(vertices.size() - 1).texCoords = sf::Vector2f(tx, ty);
			}

			texturename = variantData["RenderVertices"]["texture"]["name"].get<std::string>();
			auto typestring = variantData["RenderVertices"]["type"].get<std::string>();
		}*/

		//need to error check this shit xd

		RenderVertices(const ActorData& dat) : RenderComponent(dat) {
			auto xcoords = dat.findKey<std::vector<float>>("xcoords");
			auto ycoords = dat.findKey<std::vector<float>>("ycoords");

			auto red = dat.findKey<std::vector<int>>("color_r");
			auto green = dat.findKey<std::vector<int>>("color_g");
			auto blue = dat.findKey<std::vector<int>>("color_b");
			auto alpha = dat.findKey<std::vector<int>>("color_a");

			auto texcoordsx = dat.findKey<std::vector<float>>("texcoordsx");
			auto texcoordsy = dat.findKey<std::vector<float>>("texcoordsy");

			for (size_t i = 0; i < xcoords.size(); i++) {
				auto x = xcoords.at(i);
				auto y = xcoords.at(i);

				auto r = red.at(i);
				auto g = green.at(i);
				auto b = blue.at(i);
				auto a = alpha.at(i);

				auto tx = texcoordsx.at(i);
				auto ty = texcoordsy.at(i);
				vertices.push_back(sf::Vector2f(x, y));
				vertices.at(vertices.size() - 1).color = sf::Color(r, g, b, a);
				vertices.at(vertices.size() - 1).texCoords = sf::Vector2f(tx, ty);
			}

			texturename = dat.findKey<std::string>("texname");
			auto typestring = dat.findKey<std::string>("primtype");

			if (typestring == "quads") {
				type = sf::PrimitiveType::Quads;
			}
			else {
				type = (sf::PrimitiveType)0;
			}
		}
		virtual ~RenderVertices() {}
		virtual void start(ic::gfx::Renderer& renderer);
		virtual void update(ic::gfx::Renderer& renderer);

		std::vector<sf::Vertex> vertices;
		sf::PrimitiveType type;
		std::string texturename;
	};
}