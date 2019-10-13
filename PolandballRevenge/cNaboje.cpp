#include "cNaboje.h"



cNaboje::cNaboje(int i)
{
	switch (i)
	{
		case 1: 
		{ 
			NazwaTekstury_ = "grafiki/bullet3.png";
			obrazenia_ = 150;
			RozmiarBohatera_ = sf::Vector2f(38, 30);
			
			
			ZaladujTeksture();
			
			Bohater.setSize(RozmiarBohatera_);
			
			break;
		}
		case 2:
		{
			
			obrazenia_ = 20;
			NazwaTekstury_ = "grafiki/bullet4.png";
			ZaladujTeksture();
			RozmiarBohatera_ = sf::Vector2f(10,10);
			
			Bohater.setSize(RozmiarBohatera_);
			
			break;
		}
		case 3:
		{

			obrazenia_ = 20;
			NazwaTekstury_ = "grafiki/bullet4.png";
			ZaladujTeksture();
			RozmiarBohatera_ = sf::Vector2f(10, 10);
			
			Bohater.setSize(RozmiarBohatera_);
			
			break;
		}
	}
}


cNaboje::~cNaboje()
{
}
int cNaboje::zwroc_obrazenia()
{
	return obrazenia_;
}