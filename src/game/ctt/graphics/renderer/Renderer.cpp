//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include "Renderer.h"

#include <graphics/Window.h>

#include <graphics/VertexBuffer.h>
#include <graphics/IndexBuffer.h>

#include <graphics/Shader.h>
#include <graphics/VertexShader.h>
#include <graphics/FragmentShader.h>

#include <graphics/Vertex3d.h>

#include <graphics/Material.h>
#include <graphics/Geometry.h>

#include <graphics/ShaderProgram.h>

// Extension methods
PFNGLCOMPILESHADERPROC Renderer::glCompileShader = 0;
PFNGLCREATESHADERPROC Renderer::glCreateShader = 0;
PFNGLDELETESHADERPROC Renderer::glDeleteShader = 0;
PFNGLSHADERSOURCEPROC Renderer::glShaderSource = 0;
PFNGLCREATEPROGRAMPROC Renderer::glCreateProgram = 0;
PFNGLDELETEPROGRAMPROC Renderer::glDeleteProgram = 0;
PFNGLATTACHSHADERPROC Renderer::glAttachShader = 0;
PFNGLUSEPROGRAMPROC Renderer::glUseProgram = 0;

PFNGLGENBUFFERSPROC Renderer::glGenBuffers = 0;
PFNGLBINDBUFFERPROC Renderer::glBindBuffer = 0;
PFNGLBUFFERDATAPROC Renderer::glBufferData = 0;
PFNGLMAPBUFFERPROC Renderer::glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC Renderer::glUnmapBuffer = 0;
PFNGLDELETEBUFFERSPROC Renderer::glDeleteBuffers = 0;

Renderer * Renderer::s_instance = 0;

Renderer::Renderer()
{
	m_window = 0;
	m_glContext = 0;
	s_instance = this;
}

Renderer::~Renderer()
{
	if (m_glContext)
	{
		SDL_GL_DeleteContext(m_glContext);
		m_glContext = 0;
	}
}

bool Renderer::setup(Window * window)
{
	m_window = window;

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_glContext = SDL_GL_CreateContext(window->_window);
	
	// Shaders
	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");

	glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
	glDeleteBuffers	= (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
	glMapBuffer	= (PFNGLMAPBUFFERPROC)SDL_GL_GetProcAddress("glMapBuffer");
	glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)SDL_GL_GetProcAddress("glUnmapBuffer");

	SDL_GL_SetSwapInterval(1);

	glEnable(GL_DEPTH);

	//m_defaultMaterial = MaterialLib::FindByName("default");

	return true;
}

void Renderer::preFrame()
{

}

void Renderer::postFrame()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glClear(GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(1.0f, 0.5f, 1.0f, 1.0f);


	SDL_GL_SwapWindow(m_window->_window);
}

void Renderer::setFullscreen(bool fullscreen)
{
	
}

BufferBase * Renderer::createBuffer(BufferType::Type type)
{
	if (type == BufferType::VERTEX)
	{
		return new VertexBuffer();
	}
	else if (type == BufferType::INDEX)
	{
		return new IndexBuffer();
	}
	return 0;
}

void Renderer::setMaterial(Material * material)
{
	m_currentMaterial = material;
}

#include <stdio.h>
void Renderer::renderGeometry(Geometry *geometry, Matrix4x4 * matrix)
{
	Material *material = m_currentMaterial;
	if (!material)
		material = m_defaultMaterial;

	// Shaders
	if (material)
	{
		if (material->m_program)
			glUseProgram(material->m_program->m_programId);
	}
	
	glEnableClientState(GL_VERTEX_ARRAY);
	glEnableClientState(GL_COLOR_ARRAY);
	glEnableClientState(GL_NORMAL_ARRAY);
	
	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexPointer(3, GL_FLOAT, 0, 0);
	glColorPointer(1, GL_INT, offsetof(Vertex3d, color), 0);
	glNormalPointer(3, offsetof(Vertex3d, nx), 0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements(GL_TRIANGLES, geometry->m_trianglesCount*3, GL_UNSIGNED_SHORT, 0);

	glDisableClientState(GL_VERTEX_ARRAY);
	glDisableClientState(GL_COLOR_ARRAY);
	glDisableClientState(GL_NORMAL_ARRAY);
}

Renderer& Renderer::get()
{
	return *s_instance;
}