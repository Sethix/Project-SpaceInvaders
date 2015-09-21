#include <SFML\Graphics.hpp>
#include "gameOptions.h"
#include "gameStructs.h"
#include "graphics.h"
#include "player.h"
#include "enemy.h"
#include "box.h"
#include "projectile.h"

void gameWindow()
{
	//This is where we'll set the game variables up
	bool exit = false;
	bool movingLeft = true;

	sf::RenderWindow window(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),GAME_WINDOW_TITLE);
	window.setFramerateLimit(60);

	sf::Texture playerTex;
	sf::Texture boxTex;
	sf::Texture projectileTex;
	sf::Texture enemyWeakTex;
	sf::Texture enemyNormalTex;
	sf::Texture enemyStrongTex;

	//If the textures fail to load then we don't want to run the game.
	if (!playerTex.loadFromFile("player.jpg"))
		exit = true;

	if (!boxTex.loadFromFile("box.jpg"))
		exit = true;

	if (!projectileTex.loadFromFile("projectile.png"))
		exit = true;

	if (!enemyWeakTex.loadFromFile("enemy1.jpg"))
		exit = true;

	if (!enemyNormalTex.loadFromFile("enemy3.jpg"))
		exit = true;

	if (!enemyStrongTex.loadFromFile("enemy2.jpg"))
		exit = true;

	sf::Sprite playerSprite(playerTex);
	sf::Sprite boxSprite(boxTex);
	sf::Sprite projectileSprite(projectileTex);
	sf::Sprite enemyWeakSprite(enemyWeakTex);
	sf::Sprite enemyNormalSprite(enemyNormalTex);
	sf::Sprite enemyStrongSprite(enemyStrongTex);

	//This array of entities will include players, boxes and enemies.
	//We do this in an array so we can easily sort through entities.
	//This helps with things like collision detection.
	Entity entityList[100];

	entityList[1] = playerSetup(1, "TST", playerSprite, projectileSprite);
	entityList[1].sprite.setPosition(entityList[1].pos.x, entityList[1].pos.y);

	entityList[2] = playerSetup(2, "TST", playerSprite, projectileSprite);
	entityList[2].sprite.setPosition(entityList[2].pos.x, entityList[2].pos.y);

	entityList[5] = boxSetup(5, boxSprite);
	entityList[6] = boxSetup(6, boxSprite);
	entityList[7] = boxSetup(7, boxSprite);

	for (int a = 0; a < ENEMY_ROWS; ++a)
	{
		for (int b = 0; b < ENEMIES_PER_ROW; ++b)
		{
			entityList[(a * 10) + 10 + b + 1] = enemySetup(b + 1, a + 1, enemyWeakSprite,enemyNormalSprite,enemyStrongSprite, projectileSprite);
		}
	}

	//If we couldn't load a texture then don't open the game. Other wise, open the window.
	if (exit == false)
	{
		while (window.isOpen())
		{
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed)
					window.close();
			}

			//We have to clear the screen each frame, other wise the frames would overlap and we would get clutter.
			window.clear(sf::Color(0,0,0,255));

			//First we draw the entities, then projectiles second so they don't go under entities.
			for (int a = 0; a < 100; ++a)
			{
				setSpritePos(entityList[a].sprite, entityList[a].pos.x, entityList[a].pos.y);
				if (entityList[a].ID != 0 && entityList[a].health > 0) window.draw(entityList[a].sprite);
			}

			for (int a = 0; a < 100; ++a)
			{
				setSpritePos(entityList[a].proj.sprite, entityList[a].proj.pos.x, entityList[a].proj.pos.y);
				if (entityList[a].projectileOut == true) window.draw(entityList[a].proj.sprite);
			}


			window.display();

			//Check for player input so the players can move and shoot
			playerInput(entityList[1]);
			playerInput(entityList[2]);

			enemyMove(entityList, movingLeft);

			//Move the projectiles of players and enemies
			for (int a = 0; a < 100; ++a)
			{
				if(entityList[a].projectileOut == true) projectileMove(entityList[a].proj);
			}

			//Checks to see if anything is damaged. If the HP of an entity reaches 0 then
			//we don't draw it or collide with it anymore.
			damageCheck(entityList);

			//Close the window when we lose or win.
			exit = winCheck(entityList);

			if (exit) window.close();

			exit = loseCheck(entityList);

			if (exit) window.close();

		}
	}
	else window.close();
}