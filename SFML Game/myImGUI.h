#pragma once

#include "Common.h"
class myImGUI
{
	std::shared_ptr<sf::RenderWindow> m_window;
	int m_spawnInterval;
public:
	myImGUI();
	void init(sf::RenderWindow & window, int spawnInterval);
	void update(sf::Clock & deltaClock);
	void processEvent(sf::Event event);
	void render();
};