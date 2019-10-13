#include "cPrzeszkody.h"



cPrzeszkody::cPrzeszkody(sf::Vector2f pozycja)
{
	RozmiarBohatera_ = sf::Vector2f(100, 50);
	NazwaTekstury_ = "grafiki/platforma.png";
	Srodek_ = pozycja;
	ZaladujTeksture();
	Bohater.setOrigin(100 / 2, 50 / 2);
	Bohater.setSize(RozmiarBohatera_);
	Bohater.setPosition(Srodek_);
}


cPrzeszkody::~cPrzeszkody()
{
}
