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
	public:
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
	private:
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

		uint32 getInteger(uint32 defaultValue = 0);
		float getFloat(float defaultValue = 0);
		List<Entry *>& getArrayData();
		DynString getString(const DynString& defaultValue = DynString());
		bool getBool(bool defaultValue = false);

		ValueType::Type type();

		Entry& operator=(uint32 v);
		Entry& operator=(float v);
		Entry& operator=(const DynString& v);
		Entry& operator=(bool v);

		Entry& find(const DynString& name);
		Entry& operator[](const DynString& name);

		void serialize(File *file, Json::Value& parent);
		void deserialize(File* file, Json::Value& parent);

		friend class Config;
	};

private:
	List<Entry *> m_entries;
};

