#include "SceneManager.h"
SceneManager* SceneManager::instance = 0;

SceneManager::SceneManager() {
	//Do nothing.
}

SceneManager::~SceneManager() {
	delete instance;
}

SceneManager* SceneManager::getInstance() {
	
	if (instance == nullptr) {
		instance = new SceneManager();
	}

	return instance;
}

void SceneManager::setScene(const std::string tag) {
	sceneTag = tag;
}

void SceneManager::addScene(Scene* scene) {
	scenes[scene->getTag()] = scene;
}

Scene* SceneManager::getScene() const {

	auto it = scenes.find(sceneTag);

	//If found, return Scene*.
	if (it != scenes.end()) {
		return it->second;
	}

	//else return nullptr
	return nullptr;
}