//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/RenderPriorities.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

enum RenderPriority
{
	RENDER_HIGH_PRIORITY = 0, // Render first
	RENDER_NORMAL_PRIORITY = 1, // Render second
	RENDER_LOW_PRIORITY = 2, // Render third
	RENDER_PRIORITY_COUNT = 3
};
