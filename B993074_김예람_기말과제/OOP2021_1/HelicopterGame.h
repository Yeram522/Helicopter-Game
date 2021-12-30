#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <string>
#include "Scene.h"
#include "PanelScript.h"
#include "MapEditor.h"
#include "MoveMapScript.h"
#include "PlayerMoveScript.h"
#include "Animator.h"
#include "RigidBody.h"
#include "Collider.h"
#include "Button.h"
#include "boardScript.h"

using namespace std;



class HelicopterGame: public Scene
{
	GameObject* map;
	GameObject* player;//헬리콥터
	GameObject* board; //Game State UI

	string sprite = "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0";
	MoveMapScript* mapScript;
	Animator* animator;

	Renderer* mapRender;
	string mergedMap;
	int mapmovenm;
public:
	HelicopterGame(int scenenumber):Scene(scenenumber), player(nullptr), mapmovenm(0)
	{
		map = new GameObject("map", "panel", nullptr, { 50,20 }, { 5,5 }, Position::zeros, nullptr);
		rootChildren.push_back(map);

		mapScript = map->getOrAddComponent<MoveMapScript>();

		mapRender = map->getComponent<Renderer>();	
		int size = mapRender->getDimension().x * mapRender->getDimension().y;
		mapRender->setShape(loadData(size));
		mergedMap = loadMergeData("mapdata", mapRender->getShape(), size, 1);
		mapScript->movemapLeft = [&]() {/*moveMap(mergedMap.c_str(), mapmovenm);*/moveMap(); };

		player = new GameObject{ "helicopter", "player", sprite.c_str(),
			{5,4}, {0,10},  Position::zeros, map };
		player->addComponent<RigidBody>();
		player->addComponent<Collider>();
		animator = player->getOrAddComponent<Animator>();//애니메이터 추가 및 가져오기
		animator->addClip({ "\xCD\xCD\xCB\xCD\xCD\xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });
		animator->addClip({ "  \xCB  \xF0\xF0\xF0  \xF0\xF0\xF0\xF0  \xF0\xF0", {5,4} });//클립추가.
		player->addComponent<PlayerMoveScript>();

		board = new GameObject("board", "ui", nullptr, { 10,3 }, { 25,27}, Position::zeros, nullptr);
		auto button = board->getOrAddComponent<Button>();
		button->setText("Time: 0s");
		board->addComponent<boardScript>();
		rootChildren.push_back(board);
	
	};

	int checkFileCount(string filename, int index)
	{
		if ((access((filename + ".txt").c_str(), 0) == -1)) return index;
		index++;
		string newfilename = filename + to_string(index);
		return checkFileCount(newfilename.c_str(), index);
	}

	const char* loadMergeData(string filename, const char* mapdata, int mapsize,int fileindex) 
	{
		//새로운 파일 불러오기
		char* newfile = new char[mapsize];
		string newfilename = filename + to_string(fileindex);
		if ((access((newfilename + ".txt").c_str(), 0) == -1)) return mapdata; //인덱스를 증가한 파일이 없으면 반환.

		ifstream fin(newfilename + ".txt");//입력스트림을 관리하기 위한 객체를 선언 및 파일 열기

		if (fin.fail()) {
			Borland::gotoxy(10, 40);
			cout << "파일 오픈에 실패했습니다." << endl;
			return nullptr;
		}

		fin >> newfile; 
		newfile = convert2Shape(newfile, mapsize);


		string newfiles = newfile;

		string mergedata = "";
		mergedata.append(mapdata);//기존 맵 append

		
		for (int i = 0; i < (mapRender->getDimension().y); i++)
		{
			int index = i * mapRender->getDimension().x  ;
			string temp = newfiles.substr(index, mapRender->getDimension().x);//뒤로 push할 행
			mergedata.insert(index * fileindex  + mapRender->getDimension().x - 1,temp);
		}

		char* result = (char*)mergedata.c_str();

		return loadMergeData(filename, result, mapsize, ++fileindex);
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


		return convert2Shape(result, mapsize);
	}

	char* convert2Shape(char* intDatas, int mapsize)
	{

		//한꺼번에 처리.
		for (int i = 0; i < mapsize; i++)
		{
			if (intDatas[i] == '0') intDatas[i] = ' ';
			else if (intDatas[i] == '1') intDatas[i] = '\xB0';
			else if (intDatas[i] == '2') intDatas[i] = '\xB2';
			else if (intDatas[i] == '3') intDatas[i] = '\xDB';
		}


		return intDatas;
	}

	void moveMap(const char* multipleMap,int nm)
	{
		if (nm == checkFileCount("mapdata", 0) * mapRender->getDimension().x) nm = 0;
		string mapdata = "";//현재 맵의 이미지 가져오기.
		mapdata.append(multipleMap);

		string screendata = "";
		screendata.append(mapRender->getShape());

		for (int i = 0; i < mapRender->getDimension().y; i++)
		{
			int index = (i+1) * mapRender->getDimension().x - 1+ nm;
			string temp;//뒤로 push할 char
			temp.push_back(mapdata[index]);
			screendata.erase(index, 1);
			screendata.insert(index + mapRender->getDimension().x - 1, temp);
		}

		char* result = (char*)screendata.c_str();
		mapRender->setShape(result);

		nm++;
	}

    void moveMap()//좌측으로 맵을 이동한다.
	{

		string mapdata = "";//현재 맵의 이미지 가져오기.
		mapdata.append(mapRender->getShape());

		for (int i = 0; i < mapRender->getDimension().y; i++)
		{
			int index = i * mapRender->getDimension().x;
			string temp;//뒤로 push할 char
			temp.push_back(mapdata[index]);
			mapdata.erase(index, 1);
			mapdata.insert(index + mapRender->getDimension().x- 1, temp);
		}

		char* result = (char* )mapdata.c_str();
		mapRender->setShape(result);
	}

	bool isGameOver()
	{
		if (player->getComponent<PlayerMoveScript>()->getIsCrushed())
		{
			board->getComponent<boardScript>()->stopTimer();
			board->getComponent<Button>()->setText("GameOver");		
			return true;
		}
		return false;
	}

	void start() override
	{
		board->getComponent<boardScript>()->startTimer();
	}

	void update() override {
		if (isGameOver())
		{
			map->setFreeze();
			player->setFreeze();
		}
		animator->Play();
		
		Scene::update();
	}
};

