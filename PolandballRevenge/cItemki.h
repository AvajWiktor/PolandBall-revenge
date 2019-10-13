#pragma once
#include"cBohater.h"
class cItemki:public cBohater
{
public:
	cItemki(int i);
	~cItemki();
	int zwroc_numerek();
private:
	int numerek_;
};

