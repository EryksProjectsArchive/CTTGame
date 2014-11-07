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

template <typename type>
class List
{
private:
	class Node
	{
	private:
		type m_value;
		Node * m_next;
		Node * m_previous;
	public:
		Node(type value)
		{
			m_next = m_previous = 0;
			m_value = value;
		}

		friend class List;
	};

	Node * m_begin;
	Node * m_end;

	uint32 m_size;
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
		m_begin = 0;
		m_end = 0;
	}

	/**
	 * This functions push value in front of list
	 */
	void pushFront(type value)
	{
		Node *newNode = new Node(value);
		
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

	/**
	 * This function push value on back of list
	 */
	void pushBack(type value)
	{	
		Node *newNode = new Node(value);
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

	uint32 remove(type value)
	{
		Node *node = m_begin;
		uint32 removedElements = 0;
		while (node)
		{
			Node * next = node->m_next;
			if (node->m_value == value)
			{
				if (node->m_next)
				{
					node->m_next->m_previous = node->m_previous;
				}

				if (node->m_previous)
				{
					node->m_previous->m_next = node->m_next;
				}

				if (node == m_begin)
				{
					m_begin = node->m_next;
				}

				if (node == m_end)
				{
					m_end = node->m_previous;
				}

				delete node;
				m_size --;
				removedElements++;
			}

			node = next;
		}
		return removedElements;
	}

	void erase(Iterator& iter)
	{
		Node *currentNode = iter.m_current;
		if (currentNode)
		{
			Node *nextNode = currentNode->m_next;
			Node *previousNode = currentNode->m_previous;

			if (nextNode)
			{
				nextNode->m_previous = previousNode;
			}

			if (previousNode)
			{
				previousNode->m_next = nextNode;
			}

			delete currentNode;
			currentNode = 0;

			--m_size;
		}
	}

	uint32 remove(Iterator iter)
	{
		return remove(*iter);
	}

	uint32 size() const
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

	/**
	 * Remember! Use --operator for it. 
	 */
	Iterator rbegin()
	{
		Iterator iter;
		iter.m_current = m_end;
		return iter;
	}

	Iterator rend()
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

		type operator*()
		{
			if (!m_current) {
				Error("List", "Null current pointer at %s:%d", __FILE__, __LINE__);
			}
			return m_current->m_value;
		}

		type get_value()
		{
			if (!m_current) {
				Error("List", "Null current pointer at %s:%d", __FILE__, __LINE__);
			}
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