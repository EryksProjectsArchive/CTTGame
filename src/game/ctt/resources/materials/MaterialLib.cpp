//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/materials/MaterialLib.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

//#include <core/DynString.h>
#include <core/List.h>

#include "MaterialLib.h"

#include <core/Logger.h>

#include <json/json.h>

#include <graphics/Texture.h>
#include <graphics/Shader.h>
#include <graphics/VertexShader.h>
#include <graphics/FragmentShader.h>
#include <graphics/ShaderProgram.h>
#include <graphics/Material.h>

#include <io/fs/FileSystem.h>

MaterialLib::MaterialLib()
{

}

MaterialLib::~MaterialLib()
{
	for (Material * mat : m_materials)
		delete mat;

	m_materials.clear();
}

Material * MaterialLib::findByName(const DynString& name)
{
	for (Material* mat : m_materials)
	{
		if (mat->m_name == name)
			return mat;
	}

	Material* material = 0;
	File *file = FileSystem::get()->open(FilePath("materials/%s.json", name.get()), FileOpenMode::Read);
	if (file->isLoaded())
	{
		DynString content = file->getContent();
		Json::Value root;
		Json::Reader reader;

		if (reader.parse(content.get(), root))
		{			
			material = new Material(name, FilePath("materials/%s.json", name.get()));

			if (!root["texture"].empty() && !root["texture"]["name"].empty())
			{
				material->m_textureName = root["texture"]["name"].asCString();
				material->m_mipmaps = root["texture"].get("mipMaps", false).asBool();
				material->m_hasTexture = 1;
			}
			else
				Warning("MatLib", "Material %s has no textures set.", name.get());

			if (root["shaders"].empty())
			{
				Warning("MatLib", "Material %s has no shaders set.", name.get());
			}
			else
			{
				if (!root["shaders"]["vertex"].empty())
				{
					material->m_hasVertexShader = 1;
					material->m_vertexShaderName = root["shaders"]["vertex"].asCString();
				}
				else
					Warning("MatLib", "Material %s has no vertex shader set.", name.get());

				if (!root["shaders"]["fragment"].empty())
				{
					material->m_hasFragmentShader = 1;
					material->m_fragmentShaderName = root["shaders"]["fragment"].asCString();
				}
				else
					Warning("MatLib", "Material %s has no vertex shader set.", name.get());
			}
			
			Debug("MatLib", "New material loaded %s.", name.get());
			m_materials.pushBack(material);
		}
		else
		{
			Error("MatLib", "Cannot parse material file %s. Error: %s '%s'", name.get(), reader.getFormattedErrorMessages().c_str(), content.get());
		}
	}
	else 
	{
		Error("MatLib", "Cannot open file for material %s. Path '%s'.", name.get(), FilePath("../data/materials/%s.json", name.get()).get());
	}
	FileSystem::get()->close(file);

	if (!material)
	{
		Error("MatLib", "Unable to find material '%s'.", name.get());
	}

	return material;
}