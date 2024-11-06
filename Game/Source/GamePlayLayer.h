#pragma once

#include "Core/Layer/Layer.h"
#include "Core/Logger/Logger.h"
#include "Core/Memory/MemoryChunkManager.h"

static size_t Count = 0;

struct Texture {
	Texture() {
		id = Count++;
	}

	uint32_t id;
	std::string filePath;
};

using namespace VIEngine;

class ResourceManager {

	class TextureManager : public MemoryChunkManager<Texture, 4> {
	public:
		TextureManager(const char* usage, const MemoryConfiguration& config) : MemoryChunkManager(usage, config) {

		}

		Texture* loadTexture() {
			return newObject();
		}

		void unload(void* memory) {
			freeObject(memory);
		}
	};

public:
	ResourceManager() : mTextureManager("TextureManager", {}) {

	}

	Texture* loadTexture() {
		return mTextureManager.loadTexture();
	}

	void unloadTexture(void* memory) {
		mTextureManager.unload(memory);
	}

	void unloadAllTextures() {
		mTextureManager.reset();
	}

	void shutdown() {
		mTextureManager.detectMemoryLeaks();
	}

private:
	TextureManager mTextureManager;
};

class GameplayLayer : public VIEngine::Layer {
public:
	GameplayLayer() : mResourceManager() {}
	~GameplayLayer() {}

	virtual void onAttach() override {
		LOG_TRACE("GameplayLayer is attached");

		std::vector<Texture*> textures;

		int count = 10;
		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.loadTexture());
		}

		mResourceManager.unloadTexture(textures[1]);
		mResourceManager.unloadTexture(textures[9]);

		mResourceManager.loadTexture();
		mResourceManager.loadTexture();

		mResourceManager.unloadAllTextures();
		textures.clear();

		for (int i = 0; i < count; i++) {
			textures.emplace_back(mResourceManager.loadTexture());
		}

		//mResourceManager.unloadAllTextures();
		mResourceManager.shutdown();

		CORE_LOG_WARN("Testing point");
	}

	virtual void onDetach() override {
		LOG_TRACE("GameplayLayer is detached");
	}

	virtual void onUpdate(VIEngine::Time time) {
		//LOG_TRACE("{0} deltaTime", time.GetDeltaTime());
	}

	virtual bool onKeyPressedEvent(const VIEngine::KeyPressedEvent& eventContext) override {
		//LOG_TRACE("Key {0} is pressed", (char)eventContext.GetKey());
		return false;
	}
private:
	ResourceManager mResourceManager;
};