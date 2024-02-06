#include "myImGUI.h"

myImGUI::myImGUI()
{}

void myImGUI::init(sf::RenderWindow& window, int spawnInterval)
{
	m_window = std::make_shared<sf::RenderWindow>(window);

}