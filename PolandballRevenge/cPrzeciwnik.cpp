#include "cPrzeciwnik.h"



cPrzeciwnik::cPrzeciwnik(int i)
{
	switch (i)
	{
		case 1:
		{
			typ_= 1;
			hp_ = 100;
			NazwaTekstury_ = "grafiki/germanball.png";
			Szerokosc_ = 100;
			Wysokosc_ = 100;
			Srodek_.x = ((rand() % 50) + 1) * 100;
			Srodek_.y = 600;
			break;
		}
		case 2:
		{
			typ_ = 2;
			hp_ = 250;
			NazwaTekstury_ = "grafiki/germanball_elita.png";
			Bohater.setScale(-1, 1);
			Szerokosc_ = 200;
			Wysokosc_ = 200;
			Srodek_.x = ((rand() % 50) + 1) * 100;
			Srodek_.y = 500;
			break;
		}
		case 3:
		{
			typ_ = 3;
			hp_ = 2500;
			NazwaTekstury_ = "grafiki/german_boss.png";
			
			Szerokosc_ = 350;
			Wysokosc_ = 350;
			Srodek_.x = 100;
			Srodek_.y = 500;
			break;
		}
	}
	ZaladujTeksture();
	
	RozmiarBohatera_.x = Szerokosc_;
	RozmiarBohatera_.y = Wysokosc_;
	Bohater.setOrigin(Szerokosc_ / 2, Wysokosc_ / 2);
	Bohater.setSize(RozmiarBohatera_);
	Bohater.setPosition(Srodek_);
}


cPrzeciwnik::~cPrzeciwnik()
{
}
int cPrzeciwnik::zwroc_obrazenia()
{
	return 0;
}
int cPrzeciwnik::zwroc_typ()
{
	return typ_;
}