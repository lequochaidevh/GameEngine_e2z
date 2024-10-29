#include"LayerStack.h"

/*11.1.4_Define func in LayerStack*/

namespace VIEngine {
	LayerStack::LayerStack() : mIndex(0), mLayers() {
	}
	LayerStack::~LayerStack() {
	}
	void LayerStack::push(Layer* layer) {
		mLayers.emplace(mLayers.begin() + mIndex, layer);
		mIndex++;
	}
	void LayerStack::pushOverlay(Layer* layer) {
		mLayers.emplace_back(layer);
	}
	void LayerStack::pop(Layer* layer) {
		auto iter = std::find(mLayers.begin(), mLayers.end(), layer);
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
			mIndex--;
		}
	}
	void LayerStack::popOverlay(Layer* layer) {
		auto iter = std::find(mLayers.begin() + mIndex, mLayers.end(), layer);//fix
		if (iter != mLayers.end()) {
			mLayers.erase(iter);
		}
	}
}