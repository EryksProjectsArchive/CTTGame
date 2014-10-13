//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/Config.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Singleton.h>
#include <core/List.h>
#include <core/DynString.h>

#include <json/json.h>

class Config
{
private:
	static Config *s_singleton;
public:
	class Entry;
	Config();
	~Config();

	void serialize(File *file);
	void deserialize(File* file);

	Entry& find(const DynString& name);
	Entry& operator[](const DynString& name);

	static Config& get();
public:
	friend class Entry;
	class Entry
	{
	private:
		struct ValueType
		{
			enum Type
			{
				Integer,
				String,
				Float,
				Boolean,				
				Array,
				Empty
			};
		};

		DynString m_name;
		ValueType::Type m_type;
		struct
		{
			union
			{
				uint32 integerValue;
				float floatValue;
				bool booleanData;
			};
			List<Entry *> arrayData;
			DynString stringData;
		} m_data;
		Config *m_config;
	public:
		Entry();
		Entry(const DynString& name);
		~Entry();

		uint32 getInteger(uint32 def = 0);
		float getFloat(float def = 0);
		List<Entry *> getArrayData();
		DynString getString(const DynString& def = DynString());
		bool getBool(bool def = false);

		Entry& find(const DynString& name);
		Entry& operator[](const DynString& name);

		void serialize(File *file, Json::Value& parent);
		void deserialize(File* file, Json::Value& parent);

		friend class Config;
	};

private:
	List<Entry *> m_entries;
};

