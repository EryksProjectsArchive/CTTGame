//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/MaterialLib.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "MaterialLib.h"

#include <core/Logger.h>

#include <json/json.h>

#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/VertexShader.h>
#include <graphics/FragmentShader.h>
#include <graphics/ShaderProgram.h>

#include <io/fs/FileSystem.h>

MaterialLib::MaterialLib()
{

}

MaterialLib::~MaterialLib()
{
	m_materials.clear();
}

SharedPtr<Material> MaterialLib::findByName(DynString name)
{
	for (SharedPtr<Material> mat : m_materials)
	{
		if (mat->m_name == name)
			return mat;
	}

	SharedPtr<Material> material;
	File *file = FileSystem::get()->open(FilePath("materials/%s.json", *name), FileOpenMode::Read);
	if (file->isLoaded())
	{
		DynString content = file->getContent();
		Json::Value root;
		Json::Reader reader;

		if (reader.parse(content.get(), root))
		{
			material = SharedPtr<Material>(new Material(name));

			if (!root["texture"].empty() && !root["texture"]["name"].empty())
			{
				material->m_texture = SharedPtr<Texture>(new Texture(FilePath("../../data/textures/%s", root["texture"]["name"].asCString()), !root["texture"]["mipMaps"] ? false : root["texture"]["mipMaps"].asBool()));
				material->m_texture->acquire(); // Acquire texture into material - we are calling free when material is being removed
			}
			else
				Warning("MatLib", "Material %s has no textures set.", *name);

			material->m_program = SharedPtr<ShaderProgram>(new ShaderProgram());

			if (root["shaders"].empty())
			{
				Warning("MatLib", "Material %s has no shaders set.", *name);
			}
			else
			{
				if (!root["shaders"]["vertex"].empty())
					material->m_program->attachShader(new VertexShader(FilePath("../../data/shaders/%s.vert", root["shaders"]["vertex"].asCString())));
				else
					Warning("MatLib", "Material %s has no vertex shader set.", *name);

				if (!root["shaders"]["fragment"].empty())
					material->m_program->attachShader(new FragmentShader(FilePath("../../data/shaders/%s.frag", root["shaders"]["fragment"].asCString())));
				else
					Warning("MatLib", "Material %s has no vertex shader set.", *name);
			}

			material->m_program->link();

			Debug("MatLib", "New material loaded. %s", *name);
			m_materials.pushBack(material);
		}
		else
		{
			Error("MatLib", "Cannot parse material file %s. Error: %s '%s'", *name, reader.getFormattedErrorMessages().c_str(), content.get());
		}
	}
	else 
	{
		Error("MatLib", "Cannot open file for material %s. Path '%s'.", *name, *FilePath("../data/materials/%s.json", *name));
	}
	FileSystem::get()->close(file);
	return material;
}