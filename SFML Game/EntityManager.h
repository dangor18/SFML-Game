#pragma once

#include "Common.h"
#include "Entity.h"

typedef std::vector<std::shared_ptr<Entity>> EntityVec;

class EntityManager {
	EntityVec							m_entities;
	EntityVec							m_entitiesToAdd;
	std::map<std::string, EntityVec>	m_entityMap;	// map entity tag to list of entities
	size_t								m_totalEntities = 0;

	void removeDeadEntities(EntityVec & vec);

public:
	EntityManager();

	void update();

	std::shared_ptr<Entity> addEntity(const std::string& tag);

	EntityVec& getEntities();							// return all entities
	EntityVec& getEntities(const std::string& tag);		// return entities of a certain tag
};