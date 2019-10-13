#pragma once
#include<SFML\Graphics.hpp>

#include"cBohater.h"
class cBron:public cBohater
{
public:
	cBron(int i);
	~cBron();
	int cBron::zwroc_obrazenia();
	int cBron::zwroc_magazynek();
	void cBron::wystrzel();
	void cBron::zaladuj_tobiasz_w_koncu(int numerek);
private:
	int magazynek_;
		int attack_speed_;
};

