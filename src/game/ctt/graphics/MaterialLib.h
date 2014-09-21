//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/MaterialLib.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <core/Singleton.h>
#include <core/DynString.h>
#include <core/List.h>

#include "Material.h"
#include <list>

class MaterialLib : public Singleton<MaterialLib>
{
private:
	List<SharedPtr<Material>> m_materials;
public:
	MaterialLib();
	~MaterialLib();

	SharedPtr<Material> findByName(DynString name);	
};