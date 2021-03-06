#pragma once
#ifndef MONSTER_H
#define MONSTER_H

#include<string>
#include <vector>
#include "JSON.h"

struct Damage
{

	///This represents the physical damage.
	int physical;
	///This represents the magical damage.
	int magical;

	///\brief Operator override for operator+ in Damage struct.
	///\param Damage& dmg
	///\return Damage
	Damage operator+(const Damage& dmg) 
	{
		Damage return_dmg;

		return_dmg.physical = dmg.physical+ this->physical;
		return_dmg.magical = dmg.magical + this->magical;

		return return_dmg;
	}
	///\brief Operator override for operator+= in Damage struct.
	///\param Damage& dmg
	///\return Damage&
	Damage& operator+=(const Damage& dmg) 
	{
		this->physical += dmg.physical;
		this->magical += dmg.magical;

		return *this;
	}
	///\brief Operator override for operator*= in Damage struct.
	///\param Damage& dmg
	///\return Damage&
	Damage& operator*=(const Damage& dmg) 
	{
		this->physical *= dmg.physical;
		this->magical *= dmg.magical;

		return *this;
	}
};



class Monster
{
   /**
  *\brief A class for creating a monster.
  *\param name The name of the monster.
  *\param health The health of the monster.
  *\param damage The damage of the monster (physical and magical).
  *\param attackCooldown The speed of the monster's attack.
  *\param defense The defense of the monster.
  *\param texture The texture of the monster in svg.
  */
public:

	Monster(const std::string& name, const int health, Damage damage, const double attackCooldown, const int defense, const std::string& texture);
	Monster() { damage.magical = 0; damage.physical = 0; };
	///It returns the texture of the monster.
	///\return string
	std::string getTexture() const;
	///It returns the defense of the Monster
	///\return defense
	int getDefense() const;
	///It sets the defense of the Hero when it levels up
	///\param bonus The amount we add to the defense
	void setDefense(const int bonus);
	///This function parse a Monster from a file.
	///\param s The file name we parse.
	///\return Monster
	static Monster parse(const std::string& s);
	///This function parse a Monster using istream.
	///\param stream The stream we parse from.
	///\return Monster
	static Monster parse(std::istream& stream);
	///It returns the name of the monster.
	///\return name
	std::string getName() const;
	///It returns the health of the monster.
	///\return health
	int getHealthPoints() const;
	///It sets the health of the monster.
	///\param health The current health of the monster
	void SetHealth(const int health);
	///It returns the physical damage of the monster.
	///\return damage.physical
	int getPhysicalDmg() const;
	///It returns the magical damage of the monster.
	///\return damage.magical
	int getMagicalDmg() const;
	///It sets the damage of the hero after level up
	///\param bonus, type The damage the hero gains after level up and the type of damage it gains
	void GainDamage(const int bonus, const std::string& type);
	///It multiplies the attack cooldown with the given amount.
	///\param multplier The amound we multiply the attack cooldown.
	void AcdMultiplier(const double multiplier);
	///It checks if the monster is alive.
	///\return true or false.
	bool isAlive() const;
	///\brief A function to simulate the battle of two given monster.
	///\param enemy The enemy which the monster attacks.
	void fightTilDeath(Monster& enemy);
	///It returns the attack speed of the monster.
	///\return attackCooldown
	double getAttackCoolDown() const;
	///Attacks the enemy.
	///\param damage The damage we attack the enemy with
	void getAttacked(const int damage);
private:
	virtual void Attack(Monster& enemy);

	const std::string name = "";
	int health = 0;
	Damage damage;
	double attackCooldown = 0;
	int defense = 0;
	std::string texture = "";
};

#endif // CHARACTER_H
