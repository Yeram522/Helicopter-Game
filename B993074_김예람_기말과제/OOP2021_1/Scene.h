#pragma warning(disable: 4996)
#pragma once
#include <iostream>
#include <io.h>
#include <string>
#include "Position.h"
#include "GameObject.h"
#include "RendererEnabler.h"
using namespace std;


class Scene
{
	int buildindex;
	bool isload;
protected:
	vector<GameObject*> rootChildren;
public:
	Scene(int buildindex): isload(false), buildindex(buildindex)
	{}

	bool isLoaded() { return this->isload; };
	void setLoad(bool trigger = true) { this->isload = trigger; }
	int getIndex() { return this->buildindex; }

	virtual void start() {}
	virtual void update()
	{
		for (auto child : rootChildren) child->internalUpdate();
		rootChildren.erase(
			std::remove_if(rootChildren.begin(), rootChildren.end(),
				[](auto child) { return child->isActive() == false; }),
			rootChildren.end());
		for (auto child : rootChildren) child->internalRemove();
		for (auto child : rootChildren) child->internalRender();
	
	}
};

