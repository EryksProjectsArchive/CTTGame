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

#include <core/StringUtilities.h>

MaterialLib::MaterialLib()
{
	Console::get()->addCommand(new MaterialLib::MaterialsCommand(this));
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

			material->m_wireframe = root.get("wireframe", false).asBool();

			if (root["textures"].isArray())
			{
				Json::Value textures = root["textures"];
				uint32 size = textures.size();
				if (size > 32)
				{
					Warning("MaterialLib", "Maximum supported textures = 32 (Found %d). Material: %s", size, name.get());
					size = 32;
				}
				for (uint32 i = 0; i < size; ++i)
				{
					Json::Value texture = textures[i];
					if (texture.isObject() && texture["path"].isString())
					{												
						Json::Value name = texture.get("name", String<64>("texture%d", i).get());
						Json::Value path = texture["path"];
						Json::Value mipmap = texture["mipMaps"];

						material->addTexture(name.asCString(), path.asCString(), mipmap.asBool());
					}
				}
			}


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

MaterialLib::MaterialsCommand::MaterialsCommand(MaterialLib * matLib)
	: Console::ICommand(L"materials", L"Shows list of currently used materials")
{
	m_matLib = matLib;
}
	
void MaterialLib::MaterialsCommand::onExecute(const WDynString& params)
{
	m_console->output(Console::MessageType::Info, WString<64>(L"Currently loaded materials (%d):", m_matLib->m_materials.size()));
	for (Material * mat : m_matLib->m_materials)
	{
		m_console->output(Console::MessageType::Info, WString<256>(L"%s Refs:%d", StringUtilities::toWideChar(mat->m_name).get(), mat->getRefCount()));
	}
}