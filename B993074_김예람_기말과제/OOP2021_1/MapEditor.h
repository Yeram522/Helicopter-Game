#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"
#include "Button.h"
#include "ButtonScript.h"
#include "SceneManager.h"
#include "MapEditScript.h"
#include "Borland.h"
#include "Renderer.h"
#include "PanelScript.h"

using namespace std;

class MapEditor:public Scene
{
	GameObject* map;
	GameObject* blockCategory;
	GameObject* categPrev;//btn
	GameObject* categNext;//btn
	GameObject* loadMap;//btn
	GameObject* saveMap;//btn
	GameObject* prevPage;//btn
	GameObject* nextPage;//btn
	GameObject* currentBlock;

	MapEditScript* editorScript;

public:
	MapEditor(int scenenumber) : Scene(scenenumber) 
	{
		map = new GameObject("map", "panel", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		rootChildren.push_back(map);
		auto panelScript = map->getOrAddComponent<PanelScript>();
		panelScript->setTitle(" screen");
		editorScript = map->getOrAddComponent<MapEditScript>();

		blockCategory = new GameObject("category", "panel", nullptr, { 10,4 }, { 64,5 }, Position::zeros, nullptr);
		rootChildren.push_back(blockCategory);
		panelScript = blockCategory->getOrAddComponent<PanelScript>();
		panelScript->setTitle("category");

		auto blockShape = editorScript->getCurrentBlock();
		Position pos = { 5,2 };
		currentBlock = new GameObject("currentBlock", "block", &blockShape.shape, { 1,1 },
			blockCategory->getComponent<Transform>()->getPos() + pos, Position::zeros, nullptr);
		rootChildren.push_back(currentBlock);

		categPrev = new GameObject("prevBtn", "button", nullptr, { 3,3 }, { 59,6 }, Position::zeros, nullptr);
		rootChildren.push_back(categPrev);
		auto button = categPrev->getOrAddComponent<Button>();
		button->setText("<");
		auto script = categPrev->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {		
			editorScript->prevCategoryList();
			Borland::gotoxy(10, 40); printf("categPrev button\n");
		};

		categNext = new GameObject("prevBtn", "button", nullptr, { 3,3 }, { 76,6 }, Position::zeros, nullptr);
		rootChildren.push_back(categNext);
		button = categNext->getOrAddComponent<Button>();
		button->setText(">");
		script = categNext->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {
			editorScript->nextCategoryList();
			Borland::gotoxy(10, 40); printf("categNext button\n");
		};

		loadMap = new GameObject("clearBtn", "button", nullptr, { 6,2 }, { 64,16 }, Position::zeros, nullptr);
		rootChildren.push_back(loadMap);
		button = loadMap->getOrAddComponent<Button>();
		button->setText("Clear");
		script = loadMap->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {
			Renderer* mapRender = map->getComponent<Renderer>();
			int size = mapRender->getDimension().x * mapRender->getDimension().y;
			mapRender->setShape("");
		};

		loadMap = new GameObject("loadBtn", "button", nullptr, { 6,2 }, { 64,20}, Position::zeros, nullptr);
		rootChildren.push_back(loadMap);
		button = loadMap->getOrAddComponent<Button>();
		button->setText("Load");
		script = loadMap->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {
			Renderer* mapRender = map->getComponent<Renderer>();
			int size = mapRender->getDimension().x * mapRender->getDimension().y;
			mapRender->setShape(loadData(size));
		};

		saveMap = new GameObject("saveBtn", "button", nullptr, { 6,2 }, { 64,24 }, Position::zeros, nullptr);
		rootChildren.push_back(saveMap);
		button = saveMap->getOrAddComponent<Button>();
		button->setText("Save");
		script = saveMap->getOrAddComponent<ButtonScript>();
		script->onClick = [&]() {			
			saveData();
		};

	}

	void saveData()
	{
		Renderer* mapRender = map->getComponent<Renderer>();
		string dt = "";
		dt.append(mapRender->getShape());
		char from = '\xB0';
		char to = '1';
		replace(dt.begin(), dt.end(), from, to);
		from = '\xB2';
		to = '2';
		replace(dt.begin(), dt.end(), from, to);
		from = '\xDB';
		to = '3';
		replace(dt.begin(), dt.end(), from, to);
		from = ' ';
		to = '0';
		replace(dt.begin(), dt.end(), from, to);

		dt.resize(mapRender->getDimension().x * mapRender->getDimension().y);

		const char* result = dt.c_str();

		ofstream fout;
		
		fout.open(checkFileExist("mapdata", 0)+ ".txt");

		fout << result << endl;

		fout.close();

		Borland::gotoxy(10, 40); printf("saveBtn button:\n");
	}

	string checkFileExist(string filename, int index)
	{
		if ((access((filename + ".txt").c_str(), 0) == -1)) return filename;
		index++;
		string newfilename = filename + to_string(index);
		return checkFileExist(newfilename.c_str(), index);
	}

    char* loadData(int mapsize)
	{
		char* result = new char[mapsize];

		ifstream fin("mapdata.txt");//입력스트림을 관리하기 위한 객체를 선언 및 파일 열기

		if (fin.fail()) {
			Borland::gotoxy(10, 40);
			cout << "파일 오픈에 실패했습니다." << endl;
			return nullptr;
		}

		fin >> result;


		for (int i = 0; i < mapsize; i++)
		{
			if (result[i] == '0') result[i] = ' ';
			else if (result[i] == '1') result[i] = '\xB0';
			else if (result[i] == '2') result[i] = '\xB2';
			else if (result[i] == '3') result[i] = '\xDB';
		}

		//Borland::gotoxy(10, 40); printf("loadBtn button %d\n");
		return result;
		
	}

	void update() override {

		auto blockShape = editorScript->getCurrentBlock();
		currentBlock->getComponent<Renderer>()->setShape(&blockShape.shape);

		Scene::update();
	}
};

