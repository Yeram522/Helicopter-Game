#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "Scene.h"
using namespace std;

class Scene;

class SceneManager
{
	int scenecount;
	vector<Scene*> sceneinbuild;
	static SceneManager* Instance;
	Scene* CurrentScene;
	SceneManager():scenecount(0), CurrentScene(nullptr)
	{}
public:
	static SceneManager* GetInstance()
	{
		if (Instance == nullptr) {
			Instance = new SceneManager();
		}
		return Instance;
	}

	template <typename T>
	void createScene(T* newscene)
	{
		sceneinbuild.push_back((Scene*)newscene);
	}


	int getSceneCount() { return sceneinbuild.size(); };

	void enableScene(Scene* scene)
	{
		CurrentScene = scene;
		CurrentScene->setLoad(true);
		CurrentScene->start();
	}

	void enableSceneinIndex(int index)
	{
		disableScene(CurrentScene);
		for (int i = 0; i < getSceneCount(); i++)
			if (i == index)
			{
				CurrentScene = sceneinbuild[i];
				CurrentScene->setLoad(true);
				CurrentScene->start();
				return;
			}	
	}

	void disableScene(Scene* scene)
	{
		scene->setLoad(false);
		CurrentScene = nullptr;
	}

	void loadScene()
	{
		for (auto scene : sceneinbuild)
			if (scene->isLoaded()) scene->update();
	}



};

