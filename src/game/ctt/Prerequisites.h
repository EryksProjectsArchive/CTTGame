//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: Prerequisites.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

//#define _MEM_LEAKS_DEBUG
#ifdef _MEM_LEAKS_DEBUG
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#define new new(_NORMAL_BLOCK, __FILE__, __LINE__)
#endif

// GLM
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/glm.hpp>

// Versioning
#define GAME_NAME "City Transport Tycoon"
#define GAME_VERSION_MAJOR 1
#define GAME_VERSION_MINOR 0
#define GAME_VERSION_REVISION 0

#define MAKE_GAME_VERSION(major, minor, revision)\
	(unsigned char)((major<<6)|(minor<<3)|revision)

#define GAME_VERSION_INT MAKE_GAME_VERSION(GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVISION)

// Types
typedef signed char sint8;
typedef char int8;
typedef unsigned char uint8;

typedef signed short sint16;
typedef short int16;
typedef unsigned short uint16;

typedef signed int sint32;
typedef int int32;
typedef unsigned int uint32;

typedef signed long long sint64;
typedef long long int64;
typedef unsigned long long uint64;

typedef unsigned int flags32;

#ifdef DOUBLE_SCALAR_PRECISION
typedef double Scalar;
#else 
typedef float Scalar;
#endif

// Predefinitions

// Core
class Logger;
class Timer;
class DynString;
class WDynString;
template <typename T>
class List;
template <class Type>
class ProtectedPtr;
template <class Type>
class SharedPtr;
template <int maxSize>
class String;
template <int maxSize>
class WString;

// Hashing
class Hash;
class JenkinsHash;

// Game
class Game;
class Scene;
class Entity;

// Physics
class PhysicsWorld;
class PhysicalEntity;

// IO
template <typename Type>
class CachedItem;
class File;
class FileSystem;
class DynamicLibrary;
namespace Stdio
{
	class File;
	class FileSystem;
};
class Config;
class Serializeable;

// Resources
class Resource;
class CacheableResource;
class ImageLoader;
template <typename Type>
class ResourceLib;

// Sound
namespace OpenAL
{
	class Impl;
};

class Sound;
class SoundManager;
struct SoundData;

// Graphics
class RenderContext;
class Renderer;
class ModelFormat;
class BufferBase;
class IndexBuffer;
class VertexBuffer;
class Window;
class Shader;
class VertexShader;
class FragmentShader;
class ShaderProgram;
class Texture;
template <class T = Vertex3d>
class Geometry;
class Material;
class MaterialLib;
class Model;
class Mesh;
struct Vertex3d;
class Camera;
struct ImageData;
class Font;

// Math
typedef glm::quat Quaternion;
typedef glm::mat4x4 Matrix4x4;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
class AABB;
class Rect;
typedef glm::vec4 Color;

// Input
class Controllable;
class Input;

// EOF