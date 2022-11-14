#ifndef SCENEMANAGER_H
#define SCENEMANAGER_H

#include "Scene.h"
#include <string>
#include <map>

class SceneManager {

	public:
		~SceneManager();

		static SceneManager* getInstance();

		void addScene(Scene* scene);
		void setScene(const std::string tag);
		Scene* getScene() const;

	private:
		SceneManager();
		std::map<std::string, Scene*> scenes;
		std::string sceneTag;
		static SceneManager* instance;
};

#endif
