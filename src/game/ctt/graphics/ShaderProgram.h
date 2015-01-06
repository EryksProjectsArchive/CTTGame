//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ShaderProgram.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/List.h>

class ShaderProgram
{
private:
	struct UniformData
	{
		uint32 name;
		uint32 location;
	};

	struct AttributeData
	{
		uint32 name;
		uint32 location;
	};

protected:
	unsigned int m_programId;

	// TODO: replace it with dynarray
	UniformData * m_uniforms;
	uint32 m_uniformsCount;

	AttributeData * m_attributes;
	uint32 m_attributesCount;

	List<Shader *> m_shaders;

public:
	ShaderProgram();
	~ShaderProgram();

	void attachShader(Shader * shader);
	void link();

	uint32 getUniformLocation(const char *name);
	uint32 getAttributeLocation(const char *name);

	void begin();
	void end();
	bool isValid();
	
	friend class Renderer;
	friend class DeferredRendering;
};