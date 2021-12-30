#pragma once
#include "GameObject.h"
#include "Component.h"
#include "Renderer.h"

struct AnimationClip {
	string		shape;
	Dimension	dim;
};

class Animator : public Component
{
	vector<AnimationClip> clips;//�ִϸ��̼� Ŭ��
	int currnetAnimation;//���� �������� �ִϸ��̼� Ŭ���� �ε���
protected:
	Renderer* renderer;
public:
	Animator(GameObject* gameObject) : Component(gameObject), currnetAnimation(0)
	{
		renderer = gameObject->getComponent<Renderer>();//������ ����
	}

	void addClip(AnimationClip clip)//�ִϸ��̼� Ŭ���� �߰��Ѵ�.
	{
		clips.push_back(clip);
	}

	void Play()
	{
		if (currnetAnimation == clips.capacity() - 1) currnetAnimation = 0;//������ Ŭ���̸� ó��Ŭ������ ���ư���.
		else currnetAnimation++;


		renderer->setShape(clips[currnetAnimation].shape.c_str());
	}

	
};

