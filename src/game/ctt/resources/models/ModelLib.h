//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/models/ModelLib.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <resources/ResourceLib.h>
#include <core/Singleton.h>
#include <core/List.h>

class ModelLib : public ResourceLib<Model>, public Singleton<ModelLib>
{
private:
	List<Model *> m_models;
public:
	ModelLib();
	~ModelLib();

	Model * findByName(const DynString& name) override;
};