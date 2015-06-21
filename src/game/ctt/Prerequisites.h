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
#define MAKE_VERSION(major, minor, revision)\
	(unsigned char)((major<<6)|(minor<<3)|revision)

#define WC_GAME_NAME L"City Transport Tycoon"
#define GAME_NAME "City Transport Tycoon"
#define GAME_VERSION_MAJOR 1
#define GAME_VERSION_MINOR 0
#define GAME_VERSION_REVISION 0

#define GAME_VERSION_INT MAKE_VERSION(GAME_VERSION_MAJOR, GAME_VERSION_MINOR, GAME_VERSION_REVISION)

#define WC_ENGINE_NAME L"BIM3D"
#define ENGINE_NAME "BIM3D"
#define ENGINE_VERSION_MAJOR 1
#define ENGINE_VERSION_MINOR 0
#define ENGINE_VERSION_REVISION 0

#define ENGINE_VERSION_INT MAKE_VERSION(ENGINE_VERSION_MAJOR, ENGINE_VERSION_MINOR, ENGINE_VERSION_REVISION)

#ifdef _WIN32
#define PLATFORM_NAME "WINDOWS"
#define WC_PLATFORM_NAME L"WINDOWS"
#elif __LINXU__
#define PLATFORM_NAME "LINUX"
#define WC_PLATFORM_NAME L"LINUX"
#else
#define PLATFORM_NAME "UNKNOWN"
#define WC_PLATFORM_NAME L"UNKNOWN"
#endif

#if defined(_WIN32)
#ifdef _WIN64
#define ARCH_NAME "X64"
#define WC_ARCH_NAME L"X64"
#else
#define ARCH_NAME "X86"
#define WC_ARCH_NAME L"X86"
#endif
#else
#define ARCH_NAME "UNKNOWN"
#define WC_ARCH_NAME L"UNKNOWN"
#endif

#if defined(__GNUC__)
#define FUNCTION_NAME __PRETTY_FUNCTION__
#define BIM_ASSERT(expr, message)
#else
#define FUNCTION_NAME __FUNCSIG__
#endif

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

#if defined(_WIN64)
typedef uint64 mem_addr_t;
#else
typedef uint32 mem_addr_t;
#endif

#ifdef DOUBLE_SCALAR_PRECISION
typedef double Scalar;
#else 
typedef float Scalar;
#endif

typedef char ansichar; // utf8
typedef wchar_t widechar; // utf16 wide char
typedef uint32 utf32char; // utf32
typedef uint64 utf64char; // utf64

// Predefinitions

// Core
class Logger;
class Timer;
class DynString;
class WDynString;
template <typename type>
class List;
template <class type>
class SharedPtr;
template <uint32 size>
class String;
template <uint32 size>
class WString;

// Hashing
class Hash;
class JenkinsHash;

// Environment
class Environment;
class TerrainNode;
class Terrain;

// Game
class Game;
class Scene;
class Entity;

// Physics
class PhysicsWorld;
class PhysicalEntity;
class DynamicPhysicalEntity;
class StaticPhysicalEntity;

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
class DynamicShadowsPass;
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
class Camera;
class Font;
namespace UI
{
	class Manager;
	class View;
	class Control;
};

struct Vertex2d;
struct Vertex3d;
struct SimpleVertex2d;
struct ImageData;



// Math
typedef glm::quat Quaternion;
typedef glm::mat4x4 Matrix4x4;
typedef glm::vec2 Vector2;
typedef glm::vec3 Vector3;
typedef glm::vec4 Vector4;
typedef glm::vec4 Color;

class AABB;
class Rect;

// Input
class Controllable;
class Input;

// EOF