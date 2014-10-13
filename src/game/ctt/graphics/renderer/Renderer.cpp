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

#include <core/Logger.h>

#include <graphics/Window.h>

#include <graphics/VertexBuffer.h>
#include <graphics/IndexBuffer.h>

#include <graphics/Shader.h>
#include <graphics/VertexShader.h>
#include <graphics/FragmentShader.h>

#include <graphics/Vertex3d.h>

#include <graphics/Material.h>
#include <graphics/Geometry.h>
#include <graphics/Texture.h>

#include <graphics/ShaderProgram.h>

#include <resources/materials/MaterialLib.h>

#include <graphics/Camera.h>

#include <game/environment/Environment.h>

#include <graphics/fonts/Font.h>

#include <os/OS.h>
#include <core/Timer.h>
#include <math/Rect.h>

#include <io/Config.h>

// Extension methods
PFNGLENABLEIPROC Renderer::glEnablei = 0;

PFNGLGENBUFFERSPROC Renderer::glGenBuffers = 0;
PFNGLBINDBUFFERPROC Renderer::glBindBuffer = 0;
PFNGLBUFFERDATAPROC Renderer::glBufferData = 0;
PFNGLMAPBUFFERPROC Renderer::glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC Renderer::glUnmapBuffer = 0;
PFNGLDELETEBUFFERSPROC Renderer::glDeleteBuffers = 0;
PFNGLBINDVERTEXARRAYPROC Renderer::glBindVertexArray = 0;
PFNGLGETBUFFERPARAMETERIVPROC Renderer::glGetBufferParameteriv = 0;

PFNGLGENERATEMIPMAPPROC Renderer::glGenerateMipmap = 0;
PFNGLACTIVETEXTUREPROC Renderer::glActiveTexture = 0;

