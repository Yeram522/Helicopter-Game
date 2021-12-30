#ifndef _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_WARNINGS
#endif
#include<iostream>
#include "Position.h"
#include "Input.h"
#if 0
#include "Score.h"
#include "Block.h"
#include "Panel.h"
#endif
#include "SceneManager.h"
#include "MainScene.h"
#include "MapEditor.h"
#include "HelicopterGame.h"

using namespace std;


int main()
{
	
	auto screen = Screen::GetInstance();
	auto input = Input::GetInstance();
	auto sceneManager = SceneManager::GetInstance();
	auto main = new MainScene(sceneManager->getSceneCount());
	auto editor = new MapEditor(sceneManager->getSceneCount());
	auto game = new HelicopterGame(sceneManager->getSceneCount());
	
	sceneManager->createScene(main);
	sceneManager->createScene(editor);
	sceneManager->createScene(game);

	sceneManager->enableScene((Scene*)main);//실행할 씬
	while (true) 
	{
		screen->clear();

		input->readInputs();

		sceneManager->loadScene();

		screen->render();

		Sleep(100);
	}


	return 0;
}
