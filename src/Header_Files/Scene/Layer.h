#include "StringableEnum.h"

_CREATE_STRINGABLE_ENUM(LayerType, Object, Tilemap, GUI);


struct LayerData {
	int layerID;
	LayerType type;


	bool operator==(const LayerData& rhs) const {
		return layerID == rhs.layerID;
	}
	bool operator!=(const LayerData& rhs) const;
	bool operator<(const LayerData& rhs) const;
	bool operator>(const LayerData& rhs) const;
	bool operator<=(const LayerData& rhs) const;
	bool operator>=(const LayerData& rhs) const;
};

void RegisterLayerBack(std::string layerName, LayerType type);
void RegisterLayerFront(std::string layerName, LayerType type);

void RegisterLayerBefore(std::string layerName, LayerType type, std::string beforeLayer);
void RegisterLayerAfter(std::string layerName, LayerType type, std::string afterLayer);
