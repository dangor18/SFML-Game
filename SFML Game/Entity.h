#pragma once

#include "Components.h"
#include "Common.h"

class Entity
{
	bool			m_active = true;
	size_t			m_id = 0;
	std::string		m_tag = "default";

public:
	// component pointers
	std::shared_ptr <CTransform>	cTransform;
	std::shared_ptr <CShape>		cShape;
	std::shared_ptr <CCollision>	cCollision;
	std::shared_ptr <CInput>		cInput;
	std::shared_ptr <CScore>		cScore;
	std::shared_ptr <CLifeSpan>		cLifeSpan;

	// constructor and destructor
	Entity(const size_t& id, const std::string& tag);

	bool isActive() const;
	const std::string& tag() const;
	size_t id() const;
	void destroy();
};