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
	vector<AnimationClip> clips;//애니메이션 클립
	int currnetAnimation;//현재 진행중인 애니메이션 클립의 인덱스
protected:
	Renderer* renderer;
public:
	Animator(GameObject* gameObject) : Component(gameObject), currnetAnimation(0)
	{
		renderer = gameObject->getComponent<Renderer>();//랜더러 참조
	}

	void addClip(AnimationClip clip)//애니메이션 클립을 추가한다.
	{
		clips.push_back(clip);
	}

	void Play()
	{
		if (currnetAnimation == clips.capacity() - 1) currnetAnimation = 0;//마지막 클립이면 처음클립으로 돌아간다.
		else currnetAnimation++;


		renderer->setShape(clips[currnetAnimation].shape.c_str());
	}

	
};

