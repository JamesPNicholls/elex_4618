#pragma once
#include "CGameObject.h"
/**
 * @brief Child class of CGameObject, used to generate and asteroid circle on screen
 * 
 */
class CAsteroid : public CGameObject
{
public: 
	/**
	 * @brief Construct a new CAsteroid object
	 * 
	 */
	CAsteroid();

	/**
	 * @brief Destroy the CAsteroid object
	 * 
	 */
	~CAsteroid();
};

