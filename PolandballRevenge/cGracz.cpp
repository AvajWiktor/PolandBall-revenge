#include "cGracz.h"



cGracz::cGracz()
{
	hp_ = 1000;
	Szerokosc_ = 120;
	Wysokosc_ =120;
	NazwaTekstury_ = "grafiki/polandball.png";
	Srodek_.x = 640;
	Srodek_.y = 502;
	ZaladujTeksture();
	RozmiarBohatera_.x = Szerokosc_;
	RozmiarBohatera_.y = Wysokosc_;
	Bohater.setOrigin(Szerokosc_ / 2, Wysokosc_ / 2);
	Bohater.setSize(RozmiarBohatera_);
	Bohater.setPosition(Srodek_);
	
}


cGracz::~cGracz()
{
}

int cGracz::zwroc_obrazenia()
{
	return 0;
}