#pragma once
#include "GameObject.h"
#include "Behaviour.h"
#include <functional>

//�̵��ϴ¸��� ��ũ��Ʈ
class MoveMapScript :
    public Behaviour
{
	float		speed;//���̵� �ӵ�.: ¦��������!!!
	float	speedFlag;//���̵� �ӵ�.
public:
	function<void(void)> movemapLeft;

	MoveMapScript(GameObject* gameObject) :Behaviour(gameObject), speed(0.5f),speedFlag(0.0f)
    {
		
    }

	void update() override
	{
		if (speedFlag - (int)speedFlag == 0)
		{
			movemapLeft();
		}
		
		speedFlag += speed;
	}

	float getSpeed() { return speed; }
};

