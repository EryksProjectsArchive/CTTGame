//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: resources/materials/MaterialLib.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <resources/ResourceLib.h>
#include <core/Singleton.h>
#include <core/List.h>
#include <core/console/Console.h>

class MaterialLib : public ResourceLib<Material>, public Singleton<MaterialLib>
{
private:
	List<Material *> m_materials;
public:
	MaterialLib();
	~MaterialLib();

	Material * findByName(const DynString& name) override;

	class MaterialsCommand : public Console::ICommand
	{
	private:
		MaterialLib *m_matLib;
	public:
		MaterialsCommand(MaterialLib * matLib);
		void onExecute(const WDynString& params);
	};
};