#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

struct edgePosition {
	Direction dir; //����
	Position  pos; //�����ڸ� ��ġ
};

class RigidBody : public Component 
{
	vector<edgePosition> rightedges;
	vector<edgePosition> leftedges;
	vector<edgePosition> upedges;
	vector<edgePosition> downedges;

	Dimension dim;//gameObject�� �����ִ� sprite�� dim
	string sprite; //��������Ʈ ����

	Renderer* renderer;
public:
	RigidBody(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getComponent<Renderer>();//������ ����

		dim = renderer->getDimension();
		sprite = renderer->getShape();

		init();
	}

	void init() //��������Ʈ �����ڸ� ������ٵ� ���� ����.
	{	

		for (int i = 0; i < dim.y; i++) {
			int rightcount = 0;//�� ��� ��,�� 2���� push_back�ؾ���.
			int leftcount = 0;
			for (int j = 0; j < dim.x; j++) {
				if(i == 0 && sprite[j] != ' ')  upedges.push_back({ Direction::up,renderer->offset2Pos(j) });
				if(i == dim.y - 1 && sprite[i*dim.x+j] != ' ')  downedges.push_back({ Direction::down,renderer->offset2Pos(i * dim.x + j) });

				if (rightcount ==1 && leftcount ==1) continue;

				//left edge
				if (sprite[dim.x * i + j] != ' ' && leftcount == 0)
				{
					leftedges.push_back({ Direction::left,renderer->offset2Pos(dim.x * i + j) });
					leftcount++;
				}

				//right edge
				if (sprite[dim.x * i + dim.x - j - 1] != ' ' && rightcount == 0)
				{
					rightedges.push_back({ Direction::right,renderer->offset2Pos(dim.x * i + dim.x - j - 1) });
					rightcount++;
				}
			}

		}
		
	}


	//������ ��! worldpos�� �ƴ� localpos�� ����Ǿ�������!!
	vector<edgePosition> getEdges(Direction dir) //�ݶ��̴����� �� ������ٵ� ������ �����ͼ� �浹üũ�� �� ����.
	{
		if (dir == Direction::right) return rightedges;
		else if (dir == Direction::left) return leftedges;
		else if (dir == Direction::up) return upedges;
		else if (dir == Direction::down) return downedges;
	}


};

