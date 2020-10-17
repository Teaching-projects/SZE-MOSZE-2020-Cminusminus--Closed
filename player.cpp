#include "player.h"
#include <string>
#include <cmath>

Player::Player(const std::string& name, int health, int damage) : Character(name, health, damage) { xp = 0; level = 1, maxHP = health; }

int Player::GetLevel() const
{
	return level;
}

void Player::Attack(Character& enemy){
	enemy.GetAttacked(*this);
	XPManager(enemy);
}

void Player::XPManager(Character& enemy)
{
	if (enemy.GetHealth() < this->GetDamage())
	{
		xp += enemy.GetHealth();
	}
	else
	{
		xp += this->GetDamage();
	}
	

		int i = xp / 100;
		
		for (int j = 0; j < i; j++)
		{
			level++;
			maxHP = (int)(round(1.1*maxHP));
			SetHealth(maxHP);
			GainDamage(1.1);
			xp -= 100;
		}	

}
