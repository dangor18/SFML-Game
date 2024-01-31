#include "Game.h"

// constructor takes in config file name
Game::Game(const std::string& config)
{
	// call initializer method
	init(config);
}

// create game window and store config data
void Game::init(const std::string& path)
{
	//Read in the config file 
	std::fstream fin{ path };

	if (!fin.is_open())
	{
		std::cout << "Failed to open: " << path << std::endl;
		exit(-1);
	}

	std::string identifier;
	while (fin >> identifier)
	{
		// load window parameters
		if (identifier == "Window")
		{
			unsigned int width, height;
			fin >> width;
			fin >> height;

			unsigned int frameLimit, fullScreen;
			fin >> frameLimit;
			fin >> fullScreen;

			if (fullScreen == 0)
			{
				m_window.create(sf::VideoMode(width, height), "Geometry Wars", sf::Style::Close);
				m_window.setFramerateLimit(frameLimit);
			}
			else if (fullScreen == 1)
			{
				auto fullscreenMode{ sf::VideoMode::getFullscreenModes() };
				//fullscreenMode[0] is the most compatible mode for fullscreen on this device
				m_window.create(fullscreenMode[0], "Geometry Wars", sf::Style::Fullscreen);
				m_window.setFramerateLimit(frameLimit);
			}
		}
		// load and set font and text parameters for displaying the score
		else if (identifier == "Font")
		{
			std::string filepath;
			fin >> filepath;
			if (!m_font.loadFromFile(filepath))
			{
				std::cerr << "Failed to load font. Filepath: " << filepath;
			}

			m_text.setFont(m_font);

			int fontSize;
			fin >> fontSize;
			m_text.setCharacterSize(fontSize);

			sf::Vector3<sf::Uint16> RGB;
			fin >> RGB.x;
			fin >> RGB.y;
			fin >> RGB.z;
			m_text.setFillColor(sf::Color(RGB.x, RGB.y, RGB.z));
		}
		else if (identifier == "Player")
		{
			// raidii
			fin >> m_playerConfig.SR;
			fin >> m_playerConfig.CR;

			// speed
			fin >> m_playerConfig.S;

			// fill
			fin >> m_playerConfig.FR;
			fin >> m_playerConfig.FG;
			fin >> m_playerConfig.FB;

			// outline
			fin >> m_playerConfig.OR;
			fin >> m_playerConfig.OG;
			fin >> m_playerConfig.OB;
			fin >> m_playerConfig.OT;

			// vertices
			fin >> m_playerConfig.V;
		}
		else if (identifier == "Enemy")
		{
			fin >> m_enemyConfig.SR;
			fin >> m_enemyConfig.CR;

			fin >> m_enemyConfig.SMIN;
			fin >> m_enemyConfig.SMAX;

			fin >> m_enemyConfig.OR;
			fin >> m_enemyConfig.OG;
			fin >> m_enemyConfig.OB;
			fin >> m_enemyConfig.OT;

			fin >> m_enemyConfig.VMIN;
			fin >> m_enemyConfig.VMAX;

			fin >> m_enemyConfig.L;

			fin >> m_spawnInterval;
		}
		else if (identifier == "Bullet")
		{
			fin >> m_bulletConfig.SR;
			fin >> m_bulletConfig.CR;

			fin >> m_bulletConfig.S;

			// fill
			fin >> m_bulletConfig.FR;
			fin >> m_bulletConfig.FG;
			fin >> m_bulletConfig.FB;

			// outline
			fin >> m_bulletConfig.OR;
			fin >> m_bulletConfig.OG;
			fin >> m_bulletConfig.OB;
			fin >> m_bulletConfig.OT;

			fin >> m_bulletConfig.V;

			fin >> m_bulletConfig.L;

			// special 
			fin >> m_bulletConfig.S;
		}
	}

	m_text.setPosition(0, 0);
	m_text.setString(std::to_string(score));

	spawnPlayer();
}

void Game::run()
{
	// TODO: add pause functionality here

	// while the game is running = true...
	while (m_running)
	{
		///if (!m_paused)
		// update entity manager
		m_entities.update();
		// call systems
		sEnemySpawner();
		sMovement();
		sCollision();
		sUserInput();
		sRender();

		m_currentFrame++;
	}
}

