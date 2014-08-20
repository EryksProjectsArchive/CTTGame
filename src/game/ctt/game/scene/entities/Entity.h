//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: game/scene/entities/Entity.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/DynString.h>

class Entity
{
private:
	/**
	* @name: m_nae
	* @type: DynString
	* Hashed name of entity
	*/
	DynString m_name;

	/**
	* @name: m_hashedName
	* @type: unsigned int
	* Hashed name of entity.
	*/
	unsigned int m_hashedName;
public:
	/**
	* @name: Entity
	* Constructor of entity class.
	* @param: name of entity (String<32>)
	*/
	Entity(String<32> name);

	/**
	* @name: ~Entity
	* Destructor of entity class.
	*/
	virtual ~Entity();

	/**
	* @name: getName
	* This function returns name of entity
	* @return: name of entity (DynString)
	*/
	virtual DynString getName();

	/**
	 * @name: getHashedName
	 * This function returns hashed name of entity. We are using Jenkins Hash to hash names.
	 * It may be used to faster searching throught entities tree via name.
	 * @return: hashed name (unsigned int)
	 */
	virtual unsigned int getHashedName();

	/**
	* @name: render
	* This function is called from Scene when whole scene is rendered.
	* @param: render context (RenderContext)
	*/
	virtual void render();

	/**
	* @name: physicsUpdate
	* This function is when is updated.
	* @param: render context (RenderContext)
	*/
	virtual void updatePhysics();
};