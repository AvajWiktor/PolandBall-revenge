#include <SFML\Graphics.hpp>
#include <SFML\Audio.hpp>
#include <iostream>
#include <list>
#include <cstdlib>
#include<string>
#include"cBohater.h"
#include"cPrzeciwnik.h"
#include"cGracz.h"
#include<Windows.h>
#include"menu.h"
#include"cBron.h"
#include <algorithm>
#include <cmath>
#include"cNaboje.h"
#include"cItemki.h"
#include <fstream>
#include "cPrzeszkody.h"
using namespace sf;



float predkosc = 5;
float pokonana_droga = 0;
float pozycja = 0;
float poziom_stopy;

RenderWindow window(VideoMode(1280, 720), "Polandball 1939 - Revenge");

int stan_rozgrywki = 0;
int ktora_bron = 1;
int czy_skacze = 0;
int if_muzyka_menu=0, if_muzyka_map1=0;
int poziom_gry = 0;
int opozniacz = 0;
int poziom_gruntu = 700;
int tajmer = 0;
int booster = 0;
int wudeczka = 0;
int boss = 1;
bool mam_dosyc = true;
bool czy_wygralem = false;
bool kolirzyn = true;
bool Czy_tyskie = false;
bool Czy_zuber = false;
bool Czy_menu = true;
bool Czy_przegralem = false;
bool czy_skacze2 = false;
bool czy_liczyc = false;
Texture wuda1, piwu1,piwu2, pak1,pak2;
Music muzyka_menu,muzyka_map1,muzyka_win;
SoundBuffer german_ball,piwerko_o,fajnal_bos,dymy_gy;
Sound germanball,piwerkoo,fajnalbos,dymygy;
std::vector<RectangleShape> score;
std::vector<menu> guziki;
std::vector<cBron> bronie;


std::list<cPrzeciwnik> przeciwnicy;
std::list<cNaboje> naboje;
std::list<cItemki> itemki;
std::list<cPrzeszkody> przeszkody;
std::fstream plik;
Font font;
Text skore,magazynek,hp;
View widok(FloatRect(pozycja,0,1280,720));

Vector2f pozycja_myszy;
Vector2f pozycja_gracza;
Vector2f vektor;
Vector2f vektor_normal;

