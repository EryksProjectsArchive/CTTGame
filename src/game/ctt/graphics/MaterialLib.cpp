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

MaterialLib::MaterialLib()
{

}

MaterialLib::~MaterialLib()
{
	for (Material *mat : m_materials)
		delete mat;

	m_materials.clear();
}

Material * MaterialLib::findByName(DynString name)
{
	for (Material *mat : m_materials)
	{
		if (mat->m_name == name)
			return mat;
	}

	// TODO: use fs here
	Material * material = 0;
	FILE *fp = fopen(FilePath("../../data/materials/%s.json", *name), "r");
	if (fp)
	{
		fseek(fp, 0, SEEK_END);
		long size = ftell(fp);
		rewind(fp);
		char * szBuffer = new char[size+1];
		if (szBuffer)
		{
			fread(szBuffer, sizeof(char), size, fp);
			szBuffer[size] = '\0';

			Json::Value root;
			Json::Reader reader;

			if (reader.parse(szBuffer, root))
			{
				material = new Material(name);

				if (!root["texture"].empty() && !root["texture"]["name"].empty())
				{
					material->m_texture = new Texture(FilePath("../../data/textures/%s", root["texture"]["name"].asCString()), !root["texture"]["mipMaps"] ? false : root["texture"]["mipMaps"].asBool());
					material->m_texture->acquire();
				}
				else
					Warning("MatLib", "Material %s has no textures set.", *name);

				material->m_program = new ShaderProgram();

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
				Error("MatLib", "Cannot parse material file %s. Error: %s '%s'", *name, reader.getFormattedErrorMessages().c_str(), szBuffer);
			}
			delete[]szBuffer;
		}
		fclose(fp);
	}
	else 
	{
		Error("MatLib", "Cannot open file for material %s. Path '%s'.", *name, *FilePath("../data/materials/%s.json", *name));
	}
	return material;
}