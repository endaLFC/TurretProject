#pragma once
class Energy
{
public:
	static Energy* GetInstance();
	~Energy();
	void Initialise();
	void Draw(sf::RenderWindow &window);

private:
	Energy()
	{ 
		
	}
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f m_pos;

	static bool instanceFlag;
	static Energy* instance;
};

