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

class Config : public Singleton<Config>
{
public:
	class Entry;
	Config();
	~Config();

	void serialize(File *file);
	void deserialize(File* file);

	Entry find(DynString name);
	Entry operator[](DynString name);
public:
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
			List<Entry> arrayData;
			DynString stringData;
		} m_data;

	public:
		Entry();
		Entry(DynString name);
		~Entry();

		uint32 getInteger(uint32 default = 0);
		float getFloat(float default = 0);
		List<Entry>& getArrayData();
		DynString getString(DynString default = DynString());
		bool getBool(bool default = false);

		Entry operator[](DynString name);

		void serialize(File *file, Json::Value parent);
		void deserialize(File* file, Json::Value parent);

		friend class Config;
	};

private:
	List<Entry> m_entries;
};