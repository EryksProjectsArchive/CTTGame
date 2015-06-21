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

#include <graphics/ShaderProgram.h>

// Extension methods
PFNGLGENBUFFERSPROC Renderer::glGenBuffers = 0;
PFNGLBINDBUFFERPROC Renderer::glBindBuffer = 0;
PFNGLBUFFERDATAPROC Renderer::glBufferData = 0;
PFNGLMAPBUFFERPROC Renderer::glMapBuffer = 0;
PFNGLUNMAPBUFFERPROC Renderer::glUnmapBuffer = 0;
PFNGLDELETEBUFFERSPROC Renderer::glDeleteBuffers = 0;
PFNGLBINDVERTEXARRAYPROC Renderer::glBindVertexArray = 0;

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
{
	m_window = 0;
	m_glContext = 0;
	s_instance = this;
	m_defaultMaterial = 0;
	m_currentMaterial = 0;
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
	
	// Buffers (OpenGL 1.5)
	glGenBuffers = (PFNGLGENBUFFERSPROC)SDL_GL_GetProcAddress("glGenBuffers");
	glBindBuffer = (PFNGLBINDBUFFERPROC)SDL_GL_GetProcAddress("glBindBuffer");
	glBufferData = (PFNGLBUFFERDATAPROC)SDL_GL_GetProcAddress("glBufferData");
	glDeleteBuffers	= (PFNGLDELETEBUFFERSPROC)SDL_GL_GetProcAddress("glDeleteBuffers");
	glMapBuffer	= (PFNGLMAPBUFFERPROC)SDL_GL_GetProcAddress("glMapBuffer");
	glUnmapBuffer = (PFNGLUNMAPBUFFERPROC)SDL_GL_GetProcAddress("glUnmapBuffer");
	glBindVertexArray = (PFNGLBINDVERTEXARRAYPROC)SDL_GL_GetProcAddress("glBindVertexArray");

	// Shaders (OpenGL 2.0)
	glBlendEquationSeparate = (PFNGLBLENDEQUATIONSEPARATEPROC)SDL_GL_GetProcAddress("glBlendEquationSeparate");
	glDrawBuffers = (PFNGLDRAWBUFFERSPROC)SDL_GL_GetProcAddress("glDrawBuffers");
	glStencilOpSeparate = (PFNGLSTENCILOPSEPARATEPROC)SDL_GL_GetProcAddress("glStencilOpSeparate");
	glStencilFuncSeparate = (PFNGLSTENCILFUNCSEPARATEPROC)SDL_GL_GetProcAddress("glStencilFuncSeparate");
	glStencilMaskSeparate = (PFNGLSTENCILMASKSEPARATEPROC)SDL_GL_GetProcAddress("glStencilMaskSeparate");
	glAttachShader = (PFNGLATTACHSHADERPROC)SDL_GL_GetProcAddress("glAttachShader");
	glBindAttribLocation = (PFNGLBINDATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glBindAttribLocation");
	glCompileShader = (PFNGLCOMPILESHADERPROC)SDL_GL_GetProcAddress("glCompileShader");
	glCreateProgram = (PFNGLCREATEPROGRAMPROC)SDL_GL_GetProcAddress("glCreateProgram");
	glCreateShader = (PFNGLCREATESHADERPROC)SDL_GL_GetProcAddress("glCreateShader");
	glDeleteProgram = (PFNGLDELETEPROGRAMPROC)SDL_GL_GetProcAddress("glDeleteProgram");
	glDeleteShader = (PFNGLDELETESHADERPROC)SDL_GL_GetProcAddress("glDeleteShader");
	glDetachShader = (PFNGLDETACHSHADERPROC)SDL_GL_GetProcAddress("glDetachShader");
	glDisableVertexAttribArray = (PFNGLDISABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glDisableVertexAttribArray");
	glEnableVertexAttribArray = (PFNGLENABLEVERTEXATTRIBARRAYPROC)SDL_GL_GetProcAddress("glEnableVertexAttribArray");
	glGetActiveAttrib = (PFNGLGETACTIVEATTRIBPROC)SDL_GL_GetProcAddress("glGetActiveAttrib");
	glGetActiveUniform = (PFNGLGETACTIVEUNIFORMPROC)SDL_GL_GetProcAddress("glGetActiveUniform");
	glGetAttachedShaders = (PFNGLGETATTACHEDSHADERSPROC)SDL_GL_GetProcAddress("glGetAttachedShaders");
	glGetAttribLocation = (PFNGLGETATTRIBLOCATIONPROC)SDL_GL_GetProcAddress("glGetAttribLocation");
	glGetProgramiv = (PFNGLGETPROGRAMIVPROC)SDL_GL_GetProcAddress("glGetProgramiv");
	glGetProgramInfoLog = (PFNGLGETPROGRAMINFOLOGPROC)SDL_GL_GetProcAddress("glGetProgramInfoLog");
	glGetShaderiv = (PFNGLGETSHADERIVPROC)SDL_GL_GetProcAddress("glGetShaderiv");
	glGetShaderInfoLog = (PFNGLGETSHADERINFOLOGPROC)SDL_GL_GetProcAddress("glGetShaderInfoLog");
	glGetShaderSource = (PFNGLGETSHADERSOURCEPROC)SDL_GL_GetProcAddress("glGetShaderSource");
	glGetUniformLocation = (PFNGLGETUNIFORMLOCATIONPROC)SDL_GL_GetProcAddress("glGetUniformLocation");
	glGetUniformfv = (PFNGLGETUNIFORMFVPROC)SDL_GL_GetProcAddress("glGetUniformfv");
	glGetUniformiv = (PFNGLGETUNIFORMIVPROC)SDL_GL_GetProcAddress("glGetUniformiv");
	glGetVertexAttribdv = (PFNGLGETVERTEXATTRIBDVPROC)SDL_GL_GetProcAddress("glGetVertexAttribdv");
	glGetVertexAttribfv = (PFNGLGETVERTEXATTRIBFVPROC)SDL_GL_GetProcAddress("glGetVertexAttribfv");
	glGetVertexAttribiv = (PFNGLGETVERTEXATTRIBIVPROC)SDL_GL_GetProcAddress("glGetVertexAttribiv");
	glGetVertexAttribPointerv = (PFNGLGETVERTEXATTRIBPOINTERVPROC)SDL_GL_GetProcAddress("glGetVertexAttribPointerv");
	glIsProgram = (PFNGLISPROGRAMPROC)SDL_GL_GetProcAddress("glIsProgram");
	glIsShader = (PFNGLISSHADERPROC)SDL_GL_GetProcAddress("IsShader");
	glLinkProgram = (PFNGLLINKPROGRAMPROC)SDL_GL_GetProcAddress("glLinkProgram");
	glShaderSource = (PFNGLSHADERSOURCEPROC)SDL_GL_GetProcAddress("glShaderSource");
	glUseProgram = (PFNGLUSEPROGRAMPROC)SDL_GL_GetProcAddress("glUseProgram");
	glUniform1f = (PFNGLUNIFORM1FPROC)SDL_GL_GetProcAddress("glUniform1f");
	glUniform2f = (PFNGLUNIFORM2FPROC)SDL_GL_GetProcAddress("glUniform2f");
	glUniform3f = (PFNGLUNIFORM3FPROC)SDL_GL_GetProcAddress("glUniform3f");
	glUniform4f = (PFNGLUNIFORM4FPROC)SDL_GL_GetProcAddress("glUniform4f");
	glUniform1i = (PFNGLUNIFORM1IPROC)SDL_GL_GetProcAddress("glUniform1i");
	glUniform2i = (PFNGLUNIFORM2IPROC)SDL_GL_GetProcAddress("glUniform2i");
	glUniform3i = (PFNGLUNIFORM3IPROC)SDL_GL_GetProcAddress("glUniform3i");
	glUniform4i = (PFNGLUNIFORM4IPROC)SDL_GL_GetProcAddress("glUniform4i");
	glUniform1fv = (PFNGLUNIFORM1FVPROC)SDL_GL_GetProcAddress("glUniform1fv");
	glUniform2fv = (PFNGLUNIFORM2FVPROC)SDL_GL_GetProcAddress("glUniform2fv");
	glUniform3fv = (PFNGLUNIFORM3FVPROC)SDL_GL_GetProcAddress("glUniform3fv");
	glUniform4fv = (PFNGLUNIFORM4FVPROC)SDL_GL_GetProcAddress("glUniform4fv");
	glUniform1iv = (PFNGLUNIFORM1IVPROC)SDL_GL_GetProcAddress("glUniform1iv");
	glUniform2iv = (PFNGLUNIFORM2IVPROC)SDL_GL_GetProcAddress("glUniform2iv");
	glUniform3iv = (PFNGLUNIFORM3IVPROC)SDL_GL_GetProcAddress("glUniform3iv");
	glUniform4iv = (PFNGLUNIFORM4IVPROC)SDL_GL_GetProcAddress("glUniform4iv");
	glUniformMatrix2fv = (PFNGLUNIFORMMATRIX2FVPROC)SDL_GL_GetProcAddress("glUniformMatrix2fv");
	glUniformMatrix3fv = (PFNGLUNIFORMMATRIX3FVPROC)SDL_GL_GetProcAddress("glUniformMatrix3fv");
	glUniformMatrix4fv = (PFNGLUNIFORMMATRIX4FVPROC)SDL_GL_GetProcAddress("glUniformMatrix4fv");
	glValidateProgram = (PFNGLVALIDATEPROGRAMPROC)SDL_GL_GetProcAddress("glValidateProgram");
	glVertexAttrib1d = (PFNGLVERTEXATTRIB1DPROC)SDL_GL_GetProcAddress("glVertexAttrib1d");
	glVertexAttrib1dv = (PFNGLVERTEXATTRIB1DVPROC)SDL_GL_GetProcAddress("glVertexAttrib1dv");
	glVertexAttrib1f = (PFNGLVERTEXATTRIB1FPROC)SDL_GL_GetProcAddress("glVertexAttrib1f");
	glVertexAttrib1fv = (PFNGLVERTEXATTRIB1FVPROC)SDL_GL_GetProcAddress("glVertexAttrib1fv");
	glVertexAttrib1s = (PFNGLVERTEXATTRIB1SPROC)SDL_GL_GetProcAddress("glVertexAttrib1s");
	glVertexAttrib1sv = (PFNGLVERTEXATTRIB1SVPROC)SDL_GL_GetProcAddress("glVertexAttrib1sv");
	glVertexAttrib2d = (PFNGLVERTEXATTRIB2DPROC)SDL_GL_GetProcAddress("glVertexAttrib2d");
	glVertexAttrib2dv = (PFNGLVERTEXATTRIB2DVPROC)SDL_GL_GetProcAddress("glVertexAttrib2dv");
	glVertexAttrib2f = (PFNGLVERTEXATTRIB2FPROC)SDL_GL_GetProcAddress("glVertexAttrib2f");
	glVertexAttrib2fv = (PFNGLVERTEXATTRIB2FVPROC)SDL_GL_GetProcAddress("glVertexAttrib2fv");
	glVertexAttrib2s = (PFNGLVERTEXATTRIB2SPROC)SDL_GL_GetProcAddress("glVertexAttrib2s");
	glVertexAttrib2sv = (PFNGLVERTEXATTRIB2SVPROC)SDL_GL_GetProcAddress("glVertexAttrib2sv");
	glVertexAttrib3d = (PFNGLVERTEXATTRIB3DPROC)SDL_GL_GetProcAddress("glVertexAttrib3d");
	glVertexAttrib3dv = (PFNGLVERTEXATTRIB3DVPROC)SDL_GL_GetProcAddress("glVertexAttrib3dv");
	glVertexAttrib3f = (PFNGLVERTEXATTRIB3FPROC)SDL_GL_GetProcAddress("glVertexAttrib3f");
	glVertexAttrib3fv = (PFNGLVERTEXATTRIB3FVPROC)SDL_GL_GetProcAddress("glVertexAttrib3fv");
	glVertexAttrib3s = (PFNGLVERTEXATTRIB3SPROC)SDL_GL_GetProcAddress("glVertexAttrib3s");
	glVertexAttrib3sv = (PFNGLVERTEXATTRIB3SVPROC)SDL_GL_GetProcAddress("glVertexAttrib3sv");
	glVertexAttrib4Nbv = (PFNGLVERTEXATTRIB4NBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nbv");
	glVertexAttrib4Niv = (PFNGLVERTEXATTRIB4NIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Niv");
	glVertexAttrib4Nsv = (PFNGLVERTEXATTRIB4NSVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nsv");
	glVertexAttrib4Nub = (PFNGLVERTEXATTRIB4NUBPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nub");
	glVertexAttrib4Nubv = (PFNGLVERTEXATTRIB4NUBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nubv");
	glVertexAttrib4Nuiv = (PFNGLVERTEXATTRIB4NUIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nuiv");
	glVertexAttrib4Nusv = (PFNGLVERTEXATTRIB4NUSVPROC)SDL_GL_GetProcAddress("glVertexAttrib4Nusv");
	glVertexAttrib4bv = (PFNGLVERTEXATTRIB4BVPROC)SDL_GL_GetProcAddress("glVertexAttrib4bv");
	glVertexAttrib4d = (PFNGLVERTEXATTRIB4DPROC)SDL_GL_GetProcAddress("glVertexAttrib4d");
	glVertexAttrib4dv = (PFNGLVERTEXATTRIB4DVPROC)SDL_GL_GetProcAddress("glVertexAttrib4dv");
	glVertexAttrib4f = (PFNGLVERTEXATTRIB4FPROC)SDL_GL_GetProcAddress("glVertexAttrib4f");
	glVertexAttrib4fv = (PFNGLVERTEXATTRIB4FVPROC)SDL_GL_GetProcAddress("glVertexAttrib4fv");
	glVertexAttrib4iv = (PFNGLVERTEXATTRIB4IVPROC)SDL_GL_GetProcAddress("glVertexAttrib4iv");
	glVertexAttrib4s = (PFNGLVERTEXATTRIB4SPROC)SDL_GL_GetProcAddress("glVertexAttrib4s");
	glVertexAttrib4sv = (PFNGLVERTEXATTRIB4SVPROC)SDL_GL_GetProcAddress("glVertexAttrib4sv");
	glVertexAttrib4ubv = (PFNGLVERTEXATTRIB4UBVPROC)SDL_GL_GetProcAddress("glVertexAttrib4ubv");
	glVertexAttrib4uiv = (PFNGLVERTEXATTRIB4UIVPROC)SDL_GL_GetProcAddress("glVertexAttrib4uiv");
	glVertexAttrib4usv = (PFNGLVERTEXATTRIB4USVPROC)SDL_GL_GetProcAddress("glVertexAttrib4usv");
	glVertexAttribPointer = (PFNGLVERTEXATTRIBPOINTERPROC)SDL_GL_GetProcAddress("glVertexAttribPointer");

	glGenVertexArrays = (PFNGLGENVERTEXARRAYSPROC)SDL_GL_GetProcAddress("glGenVertexArrays");

	SDL_GL_SetSwapInterval(1);

	glViewport(0, 0, 800, 600);
	//glEnablei(GL_BLEND, 0);
	//glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	
	m_defaultMaterial = new Material();// MaterialLib::FindByName("default");

	ShaderProgram *shaderProgram = new ShaderProgram();

	FragmentShader * fragmentShader = new FragmentShader("../../data/shaders/simple.frag");
	shaderProgram->attachShader(fragmentShader);

	VertexShader * vertexShader = new VertexShader("../../data/shaders/simple.vert");
	shaderProgram->attachShader(vertexShader);

	shaderProgram->link();

	m_defaultMaterial->m_program = shaderProgram;

	unsigned int HackVAO;
	glGenVertexArrays(1, &HackVAO);
	glBindVertexArray(HackVAO);

	return true;
}

void Renderer::preFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glClearDepth(1.0f);
	glClearColor(0.0f, 0.5f, 0.0f, 0.0f);	
}

void Renderer::postFrame()
{
	
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

void Renderer::renderGeometry(Geometry *geometry, glm::mat4x4 * matrix)
{
	Material *material = m_currentMaterial;
	if (!material)
		material = m_defaultMaterial;

	// Shaders
	if (material)
	{
		if (material->m_program && glIsProgram(material->m_program->m_programId))
		{
			glUseProgram(material->m_program->m_programId);

			unsigned int modelMatrixLocation = material->m_program->getUniformLocation("modelMatrix");
			if (modelMatrixLocation != -1)
			{
				glUniformMatrix4fv(modelMatrixLocation, 1, false, (float *)matrix);
			}
		
			glm::mat4x4 projectionMatrix;
			projectionMatrix = glm::perspective(0.78f, 800.f / 600.f, 0.1f, 10000.0f);

			unsigned int projectionMatrixLocation = material->m_program->getUniformLocation("projectionMatrix");
			if (projectionMatrixLocation != -1)
			{
				glUniformMatrix4fv(projectionMatrixLocation, 1, false, &projectionMatrix[0][0]);
			}

			glm::mat4x4 viewMatrix = glm::lookAt(glm::vec3(30, 30, 30), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
			
			unsigned int viewMatrixLocation = material->m_program->getUniformLocation("viewMatrix");
			if (viewMatrixLocation != -1)
			{
				glUniformMatrix4fv(viewMatrixLocation, 1, false, &viewMatrix[0][0]);
			}
			
			glm::mat4x4 mvp = projectionMatrix * viewMatrix * *matrix;

			unsigned int mvpMatrixLocation = material->m_program->getUniformLocation("mvpMatrix");
			if (mvpMatrixLocation != -1)
			{
				glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp));
			}
			
			unsigned int texture0Location = material->m_program->getUniformLocation("texture0");
			if (texture0Location != -1)
			{
				glUniform1i(texture0Location, 0);
			}
			
			
#ifdef DEBUG_PROGRAM_ON_RUNTIME
			int m_programId = material->m_program->m_programId;
			GLint maxLength = 0;
			Renderer::glGetProgramiv(m_programId, GL_INFO_LOG_LENGTH, &maxLength);

			//The maxLength includes the NULL character
			char *errorLog = new char[maxLength + 1];

			Renderer::glGetProgramInfoLog(m_programId, maxLength, &maxLength, errorLog);

			Error("program", "LOG: %s", errorLog);

			delete[]errorLog;
#endif
		}
		
	}

	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), (void *)(sizeof(float) * 3));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements(GL_TRIANGLES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);

	glUseProgram(0);	
}

Renderer& Renderer::get()
{
	return *s_instance;
}