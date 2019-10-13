#include "cItemki.h"



cItemki::cItemki(int i)
{
	
	if (i % 10 == 0)
	{
		numerek_ = 1;
		Szerokosc_ = 50;
		Wysokosc_ = 70;
		NazwaTekstury_ = "grafiki/zubrowka_b1.png";


	}
	else if (i % 7 == 0)
	{
		numerek_ = 2;
		Szerokosc_ = 70;
		Wysokosc_ = 70;
		NazwaTekstury_ = "grafiki/zuber.png";


	}
	else if (i % 5 == 0)
	{
		numerek_ = 3;
		Szerokosc_ = 50;
		Wysokosc_ = 70;
		NazwaTekstury_ = "grafiki/tyskie.png";

	}
	else if (i % 8 == 0)
	{
		numerek_ = 4;
		Szerokosc_ = 96;
		Wysokosc_ = 54;
		NazwaTekstury_ = "grafiki/ammo3.png";


	}
	else if (i % 6 == 0)
	{
		numerek_ = 5;
		Szerokosc_ = 96;
		Wysokosc_ = 54;
		NazwaTekstury_ = "grafiki/ammo2.png";



	}
	
	
	

	ZaladujTeksture();
	RozmiarBohatera_.x = Szerokosc_;
	RozmiarBohatera_.y = Wysokosc_;
	Bohater.setOrigin(Szerokosc_ / 2, Wysokosc_ / 2);
	Bohater.setSize(RozmiarBohatera_);
	
}


cItemki::~cItemki()
{
}
int cItemki::zwroc_numerek()
{
	return numerek_;
}