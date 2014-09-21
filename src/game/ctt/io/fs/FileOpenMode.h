//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: io/fs/FileOpenMode.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

struct FileOpenMode
{
	enum Type
	{
		Read = 0,
		Write = 1,
		Binary = 2,
		Extra = 4,

		Safe = (Read | Extra),
		SafeBinary = (Read | Binary | Extra),
		StandardBinary = (Write | Binary | Extra),
		Standard = (Write | Extra)
	};
};