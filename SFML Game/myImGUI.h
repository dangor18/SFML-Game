#pragma once

#include "Common.h"
#include "Entity.h"
#include "EntityManager.h"

class myImGUI
{
	sf::RenderWindow* m_window;
public:
	myImGUI();
	void init(sf::RenderWindow* window, int initialSpawnInterval);
	void update(sf::Clock& deltaClock, EntityManager& m_entities);
	void render();
	void processEvent(sf::Event& event);
	
	// spawn rate
	int m_spawnInterval = 60;
	
	// flags
	bool isLifeSpanActive = true;
	bool isSpawnerActive = true;
	bool isMovementActive = true;
	bool isSpecialActive = true;
	bool isCollisionActive = true;
	bool isRenderActive = true;
};