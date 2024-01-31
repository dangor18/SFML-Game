#include "EntityManager.h"

// helper function to remove dead entities from a given vector
void EntityManager::removeDeadEntities(EntityVec& vec)
{
	// TODO use this or removeif (lambda)
	for (auto e : vec)
	{
		// this is the sign of an entity we want to remove 
		if (!e->isActive())
		{
			//remove e from vec
		}
	}
}

EntityManager::EntityManager()
{

}


void EntityManager::update()
{
	// TODO: add entities from m_entitiesToAdd the the proper location(s)
	// TODO: clean up dead entities from all entities as well as the map vectors


	// how to iterate through map in c++
	for (auto& kv : m_entityMap)
	{
		kv.first;	// this will be the tag
		kv.second;	// this will be vector
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