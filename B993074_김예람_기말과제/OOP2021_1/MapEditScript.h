#pragma once
#include "GameObject.h"
#include "Transform.h"
#include "Behaviour.h"
#include "Position.h"
#include "Renderer.h"

typedef int strong;

struct BlockShapes {
	char	shape;
	strong  strong;
};

class MapEditScript :
    public Behaviour
{
	vector<BlockShapes> candidates{
		{ '\xDB',3},
		{ '\xB2',2 },
		{ '\xB0',1 }
	};

	BlockShapes currentBlockShape;
	int indexNum;
	vector<BlockShapes*> mapdesign;

public:
    MapEditScript(GameObject* gameObject) : Behaviour(gameObject),indexNum(0), currentBlockShape(candidates[0])
    {

    }

	void update() override
	{
		if (!input->getMouseButtonDown(0)) return;
		auto pos = input->getMousePosition();
		if(transform->getPosition().x<pos.x && pos.x<transform->getPosition().x+renderer->getDimension().x
			&& transform->getPosition().y < pos.y && pos.y < transform->getPosition().y + renderer->getDimension().y)
		{
			
			if (renderer->getShape(transform->world2Local(pos)) != ' ')//비어있는칸이 아니면
			{
				renderer->setShape(' ', transform->world2Local(pos));
				return;
			}
			const char shape = currentBlockShape.shape;
			renderer->setShape(shape, transform->world2Local(pos));
			Borland::gotoxy(10, 40); printf("buttonClcikc:%d\n"); cout << pos;
		}
	}

	void prevCategoryList()
	{
		indexNum--;
		if (indexNum == -1 ? true : false) indexNum = 2;
		currentBlockShape.shape = candidates[indexNum].shape;
		Borland::gotoxy(1, 40); printf("index:%d\n", indexNum);

	}
	void nextCategoryList()
	{
		indexNum++;
		if (indexNum == 3 ? true : false) indexNum = 0;
		currentBlockShape.shape = candidates[indexNum].shape;
		Borland::gotoxy(1, 40); printf("index:%d\n", indexNum);
	}

	BlockShapes getCurrentBlock() { return currentBlockShape; }
};

