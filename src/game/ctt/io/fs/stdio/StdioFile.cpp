//////////////////////////////////////////////
//
//		City Transport Tycoon
//	Copyright (C) Black Ice Mountains
//		All rights reserved
//
// File		: io/fs/stdio/StdioFile.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "StdioFile.h"

#include <core/Logger.h>

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

	bool File::load(const FilePath& file, uint32 mode)
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

	size_t File::write(const void *data, size_t count, size_t size)
	{
		if (m_isLoaded)
		{
			return fwrite(data, size, count, m_filePtr);
		}
		return -1;
	}

	size_t File::read(void * data, size_t count, size_t size)
	{
		if (m_isLoaded)
		{
			return fread(data, size, count, m_filePtr);
		}
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
			int32 size = tell();
			rewind();

			char *buffer = new char[size + 1];
			memset(buffer, 0, size);
			read(buffer, size, sizeof(char));
			buffer[size] = '\0';

			DynString string(buffer);
			delete[]buffer;
			return string;
		}
		return DynString();
	}


	int32 File::tell()
	{
		return m_isLoaded ? ftell(m_filePtr) : -1;
	}

	void File::seek(int32 position, SeekOrigin::Type origin)
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
		{
			::rewind(m_filePtr);
		}
	}
};