#include "cBron.h"

using namespace sf;

cBron::cBron(int i)
{
	switch (i)
	{
		case 1:
			{
			magazynek_ = 10;
			RozmiarBohatera_ = Vector2f(100, 25);
			NazwaTekstury_ = "grafiki/bazooka.png";
			Srodek_ = Vector2f(100, 25);
			ZaladujTeksture();
			
			attack_speed_ = 1;
			Bohater.setOrigin(100 / 2, 25 / 2);
			Bohater.setSize(RozmiarBohatera_);
			Bohater.setPosition(Srodek_);
			break;
			}
		case 2:
			{
			magazynek_ = 50;
			RozmiarBohatera_ = Vector2f(100, 30);
			NazwaTekstury_ = "grafiki/ak-47.png";
			Srodek_ = Vector2f(100, 25);
			ZaladujTeksture();
			
			attack_speed_ = 10;
			Bohater.setOrigin(100 / 2, 30 / 2);
			Bohater.setSize(RozmiarBohatera_);
			Bohater.setPosition(Srodek_);
			break;
			}
		case 3:
			{
			magazynek_ = 8;
			RozmiarBohatera_ = Vector2f(50,35);
			NazwaTekstury_ = "grafiki/glock.png";
			Srodek_ = Vector2f(100, 25);
			ZaladujTeksture();
			
			attack_speed_ = 3;
			Bohater.setOrigin(50 / 2, 35 / 2);
			Bohater.setSize(RozmiarBohatera_);
			Bohater.setPosition(Srodek_);
			break;
			}
	}
}


cBron::~cBron()
{
}
int cBron::zwroc_obrazenia()
{
	return 0;
}
int cBron::zwroc_magazynek()
{
	return magazynek_;
}
void cBron::wystrzel()
{
	magazynek_--;
}
void cBron::zaladuj_tobiasz_w_koncu(int numerek)
{

	if (numerek == 6)
	{
		magazynek_ += 50;
	}
	else if (numerek == 5)
	{
		magazynek_ += 25;
	}
	else if (numerek == 4)
	{
		magazynek_ += 5;
	}
}