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
		renderer = gameObject->getParent()->getComponent<Renderer>();//������ ����
		rigidbody = gameObject->getComponent<RigidBody>(); //���� ���ӿ�����Ʈ�� rigidbody�� ���ٸ� nullptr�� ����/
	}


	bool OnCollisionEnter(Direction dir)//������ �Ű������� �����´�.
	{
		if (rigidbody == nullptr) return false; //component�� ���� ��� üũ�� �� ����. return false;

		Position nextPos = gameObject->getTransform()->getPosition() + dir; //���� ���ӿ�����Ʈ�� ��ġ�� �����´�.
		vector<edgePosition> edges = rigidbody->getEdges(dir); //�̵� ���⿡ �ش�Ǵ� ������ٵ� �����ڸ� ��ġ������ ���ͷ� �����´�.

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

