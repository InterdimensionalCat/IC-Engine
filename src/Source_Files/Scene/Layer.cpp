#include "include.h"
#include "Layer.h"

std::map<std::string, std::pair<int, LayerType>> layerMap;
int numLayers = 0;


void RegisterLayerBack(std::string layerName, LayerType type) {
	layerMap.emplace(layerName, std::pair(numLayers++, type));
}

void RegisterLayerFront(std::string layerName, LayerType type) {

}

void RegisterLayerBefore(std::string layerName, LayerType type, std::string beforeLayer) {

}

void RegisterLayerAfter(std::string layerName, LayerType type, std::string afterLayer) {

}