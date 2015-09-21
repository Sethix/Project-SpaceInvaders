#pragma once
#include "SFML\Graphics.hpp"

enum EntityClass : int {
	Player = 0,
	Enemy = 1,
	Box = 2
};

struct Vector2
{
	float x;
	float y;
};

struct Projectile
{
	Vector2 pos;
	Vector2 size;
	float speed;
	bool isFriendly;
	sf::Sprite sprite;
};

struct Entity
{
	int ID;
	EntityClass type;
	Vector2 pos;
	Vector2 size;
	float speed;
	int health;
	int score;
	char name[4];
	bool projectileOut;
	Projectile proj;
	sf::Sprite sprite;
};