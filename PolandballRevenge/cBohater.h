#pragma once
#include<SFML\Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
class  cBohater :public sf::Drawable
{
public:
	cBohater();
	~cBohater()=default;
	void draw(sf::RenderTarget& target, sf::RenderStates state) const override;
	
	void move(double x, double y);
	bool cBohater::kolizja(sf::RectangleShape x);
	void cBohater::ZaladujTeksture();
	void cBohater::set_velocity(double vx, double vy);
	void cBohater::animate(double time);
	void cBohater::set_position(float iks, float igrek);
	sf::RectangleShape cBohater::Zwroc_bohatera();
	std ::vector<float> zwroc_srodek();
	void cBohater::grawitacja(const float stala);
	std::vector<double>cBohater::zwroc_predkosc();
	sf::Vector2f cBohater::zwroc_rozmiar();
	void set_texture(std::string tex);
	void cBohater::obroc(float kat);
	void cBohater::set_origin(float x,float y);
	void cBohater::set_scale(float x, float y);
	sf::Vector2f cBohater::get_scale();
	void cBohater::zadaj_obrazenia(int dmg);
	virtual int cBohater::zwroc_obrazenia();
	int cBohater::zwroc_hp();
protected:
	sf::RectangleShape Bohater;
	std::string NazwaTekstury_;
	sf::Texture TexturaBohatera_;
	sf::Vector2f RozmiarBohatera_;
	double v_x_=0.0;
	double v_y_ = 0.0;
	int Szerokosc_;
	int Wysokosc_;
	int hp_;
	int typ_;

	sf::Vector2f Srodek_;
	
	
};

