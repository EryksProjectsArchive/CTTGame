//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/models/ModelLib.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "ModelLib.h"

#include <graphics/Model.h>
#include <core/DynString.h>

#include <io/fs/FileSystem.h>

#include <graphics/ModelFormat.h>

ModelLib::ModelLib()
{

}

ModelLib::~ModelLib()
{
	for (Model *model : m_models)
		delete model;

	m_models.clear();
}

Model * ModelLib::findByName(const DynString& name)
{	
	for (Model *model : m_models)
	{
		if (model->m_name == name)
			return model;
	}

	Model *model = 0;
	FilePath path("models/%s.mdl", name.get());
	File *file = FileSystem::get()->open(path, FileOpenMode::Read | FileOpenMode::Binary);
	if (file->isLoaded())
	{
		mdl m;
		file->read(&m, 1, sizeof(mdl) - sizeof(m.meshes));
		if (!memcmp(m.id, "CTTMDL", 6) && m.version == 1)
		{
			model = new Model(name, path);
			m_models.pushBack(model);
		}
		else
		{			
			Info("ModelLib", "Cannot load %s. (Version: %X)", name.get(), m.version);
		}
	}
	FileSystem::get()->close(file);

	if (!model)
	{
		Error("ModelLib", "Unable to find model '%s'!.", name.get());
	}

	return model;
}