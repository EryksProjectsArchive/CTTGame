//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/DynamicShadowsPass.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <graphics/Material.h>

class DynamicShadowsPass
{
private:
	uint32 m_fbo;

	uint32 m_depthShadowRenderBuffer;

	uint32 m_depthShadowTexture;

	Material *m_material;

	bool m_active;

	uint32 m_width;
	uint32 m_height;

	Matrix4x4 m_depthMVP;
public:
	DynamicShadowsPass();
	~DynamicShadowsPass();

	bool isActive();

	bool initialize(Renderer *renderer, uint32 width, uint32 height);
	void destroy();

	void begin();
	void end();

	void renderGeometry(Geometry<Vertex3d> *geometry, const Matrix4x4& matrix);

	uint32 getShadowTexture();

	inline Matrix4x4& getDepthMVP() { return m_depthMVP;  }
};