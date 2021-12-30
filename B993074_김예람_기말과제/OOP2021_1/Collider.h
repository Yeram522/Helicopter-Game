#pragma once
#include "Component.h"
#include "GameObject.h"
#include "Renderer.h"
#include "RigidBody.h"

class Collider: public Component
{
	Renderer* renderer; //parent
	RigidBody* rigidbody;
public:
	Collider(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getParent()->getComponent<Renderer>();//랜더러 참조
		rigidbody = gameObject->getComponent<RigidBody>(); //만약 게임오브젝트에 rigidbody가 없다면 nullptr일 것임/
	}


	bool OnCollisionEnter(Direction dir)//방향을 매개변수로 가져온다.
	{
		if (rigidbody == nullptr) return false; //component가 없을 경우 체크할 수 없음. return false;

		Position nextPos = gameObject->getTransform()->getPosition() + dir; //다음 게임오브젝트의 위치를 가져온다.
		vector<edgePosition> edges = rigidbody->getEdges(dir); //이동 방향에 해당되는 리지드바디 가장자리 위치정보를 벡터로 가져온다.

		//search
		for (int i = 0; i < edges.size(); i++)
		{
			int offset = renderer->pos2Offset(nextPos + edges[i].pos);
			Borland::gotoxy(10, 40); printf("Collide!! : %c\n", renderer->getShape()[offset]);
			if (renderer->getShape()[offset] != ' ') return true;
		}

		return false;
	}
};

