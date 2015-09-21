#pragma once
#include "SFML\Graphics.hpp"
#include "gameStructs.h"


Entity playerSetup(int id, char n[], sf::Sprite playerSprite, sf::Sprite projSprite);

void playerInput(Entity &p);

void playerMove(bool isLeft, Entity &p);

void playerShoot(Entity &p);

bool loseCheck(Entity entities[]);