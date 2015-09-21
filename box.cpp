#include "gameOptions.h"
#include "gameStructs.h"
#include "box.h"

Entity boxSetup(int id, sf::Sprite s)
{
	Entity tempBox;

	tempBox.ID = id;
	tempBox.type = Box;

	tempBox.size.x = BOX_SPRITE_WIDTH;
	tempBox.size.y = BOX_SPRITE_HEIGHT;

	if (tempBox.ID == 5)
	{
		tempBox.pos.x = (WINDOW_WIDTH / 4) - (tempBox.size.x / 2);
	}
	if (tempBox.ID == 6)
	{
		tempBox.pos.x = (WINDOW_WIDTH / 2) - (tempBox.size.x / 2);
	}
	if (tempBox.ID == 7)
	{
		tempBox.pos.x = (WINDOW_WIDTH / 4) * 3 - (tempBox.size.x / 2);
	}

	tempBox.pos.y = WINDOW_HEIGHT - BOX_DEFAULT_Y;

	tempBox.sprite = s;

	tempBox.health = BOX_MAX_HEALTH;

	return tempBox;
}