void Game::setPaused(bool paused)
{
	m_paused = paused;
}

// respawn player in the middle of the screen
void Game::spawnPlayer()
{
	// TODO: player properties from config
	
	// create entitiy with player tag
	auto entity = m_entities.addEntity("player");
	// give a transform to define spawn position, velocity and angle
	entity->cTransform = std::make_shared<CTransform>(Vec2(200.0f, 200.0f), Vec2(1.0f, 1.0f), 0.0f);

	// add shape component
	entity->cShape = std::make_shared<CShape>(32.0f, 8, sf::Color(10, 10, 10), sf::Color(255, 0, 0), 4.0f);

	// add input component
	entity->cInput = std::make_shared<CInput>();

	m_player = entity;
}

void Game::spawnEnemy()
{
	// TODO: config ...

	// TODO: SPAWN AND PREVENT OVERLAP WITH WINDOW using radius and random range
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	// TODO: ...
	
	float angle = 360.0f / e->cShape->circle.getPointCount();
	// How do we get the small enemies vec2 for velocity using enemy speed and angle
	for (int i = 0; i < e->cShape->circle.getPointCount(); i++)
	{
		auto entity = m_entities.addEntity("smallenemy");
		// parameters
		angle += angle;
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
	// TODO: ...
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// TODO: ...
}

void Game::sMovement()
{
	// TODO: Incorporate ALL entity movemement

	m_player->cTransform->pos += m_player->cTransform->velocity;
}

void Game::sLifespan()
{
	// TODO:
	// for all entities, if it has a lifespan and is alive
	// scale its alpha channel (linearly with lifespan)
	// if alive and lifespan is up then destroy

	for (auto e : m_entities.getEntities())
	{
		if (e->cLifeSpan)
		{
			int remaining = e->cLifeSpan->lifespan - e->cLifeSpan->frameCreated;

			if (remaining <= 0)
			{
				e->destroy();
			}
			else
			{
				//1:25
			}
		}
	}
}

void Game::sCollision()
{
	// TODO: use collision radius not shape radius

	for (auto e : m_entities.getEntities("enemy"))
	{
		// if collision between e and player, spawnPlayer and destroy enemy
	}

	for (auto e : m_entities.getEntities("smallenemy"))
	{
		// if collision between e and player, spawnPlayer and destroy enemy
	}

	for (auto e : m_entities.getEntities("bullet"))
	{
		for (auto e : m_entities.getEntities("enemy"))
		{
			
		}

		for (auto e : m_entities.getEntities("smallenemy"))
		{
			
		}
	}
}

void Game::sEnemySpawner()
{
	// TODO: Count number of frames since last spawning an enemy, spawn and then reset
}

void Game::sRender()
{
	m_window.clear();

	for (auto e : m_entities.getEntities())
	{
		if (e->cTransform && e->cShape)
		{
			// set the shapes position to the entities transform->pos
			e->cShape->circle.setPosition(e->cTransform->pos.x, e->cTransform->pos.y);

			// set the rotation of the shape to the entities transform->angle
			e->cTransform->angle += 1.0f;
			e->cShape->circle.setRotation(e->cTransform->angle);

			// draw the entities sf::Circle shape
			m_window.draw(e->cShape->circle);
		}
		m_window.display();
	}
}

void Game::sUserInput()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			// setting this to false will terminate the run() function
			m_running = false;
		}

		// manage key press events
		if (event.type == sf::Event::KeyPressed)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				// TODO set player input component to true
				break;
			case sf::Keyboard::A:
				// TODO
				break;
			case sf::Keyboard::S:
				// TODO
				break;
			case sf::Keyboard::D:
				// TODO
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				// TODO set player input component to false
				break;
			case sf::Keyboard::A:
				// TODO
				break;
			case sf::Keyboard::S:
				// TODO
				break;
			case sf::Keyboard::D:
				// TODO
				break;
			}
		}

		if (event.type == sf::Event::MouseButtonPressed)
		{
			if (event.mouseButton.button == sf::Mouse::Left)
			{
				// spawn bullet
				spawnBullet(m_player, Vec2(event.mouseButton.x, event.mouseButton.y));
			}

			if (event.mouseButton.button == sf::Mouse::Right)
			{
				// spawn special weapon 
			}
		}
	}
}