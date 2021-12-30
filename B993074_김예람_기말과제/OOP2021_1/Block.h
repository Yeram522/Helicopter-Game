#pragma once

#include "Map.h"

struct BlockShape {
	string		shape;
	Dimension	dim;
};

class Block :
    public GameObject
{
	bool		interactable; /* indicator whether it can respond with user input events.*/
	float		currentX;
	float		currentY;
	float		speed;
	Map*		map;
	char*		shapeBuffer;

	void rotateShape() {
		auto originalShape = getShape();
		auto sz = getDimension();
		int w = sz.x; int h = sz.y;
		for (int y = 0; y < h; y++)
			for (int x = 0; x < w; x++)
				shapeBuffer[(w - 1 - x) * h + y] = originalShape[y * w + x];
		setShape(shapeBuffer);
		sz.x = h; sz.y = w;
		setDimension(sz);
	}

	

public:
	Block(const string& shape, const Position& pos, 
		  const Position& dim, GameObject* parent = nullptr, bool interactable = true)
		: GameObject(shape.c_str(), pos, dim, parent), 
		interactable(interactable), map(nullptr),
		currentX(pos.x), currentY(pos.y), speed(0.1f), shapeBuffer{ new char[(size_t)dim.x * dim.y] }
	{}

	~Block() {
		if (shapeBuffer != nullptr) delete[] shapeBuffer;
		shapeBuffer = nullptr;
	}

	void update() override
	{
		if (!interactable || !map) return;

		auto shape = getShape();
		auto pos = getPos();
		auto width = dim.x; 
		auto height = dim.y;

		if (map->isGrounded(shape, pos, width, height)) {
			map->place(shape, pos, width, height);
			for (int i = height - 1; i >= 0; --i) {
				int nCombos = 0;
				while (map->evaluateLine(pos.y + i)) {
					nCombos++;
				}
			}

			setActive(false);
			return;
		}

		if (input->getKey(VK_RIGHT)) {
			float nextX = currentX + 1.0f;
			if (map && map->isValidRange({ (int)nextX, (int)currentY }, dim) )
				currentX = nextX;
			return;
		}
		if (input->getKey(VK_LEFT)) {
			float nextX = currentX - 1.0f;
			if (map && map->isValidRange({ (int)nextX, (int)currentY }, dim))
				currentX = nextX;
			return;
		}
		if (input->getKey(VK_UP)) {
			rotateShape();
		}
		if (input->getKey(VK_DOWN)) {
			speed *= 2;
		}
		if (input->getKey(VK_SPACE)) {
			if (map) {
				pos.y = currentY;
				while (!map->isGrounded(shape, pos, width, height)) {
					float nextY = currentY + 1;
					if (map->isValidRange({ (int)currentX, (int)nextY }, dim)) {
						pos.y = nextY;
						currentY = nextY;
					}
				}

				return;
			}
		}
		float nextY = currentY + speed;
		if (map && map->isValidRange({ (int)currentX, (int)nextY }, dim)) {
			currentY = nextY;
		}
		Borland::gotoxy(0, 36);
		printf("dim(%d, %d) (%f, %f)\n", dim.x, dim.y, currentX, currentY);
	}

	void draw() override
	{	
		if (interactable == true) {
			setPos(currentX, currentY);
		}
		auto shape = getShape();
		auto pos = getPos();
		auto width = dim.x;
		auto height = dim.y;
		screen->draw(local2Screen(), getShape(), dim);
	}

	void setMap(Map* map) {
		this->map = map;
	}

	void reset() {
		currentX = 4.0f; currentY = 0.0f;
		speed = 0.1f;
		setPos(currentX, currentY);
	}

	void setInteractable(bool interactable = true) { this->interactable = interactable; }

	static BlockShape chooseShape() {
		static vector<BlockShape> candidates{
			{ "\xDB\xDB \xDB \xDB", {2, 3}	},
			{ "\xDB\xDB\xDB\xDB",	{2, 2}	},
			{ "\xDB\xDB\xDB\xDB",	{4, 1}	},
			{ "\xDB\xDB\xDB \xDB ", {2, 3}	},
			{ " \xDB\xDB\xDB\xDB ", {2, 3}	},
			{ " \xDB\xDB\xDB \xDB", {2, 3}	},
			{ "\xDB \xDB\xDB \xDB", {2, 3}  }
		};
		return candidates[rand() % candidates.size()];
	}
};

