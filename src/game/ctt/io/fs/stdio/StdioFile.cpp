//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/stdio/StdioFile.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "StdioFile.h"

namespace Stdio
{
	File::File()
	{
		m_filePtr = 0;
	}
	
	File::~File()
	{
		if (m_filePtr)
		{
			fclose(m_filePtr);
			m_filePtr = 0;
		}
	}

	bool File::load(FilePath file, FileOpenMode::Type mode)
	{
		if (!m_isLoaded)
		{
			// Build mode
			char _mode[4] = { 0 };

			_mode[0] = (mode & FileOpenMode::Write) ? 'w' : 'r';

			bool isBinary = (mode & FileOpenMode::Binary) ? true : false;
			if(isBinary)
				_mode[1] = 'b';

			_mode[isBinary ? 2 : 1] = (mode & FileOpenMode::Extra) ? '+' : 0;

			m_isLoaded = (m_filePtr = fopen(file, _mode)) != 0;
			return m_isLoaded;
		}
		return false;
	}
	
	bool File::unload()
	{
		if (m_filePtr)
		{
			fclose(m_filePtr);
			m_filePtr = 0;
			m_isLoaded = false;
			return true;
		}
		return false;
	}

	unsigned int File::write(const void *data, unsigned int count, unsigned int size)
	{
		if (m_isLoaded)
			return fwrite(data, size, count, m_filePtr);

		return -1;
	}

	unsigned int File::read(void * data, unsigned int count, unsigned int size)
	{
		if (m_isLoaded)
			return fread(data, size, count, m_filePtr);

		return -1;
	}

	void File::flush()
	{
		if (m_isLoaded)
		{
			fflush(m_filePtr);
		}
	}

	DynString File::getContent()
	{
		if (m_isLoaded)
		{
			seek(0, SeekOrigin::End);
			long size = tell();
			rewind();

			char *buffer = new char[size + 1];
			read(buffer, size, sizeof(char));

			DynString string = buffer;
			delete[]buffer;
			return string;
		}
		return DynString();
	}


	long File::tell()
	{
		return m_isLoaded ? ftell(m_filePtr) : -1;
	}

	void File::seek(int position, SeekOrigin::Type origin)
	{
		if (m_isLoaded)
		{
			int _origin = SEEK_CUR;
			if (origin == SeekOrigin::Set) _origin = SEEK_SET;
			else if (origin == SeekOrigin::End) _origin = SEEK_END;
				
			fseek(m_filePtr, position, origin);
		}
	}

	void File::rewind()
	{
		if (m_isLoaded)
			::rewind(m_filePtr);
	}
};