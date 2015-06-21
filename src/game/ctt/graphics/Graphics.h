//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/Graphics.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

class IRenderer;

class Graphics
{
private:
	static IRenderer * s_rendererInstance;
public:
	struct RendererAPIs
	{
		enum Type
		{
			NOAPI,
			OPENGL,			
			COUNT
		};
	};

	static IRenderer * createRenderer(RendererAPIs::Type api);
	static RendererAPIs::Type getRendererAPIFromString(const char *api);
	static IRenderer * getRenderer();
};