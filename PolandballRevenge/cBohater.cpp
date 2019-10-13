#include "cBohater.h"



cBohater::cBohater()
{

	
	
	
}
sf::RectangleShape cBohater::Zwroc_bohatera()
{
	return Bohater;
}
void cBohater::ZaladujTeksture()
{
	TexturaBohatera_.loadFromFile(NazwaTekstury_);
	Bohater.setTexture(&TexturaBohatera_);
	
}
void cBohater::move(double x,double y)
{
	Srodek_.x += x;
	Srodek_.y += y;
	Bohater.setPosition(Srodek_);
	Srodek_.x = Bohater.getPosition().x;
	Srodek_.y = Bohater.getPosition().y;
}

void cBohater::draw(sf::RenderTarget& target, sf::RenderStates state) const
{
	target.draw(this->Bohater, state);
}
void cBohater::set_velocity(double vx, double vy) {
	v_x_ = vx;
	v_y_ = vy;
}

void cBohater::animate(double time) {
	Srodek_.x += v_x_ * time/10000;
	Srodek_.y += v_y_ * time/10000;
	Bohater.setPosition(Srodek_);
	
	
}

std::vector<float>cBohater:: zwroc_srodek()
{
	std::vector<float> wspolrzedne;
	
	wspolrzedne.push_back(Bohater.getPosition().x);
	wspolrzedne.push_back(Bohater.getPosition().y);
	return wspolrzedne;
}

sf::Vector2f cBohater::zwroc_rozmiar()
{
	sf::Vector2f iksde(Szerokosc_,Wysokosc_);
	return iksde;
}
std::vector<double>cBohater:: zwroc_predkosc()
{
	std::vector<double> predkosc;
	predkosc.push_back(v_x_);
	predkosc.push_back(v_y_);
	return predkosc;
}

void cBohater::set_position(float iks, float igrek)
{
	Bohater.setPosition(iks, igrek);
	Srodek_.x = Bohater.getPosition().x;
	Srodek_.y = Bohater.getPosition().y;

}
void cBohater::grawitacja(const float stala)
{
	v_y_ += stala;

}
bool cBohater::kolizja(sf::RectangleShape x)
{
	if (Bohater.getGlobalBounds().intersects(x.getGlobalBounds()))
	{
		return true;
	}
	else return false;
}
void cBohater::set_texture(std::string tex)
{
	NazwaTekstury_ = tex;
	ZaladujTeksture();
}
void cBohater::obroc(float kat)
{
	Bohater.setRotation(0);
	Bohater.rotate(-kat);
	
}
void cBohater::set_origin(float x, float y)
{
	Bohater.setOrigin(x,y);
}
void cBohater::set_scale(float x, float y)
{
	Bohater.setScale(x, y);
	
}
sf::Vector2f cBohater::get_scale()
{
	return Bohater.getScale();
}
void cBohater::zadaj_obrazenia(int dmg)
{
	hp_ -= dmg;
}

int cBohater::zwroc_hp()
{
	return hp_;
}
int cBohater::zwroc_obrazenia()
{
	return 0;
}
