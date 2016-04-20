#pragma once
class Notification
{
public:
	Notification();
	~Notification();
	void Initialise();
	void Draw(sf::RenderWindow& window);
	void Update(float time);
	

private:
	sf::Vector2f m_position;
	sf::Vector2f m_textPosition;
	sf::Sprite m_sprite;
	sf::Texture m_texture;
	sf::Font font;
	sf::Text text;
	bool m_alive;
	bool inPosition;
	float waitTime;

	sf::SoundBuffer buffer;
	sf::Sound sound;
};

