#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include<cstdlib>
#include"cBohater.h"
class cNaboje:public cBohater
{
public:
	cNaboje(int i);
	~cNaboje();
	 int cNaboje::zwroc_obrazenia();
private:

	
	sf::Vector2f destiny_;
	int obrazenia_;
	
};