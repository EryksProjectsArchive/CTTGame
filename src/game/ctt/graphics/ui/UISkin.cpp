//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/ui/UISkin.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <resources/materials/MaterialLib.h>
#include "../Texture.h"

#include "UISkin.h"

#include <json/json.h>
#include <io/fs/FileSystem.h>

#include <math/Rect.h>

namespace UI
{
	Skin::Skin(const DynString& name) : m_name(name), m_material(0)
	{
		m_material = MaterialLib::get()->findByName("uiMaterial");
		setupDefaults();
		setup();
	}

	Skin::~Skin()
	{
		if (m_material)
		{		
			m_material->release();
			m_material = 0;
		}
	}

	void Skin::setupDefaults()
	{
		m_colors.buttonNormal = Color(1, 1, 1, 1);
		m_colors.buttonHover = Color(1, 1, 1, 1);
		m_colors.labelNormal = Color(1, 1, 1, 1);
		m_colors.labelShadow = Color(0, 0, 0, 1);

		m_data.label.shadowOffset = Vector2(1, 1);
		m_data.label.shadow = true;
	}

	void Skin::setup()
	{
		if (m_material)
		{
			FilePath path("ui/%s/definition.json", m_name.get());
			File *skinDefinition = FileSystem::get()->open(path, FileOpenMode::Read);
			if (skinDefinition->isLoaded())
			{
				Json::Reader reader;
				Json::Value root;
				DynString data = skinDefinition->getContent();
				if (reader.parse(data.get(), root))
				{
					uint32 textureWidth = 1;
					uint32 textureHeight = 1;
	
					if (root["texture"].isString())
					{
						Material::TextureWrap wrap[2] = { Material::TextureWrap::TEXTURE_WRAP_CLAMP, Material::TextureWrap::TEXTURE_WRAP_CLAMP };
						m_material->addTexture("diffuse", root["texture"].asCString(), false, wrap);
					}
					else 
					{
						Warning("UISkin", "UI skin '%s' has not texture set.", m_name.get());
					}

					// Acquire our material
					m_material->acquire();

					Texture* texture = m_material->getTexture(0);
					if (texture)
					{
						textureWidth = texture->width();
						textureHeight = texture->height();
					}

					if (root["controls"].isArray())
					{
						for (uint32 i = 0; i < root["controls"].size(); ++i)
						{
							Json::Value node = root["controls"][i];
							if (node.isObject())
							{
								if (node["name"].isString())
								{
									if (node["name"].asString() == "button")
									{
										if (node["elements"].isArray())
										{
											for (uint32 j = 0; j < node["elements"].size(); ++j)
											{
												Json::Value element = node["elements"][j];
												if (element.isObject())
												{
													if (element["name"].isString() && element["name"].asString() == "body")
													{
														if (element["state"].isString() && element["state"].asString() == "hover")
														{
															m_geometry.buttonHover.x = element["x"].asFloat() / textureWidth;
															m_geometry.buttonHover.y = (element["y"].asFloat() / textureHeight);
															m_geometry.buttonHover.w = element["w"].asFloat() / textureWidth;
															m_geometry.buttonHover.h = (element["h"].asFloat() / textureHeight);
														}
														else
														{
															m_geometry.buttonNormal.x = element["x"].asFloat() / textureWidth;
															m_geometry.buttonNormal.y = (element["y"].asFloat() / textureHeight);
															m_geometry.buttonNormal.w = element["w"].asFloat() / textureWidth;
															m_geometry.buttonNormal.h = (element["h"].asFloat() / textureHeight);
														}
													}
												}
											}
										}										
									}
									else if (node["name"].asString() == "label")
									{
										for (uint32 j = 0; j < node["elements"].size(); ++j)
										{
											Json::Value element = node["elements"][j];
											if (element.isObject())
											{
												if (element["name"].isString())
												{
													if(element["name"].asString() == "shadowOffset")
													{
														m_data.label.shadowOffset.x = element.get("x", 1.0f).asFloat();
														m_data.label.shadowOffset.y = element.get("y", 1.0f).asFloat();			
													}
													else if (element["name"].asString() == "shadow")
													{
														m_data.label.shadow = element.get("enabled", true).asBool();
													}													
												}
											}
										}									
									}
								}
							}
						}
					}
					else
					{
						Warning("UISkin", "UI skin '%s' has no controls definition.", m_name.get());
					}

					if (root["colors"].isObject())
					{
						for (std::string name : root["colors"].getMemberNames())
						{
							#define CLAMP_COLOR(a) ((a>1.0f)?1.0f:((a<0.0f)?0.0f:a))
							#define READ_COLOR(n) \
								if(name == #n) { \
									Json::Value node = root["colors"][#n];\
									if(node.isObject()) {\
										m_colors.##n.r = CLAMP_COLOR(node.get("r", 1.0f).asFloat());\
										m_colors.##n.g = CLAMP_COLOR(node.get("g", 1.0f).asFloat());\
										m_colors.##n.b = CLAMP_COLOR(node.get("b", 1.0f).asFloat());\
										m_colors.##n.a = CLAMP_COLOR(node.get("a", 1.0f).asFloat());\
									}\
								}

							READ_COLOR(buttonNormal);
							READ_COLOR(buttonHover);
							READ_COLOR(labelNormal);
							READ_COLOR(labelShadow);

							#undef READ_COLOR
							#undef CLAMP_COLOR						
						}
					}
					else
					{
						Warning("UISkin", "UI skin '%s' has no colors definition.", m_name.get());
					}					
				}
				else
				{
					Error("UISkin", "Unable to parse skin definition for '%s'.", m_name.get());
					Error("UISkin", reader.getFormatedErrorMessages().c_str());
				}
			}
			else
			{
				Error("UISkin", "Unable to load skin definition for %s. (%s)", m_name.get(), path.get());
			}
			FileSystem::get()->close(skinDefinition);
		}
	}

	DynString Skin::getName()
	{
		return m_name;
	}

	Material * Skin::getMaterial()
	{
		return m_material;
	}

	const Skin::Colors& Skin::colors()
	{
		return m_colors;
	}

	const Skin::Data& Skin::data()
	{
		return m_data;
	}

	Geometry<Vertex2d>* Skin::generateButtonGeometry(const Rect& rect, bool hover)
	{
		ButtonGeometryData geometryData = hover ? m_geometry.buttonHover : m_geometry.buttonNormal;
		Vertex2d vertices[4] = {
			{ rect.left, rect.top, geometryData.x, geometryData.y, 0xFFFFFFFF },
			{ rect.left, rect.bottom, geometryData.x, geometryData.h, 0xFFFFFFFF },
			{ rect.right, rect.bottom, geometryData.w, geometryData.h, 0xFFFFFFFF },
			{ rect.right, rect.top, geometryData.w, geometryData.y, 0xFFFFFFFF }
		};

		uint16 indices[6] = {
			0, 1, 2, 
			0, 2, 3 
		};
		Geometry<Vertex2d> *geometry = new Geometry<Vertex2d>();
		geometry->fillData(vertices, 4, indices, 6 / 3);
		return geometry;
	}
}