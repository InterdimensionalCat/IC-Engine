#include "StringableEnum.h"

_CREATE_STRINGABLE_ENUM(LayerType, Object, Tilemap, GUI);

namespace ic {
	class LayerData {
	private:

		std::string name;
		LayerType type;
		int layerID;
		static std::vector<LayerData> layers;


		LayerData(std::string name, LayerType type, int layerID) :
			name(name), type(type), layerID(layerID) {}

	public:

		bool operator==(const LayerData& rhs) const {
			return layerID == rhs.layerID;
		}

		bool operator!=(const LayerData& rhs) const {
			return layerID != rhs.layerID;
		}

		bool operator<(const LayerData& rhs) const {
			return layerID < rhs.layerID;
		}

		bool operator>(const LayerData& rhs) const {
			return layerID > rhs.layerID;
		}

		bool operator<=(const LayerData& rhs) const {
			return layerID <= rhs.layerID;
		}

		bool operator>=(const LayerData& rhs) const {
			return layerID >= rhs.layerID;
		}

		static LayerData GetFromString(std::string name) {
			auto it = std::find_if(layers.begin(), layers.end(),
				[name](const auto& elt) -> bool {
					return elt.name == name;
			});

			return *it;
		}

		static LayerData RegisterLayerBack(std::string layerName, LayerType type) {
			LayerData insertval(layerName, type, layers.back().layerID + 1);
			layers.insert(layers.end(), insertval);
			return layers.back();
		}
		static LayerData RegisterLayerFront(std::string layerName, LayerType type) {

			for (auto& layer : layers) {
				layer.layerID += 1;
			}

			LayerData insertval(layerName, type, 0);
			layers.insert(layers.begin(), insertval);

			return layers.front();
		}

		static LayerData RegisterLayerBefore(std::string layerName, LayerType type, LayerData beforeLayer) {
			auto it = std::find(layers.begin(), layers.end(), beforeLayer);
			for (int i = it->layerID; i < layers.size(); i++) {
				layers.at(i).layerID += 1;
			}

			LayerData insertval(layerName, type, it->layerID - 1);

			layers.insert(it, insertval);
			return layers.at(it->layerID - 1);
		}
		static LayerData RegisterLayerAfter(std::string layerName, LayerType type, LayerData afterLayer) {
			auto it = std::find(layers.begin(), layers.end(), afterLayer);
			for (int i = it->layerID + 1; i < layers.size(); i++) {
				layers.at(i).layerID += 1;
			}
			LayerData insertval(layerName, type, it->layerID + 1);
			layers.insert(it + 1, insertval);
			return layers.at(it->layerID + 1);
		}

	};
}
