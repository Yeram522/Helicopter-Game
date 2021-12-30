#pragma once
#include "Scene.h"
#include "Button.h"
#include "ButtonScript.h"
#include "SceneManager.h"
#include "Borland.h"

class MainScene : Scene
{
	GameObject* startBtn;
	GameObject* editBtn;

	SceneManager* sceneManager;
public:
	MainScene(int scenenumber) : Scene(scenenumber){
		sceneManager = SceneManager::GetInstance();
		startBtn = new GameObject("Start", "button", nullptr, { 10,3 }, { 35,25 }, Position::zeros, nullptr);
		rootChildren.push_back(startBtn);
		auto button = startBtn->getOrAddComponent<Button>();
		button->setText("Start");
		auto script = startBtn->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {sceneManager->enableSceneinIndex(2);
			Borland::gotoxy(10, 40); printf("buttonClcikc: Start\n");
		};
		

		editBtn = new GameObject("Edit", "button", nullptr, { 10,3 }, { 35,30 }, Position::zeros, nullptr);
		rootChildren.push_back(editBtn);
		button = editBtn->getOrAddComponent<Button>();
		button->setText("Edit");
		script = editBtn->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {sceneManager->enableSceneinIndex(1);
		Borland::gotoxy(10, 40); printf("buttonClcikc: Start\n");
		};
	}

};

