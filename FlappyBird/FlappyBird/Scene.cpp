#include "Scene.h"

Scene::Scene(const std::string tag) : sceneTag(tag) {

}

Scene::~Scene() {

}

void Scene::init() {

}

std::string Scene::getTag() const {
	return sceneTag;
}
