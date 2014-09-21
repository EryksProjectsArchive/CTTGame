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
		if (!m_filePtr)
		{
			// Build mode
			char _mode[4] = { 0 };

			_mode[0] = (mode & FileOpenMode::Write) ? 'w' : 'r';

			bool isBinary = (mode & FileOpenMode::Binary) ? true : false;
			if(isBinary)
				_mode[1] = 'b';

			_mode[isBinary ? 2 : 1] = (mode & FileOpenMode::Extra) ? '+' : 0;

			return (m_filePtr = fopen(file, _mode)) != 0;
		}
		return false;
	}
	
	bool File::unload()
	{
		if (m_filePtr)
		{
			fclose(m_filePtr);
			m_filePtr = 0;
			return true;
		}
		return false;
	}
};