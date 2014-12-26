//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/DynArray.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <malloc.h>

#include <core/Logger.h>

template <typename T>
class DynArray
{
private:
	uint32 m_size;
	T * m_data;

	void resize(uint32 newSize)
	{
		if (newSize > m_size)
		{
			T * temp = 0;
			uint32 oldSize = m_size;
			if (m_data)
			{
				temp = (T *)malloc(sizeof(T) * m_size);
				memcpy(temp, m_data, sizeof(T) * m_size);

				delete[]m_data;
			}

			m_size = newSize;

			m_data = (T *)malloc(sizeof(T) * m_size);
			memset(m_data, 0, sizeof(T) * m_size);
			if (temp)
			{
				memcpy(m_data, temp, sizeof(T) * oldSize);
				free(temp);
			}
		}
	}
public:
	DynArray()
	{
		m_data = 0;
		m_size = 0;
	}

	DynArray(uint32 elements)
	{
		m_size = elements;
		m_data = (T *)malloc(sizeof(T) * m_size);
	}

	DynArray(const DynArray& array)
	{
		m_size = array.m_size;
		m_data = (T *)malloc(sizeof(T) * m_size);
		memcpy(m_data, array.m_data, sizeof(T) * m_size);
	}

	~DynArray()
	{
		if (m_data)
		{
			free(m_data);
			m_data = 0;
		}
		m_size = 0;
	}

	T& operator[](uint32 index)
	{
		if (index >= m_size)
		{
			Error("DynArray", "%s: Out of range (%s:%d)!", FUNCTION_NAME, __FILE__, __LINE__);
		}
		return m_data[index];
	}

	bool insert(T& element, unsigned int index)
	{
		if ((index + 1) >= m_size)
		{
			resize(index + 1);
		}
		m_data[index] = element;
		return true;
	}

	bool pushBack(T& element)
	{
		resize(m_size + 1);
		m_data[m_size - 1] = element;
		return true;
	}

	bool pushFront(T& element)
	{
		resize(m_size + 1);
		for (uint32 i = m_size - 1; i > 0; --i)
			m_data[i] = m_data[i - 1];
		m_data[0] = element;
		return true;
	}

	// This function push element into array at the first empty slot - if there are no empty slots this method retuns false.
	bool push(T& element)
	{
		for (uint32 i = 0; i < m_size; ++i)
		{
			if (!m_data[i])
			{
				m_data[i] = element;
				return true;
			}
		}
		return false;
	}

	void clear()
	{
		memset(m_data, 0, sizeof(T) * m_size);
	}

	uint32 size()
	{
		return m_size;
	}

	class Iterator
	{
	private:
		uint32 m_size;
		T * m_data;
		uint32 m_index;
		bool m_end;
	public:
		Iterator(uint32 size, T * data, uint32 index)
		{
			m_size = size;
			m_data = data;
			m_index = index;
		}

		void operator++()
		{
			++m_index;
		}

		T& operator*()
		{
			if (m_index >= m_size)
				m_index = m_size - 1;

			return m_data[m_index];
		}

		bool operator!=(Iterator& iter)
		{
			return (iter.m_data != m_data || iter.m_size != m_size || iter.m_index != m_index);
		}
	};


	Iterator begin()
	{
		return Iterator(m_size, m_data, 0);
	}

	Iterator end()
	{
		return Iterator(m_size, m_data, m_size);
	}
};
