//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/CameraManager.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <core/Singleton.h>

enum CameraType
{
	CAMERA_TYPE_STATIC,
	CAMERA_TYPE_EDITOR_FREE,
	CAMERA_TYPE_FREE,
	CAMERA_TYPES_COUNT
};

#define DEFINE_CAMERA_TYPE(type) static CameraType getType() { return CAMERA_TYPE_##type; }

class CameraManager : public Singleton<CameraManager>
{
private:
	CameraType m_current;
	Camera * m_cameras[CAMERA_TYPES_COUNT];

	Camera * _createCameraByType(CameraType type);
public:
	CameraManager();
	~CameraManager();

	void setCurrent(CameraType type);
	Camera * getCurrent();

	template <class camClass>
	camClass * getByType(CameraType type)
	{
		if (!m_cameras[type])
			m_cameras[type] = _createCameraByType(type);

		return (camClass *)m_cameras[type];
	}
};