PFNGLBLENDEQUATIONSEPARATEPROC Renderer::glBlendEquationSeparate = 0;
PFNGLDRAWBUFFERSPROC Renderer::glDrawBuffers = 0;
PFNGLSTENCILOPSEPARATEPROC Renderer::glStencilOpSeparate = 0;
PFNGLSTENCILFUNCSEPARATEPROC Renderer::glStencilFuncSeparate = 0;
PFNGLSTENCILMASKSEPARATEPROC Renderer::glStencilMaskSeparate = 0;
PFNGLATTACHSHADERPROC Renderer::glAttachShader = 0;
PFNGLBINDATTRIBLOCATIONPROC Renderer::glBindAttribLocation = 0;
PFNGLCOMPILESHADERPROC Renderer::glCompileShader = 0;
PFNGLCREATEPROGRAMPROC Renderer::glCreateProgram = 0;
PFNGLCREATESHADERPROC Renderer::glCreateShader = 0;
PFNGLDELETEPROGRAMPROC Renderer::glDeleteProgram = 0;
PFNGLDELETESHADERPROC Renderer::glDeleteShader = 0;
PFNGLDETACHSHADERPROC Renderer::glDetachShader = 0;
PFNGLDISABLEVERTEXATTRIBARRAYPROC Renderer::glDisableVertexAttribArray = 0;
PFNGLENABLEVERTEXATTRIBARRAYPROC Renderer::glEnableVertexAttribArray = 0;
PFNGLGETACTIVEATTRIBPROC Renderer::glGetActiveAttrib = 0;
PFNGLGETACTIVEUNIFORMPROC Renderer::glGetActiveUniform = 0;
PFNGLGETATTACHEDSHADERSPROC Renderer::glGetAttachedShaders = 0;
PFNGLGETATTRIBLOCATIONPROC Renderer::glGetAttribLocation = 0;
PFNGLGETPROGRAMIVPROC Renderer::glGetProgramiv = 0;
PFNGLGETPROGRAMINFOLOGPROC Renderer::glGetProgramInfoLog = 0;
PFNGLGETSHADERIVPROC Renderer::glGetShaderiv = 0;
PFNGLGETSHADERINFOLOGPROC Renderer::glGetShaderInfoLog = 0;
PFNGLGETSHADERSOURCEPROC Renderer::glGetShaderSource = 0;
PFNGLGETUNIFORMLOCATIONPROC Renderer::glGetUniformLocation = 0;
PFNGLGETUNIFORMFVPROC Renderer::glGetUniformfv = 0;
PFNGLGETUNIFORMIVPROC Renderer::glGetUniformiv = 0;
PFNGLGETVERTEXATTRIBDVPROC Renderer::glGetVertexAttribdv = 0;
PFNGLGETVERTEXATTRIBFVPROC Renderer::glGetVertexAttribfv = 0;
PFNGLGETVERTEXATTRIBIVPROC Renderer::glGetVertexAttribiv = 0;
PFNGLGETVERTEXATTRIBPOINTERVPROC Renderer::glGetVertexAttribPointerv = 0;
PFNGLISPROGRAMPROC Renderer::glIsProgram = 0;
PFNGLISSHADERPROC Renderer::glIsShader = 0;
PFNGLLINKPROGRAMPROC Renderer::glLinkProgram = 0;
PFNGLSHADERSOURCEPROC Renderer::glShaderSource = 0;
PFNGLUSEPROGRAMPROC Renderer::glUseProgram = 0;
PFNGLUNIFORM1FPROC Renderer::glUniform1f = 0;
PFNGLUNIFORM2FPROC Renderer::glUniform2f = 0;
PFNGLUNIFORM3FPROC Renderer::glUniform3f = 0;
PFNGLUNIFORM4FPROC Renderer::glUniform4f = 0;
PFNGLUNIFORM1IPROC Renderer::glUniform1i = 0;
PFNGLUNIFORM2IPROC Renderer::glUniform2i = 0;
PFNGLUNIFORM3IPROC Renderer::glUniform3i = 0;
PFNGLUNIFORM4IPROC Renderer::glUniform4i = 0;
PFNGLUNIFORM1FVPROC Renderer::glUniform1fv = 0;
PFNGLUNIFORM2FVPROC Renderer::glUniform2fv = 0;
PFNGLUNIFORM3FVPROC Renderer::glUniform3fv = 0;
PFNGLUNIFORM4FVPROC Renderer::glUniform4fv = 0;
PFNGLUNIFORM1IVPROC Renderer::glUniform1iv = 0;
PFNGLUNIFORM2IVPROC Renderer::glUniform2iv = 0;
PFNGLUNIFORM3IVPROC Renderer::glUniform3iv = 0;
PFNGLUNIFORM4IVPROC Renderer::glUniform4iv = 0;
PFNGLUNIFORMMATRIX2FVPROC Renderer::glUniformMatrix2fv = 0;
PFNGLUNIFORMMATRIX3FVPROC Renderer::glUniformMatrix3fv = 0;
PFNGLUNIFORMMATRIX4FVPROC Renderer::glUniformMatrix4fv = 0;
PFNGLVALIDATEPROGRAMPROC Renderer::glValidateProgram = 0;
PFNGLVERTEXATTRIB1DPROC Renderer::glVertexAttrib1d = 0;
PFNGLVERTEXATTRIB1DVPROC Renderer::glVertexAttrib1dv = 0;
PFNGLVERTEXATTRIB1FPROC Renderer::glVertexAttrib1f = 0;
PFNGLVERTEXATTRIB1FVPROC Renderer::glVertexAttrib1fv = 0;
PFNGLVERTEXATTRIB1SPROC Renderer::glVertexAttrib1s = 0;
PFNGLVERTEXATTRIB1SVPROC Renderer::glVertexAttrib1sv = 0;
PFNGLVERTEXATTRIB2DPROC Renderer::glVertexAttrib2d = 0;
PFNGLVERTEXATTRIB2DVPROC Renderer::glVertexAttrib2dv = 0;
PFNGLVERTEXATTRIB2FPROC Renderer::glVertexAttrib2f = 0;
PFNGLVERTEXATTRIB2FVPROC Renderer::glVertexAttrib2fv = 0;
PFNGLVERTEXATTRIB2SPROC Renderer::glVertexAttrib2s = 0;
PFNGLVERTEXATTRIB2SVPROC Renderer::glVertexAttrib2sv = 0;
PFNGLVERTEXATTRIB3DPROC Renderer::glVertexAttrib3d = 0;
PFNGLVERTEXATTRIB3DVPROC Renderer::glVertexAttrib3dv = 0;
PFNGLVERTEXATTRIB3FPROC Renderer::glVertexAttrib3f = 0;
PFNGLVERTEXATTRIB3FVPROC Renderer::glVertexAttrib3fv = 0;
PFNGLVERTEXATTRIB3SPROC Renderer::glVertexAttrib3s = 0;
PFNGLVERTEXATTRIB3SVPROC Renderer::glVertexAttrib3sv = 0;
PFNGLVERTEXATTRIB4NBVPROC Renderer::glVertexAttrib4Nbv = 0;
PFNGLVERTEXATTRIB4NIVPROC Renderer::glVertexAttrib4Niv = 0;
PFNGLVERTEXATTRIB4NSVPROC Renderer::glVertexAttrib4Nsv = 0;
PFNGLVERTEXATTRIB4NUBPROC Renderer::glVertexAttrib4Nub = 0;
PFNGLVERTEXATTRIB4NUBVPROC Renderer::glVertexAttrib4Nubv = 0;
PFNGLVERTEXATTRIB4NUIVPROC Renderer::glVertexAttrib4Nuiv = 0;
PFNGLVERTEXATTRIB4NUSVPROC Renderer::glVertexAttrib4Nusv = 0;
PFNGLVERTEXATTRIB4BVPROC Renderer::glVertexAttrib4bv = 0;
PFNGLVERTEXATTRIB4DPROC Renderer::glVertexAttrib4d = 0;
PFNGLVERTEXATTRIB4DVPROC Renderer::glVertexAttrib4dv = 0;
PFNGLVERTEXATTRIB4FPROC Renderer::glVertexAttrib4f = 0;
PFNGLVERTEXATTRIB4FVPROC Renderer::glVertexAttrib4fv = 0;
PFNGLVERTEXATTRIB4IVPROC Renderer::glVertexAttrib4iv = 0;
PFNGLVERTEXATTRIB4SPROC Renderer::glVertexAttrib4s = 0;
PFNGLVERTEXATTRIB4SVPROC Renderer::glVertexAttrib4sv = 0;
PFNGLVERTEXATTRIB4UBVPROC Renderer::glVertexAttrib4ubv = 0;
PFNGLVERTEXATTRIB4UIVPROC Renderer::glVertexAttrib4uiv = 0;
PFNGLVERTEXATTRIB4USVPROC Renderer::glVertexAttrib4usv = 0;
PFNGLVERTEXATTRIBPOINTERPROC Renderer::glVertexAttribPointer = 0;
PFNGLGENVERTEXARRAYSPROC Renderer::glGenVertexArrays = 0;

