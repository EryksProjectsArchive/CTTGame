//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/CameraManager.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <core/Logger.h>

#include "Camera.h"
#include "EditorFreeCamera.h"
#include "FreeCamera.h"

#include "CameraManager.h"


CameraManager::CameraManager()
{
	for (uint32 i = 0; i < CAMERA_TYPES_COUNT; ++i)
		m_cameras[i] = 0;

	m_current = CAMERA_TYPE_STATIC;
	m_cameras[m_current] = new Camera();
	m_cameras[m_current]->activate();
}

CameraManager::~CameraManager()
{
	for (uint32 i = 0; i < CAMERA_TYPES_COUNT; ++i)
	{
		if (m_cameras[i])
		{
			delete m_cameras[i];
			m_cameras[i] = 0;
		}
	}
}

Camera * CameraManager::_createCameraByType(CameraType type)
{
	Camera * camera = NULL;
	switch (type)
	{
	case CAMERA_TYPE_STATIC:
		{
			camera = new Camera();
		} break;
	case CAMERA_TYPE_EDITOR_FREE:
		{
			camera = new EditorFreeCamera();
		} break;
	case CAMERA_TYPE_FREE:
		{
			camera = new FreeCamera();
		} break;
	default:
		Error("CameraManager", "Tried to create unsupported camera type: %d", type);
		break;
	}
	return camera;
}

void CameraManager::setCurrent(CameraType type)
{
	if (!m_cameras[type])
		m_cameras[type] = _createCameraByType(type);

	if (m_cameras[m_current])
	{
		m_cameras[m_current]->deactivate();
	}

	m_current = type;

	if (m_cameras[m_current])
	{
		m_cameras[m_current]->activate();
	}
	else
		Error("CameraManager", "Unable to activate new camera.");
}

Camera * CameraManager::getCurrent()
{
	return m_cameras[m_current];
}