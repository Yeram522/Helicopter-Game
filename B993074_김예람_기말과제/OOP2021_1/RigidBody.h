#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

struct edgePosition {
	Direction dir; //방향
	Position  pos; //가장자리 위치
};

class RigidBody : public Component 
{
	vector<edgePosition> rightedges;
	vector<edgePosition> leftedges;
	vector<edgePosition> upedges;
	vector<edgePosition> downedges;

	Dimension dim;//gameObject가 갖고있는 sprite의 dim
	string sprite; //스프라이트 정보

	Renderer* renderer;
public:
	RigidBody(GameObject* gameObject) : Component(gameObject)
	{
		renderer = gameObject->getComponent<Renderer>();//랜더러 참조

		dim = renderer->getDimension();
		sprite = renderer->getShape();

		init();
	}

	void init() //스프라이트 가장자리 리지드바디 라인 생성.
	{	

		for (int i = 0; i < dim.y; i++) {
			int rightcount = 0;//한 행당 왼,오 2개만 push_back해야함.
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


	//주의할 점! worldpos가 아닌 localpos로 저장되어져있음!!
	vector<edgePosition> getEdges(Direction dir) //콜라이더에서 이 리지드바디 정보를 가져와서 충돌체크를 할 예정.
	{
		if (dir == Direction::right) return rightedges;
		else if (dir == Direction::left) return leftedges;
		else if (dir == Direction::up) return upedges;
		else if (dir == Direction::down) return downedges;
	}


};