const float grawitacja = 9;
bool jest_3_w_nocy(cGracz &plat,std::string moje_oczy)
{
	if (moje_oczy == "A")
	{
		for (auto itr = przeszkody.begin(); itr != przeszkody.end(); itr++)
		{
			if (plat.zwroc_srodek()[0] - itr->zwroc_srodek()[0] == 1)
			{
				return true;
			}
			else
				return false;
			
		}

	}
	if (moje_oczy == "D")
	{
		for (auto itr = przeszkody.begin(); itr != przeszkody.end(); itr++)
		{
			if (plat.zwroc_srodek()[0] - itr->zwroc_srodek()[0] == -1)
			{
				return true;
			}
			else return false;
		}

	}
	if (moje_oczy == "S")
	{
		for (auto itr = przeszkody.begin(); itr != przeszkody.end(); itr++)
		{
			if ((plat.kolizja(itr->Zwroc_bohatera())) && (plat.zwroc_srodek()[0] + (plat.zwroc_rozmiar().x) / 2 < itr->zwroc_srodek()[0] - (itr->zwroc_rozmiar().x) / 2))
			{
				return false;
			}
			else if ((plat.kolizja(itr->Zwroc_bohatera())) && ((plat.zwroc_srodek()[0] - (plat.zwroc_rozmiar().x) / 2) > itr->zwroc_srodek()[0] + (itr->zwroc_rozmiar().x) / 2))
			{
				return false;
			}
			else return true;
		}

	}
}
void kolizja(cGracz &gracz)
{

	for (auto itr = przeszkody.begin(); itr != przeszkody.end(); itr++)
	{
		if ((itr->Zwroc_bohatera().getGlobalBounds().intersects(gracz.Zwroc_bohatera().getGlobalBounds()))&&(itr->zwroc_srodek()[1]-60>gracz.zwroc_srodek()[1]))

		{
			poziom_gruntu = poziom_stopy;
			kolirzyn = true;
			break;
		}
		else
			poziom_gruntu = 700;
			kolirzyn = false;
	}

}
void grawitacyjnie(cGracz &plat)
{
	
	
		if ((plat.zwroc_srodek()[1] + plat.zwroc_rozmiar().y < poziom_gruntu) || (plat.zwroc_predkosc()[1] < 0))
		{

			plat.grawitacja(grawitacja / 10);

		}
		else
		{
			plat.set_position(plat.zwroc_srodek()[0], poziom_gruntu - plat.zwroc_rozmiar().y);
			plat.set_velocity(0, 0);

		}
	
		plat.animate(7000);
	
}
void okno()
{
	sf::Event evnt;

	while (window.pollEvent(evnt))
	{
		if (evnt.type == Event::Closed)
		{
			window.close();
		}
	}
}
void timer()
{
	if (Czy_tyskie||Czy_zuber) 
	{
		if (booster == 600)
		{
			Czy_tyskie = false;
			Czy_zuber = false;
			booster = 0;
		}
		else
			booster++;
	}
	if (opozniacz ==180)

		opozniacz = 0;
	else
		opozniacz++;
	if (tajmer == 60)
	{
		tajmer = 0;
		czy_liczyc = false;
	}
	else if(czy_liczyc)
		tajmer++;
}
void Ruch(cGracz &plat)
{
	if (poziom_stopy<poziom_gruntu-188)
	{
		czy_skacze = 0;
		czy_skacze2 = false;
	}
	if (poziom_stopy >= poziom_gruntu)
		{
			czy_skacze = 1;
		}
	
	
	if ((Keyboard::isKeyPressed(Keyboard::Key::P)) && (Keyboard::isKeyPressed(Keyboard::Key::O)))
	{
		czy_wygralem = true;
	}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
		{
			if (widok.getCenter().x - 640 < plat.zwroc_srodek()[0] - 100)
			{
				if ((!kolirzyn)&&(jest_3_w_nocy(plat,(std::string)"A")))
				{
					plat.move(0, 0);
				}
				else
				{
					plat.move(-predkosc, 0);
					pokonana_droga -= predkosc;
				}
				
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S))
		{
			std::cout << "pozycja: " << pozycja_gracza.x << std::endl;
			if (poziom_stopy < poziom_gruntu)
			{
				plat.move(0, predkosc);
			}

		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
		{
			if (plat.zwroc_srodek()[0] >= 13600)
			{
				if (plat.zwroc_srodek()[0] <= 14200)
				{

					plat.move(predkosc, 0);
					pokonana_droga += predkosc;
				}
			}
			else if (widok.getCenter().x - 100 < plat.zwroc_srodek()[0] && plat.zwroc_srodek()[0] < widok.getCenter().x + 100)
			{ 
				if((jest_3_w_nocy(plat, "D")) && (!kolirzyn))
				{
					plat.move(0, 0);
				}
				else 
				{
					plat.move(predkosc, 0);
					pokonana_droga += predkosc;
					pozycja += predkosc;
				}
				
			}
			else
			{
				if ((jest_3_w_nocy(plat, "D")) && (!kolirzyn))
				{
					plat.move(0, 0);
				}
				else 
				
					{
						plat.move(predkosc, 0);
						pokonana_droga += predkosc;
					}
			 
			}
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && czy_skacze > 0)
		{

			if (czy_skacze == 1)
			{

				plat.set_velocity(0, -19);
				czy_skacze2 = true;
			}
			else if (czy_skacze2)
			{
				plat.set_velocity(0, -19);
				czy_skacze = 0;
			}

		}
	
		
	widok.setCenter(pozycja + 640, 360);
	window.setView(widok);
	

}
void obsluga_broni(cGracz&plat)
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num1))
	{
		ktora_bron = 1;
		std::cout << "bron nr:" << ktora_bron<<std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num2))
	{
		ktora_bron = 2;
		std::cout << "bron nr:" << ktora_bron << std::endl;
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Num3))
	{
		ktora_bron = 3;
		std::cout << "bron nr:" << ktora_bron << std::endl;
	}
	bronie[ktora_bron - 1].set_position(pozycja_gracza.x, pozycja_gracza.y + 10);
	float kat1 = atan2((pozycja_gracza.y - pozycja_myszy.y), (pozycja_myszy.x - (pozycja_gracza.x - pokonana_droga))) * 180 / 3.14;
	if (kat1 < 90 &&kat1>-90)
	{
		plat.set_scale(1, 1);
		if(bronie[ktora_bron - 1].get_scale()==Vector2f(1,-1))
			bronie[ktora_bron - 1].set_scale(1, 1);
		bronie[ktora_bron - 1].obroc(kat1);
	}
	else if(kat1>90||kat1<-90)
	{
		plat.set_scale(-1, 1);
		bronie[ktora_bron - 1].set_scale(1, -1);
		bronie[ktora_bron - 1].obroc(kat1);
	}
	
}
void dodawanie_broni()
{
	for (int i = 1; i < 4; i++)
	{
		cBron *gun = new cBron(i);
		bronie.push_back(*gun);
	}
}
void dodaj_przeciwnikow()
{
	if (stan_rozgrywki == 3 && boss == 1)
	{
		
		cPrzeciwnik *temp = new cPrzeciwnik(stan_rozgrywki);
		temp->set_position(14500, 550);

		przeciwnicy.push_back(*temp);
		boss = 2;
		stan_rozgrywki = 3;
	}
	else if ((opozniacz % 180 == 0)&&(opozniacz!=0))
	{
		if (stan_rozgrywki == 3)
		{
			cPrzeciwnik *temp = new cPrzeciwnik(stan_rozgrywki-1);
			temp->set_position(pozycja_gracza.x + 1280, 600);
			
			przeciwnicy.push_back(*temp);
		}
		else 
		{
			cPrzeciwnik *temp = new cPrzeciwnik(stan_rozgrywki);
			temp->set_position(pozycja_gracza.x + 1280, 600);
			
			przeciwnicy.push_back(*temp);
		}
	}
	
	
}
void dodawanie_punktow()
{
	
	RectangleShape wuda, piwu, pak;
	


	wuda.setSize(Vector2f(50, 70));
	piwu.setSize(Vector2f(50,70));
	pak.setSize(Vector2f(70, 70));

	piwu.setOrigin(piwu.getSize().x / 2, piwu.getSize().y / 2);
	pak.setOrigin(pak.getSize().x / 2, pak.getSize().y / 2);
	wuda.setOrigin(wuda.getSize().x/2, wuda.getSize().y / 2);
	score.push_back(piwu);
	score.push_back(wuda);
	score.push_back(pak);
	
	wuda1.loadFromFile("grafiki/zubrowka_b1.png");
	piwu2.loadFromFile("grafiki/tyskie1.png");
	piwu1.loadFromFile("grafiki/tyskie.png");
	pak1.loadFromFile("grafiki/zuber.png");
	pak2.loadFromFile("grafiki/zuber1.png");
	score[1].setTexture(&wuda1);
	score[0].setTexture(&piwu1);
	score[2].setTexture(&pak1);
}
void rysuj(cGracz &gracz)
{
	for (int i = 0; i < 3; i++)
	{
		if (i == 2 && Czy_zuber)
		{

			score[i].setTexture(&pak2);
		}
		else if (i == 2 && !Czy_zuber)
		{
			score[i].setTexture(&pak1);
		}
		if (i == 0 && Czy_tyskie)
		{

			score[i].setTexture(&piwu2);
		}
		else if (i == 0 && !Czy_tyskie)
		{
			score[i].setTexture(&piwu1);
		}
		score[i].setPosition(widok.getCenter().x-570+i*70,90);
		hp.setPosition(widok.getCenter().x + i * 70, 50);
		window.draw(score[i]);
	}
	for (auto itr = przeciwnicy.begin(); itr != przeciwnicy.end(); itr++ )
	{
		
		if (itr->zwroc_typ() == 1)
		{
			itr->set_velocity(-50, 0);
		}
		else if (itr->zwroc_typ() == 2)
		{
			itr->set_velocity(-20, 0);
		}
		else if (itr->zwroc_typ() == 3)
		{
			if (itr->zwroc_srodek()[0] == 14000)
				(itr->set_velocity(0, 0));
			else
			itr->set_velocity(-100, 0);
		}
		
		
		
			if (itr->zwroc_srodek()[0] > widok.getCenter().x - 1000)
			{
				

				itr->animate(1000);
				window.draw(itr->Zwroc_bohatera());

			}
			else
			{
				itr = przeciwnicy.erase(itr);
				break;

			}
			
			if (itr->kolizja(gracz.Zwroc_bohatera()))
			{
				dymygy.play();

				if (itr->zwroc_typ()== 1)
				{
					gracz.zadaj_obrazenia(300);
					itr = przeciwnicy.erase(itr);
					break;
				}
				else if (itr->zwroc_typ() == 2)
				{
					gracz.zadaj_obrazenia(500);
					itr = przeciwnicy.erase(itr);
					break;
				}
				
			}
		
	}
	for (auto itr = przeszkody.begin(); itr != przeszkody.end(); itr++)
	{
		window.draw(itr->Zwroc_bohatera());
		
	}
	
for (auto itr = itemki.begin(); itr != itemki.end(); itr++)
		{
			window.draw(itr->Zwroc_bohatera());
		}
	
	window.draw(gracz);
	window.draw(bronie[ktora_bron-1]);
		for (auto itr = naboje.begin(); itr != naboje.end(); )
		{
			if (itr->zwroc_srodek()[1] < -50 || itr->zwroc_srodek()[1] > 820 || itr->zwroc_srodek()[0] < widok.getCenter().x-640 || itr->zwroc_srodek()[0] > widok.getCenter().x+640)
			{
				itr = naboje.erase(itr);


			}
			else
			{
				
				itr->animate(1000);
				window.draw(itr->Zwroc_bohatera());
				itr++;

			}


		}
		
}
void dodaj_guziki()
{

	for (int i = 0; i < 2; i++)
	{
		
		menu *temp = new menu();
		temp->set_position(640, 240 + 100 * i);
		
		if (i == 1)
		{
			
			temp->set_texture("grafiki/guzik2.png");
			
		}
		guziki.push_back(*temp);
	}
	
	
	
}
bool kolizja_myszki(menu x)
{
	
	
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		
		if (x.Zwroc_bohatera().getGlobalBounds().contains(pozycja_myszy))
		{
			return true;
		}
		else
		{
			return false;
		}

	}
	else
		return false;
	

	
}
void kolizja_naboji()
{
	if (naboje.size() != 0)
	{
		for (auto itr = naboje.begin(); itr != naboje.end(); )
		{
			if (naboje.size() != 0)
			{
				bool zmienna = 1;
				for (auto k = przeciwnicy.begin(); k != przeciwnicy.end(); )
				{
					
					if (itr->kolizja(k->Zwroc_bohatera()))
					{
						k->zadaj_obrazenia(itr->zwroc_obrazenia()+wudeczka*3);
						itr = naboje.erase(itr);
						zmienna = 0;
						if (k->zwroc_hp() <= 0)
						{
							if (k->zwroc_typ() == 3)
							{
								fajnalbos.play();
								czy_wygralem = true;
							}
							else if(k->zwroc_typ()<3)
							{
								germanball.play();
								int loot = ((rand() % 100) + 1);


								{
									cItemki *temp = new cItemki(loot);
									temp->set_position(k->zwroc_srodek()[0], k->zwroc_srodek()[1]);
									itemki.push_back(*temp);
								}
								
							}
							k = przeciwnicy.erase(k);
						}
						
						break;
					}
					else
					{

						k++;
					}

				}
				if (zmienna)
				{
					itr++;
				}
			}
		}
	}
	
}
void kolizja_itemkow(cGracz gracz)
{
	if (Czy_zuber)
	{
		predkosc = 10;
	}
	else if (Czy_tyskie)
	{
		predkosc = 7;
	}
	else
	{
		//predkosc = 5;
	}
	
	
	
	for (auto k = itemki.begin(); k != itemki.end(); )
	{
		if (gracz.kolizja(k->Zwroc_bohatera()))
		{
			if (k->zwroc_numerek() == 3)
			{
				piwerkoo.play();
				Czy_tyskie = true;
			}
			else if (k->zwroc_numerek() == 1)
			{
				wudeczka ++;
			}
			else if (k->zwroc_numerek() == 2)
			{
				piwerkoo.play();
				Czy_zuber = true;
			}
			
			
			else if (k->zwroc_numerek() == 4)
			{
				bronie[0].zaladuj_tobiasz_w_koncu(4);
			}
			else if (k->zwroc_numerek() == 5)
			{
				bronie[1].zaladuj_tobiasz_w_koncu(5);
				
			}
			k = itemki.erase(k);
		}
		else
			k++;

	}
}
void sprawdzam_czy_wylaczyc_muzyke()
{
	if (!Czy_menu)
	{
		muzyka_menu.stop();
	}
	if (Czy_przegralem)
	{
		muzyka_map1.stop();
	}
	if (czy_wygralem)
	{
		muzyka_map1.stop();

		
		
	}
}
void dodaj_muzyke()
{
	dymy_gy.loadFromFile("muzyka/dmg.ogg");
	dymygy.setBuffer(dymy_gy);
	dymygy.setVolume(30);

	german_ball.loadFromFile("muzyka/germanball.ogg");
	germanball.setBuffer(german_ball);
	germanball.setVolume(30);

	fajnal_bos.loadFromFile("muzyka/fajnalbos.ogg");
	fajnalbos.setBuffer(fajnal_bos);
	fajnalbos.setVolume(100);

	piwerko_o.loadFromFile("muzyka/Piwerko.ogv");
	piwerkoo.setBuffer(piwerko_o);
	piwerkoo.setVolume(30);

	muzyka_menu.openFromFile("muzyka/menu.ogg");
	muzyka_menu.setLoop(true); 
	muzyka_menu.setVolume(10); 
	
	muzyka_map1.openFromFile("muzyka/mapa1.ogg");
	muzyka_map1.setLoop(true); 
	muzyka_map1.setVolume(10); 

	muzyka_win.openFromFile("muzyka/win.ogg");
	muzyka_win.setLoop(true);
	muzyka_win.setVolume(10);

}
void obsluga_pociskow(int i)
{
	float kat1 = atan2((pozycja_gracza.y - pozycja_myszy.y), (pozycja_myszy.x - (pozycja_gracza.x - pokonana_droga))) * 180 / 3.14;
	switch (i)
	{
		case 1:
			{
			
			
			cNaboje *temp = new cNaboje(ktora_bron);
			temp->set_position(pozycja_gracza.x,pozycja_gracza.y);
			temp->set_origin(38 / 2, 30 / 2);
			temp->obroc(kat1);
			temp->set_velocity(vektor_normal.x*100,vektor_normal.y*100);
			naboje.push_back(*temp);
			bronie[ktora_bron - 1].wystrzel();
				break;
			}
		case 2:
			{
			
			cNaboje *temp = new cNaboje(ktora_bron);
			temp->set_position(pozycja_gracza.x, pozycja_gracza.y);
		temp->set_origin(10 / 2, 10 / 2);
			temp->obroc(kat1);
			temp->set_velocity(vektor_normal.x * 200, vektor_normal.y * 200);
			naboje.push_back(*temp);
			bronie[ktora_bron - 1].wystrzel();
				break;
			}
		case 3:
			{
			
			cNaboje *temp = new cNaboje(ktora_bron);
			temp->set_position(pozycja_gracza.x, pozycja_gracza.y);
			temp->set_origin(10 / 2, 10 / 2);
			temp->obroc(kat1);
			temp->set_velocity(vektor_normal.x * 70, vektor_normal.y * 70);
			naboje.push_back(*temp);
			
				break;
			}
	}
}
void obsluga_myszki()
{
	if (Mouse::isButtonPressed(Mouse::Button::Left))
	{
		czy_liczyc = true;
		if ((ktora_bron == 1) &&tajmer == 0)
		{
			if(bronie[ktora_bron-1].zwroc_magazynek()!=0)
			obsluga_pociskow(1);
		}
		if ((ktora_bron == 2) && (tajmer % 12 == 0) && (tajmer != 0))
		{
			if (bronie[ktora_bron - 1].zwroc_magazynek() != 0)
			obsluga_pociskow(2);
		}
		if ((ktora_bron == 3) && (tajmer % 30 == 0)&&(tajmer!=0))
		{
			if (bronie[ktora_bron - 1].zwroc_magazynek() != 0)
			obsluga_pociskow(3);
		}
	}
	
}
void aktualizacja_magazynku()
{
	if (ktora_bron != 3)
	{
		skore.setRotation(0);
		int jednorozec = bronie[ktora_bron - 1].zwroc_magazynek();

		skore.setString("Amunicja: "+std::to_string(jednorozec));
	}
	else
	{
		
		skore.setString("8");
		skore.setRotation(90);
	}

	

}
void zaladuj_elementy()
{
	
	std::vector<std::string> marciny;
	plik.open("mapa.txt", std::ios::in );
	if (!plik.is_open())
	{
		std::cout << " cos nie dziala";
	}
	while (!plik.eof())
	{
		for (int j = 0; j < 14; j++)
			{
			std::string marlena;
				getline(plik,marlena);
				marciny.push_back(marlena);
			}
		for (int j = 0; j < 14; j++)
		{
			Vector2f wspolrzedne(50,25);
			
			for (int i = 0; i < 130; i++)
			{
				if (marciny[j][i] == 'x')
				{
					wspolrzedne.x += 100;
					wspolrzedne.y = 50 * j;
				}
				else if (marciny[j][i] == 'o')
				{
					cPrzeszkody *temp = new cPrzeszkody(wspolrzedne);
					przeszkody.push_back(*temp);
					wspolrzedne.x += 100;
					wspolrzedne.y = 50 * j;
				}
			}
			
			
		}
		
	}
	plik.close();
}
int main()
{
	
	zaladuj_elementy();
	cGracz gracz;
	Texture tlo_gry,tlo_menu;
	tlo_gry.loadFromFile("grafiki/tlo.png");
	tlo_gry.setRepeated(true);
	Sprite tlo_1(tlo_gry);
	tlo_1.setTextureRect(IntRect(0, 0, 16000, 720));
	tlo_menu.loadFromFile("grafiki/menu.png");
	Sprite tlo_2(tlo_menu);	
	srand(time(NULL));
	dodaj_guziki();
	dodaj_muzyke();
	dodawanie_broni();
	dodawanie_punktow();
	
	if (!font.loadFromFile("arial.ttf"))
	{
		//error
	}
	skore.setFont(font);
	skore.setFillColor(Color::Black);
	skore.setCharacterSize(32);
	skore.setStyle(sf::Text::Bold );
	
	hp.setFont(font);
	hp.setFillColor(Color::Red);
	hp.setCharacterSize(32);
	hp.setStyle(sf::Text::Bold);
	window.setFramerateLimit(60);
	while (window.isOpen())
	{
		if (gracz.zwroc_hp() < 0)
		{
			Czy_przegralem = true;
			
		}
		kolizja(gracz);
		int juz4kropka48 = gracz.zwroc_hp();
		hp.setString("HP: "+std::to_string(juz4kropka48));
		

		okno();
		timer();
		pozycja_gracza.x -= pokonana_droga;
		vektor = pozycja_myszy - pozycja_gracza;
		vektor_normal = vektor / sqrt(pow(vektor.x, 2) + pow(vektor.y, 2));
	
		
		pozycja_gracza.x = gracz.zwroc_srodek()[0];
		pozycja_gracza.y = gracz.zwroc_srodek()[1];
		pozycja_myszy.x = Mouse::getPosition(window).x;
		pozycja_myszy.y = Mouse::getPosition(window).y;
		
		//warunki poczatkowe
		sprawdzam_czy_wylaczyc_muzyke();

		
		if (Czy_menu) // sprawdzenie czy menu jest wlaczone
		{
			if (if_muzyka_menu == 0) // odpalanie muzyki
			{
				muzyka_menu.play();
				if_muzyka_menu = 2;
			}
			window.draw(tlo_2); // wyswietlanie tla dla menu
			for (int i = 0; i < 2; i++) // wyswietlanie guzikow
			{
				
				window.draw(guziki[i]);
				//sprawdzamy czy guzik zostal wcisniety 
				if (kolizja_myszki(guziki[i])) 
				{
					
					if (i == 0)
					{
						Czy_menu = false;
						poziom_gry = 1;
						Sleep(100);
					}
					else if (i == 1)
					{
						window.close();
					}
				}
				
			}
			window.display();
		}
					else if (Czy_przegralem == false&&czy_wygralem==false&&poziom_gry==1) // 1 mapa
						{
						if (pokonana_droga < 5000)
						{
							stan_rozgrywki = 1;
						}
						else if (pokonana_droga > 5000 && pokonana_droga < 8000)
						{
							stan_rozgrywki = 2;
						}
						else
						{
							stan_rozgrywki = 3;
						
						}
						if (if_muzyka_map1 == 0)
						{
							muzyka_map1.play();
							muzyka_map1.setPlayingOffset(sf::seconds(20));
							if_muzyka_map1 = 2;
						}
						aktualizacja_magazynku();
						if (ktora_bron != 3)
						{
							skore.setPosition(gracz.zwroc_srodek()[0] - 100, gracz.zwroc_srodek()[1] - 100);
						}
						else
						{
							skore.setPosition(gracz.zwroc_srodek()[0] + 20, gracz.zwroc_srodek()[1] - 100);
						}
						poziom_stopy = gracz.zwroc_srodek()[1] + (gracz.zwroc_rozmiar().y );
						window.clear(sf::Color(0, 0, 0));
						window.draw(tlo_1);
						window.draw(skore);
						window.draw(hp);
						dodaj_przeciwnikow();
						obsluga_broni(gracz);
						Ruch(gracz);
						if (!kolirzyn)
						{
							grawitacyjnie(gracz);
						}
						obsluga_myszki();
						rysuj(gracz);
						kolizja_naboji();
						kolizja_itemkow(gracz);
						
						window.display();
						
						}
					else if(Czy_przegralem)
					{
						Texture tex;
						tex.loadFromFile("grafiki/over.png");
						RectangleShape napis;
						napis.setSize(Vector2f(300,300));
						napis.setPosition(widok.getCenter());
						napis.setOrigin(300 / 2, 300 / 2);
						napis.setTexture(&tex);
						window.clear(sf::Color(0, 0, 0));
						
						window.draw(napis);
						window.display();
					}
					else if (czy_wygralem)
					{
						if (mam_dosyc)
						{
							muzyka_win.play();
							mam_dosyc = false;
						}
						Texture tex;
						tex.loadFromFile("grafiki/winw.jpg");
						RectangleShape napis;
						napis.setSize(Vector2f(1280, 720));
						napis.setPosition(widok.getCenter());
						napis.setOrigin(1280 / 2, 720 / 2);
						napis.setTexture(&tex);
						window.clear(sf::Color(0, 0, 0));
						window.draw(napis);
						window.display();
					}
				
	}

	return 0;
}
