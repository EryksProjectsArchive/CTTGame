//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: core/List.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>

#include <core/Logger.h>

template <typename T>
class List
{
private:
	class Node
	{
	private:
		T m_value;
		Node * m_next;
		Node * m_previous;
	public:
		Node(T value)
		{
			m_next = m_previous = 0;
			m_value = value;
		}

		friend class List;
	};

	Node * m_begin;
	Node * m_end;

	unsigned int m_size;
public:
	class Iterator;

	List()
	{
		m_begin = 0;
		m_end = 0;
		m_size = 0;
	}

	~List()
	{
	}

	void clear()
	{
		Node* node = m_end;
		while (node)
		{
			Node* nodeToRemove = node;
			node = node->m_previous;
			delete nodeToRemove;
		}
	}

	void insert(T Value)
	{
		Node *newNode = new Node(Value);

		if (!m_begin)
		{
			m_begin = newNode;
			m_end = newNode;
		}
		else 
		{
			newNode->m_next = m_begin;
			m_begin->m_previous = newNode;
			m_begin = newNode;
		}

		m_size++;
	}

	void pushBack(T Value)
	{
		// Is that first element
		Node *newNode = new Node(Value);
		if (!m_begin)
		{
			m_begin = newNode;
			m_end = newNode;
		}
		else
		{
			m_end->m_next = newNode;
			newNode->m_previous = m_end;
			m_end = newNode;
		}

		m_size++;
	}

	void remove(T Value)
	{
		Node *node = m_begin;
		while (node)
		{
			if (node->m_value == Value)
			{
				if (node->m_next)
					node->m_next->m_previous = node->m_previous;

				if (node->m_previous)
					node->m_previous->m_next = node->m_next;

				if (node == m_begin)
					m_begin = node->m_next;

				if (node == m_end)
					m_end = node->m_previous;

				Node *toRemove = node;
				node = node->m_next;
				delete toRemove;

				m_size--;
			}
			else
				node = node->m_next;
		}
	}

	unsigned int size()
	{
		return m_size;
	}

	Iterator begin()
	{
		Iterator iter;
		iter.m_current = m_begin;
		return iter;
	}

	Iterator end()
	{
		return Iterator();
	}

	class Iterator
	{
	private:
		Node *m_current;
	public:
		Iterator()
		{
			m_current = 0;
		}

		T operator*()
		{
			if (!m_current)
				Error("List", "Null current pointer at %s:%d", __FILE__, __LINE__);

			return m_current->m_value;
		}

		Iterator operator ++(int)
		{
			Iterator this_ = *this;
			m_current = m_current->m_next;
			return this_;
		}

		Iterator operator ++()
		{
			m_current = m_current->m_next;
			return *this;
		}

		Iterator operator --(int)
		{
			Iterator this_ = *this;
			m_current = m_current->m_previous;
			return this_;
		}

		Iterator operator--()
		{
			m_current = m_current->m_previous;
			return *this;
		}

		bool operator!=(Iterator iter) const
		{
			return (m_current != iter.m_current);
		}

		bool operator==(Iterator iter) const
		{
			return (m_current == iter.m_current);
		}

		friend class List;
	};
};