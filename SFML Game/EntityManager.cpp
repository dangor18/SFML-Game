#include "EntityManager.h"

// helper function to remove dead entities from a given vector
void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// delete from vec
	std::erase_if(vec, [](auto& e) { return !e->isActive(); });
}

EntityManager::EntityManager()
{

}


void EntityManager::update()
{
	removeDeadEntities(m_entities);

	for (auto & [tag, entityVec] : m_entityMap)
	{
		removeDeadEntities(entityVec);
	}

	// add entities to vec and map
	for (auto& e : m_entitiesToAdd)
	{
		m_entities.push_back(e);
		m_entityMap[e->getTag()].push_back(e);
	}

	m_entitiesToAdd.clear();
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