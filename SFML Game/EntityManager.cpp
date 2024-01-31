#include "EntityManager.h"

bool isActive(std::shared_ptr<Entity> e) { return !e->isActive(); }

// helper function to remove dead entities from a given vector
void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// delete from vec
	std::remove_if(m_entities.begin(), m_entities.end(), isActive);

	// delete from map
	for (auto& kv : m_entityMap)
	{
		std::remove_if(m_entityMap[kv.first].begin(), m_entityMap[kv.first].end(), isActive);
	}
}

EntityManager::EntityManager()
{

}


void EntityManager::update()
{
	removeDeadEntities(m_entities);

	// add entities to vec and map
	for (auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}
}

std::shared_ptr<Entity> EntityManager::addEntity(const std::string& tag)
{
	// create the entity shared pointer
	auto entity = std::shared_ptr<Entity>(new Entity(m_totalEntities++, tag));

	m_entitiesToAdd.push_back(entity);
	return entity;
}


EntityVec& EntityManager::getEntities()
{
	return m_entities;
}
	
EntityVec& EntityManager::getEntities(const std::string& tag)
{
	return m_entityMap[tag];
}