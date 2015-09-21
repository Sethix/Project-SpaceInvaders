#include "gameOptions.h"
#include "gameStructs.h"
#include "enemy.h"


Entity enemySetup(int id, int row, sf::Sprite es1, sf::Sprite es2, sf::Sprite es3, sf::Sprite projSprite)
{
	Entity tempEnemy;


	tempEnemy.ID = id + (row * 10);
	tempEnemy.type = Enemy;

	tempEnemy.pos.x = WINDOW_WIDTH - (ENEMY_STARTING_DISTANCE_X * id) - ((ENEMY_SPRITE_WIDTH * id) / 2);
	tempEnemy.pos.y = (ENEMY_STARTING_DISTANCE_Y * row) - ((ENEMY_SPRITE_HEIGHT * row) / 2);

	tempEnemy.size.x = PLAYER_SPRITE_WIDTH;
	tempEnemy.size.y = PLAYER_SPRITE_HEIGHT;

	//Check the enemy's row. Set it's difficulty depending on the row.
	if (tempEnemy.ID < 40)
	{
		tempEnemy.sprite = es3;
		tempEnemy.health = ENEMY_STRONG_MAX_HEALTH;
		tempEnemy.score = ENEMY_STRONG_SCORE;
	}
	if (tempEnemy.ID < 30)
	{
		tempEnemy.sprite = es2;
		tempEnemy.health = ENEMY_NORMAL_MAX_HEALTH;
		tempEnemy.score = ENEMY_NORMAL_SCORE;
	}
	if (tempEnemy.ID < 20)
	{
		tempEnemy.sprite = es1;
		tempEnemy.health = ENEMY_WEAK_MAX_HEALTH;
		tempEnemy.score = ENEMY_WEAK_SCORE;
	}

	tempEnemy.proj.sprite = projSprite;

	tempEnemy.projectileOut = false;
	tempEnemy.proj.isFriendly = true;
	tempEnemy.proj.speed = -PROJECTILE_SPEED;

	tempEnemy.proj.size.x = PROJECTILE_SPRITE_WIDTH;
	tempEnemy.proj.size.y = PROJECTILE_SPRITE_HEIGHT;

	tempEnemy.speed = ENEMY_SPEED_X;


	return tempEnemy;
}

void enemyMove(Entity entities[], bool &l)
{
	if (l)
	{
		if (entities[10 + ENEMIES_PER_ROW].pos.x > WINDOW_X_LIMIT)
		{
			for (int a = 0; a < 100; ++a)

				if (entities[a].type == Enemy)

					entities[a].pos.x -= entities[a].speed;
		}
		else
		{
			for (int a = 0; a < 100; ++a)

				if (entities[a].type == Enemy)

					entities[a].pos.y += ENEMY_SPEED_Y;

			l = !l;
		}
	}
	if (!l)
	{
		if (entities[11].pos.x < WINDOW_WIDTH - ENEMY_SPRITE_WIDTH - WINDOW_X_LIMIT)
		{
			for (int a = 0; a < 100; ++a)

				if (entities[a].type == Enemy)

					entities[a].pos.x += entities[a].speed;
		}
		else
		{
			for (int a = 0; a < 100; ++a)

				if (entities[a].type == Enemy)

					entities[a].pos.y += ENEMY_SPEED_Y;

			l = !l;
		}
	}
}

bool winCheck(Entity entities[])
{
	//Check to see if all enemies are dead.
	bool b = true;
	
	for (int a = 0; a < 100; ++a) if (entities[a].health > 0 && entities[a].type == Enemy) b = false;

	return b;
}