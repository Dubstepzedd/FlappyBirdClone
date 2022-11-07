#include "SceneManager.h"

SceneManager::SceneManager() {
	//Do nothing.
}

SceneManager& SceneManager::getInstance() {
	
	static SceneManager instance;

	return instance;
}

void SceneManager::setScene(const std::string tag) {
	this->tag = tag;
}

void SceneManager::addScene(Scene* scene) {
	scenes[scene->getTag()] = scene;
}

Scene* SceneManager::getScene() const {
	auto it = scenes.find(tag);

	//If found, return Scene*.
	if (it != scenes.end()) {
		return it->second;
	}

	//else return nullptr
	return nullptr;
}