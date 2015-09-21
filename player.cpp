#include "gameOptions.h"
#include "gameStructs.h"
#include "player.h"

Entity playerSetup(int id, char n[], sf::Sprite playerSprite, sf::Sprite projSprite)
{
	Entity tempPlayer;


	tempPlayer.ID = id;
	tempPlayer.type = Player;
	
	tempPlayer.pos.x = PLAYER_DEFAULT_X - (PLAYER_SPRITE_WIDTH / 2);
	tempPlayer.pos.y = PLAYER_DEFAULT_Y - (PLAYER_SPRITE_HEIGHT / 2);

	tempPlayer.size.x = PLAYER_SPRITE_WIDTH;
	tempPlayer.size.y = PLAYER_SPRITE_HEIGHT;

	tempPlayer.sprite = playerSprite;
	tempPlayer.proj.sprite = projSprite;

	tempPlayer.projectileOut = false;
	tempPlayer.proj.isFriendly = true;
	tempPlayer.proj.speed = -PROJECTILE_SPEED;

	tempPlayer.proj.size.x = PROJECTILE_SPRITE_WIDTH;
	tempPlayer.proj.size.y = PROJECTILE_SPRITE_HEIGHT;
	
	tempPlayer.health = PLAYER_MAX_HEALTH;
	tempPlayer.score = 0;

	strcpy_s(tempPlayer.name,n);

	tempPlayer.speed = PLAYER_SPEED;


	return tempPlayer;
}

void playerInput(Entity &p)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && p.ID == 1) playerMove(1, p);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && p.ID == 1) playerMove(0, p);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && p.ID == 1) playerShoot(p);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::J) && p.ID == 2) playerMove(1, p);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::L) && p.ID == 2) playerMove(0, p);
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::I) && p.ID == 2) playerShoot(p);
}

void playerMove(bool isLeft, Entity &p)
{
	if (isLeft) p.pos.x -= p.speed;
	else p.pos.x += p.speed;

	//Limit player movement so we stay on screen.
	if (p.pos.x > WINDOW_WIDTH - WINDOW_X_LIMIT - p.size.x) p.pos.x = WINDOW_WIDTH - WINDOW_X_LIMIT - p.size.x;
	if (p.pos.x < WINDOW_X_LIMIT) p.pos.x = WINDOW_X_LIMIT;
}

void playerShoot(Entity &p)
{
	if (p.projectileOut == false)
	{
		p.proj.pos = p.pos;
		p.proj.pos.x += (p.size.x / 2) - (p.proj.size.x / 2);
		p.proj.pos.y -= (p.size.y / 2) + (p.proj.size.y / 2);
		p.projectileOut = true;
	}

	if (p.proj.pos.x < 0 || p.proj.pos.x > WINDOW_WIDTH || p.proj.pos.y < 0 || p.proj.pos.y > WINDOW_HEIGHT)
			p.projectileOut = false;
}

bool loseCheck(Entity entities[])
{
	//Check to see if the enemy has reached it's goal.
	bool b = false;

	if (entities[ENEMY_ROWS * 10 + 1].pos.y >= ENEMY_GOAL) b = true;

	return b;
}
