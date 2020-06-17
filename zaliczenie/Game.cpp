#include "Game.h"

void Game::initVariables()
{
	this->endGame = false;
	this->spawnTimerMax = 10.f;
	this->spawnTimer = this->spawnTimerMax;
	this->max_liczba_kulek = 30;
	this->points = 0;
}

void Game::initWindow()
{
	this->videoMode = sf::VideoMode(1280, 720);													//VideoMode::getDesktopMode(); to bêdzie pobieranie rozdzielczoœci monitora
	this->window = new sf::RenderWindow(this->videoMode, "Projekt zaliczeniowy c++", sf::Style::Close | sf::Style::Titlebar);					//nazwa gry na górnej listwie
	this->window->setFramerateLimit(60);																						//limit fpsów w grze
}

void Game::initFonts()					//do³¹czanie fontu
{
	if (!this->font.loadFromFile("Fonts/PixellettersFull.ttf"))
	{
		std::cout << "!!! Blad ladowania fontu !!!" << "\n";					//perror ladowania fontu
	}
}

void Game::initText()
{
	//inicjalizowanie tekstu
	this->guiText.setFont(this->font);
	this->guiText.setFillColor(sf::Color::Blue);
	this->guiText.setCharacterSize(32);

	//inicjalizowanie tekstu koñca gry
	this->endGameText.setFont(this->font);
	this->endGameText.setFillColor(sf::Color::Red);
	this->endGameText.setCharacterSize(110);
	this->endGameText.setPosition(sf::Vector2f(170, 300));			//pozycja tekstu na ekranie
	this->endGameText.setString("Przyszla kryska na matyska!");						//napisz koñca gry
}

//konstruktory i dekonstruktory
Game::Game()
{
	this->initVariables();
	this->initWindow();
	this->initFonts();
	this->initText();
}

Game::~Game()
{
	delete this->window;
}

const bool & Game::getEndGame() const
{
	return this->endGame;
}

//Funkcje
const bool Game::running() const
{
	return this->window->isOpen();
}

void Game::pollEvents()						//klawisz "esc" wychodzi z gry
{
	while (this->window->pollEvent(this->sfmlEvent))
	{
		switch (this->sfmlEvent.type)
		{
		case sf::Event::Closed:
			this->window->close();
			break;
		case sf::Event::KeyPressed:
			if (this->sfmlEvent.key.code == sf::Keyboard::Escape)
				this->window->close();
			break;
		}
	}
}

void Game::spawnowanie_kulek()				//pojawianie siê nowych kulek na ekranie
{
	//Timer
	if (this->spawnTimer < this->spawnTimerMax)
		this->spawnTimer += 1.f;
	else
	{
		if (this->kuleczki.size() < this->max_liczba_kulek)		//warunek, ¿e iloœæ kulek naraz na ekranie nie przekroczy zmiennej, w tym wypadku 30
		{
			this->kuleczki.push_back(kulki(*this->window, this->losowy_typ_kulki()));					//przy spawnowaniu kulek beda pojawiac sie losowe typy

			this->spawnTimer = 0.f;
		}	
	}
}

const int Game::losowy_typ_kulki() const				//procenty jakie okreœlaj¹ kiedy jaki typ kulki siê pojawia
{
	int type = rodzaje_kulek::DEFAULT;
	
	int randValue = rand() % 100 + 1;			//procenty 1-100 na spawn kulki
	if (randValue > 60 && randValue <= 90)		//jezeli numerek jaki sie wylosuje jest w przedziale 61-90 to kulka bedzie z³a
		type = rodzaje_kulek::DAMAGING;
	else if (randValue > 90 && randValue <= 100)			//jezeli wylosowana liczba jest w przedziale 90-100 to kulka bêdzie leczyæ
		type = rodzaje_kulek::HEALING;

	return type;
}

void Game::updatePlayer()				//sprawdza czy gracz zyje, ¿eby zakoñczyæ grê
{
	this->player.update(this->window);

	if (this->player.getHp() <= 0) {
		this->endGame = true;
		
		std::string wyjatek = "Hp mniej niz zero";				//Tworzenie wyjatku
		throw wyjatek;

		}
}

void Game::updateCollision()		//funkcja sprawdzaj¹ca jaka kulka zosta³a dotkniêta
{
	//Check the collision
	for (size_t i = 0; i < this->kuleczki.size(); i++)						//iterowanie przez wszystkie kulki
	{
		if (this->player.getShape().getGlobalBounds().intersects(this->kuleczki[i].getShape().getGlobalBounds()))		//sprawdzanie, czy gracz dotkn¹³ kulki
		{
			switch (this->kuleczki[i].getType())
			{
			case rodzaje_kulek::DEFAULT:					//dodawanie punktow za zbijanie kulek
				this->points++;
				break;
			case rodzaje_kulek::DAMAGING:					//to jest typ kulek który zabiera hp graczowi
				this->player.dodaj_DMG(1);
				break;
			case rodzaje_kulek::HEALING:					//to jest typ kulek który dodaje hp graczowi
				this->player.dodaj_HP(1);
				break;
			}

						//Iterator STL
			this->kuleczki.erase(this->kuleczki.begin() + i);			//to usuwa zabite kulki z mapy, begin to iterator zaczynaj¹cy od 0, który sprawdza korzystaj¹c z "i" któr¹ kulkê nale¿y usun¹æ 
		}
	}	
}

//funkcja która aktualizuje napisy z aktualnymi punktami i HP
void Game::updateGui()
{
	std::stringstream ss;

	ss << " Punkty: " << this->points << "\n"																	//pokazuje w lewym gornym rogu ile mamy ¿ycia i puntków  
		<< " HP: " << this->player.getHp() << " / " << this->player.getHpMax() << "\n";

	this->guiText.setString(ss.str());
}

//funkcja która aktualizuje to co dzieje siê na mapie
void Game::update()
{
	this->pollEvents();

	if (this->endGame == false)				//wyœwietlanie tekstu kiedy przegra siê gre, wtedy gra nie potrzebuje update'a
	{
		this->spawnowanie_kulek();
		this->updatePlayer();
		this->updateCollision();
		this->updateGui();
		
		try										//Wyjatki
		{
			this->updatePlayer();
		}

		catch (std::string w)
		{
			std::cout << "Wyjatek: " << w;
			this->endGame = true;
		}

	}

	
}

void Game::renderGui(sf::RenderTarget* target)
{
	target->draw(this->guiText);
}

void Game::render()
{
	this->window->clear();					//czyszczenie poprzedniej klatki

	//Render stuff
	this->player.render(this->window);

	//Zakresowa pêtla for
	for (auto i : this->kuleczki)
	{
		i.render(*this->window);
	}

	//Render gui
	this->renderGui(this->window);

	//Render end text									//Pokazuje poœmiertny tekst na ekranie 
	if(this->endGame == true)
		this->window->draw(this->endGameText);

	this->window->display();
}