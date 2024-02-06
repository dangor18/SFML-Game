#pragma once

#include "Common.h"
class myImGUI
{
	sf::RenderWindow* m_window;
	int m_spawnInterval = 999999;
public:
	myImGUI();
	void init(sf::RenderWindow* window, int initialSpawnInterval);
	void update(sf::Clock& deltaClock);
	void render();
	void processEvent(sf::Event& event);

	bool isLifeSpanActive{ true };
	bool isSpawnerActive{ true };
	bool isMovementActive{ true };
	bool isSpecialShootActive{ true };
	bool isCollisionActive{ true };
	bool isRenderActive{ true };
	bool isGuiActive{ true };
};