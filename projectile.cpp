#include "gameOptions.h"
#include "gameStructs.h"
#include "projectile.h"

void projectileMove(Projectile &p)
{
	if(p.isFriendly == true) p.pos.y += p.speed;
	else p.pos.y -= p.speed;
}

void damageCheck(Entity entities[])
{
	for (int a = 0; a < 100; ++a)
	{
		if (entities[a].projectileOut == true)
		{
			for (int b = 0; b < 100; ++b)
			{
				//If the projectile has collided with a living entity of another type then deal damage
				if (entities[a].proj.pos.x >= entities[b].pos.x && 
					entities[a].proj.pos.y >= entities[b].pos.y && 
					entities[a].proj.pos.x < entities[b].pos.x + entities[b].size.x &&
					entities[a].proj.pos.y < entities[b].pos.y + entities[b].size.y &&
					entities[a].type != entities[b].type && entities[b].health > 0)
				{
					entities[a].projectileOut = false;
					entities[b].health--;
					if(entities[b].health == 0) entities[a].score += entities[b].score;
				}
			}
		}
	}
}