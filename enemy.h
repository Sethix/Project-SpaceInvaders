#pragma once
#include "gameStructs.h"


Entity enemySetup(int id, int row, sf::Sprite es1, sf::Sprite es2, sf::Sprite es3, sf::Sprite projSprite);

void enemyMove(Entity entities[], bool &l);

bool winCheck(Entity entities[]);