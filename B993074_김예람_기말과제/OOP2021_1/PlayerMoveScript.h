#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include "Transform.h"
#include "MoveMapScript.h"
#include "Collider.h"
#include <vector>


class PlayerMoveScript: public Behaviour
{	
	MoveMapScript* mapscript;

	float currentX;
	float currentY;
	float speed;

	Collider* collider;

	bool isCrushed;
public:
	PlayerMoveScript(GameObject* gameObject) : Behaviour(gameObject), currentX(0.0f),currentY(10.0f)
	{
		auto pos = transform->getPos();
		auto dim = renderer->getDimension();
		currentX = pos.x;
		currentY = pos.y;
		GameObject* map = gameObject->getParent();
		mapscript = map->getComponent<MoveMapScript>();

		collider = gameObject->getComponent<Collider>();
	}

	const bool getIsCrushed() { 
		return isCrushed; 
	}

	void update() override
	{
		if (collider->OnCollisionEnter(Position::right))
		{
			isCrushed = true;
			return;
		}

		if (input->getKey(VK_RIGHT)) {
			Borland::gotoxy(10, 41); printf("pressed: RIGHT Key");
			float nextX = currentX + 1.0f;

			if (collider->OnCollisionEnter(Position::right)) isCrushed =true;
			else currentX = nextX;
			
			return;
		}
		if (input->getKey(VK_LEFT)) {
			Borland::gotoxy(10, 41); printf("pressed: LEFT Key");
			if (currentX <= 0) return;
			float nextX = currentX - 1.0f;
			
			if (collider->OnCollisionEnter(Position::left)) isCrushed = true;
			else currentX = nextX;

			
			return;
		}
		if (input->getKey(VK_UP)) {
			Borland::gotoxy(10, 41); printf("pressed: UP Key");
			float nextY = currentY - 1.0f;
			
			if (collider->OnCollisionEnter(Position::up)) isCrushed = true;
			else currentY = nextY;
			
			return;
		}

		if (input->getKey(VK_DOWN)) {
			Borland::gotoxy(10, 41); printf("pressed: DOWN Key");
			float nextY = currentY + 1.0f;
			
			if (collider->OnCollisionEnter(Position::down)) isCrushed = true;
			else currentY = nextY;
			
			return;
		}

		if (currentX != 0)
			currentX -= mapscript->getSpeed();

		transform->setPos(currentX, currentY);	
		Borland::gotoxy(10, 41); printf("                      ");
	}
};

