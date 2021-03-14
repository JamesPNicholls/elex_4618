#pragma once
#include "CGameObject.h"

/**
 * @brief Child class off GameObject, used to draw the ship on screen
 * 
 */
class CShip : public CGameObject
{
public:
	/**
	 * @brief Construct a new CShip object
	 * 
	 */
	CShip();

	/**
	 * @brief Destroy the CShip object
	 * 
	 */
	~CShip();
};

