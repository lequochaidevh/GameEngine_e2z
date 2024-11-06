#pragma once
#include"Layer.h"

/*11.1.3_Create LayerStack*/
namespace VIEngine {
	using LayerList = std::vector<Layer*>;
	class VI_API LayerStack {
		/*11.1.8_Create METHOD help for iterator -> rend to rbegin into class have vector*/
		class VI_API ReversedIterator {
		public:
			ReversedIterator() = default;
			explicit ReversedIterator(LayerList::reverse_iterator iter) : mCurrentIter(iter) {
			}
			ReversedIterator& operator++() {
				++mCurrentIter;
				return *this;
			}
			ReversedIterator& operator--() {
				--mCurrentIter;
				return *this;
			}
			bool operator!=(const ReversedIterator& other) const {
				return mCurrentIter != other.mCurrentIter;
			}
			
			Layer* operator*() const { return *mCurrentIter; }
			Layer* operator->() const { return *mCurrentIter; }
		private:
			LayerList::reverse_iterator mCurrentIter;
		};
	public:
		LayerStack();
		~LayerStack();
		void push(Layer* layer);
		void pushOverlay(Layer* layer);
		void pop(Layer* layer);
		void popOverlay(Layer* layer);
		/*define class->vector: begin() end() rbegin() rend()*/
		LayerList::iterator begin() { return mLayers.begin(); }
		LayerList::iterator end() { return mLayers.end(); }
		ReversedIterator rbegin() { return ReversedIterator(mLayers.rbegin()); }
		ReversedIterator rend() { return ReversedIterator(mLayers.rend()); }
	private:
		LayerList mLayers;
		uint8_t mIndex;
	};
}