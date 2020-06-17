#include "Player.h"



void Player::initVariables()
{
	this->movementSpeed = 3.f;				//pr�dko�� z jak� porusza si� gracz
	this->hpMax = 10;				//pocz�tkowe �ycie z jakim startuje gracz
	this->hp = hpMax;		//pocz�tkowe �ycie z jakim startuje gracz
}

void Player::initShape()
{
	this->kolka_z_punktami.setFillColor(sf::Color::Green);
	this->kolka_z_punktami.setSize(sf::Vector2f(50.f, 50.f));				//mo�na ustawi� wiele innych rzeczy, this->kolka_z_punktami."reszta"
}

Player::Player(float x, float y)
{
	this->kolka_z_punktami.setPosition(x, y);				//ustawia pozycj� pocz�tkow� gracza - lewy g�rny r�g

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}

//Accessors
const sf::RectangleShape & Player::getShape() const
{
	return this->kolka_z_punktami;
}

const int & Player::getHp() const
{
	return this->hp;
}

const int & Player::getHpMax() const
{
	return this->hpMax;
}

//Functions
void Player::dodaj_DMG(const int damage)						//zabieranie hp przez kulki
{
	if (this->hp > 0)					//kiedy mamy jeszcze hp do stracenia to traci to hp
		this->hp -= damage;

	if (this->hp < 0)					//kiedy giniemy to hp nie spada poni�ej 0, tylko niech zostaje na 0
		this->hp = 0;
}

void Player::dodaj_HP(const int health)
{
	if (this->hp < this->hpMax)				//kiedy nie mamy pelnego �ycia to jest ono uzupe�niane
		this->hp += health;

	if (this->hp > this->hpMax)				//je�eli mamy pe�ne �ycie to nie ma co uzupe�ni�, wi�c zostaje takie samo
		this->hp = this->hpMax;
}

void Player::updateInput()
{
	//Keyboard input
	//Left
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
	{
		this->kolka_z_punktami.move(-this->movementSpeed, 0.f);						//move vs. setPosition - pierwsze bierze aktualn� pozycj� gracza i przesuwa go na nowe miejsce - drugie sztywno ustawia
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))					//else if zamiast if, poniewa� A i D nie wciska si� razem, nie ma to sensu, dlatego jest to wykluczone. Np. W i A ju� mo�na, �eby i�� na skos
	{
		this->kolka_z_punktami.move(this->movementSpeed, 0.f);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
	{
		this->kolka_z_punktami.move(0.f, -this->movementSpeed);
	}
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))				//ponowne wykluczanie wciskania naraz W i S
	{
		this->kolka_z_punktami.move(0.f, this->movementSpeed);
	}
}

void Player::updateWindowBoundsCollision(const sf::RenderTarget * target)
{
	//Left
	if (this->kolka_z_punktami.getGlobalBounds().left <= 0.f)
		this->kolka_z_punktami.setPosition(0.f, this->kolka_z_punktami.getGlobalBounds().top);					//getGlobalBounds odnosi si� do kopii
	//Right
	else if (this->kolka_z_punktami.getGlobalBounds().left + this->kolka_z_punktami.getGlobalBounds().width >= target->getSize().x)								//nie da si� wyj�� graczem naraz poza lew� i praw� stron� mapy
		this->kolka_z_punktami.setPosition(target->getSize().x - this->kolka_z_punktami.getGlobalBounds().width, this->kolka_z_punktami.getGlobalBounds().top);				//pozorne sprawdzanie prawej strony, "+" po to, �eby wzi�� szeroko�� gracza. Inaczej zatrzyma�oby si� dopiero wtedy kiedy lewa kraw�d� gracza wyjdzie poza map�
	//Top
	if (this->kolka_z_punktami.getGlobalBounds().top <= 0.f)
		this->kolka_z_punktami.setPosition(this->kolka_z_punktami.getGlobalBounds().left, 0.f);
	//Bottom
	else if (this->kolka_z_punktami.getGlobalBounds().top + this->kolka_z_punktami.getGlobalBounds().height >= target->getSize().y)							//ponownie pozorne sprawdzanie do�u mapy, poniewa� znowu gracz zatrzyma�by si� jak g�rna kraw�d� dotknie granicy mapy
		this->kolka_z_punktami.setPosition(this->kolka_z_punktami.getGlobalBounds().left, target->getSize().y - this->kolka_z_punktami.getGlobalBounds().height);		
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::render(sf::RenderTarget * target)
{
	target->draw(this->kolka_z_punktami);
}
