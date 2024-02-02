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
	m_text.setString("Score: " + score);

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
	// create entitiy with player tag
	auto entity = m_entities.addEntity("player");
	// give a transform to define spawn position, velocity and angle
	int width = m_window.getSize().x;
	int height = m_window.getSize().y;
	entity->cTransform = std::make_shared<CTransform>(Vec2(width / 2, height / 2), Vec2(0, 0), 0.0f);

	// add shape component
	entity->cShape = std::make_shared<CShape>(m_playerConfig.SR, m_playerConfig.V, sf::Color(m_playerConfig.FR, m_playerConfig.FG, m_playerConfig.FB),
		sf::Color(m_playerConfig.OR, m_playerConfig.OG, m_playerConfig.OB), m_playerConfig.OT);

	// add input component
	entity->cInput = std::make_shared<CInput>();

	// give collision component
	entity->cCollision = std::make_shared<CCollision>(m_playerConfig.CR);

	// store player entity
	m_player = entity;
}

void Game::spawnEnemy()
{
	auto entity = m_entities.addEntity("enemy");

	int maxPosX = (m_window.getSize().x - m_enemyConfig.SR) - m_enemyConfig.SR;
	// getting a random x value within [SR, m_window.width - SR]
	int xRand = rand() % (1 + m_enemyConfig.SR - maxPosX) + m_enemyConfig.SR;

	int maxPosY = (m_window.getSize().y - m_enemyConfig.SR) - m_enemyConfig.SR;
	// getting a random x value within [SR, m_window.height - SR]
	int yRand = rand() % (1 + m_enemyConfig.SR - maxPosY) + m_enemyConfig.SR;
	
	int diff = 1 + m_enemyConfig.VMAX - m_enemyConfig.VMIN;
	// getting a random number of vertices within [VMIN, VMAX]
	int vRand = rand() % diff + m_enemyConfig.VMIN;

	// random colours
	int rRand = rand() % (1 + 255), gRand = rand() % (1 + 255), bRand = rand() % (1 + 255);

	// random speed
	int sRand = rand() % (1 + (int)m_enemyConfig.SMAX - (int)m_enemyConfig.SMIN) + m_enemyConfig.SMIN;

	// add shape component
	entity->cShape = std::make_shared<CShape>(m_enemyConfig.SR, vRand, sf::Color(rRand, gRand, bRand),
		sf::Color(m_enemyConfig.OR, m_enemyConfig.OG, m_enemyConfig.OB), m_enemyConfig.OT);

	// give collision component
	entity->cCollision = std::make_shared<CCollision>(m_enemyConfig.CR);

	// randomized vec
	Vec2 vec = Vec2(rand() % (1 + 100 + 100) - 100, rand() % (1 + 100 + 100) - 100);
	vec.normalize();
	// transform
	entity->cTransform = std::make_shared<CTransform>(Vec2(xRand, yRand), vec * sRand, 0.0f);

	// score
	entity->cScore = std::make_shared<CScore>(vRand * 100);
}

void Game::spawnSmallEnemies(std::shared_ptr<Entity> e)
{
	float angle = 360.0f / e->cShape->circle.getPointCount();
	// How do we get the small enemies vec2 for velocity using enemy speed and angle
	for (int i = 0; i < e->cShape->circle.getPointCount(); i++)
	{
		auto entity = m_entities.addEntity("smallenemy");
		
		// get large enemy shape by making a copy
		sf::CircleShape largeShape =  e->cShape->circle;
		// add shape component
		entity->cShape = std::make_shared<CShape>(0.2 * m_enemyConfig.SR, largeShape.getPointCount(), largeShape.getFillColor(),
			largeShape.getOutlineColor(), 0.2 * m_enemyConfig.OT);

		// give collision component
		entity->cCollision = std::make_shared<CCollision>(0.2 * m_enemyConfig.CR);

		// transform
		entity->cTransform = std::make_shared<CTransform>(Vec2(std::cosf(angle), std::sinf(angle)), e->cTransform->pos, 0.0f);

		// score
		entity->cScore = std::make_shared<CScore>(e->cScore->score * 200);

		// lifespan
		entity->cLifeSpan = std::make_shared<CLifeSpan>(m_enemyConfig.L, m_currentFrame);

		angle += angle;
	}
}

void Game::spawnBullet(std::shared_ptr<Entity> entity, const Vec2 & target)
{
	// create entitiy with bullet tag
	auto bullet = m_entities.addEntity("bullet");

	// give a transform to define spawn position, velocity and angle
	// note starting position equals that of entities


	Vec2 difference(target.x - entity->cTransform->pos.x, target.y - entity->cTransform->pos.y);
	// normalize vector to set scalar to 1
	difference.normalize();

	Vec2 velocity(m_bulletConfig.S * difference.x, m_bulletConfig.S * difference.y);

	bullet->cTransform = std::make_shared<CTransform>(entity->cTransform->pos, velocity, 0);

	// add shape component
	bullet->cShape = std::make_shared<CShape>(m_bulletConfig.SR, m_bulletConfig.V, sf::Color(m_bulletConfig.FR, m_bulletConfig.FG, m_bulletConfig.FB),
		sf::Color(m_bulletConfig.OR, m_bulletConfig.OG, m_bulletConfig.OB), m_bulletConfig.OT);

	// give collision component
	bullet->cCollision = std::make_shared<CCollision>(m_bulletConfig.CR);

	// give lifespan to fade away
	bullet->cLifeSpan = std::make_shared<CLifeSpan>(m_bulletConfig.L, m_currentFrame);
}

void Game::spawnSpecialWeapon(std::shared_ptr<Entity> entity)
{
	// TODO: ...
}

void Game::sMovement()
{
	//	player movement
	if (m_player->cInput->up)
		m_player->cTransform->pos.y -= m_playerConfig.S;

	if (m_player->cInput->down)
		m_player->cTransform->pos.y += m_playerConfig.S;

	if (m_player->cInput->left)
		m_player->cTransform->pos.x -= m_playerConfig.S;

	if (m_player->cInput->right)
		m_player->cTransform->pos.x += m_playerConfig.S;

	// move all other entities
	for (auto e : m_entities.getEntities())
	{
		e->cTransform->pos += e->cTransform->velocity;
	}
}

void Game::sLifespan()
{
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
				// adjust gamma channel
				int r = e->cShape->circle.getFillColor().r;
				int g = e->cShape->circle.getFillColor().g;
				int b = e->cShape->circle.getFillColor().b;
				int alpha = e->cShape->circle.getFillColor().a;
				auto fill = sf::Color(r, g, b, alpha);
				e->cShape->circle.setFillColor(fill);
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
	// when timer hits spawn an enemy
	if (m_currentFrame % m_spawnInterval == 0)
	{
		spawnEnemy();
	}
}

void Game::sRender()
{
	m_window.clear(); // clear the window at the start

	m_text.setString("Score: " + std::to_string(score));
	m_window.draw(m_text);

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
	}

	m_window.display(); // update the window display here, after all entities have been drawn
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
				m_player->cInput->up = true;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = true;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = true;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = true;
				break;
			}
		}

		if (event.type == sf::Event::KeyReleased)
		{
			switch (event.key.code)
			{
			case sf::Keyboard::W:
				m_player->cInput->up = false;
				break;
			case sf::Keyboard::A:
				m_player->cInput->left = false;
				break;
			case sf::Keyboard::S:
				m_player->cInput->down = false;
				break;
			case sf::Keyboard::D:
				m_player->cInput->right = false;
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