Renderer * Renderer::s_instance = 0;


Renderer::Renderer()
	: m_window(0),
	  m_glContext(0),
	  m_projectionMatrix(glm::perspective(45.0f, 800.f / 600.f, 0.1f, 1000.0f)),
	  m_orthoMatrix(glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f)),
	  m_lastTitleUpdate(0),
	  m_helperLines(0),
	  m_helperMaterial(0)
{
	s_instance = this;
	m_stats.reset();
}

Renderer::~Renderer()
{
	if (m_glContext)
	{
		SDL_GL_DeleteContext(m_glContext);
		m_glContext = 0;
	}

	if (m_helperMaterial)
		m_helperMaterial->release();

	if (m_helperLines)
	{
		delete m_helperLines;
		m_helperLines = 0;
	}

	if (m_defaultMaterial)
		m_defaultMaterial->release();
}

#define ASSERT_FUNCTION(name) if(!(name)) { Error("gl","Function %s is not available.", #name); }

bool Renderer::setup(Window * window)
{
	m_window = window;

	m_projectionMatrix = glm::perspective(45.0f, window->getAspectRatio(), 0.1f, 1000.0f);
	m_orthoMatrix = glm::ortho(0.f, (float)m_window->getWidth(), (float)m_window->getHeight(), 0.f, -1.f, 1.f);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	m_glContext = SDL_GL_CreateContext(window->_window);
	if (m_glContext == NULL)
	{
		Error("renderer", "Cannot create OpenGL context. Error: %s", SDL_GetError());
		OS::msgBox("Cannot setup OpenGL context.", "Error");
		return false;
	}

	ASSERT_FUNCTION(glEnablei = (PFNGLENABLEIPROC)SDL_GL_GetProcAddress("glEnablei"))

	// Buffers (OpenGL 1.5)
	ASSERT_FUNCTION(glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers"));
	ASSERT_FUNCTION(glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer"));
	ASSERT_FUNCTION(glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData"));
	ASSERT_FUNCTION(glDeleteBuffers = (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers"));
	ASSERT_FUNCTION(glMapBuffer = (PFNGLMAPBUFFERPROC)SDL_GL_GetProcAddress("glMapBuffer"));
	ASSERT_FUNCTION(glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)SDL_GL_GetProcAddress("glUnmapBuffer"));
	ASSERT_FUNCTION(glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray"));
	ASSERT_FUNCTION(glGetBufferParameteriv = (PFNGLGETBUFFERPARAMETERIVPROC)SDL_GL_GetProcAddress("glGetBufferParameteriv"));

	// Texture functions (OpenGL 3.0)
	ASSERT_FUNCTION(glGenerateMipmap = (PFNGLGENERATEMIPMAPPROC)SDL_GL_GetProcAddress("glGenerateMipmap"));

	// (OpenGL 2.0)
	ASSERT_FUNCTION(glActiveTexture = (PFNGLACTIVETEXTUREPROC)SDL_GL_GetProcAddress("glActiveTexture"));

	// Shaders (OpenGL 2.0)
	ASSERT_FUNCTION(glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)SDL_GL_GetProcAddress("glBlendEquationSeparate"));
	ASSERT_FUNCTION(glDrawBuffers = (PFNGLDRAWBUFFERSPROC)SDL_GL_GetProcAddress("glDrawBuffers"));
	ASSERT_FUNCTION(glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)SDL_GL_GetProcAddress("glStencilOpSeparate"));
	ASSERT_FUNCTION(glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)SDL_GL_GetProcAddress("glStencilFuncSeparate"));
	ASSERT_FUNCTION(glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)SDL_GL_GetProcAddress("glStencilMaskSeparate"));
	ASSERT_FUNCTION(glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader"));
	ASSERT_FUNCTION(glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glBindAttribLocation"));
	ASSERT_FUNCTION(glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader"));
	ASSERT_FUNCTION(glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram"));
	ASSERT_FUNCTION(glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader"));
	ASSERT_FUNCTION(glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram"));
	ASSERT_FUNCTION(glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader"));
	ASSERT_FUNCTION(glDetachShader = (PFNGLDETACHSHADERPROC)SDL_GL_GetProcAddress("glDetachShader"));
	ASSERT_FUNCTION(glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray"));
	ASSERT_FUNCTION(glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray"));
	ASSERT_FUNCTION(glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)SDL_GL_GetProcAddress("glGetActiveAttrib"));
	ASSERT_FUNCTION(glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)SDL_GL_GetProcAddress("glGetActiveUniform"));
	ASSERT_FUNCTION(glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)SDL_GL_GetProcAddress("glGetAttachedShaders"));
	ASSERT_FUNCTION(glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation"));
	ASSERT_FUNCTION(glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv"));
	ASSERT_FUNCTION(glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog"));
	ASSERT_FUNCTION(glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv"));
	ASSERT_FUNCTION(glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog"));
	ASSERT_FUNCTION(glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)SDL_GL_GetProcAddress("glGetShaderSource"));
	ASSERT_FUNCTION(glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation"));
	ASSERT_FUNCTION(glGetUniformfv = (PFNGLGETUNIFORMFVPROC)SDL_GL_GetProcAddress("glGetUniformfv"));
	ASSERT_FUNCTION(glGetUniformiv = (PFNGLGETUNIFORMIVPROC)SDL_GL_GetProcAddress("glGetUniformiv"));
	ASSERT_FUNCTION(glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)SDL_GL_GetProcAddress("glGetVertexAttribdv"));
	ASSERT_FUNCTION(glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)SDL_GL_GetProcAddress("glGetVertexAttribfv"));
	ASSERT_FUNCTION(glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)SDL_GL_GetProcAddress("glGetVertexAttribiv"));
	ASSERT_FUNCTION(glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)SDL_GL_GetProcAddress("glGetVertexAttribPointerv"));
	ASSERT_FUNCTION(glIsProgram = (PFNGLISPROGRAMPROC)SDL_GL_GetProcAddress("glIsProgram"));
	ASSERT_FUNCTION(glIsShader = (PFNGLISSHADERPROC)SDL_GL_GetProcAddress("glIsShader"));
	ASSERT_FUNCTION(glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram"));
	ASSERT_FUNCTION(glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource"));
	ASSERT_FUNCTION(glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram"));
	ASSERT_FUNCTION(glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glUniform1f"));
	ASSERT_FUNCTION(glUniform2f = (PFNGLUNIFORM2FPROC)SDL_GL_GetProcAddress("glUniform2f"));
	ASSERT_FUNCTION(glUniform3f = (PFNGLUNIFORM3FPROC)SDL_GL_GetProcAddress("glUniform3f"));
	ASSERT_FUNCTION(glUniform4f = (PFNGLUNIFORM4FPROC)SDL_GL_GetProcAddress("glUniform4f"));
	ASSERT_FUNCTION(glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glUniform1i"));
	ASSERT_FUNCTION(glUniform2i = (PFNGLUNIFORM2IPROC)SDL_GL_GetProcAddress("glUniform2i"));
	ASSERT_FUNCTION(glUniform3i = (PFNGLUNIFORM3IPROC)SDL_GL_GetProcAddress("glUniform3i"));
	ASSERT_FUNCTION(glUniform4i = (PFNGLUNIFORM4IPROC)SDL_GL_GetProcAddress("glUniform4i"));
	ASSERT_FUNCTION(glUniform1fv = (PFNGLUNIFORM1FVPROC)SDL_GL_GetProcAddress("glUniform1fv"));
	ASSERT_FUNCTION(glUniform2fv = (PFNGLUNIFORM2FVPROC)SDL_GL_GetProcAddress("glUniform2fv"));
	ASSERT_FUNCTION(glUniform3fv = (PFNGLUNIFORM3FVPROC)SDL_GL_GetProcAddress("glUniform3fv"));
	ASSERT_FUNCTION(glUniform4fv = (PFNGLUNIFORM4FVPROC)SDL_GL_GetProcAddress("glUniform4fv"));
	ASSERT_FUNCTION(glUniform1iv = (PFNGLUNIFORM1IVPROC)SDL_GL_GetProcAddress("glUniform1iv"));
	ASSERT_FUNCTION(glUniform2iv = (PFNGLUNIFORM2IVPROC)SDL_GL_GetProcAddress("glUniform2iv"));
	ASSERT_FUNCTION(glUniform3iv = (PFNGLUNIFORM3IVPROC)SDL_GL_GetProcAddress("glUniform3iv"));
	ASSERT_FUNCTION(glUniform4iv = (PFNGLUNIFORM4IVPROC)SDL_GL_GetProcAddress("glUniform4iv"));
	ASSERT_FUNCTION(glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)SDL_GL_GetProcAddress("glUniformMatrix2fv"));
	ASSERT_FUNCTION(glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)SDL_GL_GetProcAddress("glUniformMatrix3fv"));
	ASSERT_FUNCTION(glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv"));
	ASSERT_FUNCTION(glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)SDL_GL_GetProcAddress("glValidateProgram"));
	ASSERT_FUNCTION(glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)SDL_GL_GetProcAddress("glVertexAttrib1d"));
	ASSERT_FUNCTION(glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)SDL_GL_GetProcAddress("glVertexAttrib1dv"));
	ASSERT_FUNCTION(glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)SDL_GL_GetProcAddress("glVertexAttrib1f"));
	ASSERT_FUNCTION(glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)SDL_GL_GetProcAddress("glVertexAttrib1fv"));
	ASSERT_FUNCTION(glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)SDL_GL_GetProcAddress("glVertexAttrib1s"));
	ASSERT_FUNCTION(glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)SDL_GL_GetProcAddress("glVertexAttrib1sv"));
	ASSERT_FUNCTION(glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)SDL_GL_GetProcAddress("glVertexAttrib2d"));
	ASSERT_FUNCTION(glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)SDL_GL_GetProcAddress("glVertexAttrib2dv"));
	ASSERT_FUNCTION(glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)SDL_GL_GetProcAddress("glVertexAttrib2f"));
	ASSERT_FUNCTION(glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)SDL_GL_GetProcAddress("glVertexAttrib2fv"));
	ASSERT_FUNCTION(glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)SDL_GL_GetProcAddress("glVertexAttrib2s"));
	ASSERT_FUNCTION(glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)SDL_GL_GetProcAddress("glVertexAttrib2sv"));
	ASSERT_FUNCTION(glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)SDL_GL_GetProcAddress("glVertexAttrib3d"));
	ASSERT_FUNCTION(glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)SDL_GL_GetProcAddress("glVertexAttrib3dv"));
	ASSERT_FUNCTION(glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)SDL_GL_GetProcAddress("glVertexAttrib3f"));
	ASSERT_FUNCTION(glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)SDL_GL_GetProcAddress("glVertexAttrib3fv"));
	ASSERT_FUNCTION(glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)SDL_GL_GetProcAddress("glVertexAttrib3s"));
	ASSERT_FUNCTION(glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)SDL_GL_GetProcAddress("glVertexAttrib3sv"));
	ASSERT_FUNCTION(glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nbv"));
	ASSERT_FUNCTION(glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Niv"));
	ASSERT_FUNCTION(glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nsv"));
	ASSERT_FUNCTION(glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nub"));
	ASSERT_FUNCTION(glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nubv"));
	ASSERT_FUNCTION(glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nuiv"));
	ASSERT_FUNCTION(glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nusv"));
	ASSERT_FUNCTION(glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)SDL_GL_GetProcAddress("glVertexAttrib4bv"));
	ASSERT_FUNCTION(glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)SDL_GL_GetProcAddress("glVertexAttrib4d"));
	ASSERT_FUNCTION(glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)SDL_GL_GetProcAddress("glVertexAttrib4dv"));
	ASSERT_FUNCTION(glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)SDL_GL_GetProcAddress("glVertexAttrib4f"));
	ASSERT_FUNCTION(glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)SDL_GL_GetProcAddress("glVertexAttrib4fv"));
	ASSERT_FUNCTION(glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)SDL_GL_GetProcAddress("glVertexAttrib4iv"));
	ASSERT_FUNCTION(glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)SDL_GL_GetProcAddress("glVertexAttrib4s"));
	ASSERT_FUNCTION(glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)SDL_GL_GetProcAddress("glVertexAttrib4sv"));
	ASSERT_FUNCTION(glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4ubv"));
	ASSERT_FUNCTION(glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4uiv"));
	ASSERT_FUNCTION(glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)SDL_GL_GetProcAddress("glVertexAttrib4usv"));
	ASSERT_FUNCTION(glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer"));

	ASSERT_FUNCTION(glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays"));

	SDL_GL_SetSwapInterval(Config::get()["graphics"]["vsync"].getBool(false) ? 1 : 0); // set 0 to disable vsync
	
	glViewport(0, 0, window->getWidth(), window->getHeight());
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	
	m_defaultMaterial = MaterialLib::get()->findByName("default");
	m_defaultMaterial->acquire();

	m_helperMaterial = MaterialLib::get()->findByName("primitive");
	m_helperMaterial->acquire();

	unsigned int HackVAO;
	glGenVertexArrays(1, &HackVAO);
	glBindVertexArray(HackVAO);
	
	m_helperLines = new Geometry<Vertex3d>(EDrawType::LINES);

	Vertex3d vertices[4] = { 0 };

	// Format: 0xAABBGGRR bcz of endian
	vertices[1].x = 8;
	vertices[1].color = 0xFF0000FF;

	vertices[2].y = 8;
	vertices[2].color = 0xFF00FF00;

	vertices[3].z = 8;
	vertices[3].color = 0xFFFF0000;

	unsigned short indices[6] = {
		0, 1,
		0, 2,
		0, 3
	};

	m_helperLines->fillData(vertices, 4, indices, 2);
	return true;
}

void Renderer::preFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearColor(0.9f, 0.9f, 0.9f, 1.0f);	
	glClearDepth(1.0f);

	setMaterial(m_helperMaterial);
	renderGeometry(m_helperLines, glm::mat4x4());
	setMaterial(m_defaultMaterial);
}

void Renderer::postFrame()
{	
	SDL_GL_SwapWindow(m_window->_window);	

	unsigned int now = unsigned int(OS::getMicrosecondsCount() / 1000);
	if (now - m_lastTitleUpdate >= 500)
	{
		SDL_SetWindowTitle(m_window->_window, String<64>("Engine - TD: %d, DC: %d, VD: %d, FPS: %.1f", m_stats.m_trianglesDrawn, m_stats.m_drawCalls, m_stats.m_verticesDrawn, Timer::getFPS()));
		m_lastTitleUpdate = now;
	}

	m_stats.reset();
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

void Renderer::setMaterial(Material* material)
{
	m_currentMaterial = material;
}

Material * Renderer::getMaterial()
{
	return m_currentMaterial;
}

void Renderer::renderGeometry(Geometry<Vertex3d> *geometry, const glm::mat4x4& matrix)
{
	Material* material = m_currentMaterial;
	if (!material)
		material = m_defaultMaterial;

	// TODO: Renderer update matrices function
	//m_projectionMatrix = glm::perspective(Camera::current->getFov(), m_window->getAspectRatio(), 0.1f, 1000.0f);

	// Shaders
	if (!material)
	{
		//Error("renderer", "Cannot render geometry. No material found!");
		return;
	}

	if (!material->m_program || !glIsProgram(material->m_program->m_programId))
	{
		//Error("renderer", "Cannot render geometry. No shader program assigned for material.");
		return;
	}
	
	glUseProgram(material->m_program->m_programId);

	glm::mat4x4 viewMatrix = Camera::current->getViewMatrix();
#if 0
	unsigned int modelMatrixLocation = material->m_program->getUniformLocation("modelMatrix");
	if (modelMatrixLocation != -1)
	{
		glUniformMatrix4fv(modelMatrixLocation, 1, GL_FALSE, glm::value_ptr(matrix));
	}

	unsigned int projectionMatrixLocation = material->m_program->getUniformLocation("projectionMatrix");
	if (projectionMatrixLocation != -1)
	{
		glUniformMatrix4fv(projectionMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_projectionMatrix));
	}
			
	unsigned int viewMatrixLocation = material->m_program->getUniformLocation("viewMatrix");
	if (viewMatrixLocation != -1)
	{
		glUniformMatrix4fv(viewMatrixLocation, 1, GL_FALSE, glm::value_ptr(viewMatrix));
	}
#endif

	glm::mat4x4 mvp = m_projectionMatrix * viewMatrix * matrix;

	unsigned int mvpMatrixLocation = material->m_program->getUniformLocation("mvpMatrix");
	if (mvpMatrixLocation != -1)
	{
		glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	if (material->m_texture)
	{
		unsigned int texture0Location = material->m_program->getUniformLocation("texture0");
		if (texture0Location != -1 && material->m_texture->isLoaded())
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, material->m_texture->m_textureID);		

			if (material->m_texture->m_mipmaps)
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

				// Set max anisotropy level (TODO: user settings)
				GLfloat largest = 1.0f;
				glGetFloatv(GL_MAX_TEXTURE_MAX_ANISOTROPY_EXT, &largest);
				glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAX_ANISOTROPY_EXT, largest);
			}
			else 
			{
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
				glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
			}
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
			
			
			glUniform1i(texture0Location, 0);
		}
	}

	unsigned int attributePosition = material->m_program->getAttributeLocation("vertexPosition");
	unsigned int attributeNormal = material->m_program->getAttributeLocation("vertexNormal");
	unsigned int attributeUV = material->m_program->getAttributeLocation("vertexUV");
	unsigned int attributeColor = material->m_program->getAttributeLocation("vertexColor");

	glEnableVertexAttribArray(attributePosition);
	if (attributeNormal != -1)
		glEnableVertexAttribArray(attributeNormal);
	if (attributeUV != -1)
		glEnableVertexAttribArray(attributeUV);
	if (attributeColor != -1)
		glEnableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), 0);
	if (attributeNormal != -1)
		glVertexAttribPointer(attributeNormal, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void *)offsetof(Vertex3d, nx));
	if (attributeUV != -1)
		glVertexAttribPointer(attributeUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void *)offsetof(Vertex3d, u));
	if (attributeColor != -1)
		glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3d), (void *)offsetof(Vertex3d, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	unsigned int drawMode = GL_TRIANGLES;
	if (geometry->m_drawType == EDrawType::LINES) drawMode = GL_LINES;
	else if (geometry->m_drawType == EDrawType::LINE_STRIP) drawMode = GL_LINE_STRIP;

	glDrawElements(drawMode, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);
	m_stats.m_trianglesDrawn += geometry->m_trianglesCount;
	m_stats.m_drawCalls++;
	m_stats.m_verticesDrawn += geometry->m_verticesCount;

	glDisableVertexAttribArray(attributePosition);
	if (attributeNormal != -1)
		glDisableVertexAttribArray(attributeNormal);
	if (attributeUV != -1)
		glDisableVertexAttribArray(attributeUV);
	if (attributeColor!= -1)
		glDisableVertexAttribArray(attributeColor);

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

struct SimpleVertex2d
{
	float x, y;
	unsigned int color;
	float u, v;
};

void Renderer::renderFont(DynString string, const Rect& rect, const Color& color, flags32 flags, Font *font)
{
	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Material* material = font->m_material;

	uint32 xcolor = ((uint8)(color.a * 255) << 24) | ((uint8)(color.b * 255) << 16) | ((uint8)(color.g * 255) << 8) | ((uint8)(color.r * 255));

	SimpleVertex2d * vertices = new SimpleVertex2d[string.getLength() * 4];
	uint16 *indices = new uint16[string.getLength() * 6];

	uint32 vid = 0;
	uint32 iid = 0;
	float x = rect.x;
	float y = rect.y + 19.f;
	for (uint32 i = 0; i < string.getLength(); ++i)
	{
		unsigned char charCode = string[i];
		if (charCode == '\0')
			break;

		if (charCode == '\n')
		{
			y += font->m_size;
			x = rect.x;
			continue;
		}

		if (charCode == ' ')
		{
			x += font->m_size/2;
			continue;
		}

		Font::GlyphData data = font->getData(charCode);
		int a, b, c, d;
		if (data.set)
		{
			vertices[vid].x = x;
			vertices[vid].y = y - data.top;
			vertices[vid].u = data.x;
			vertices[vid].v = data.y;
			vertices[vid].color = xcolor;
			a = vid;
			vid++;

			vertices[vid].x = x + data.bmw;
			vertices[vid].y = y - data.top;
			vertices[vid].u = data.w;
			vertices[vid].v = data.y;
			vertices[vid].color = xcolor;
			b = vid;
			vid++;

			vertices[vid].x = x;
			vertices[vid].y = y + data.bmh - data.top;
			vertices[vid].u = data.x;
			vertices[vid].v = data.h;
			vertices[vid].color = xcolor;
			c = vid;
			vid++;

			vertices[vid].x = x + data.bmw;
			vertices[vid].y = y + data.bmh - data.top;
			vertices[vid].u = data.w;
			vertices[vid].v = data.h;
			vertices[vid].color = xcolor;
			d = vid;
			vid++;


			indices[iid] = a;
			iid++;
			indices[iid] = b;
			iid++;
			indices[iid] = c;
			iid++;

			indices[iid] = b;
			iid++;
			indices[iid] = d;
			iid++;
			indices[iid] = c;
			iid++;

			x += data.bmw+2;
		}
		else
		{
			Info("rr", "Using unknown character. %c", charCode);
			x += font->m_size;
		}		
	}

	Geometry<SimpleVertex2d> geometry;
	geometry.fillData(vertices, string.getLength()*4, indices, string.getLength()*2);
	delete[]vertices;
	delete[]indices;

	// Shaders
	if (!material)
	{
		Error("renderer", "Cannot render font. No material found!");
		return;
	}

	if (!material->m_program || !glIsProgram(material->m_program->m_programId))
	{
		Error("renderer", "Cannot render font. No shader program assigned for material.");
		return;
	}

	glUseProgram(material->m_program->m_programId);

	unsigned int orthoMatrixLocation = material->m_program->getUniformLocation("orthoMatrix");
	if (orthoMatrixLocation != -1)
	{
		glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_orthoMatrix));
	}

	if (glIsTexture(font->m_textureId))
	{
		unsigned int textureLocation = material->m_program->getUniformLocation("texture");
		if (textureLocation != -1)
		{
			glActiveTexture(GL_TEXTURE0);
			glBindTexture(GL_TEXTURE_2D, font->m_textureId);
			glUniform1i(textureLocation, 0);
		}
	}

	unsigned int attributePosition = material->m_program->getAttributeLocation("vertexPosition");
	unsigned int attributeUV = material->m_program->getAttributeLocation("vertexUV");
	unsigned int attributeColor = material->m_program->getAttributeLocation("vertexColor");

	glEnableVertexAttribArray(attributePosition);
	if (attributeUV != -1)
		glEnableVertexAttribArray(attributeUV);
	if (attributeColor != -1)
		glEnableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, geometry.m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(attributePosition, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex2d), 0);
	if (attributeUV != -1)
		glVertexAttribPointer(attributeUV, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex2d), (void *)offsetof(SimpleVertex2d, u));
	if (attributeColor != -1)
		glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SimpleVertex2d), (void *)offsetof(SimpleVertex2d, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry.m_indexBuffer->m_bufferId);

	glDrawElements(GL_TRIANGLES, geometry.m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(attributePosition);
	if (attributeUV != -1)
		glDisableVertexAttribArray(attributeUV);
	if (attributeColor != -1)
		glDisableVertexAttribArray(attributeColor);

	glUseProgram(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
}


Renderer& Renderer::get()
{
	return *s_instance;
}