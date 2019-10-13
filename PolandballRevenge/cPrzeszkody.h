#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include<cstdlib>
#include"cBohater.h"
class cPrzeszkody:public cBohater
{
public:
	cPrzeszkody(sf::Vector2f pozycja);
	~cPrzeszkody();
};

