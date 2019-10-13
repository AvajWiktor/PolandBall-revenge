#include "menu.h"



menu::menu()
{
	Szerokosc_ = 300;
	Wysokosc_ = 150;
	NazwaTekstury_ = "grafiki/guzik1.png";
	Srodek_.x = 640;
	Srodek_.y = 200;
	ZaladujTeksture();
	RozmiarBohatera_.x = Szerokosc_;
	RozmiarBohatera_.y = Wysokosc_;
	Bohater.setOrigin(Szerokosc_ / 2, Wysokosc_ / 2);
	Bohater.setSize(RozmiarBohatera_);
	Bohater.setPosition(Srodek_);
}


menu::~menu()
{
}
int menu::zwroc_obrazenia()
{
	return 0;
}