#pragma once
#include "CGameObject.h"

/**
 * @brief Child class of CGameObject, used to create missle on screen
 * 
 */
class CMissle : public CGameObject
{
public:
	/**
	 * @brief Construct a new CMissle object
	 * 
	 */
	CMissle();

	/**
	 * @brief Destroy the CMissle object
	 * 
	 */
	~CMissle();
};

