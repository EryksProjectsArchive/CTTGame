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

#include <core/WDynString.h>

#include <graphics/Vertex2d.h>

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
PFNGLUNIFORM1UIPROC Renderer::glUniform1ui = 0;
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

PFNGLCOMPRESSEDTEXIMAGE2DPROC Renderer::glCompressedTexImage2D = 0;

PFNGLISRENDERBUFFERPROC Renderer::glIsRenderbuffer = 0;
PFNGLBINDRENDERBUFFERPROC Renderer::glBindRenderbuffer = 0;
PFNGLDELETERENDERBUFFERSPROC Renderer::glDeleteRenderbuffers = 0;
PFNGLGENRENDERBUFFERSPROC Renderer::glGenRenderbuffers = 0;
PFNGLRENDERBUFFERSTORAGEPROC Renderer::glRenderbufferStorage = 0;
PFNGLGETRENDERBUFFERPARAMETERIVPROC Renderer::glGetRenderbufferParameteriv = 0;
PFNGLISFRAMEBUFFERPROC  Renderer::glIsFramebuffer = 0;
PFNGLBINDFRAMEBUFFERPROC Renderer::glBindFramebuffer = 0;
PFNGLDELETEFRAMEBUFFERSPROC Renderer::glDeleteFramebuffers = 0;
PFNGLGENFRAMEBUFFERSPROC Renderer::glGenFramebuffers = 0;
PFNGLCHECKFRAMEBUFFERSTATUSPROC Renderer::glCheckFramebufferStatus = 0;
PFNGLFRAMEBUFFERTEXTURE1DPROC Renderer::glFramebufferTexture1D = 0;
PFNGLFRAMEBUFFERTEXTURE2DPROC Renderer::glFramebufferTexture2D = 0;
PFNGLFRAMEBUFFERTEXTURE3DPROC Renderer::glFramebufferTexture3D = 0;
PFNGLFRAMEBUFFERRENDERBUFFERPROC Renderer::glFramebufferRenderbuffer = 0;
PFNGLGETFRAMEBUFFERATTACHMENTPARAMETERIVPROC Renderer::glGetFramebufferAttachmentParameteriv = 0;
PFNGLGENERATEMIPMAPPROC Renderer::glGenerateMipmap = 0;
PFNGLBLITFRAMEBUFFERPROC Renderer::glBlitFramebuffer = 0;
PFNGLRENDERBUFFERSTORAGEMULTISAMPLEPROC Renderer::glRenderbufferStorageMultisample = 0;
PFNGLFRAMEBUFFERTEXTURELAYERPROC Renderer::glFramebufferTextureLayer = 0;

SETUP_INSTANCE(Renderer);

Renderer::Renderer()
	: m_window(0),
	  m_glContext(0),
	  m_projectionMatrix(glm::perspective(glm::radians(45.0f), 800.f / 600.f, 0.1f, 1000.0f)),
	  m_orthoMatrix(glm::ortho(0.f, 800.f, 600.f, 0.f, -1.f, 1.f))
{
	m_stats.reset();
}

Renderer::~Renderer()
{
	if (m_glContext)
	{
		SDL_GL_DeleteContext(m_glContext);
		m_glContext = 0;
	}

	m_deferredRenderer.destroy();
	m_dynamicShadowsPass.destroy();

	if (m_defaultMaterial)
		m_defaultMaterial->release();

	if (m_simpleColorMat)
		m_simpleColorMat->release();
}

bool Renderer::setup(Window * window)
{
	m_window = window;

	m_projectionMatrix = glm::perspective(glm::radians(45.0f), window->getAspectRatio(), 0.1f, 1000.0f);

	m_rect.bottom = float(m_window->getHeight());
	m_rect.right = float(m_window->getWidth());

	m_orthoMatrix = glm::ortho(0.f, m_rect.right, m_rect.bottom, 0.f, -1.f, 1.f);
	m_viewport = glm::vec4(0, 0, m_rect.right, m_rect.bottom);

	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 32);

	m_glContext = SDL_GL_CreateContext(window->_window);
	if (m_glContext == NULL)
	{
		Error("Renderer", "Cannot create OpenGL context. Error: %s", SDL_GetError());
		OS::msgBox("Cannot setup OpenGL context.", "Error");
		return false;
	}

#ifdef DEBUG
#define MISSING_FUNCTION(name)\
	Error("Renderer", "%s: Cannot find %s function. (%s:%d)", FUNCTION_NAME, name, __FILE__, __LINE__)
#else
#define MISSING_FUNCTION(name)\
	Error("Renderer", "Cannot find %s function.", name)	
#endif


#define GL_FUNCTION(name)\
	*(mem_addr_t *)&name = (mem_addr_t)SDL_GL_GetProcAddress(#name);\
	if(!name) {\
		MISSING_FUNCTION(#name);\
	}

	GL_FUNCTION(glEnablei);

	// Buffers (OpenGL 1.5)
	GL_FUNCTION(glGenBuffers);
	GL_FUNCTION(glBindBuffer);
	GL_FUNCTION(glBufferData);
	GL_FUNCTION(glDeleteBuffers);
	GL_FUNCTION(glMapBuffer);
	GL_FUNCTION(glUnmapBuffer);
	GL_FUNCTION(glBindVertexArray);
	GL_FUNCTION(glGetBufferParameteriv);

	// (OpenGL 2.0)
	GL_FUNCTION(glActiveTexture);

	// Shaders (OpenGL 2.0)
	GL_FUNCTION(glBlendEquationSeparate);
	GL_FUNCTION(glDrawBuffers);
	GL_FUNCTION(glStencilOpSeparate);
	GL_FUNCTION(glStencilFuncSeparate);
	GL_FUNCTION(glStencilMaskSeparate);
	GL_FUNCTION(glAttachShader);
	GL_FUNCTION(glBindAttribLocation);
	GL_FUNCTION(glCompileShader);
	GL_FUNCTION(glCreateProgram);
	GL_FUNCTION(glCreateShader);
	GL_FUNCTION(glDeleteProgram);
	GL_FUNCTION(glDeleteShader);
	GL_FUNCTION(glDetachShader);
	GL_FUNCTION(glDisableVertexAttribArray);
	GL_FUNCTION(glEnableVertexAttribArray);
	GL_FUNCTION(glGetActiveAttrib);
	GL_FUNCTION(glGetActiveUniform);
	GL_FUNCTION(glGetAttachedShaders);
	GL_FUNCTION(glGetAttribLocation);
	GL_FUNCTION(glGetProgramiv);
	GL_FUNCTION(glGetProgramInfoLog);
	GL_FUNCTION(glGetShaderiv);
	GL_FUNCTION(glGetShaderInfoLog);
	GL_FUNCTION(glGetShaderSource);
	GL_FUNCTION(glGetUniformLocation);
	GL_FUNCTION(glGetUniformfv);
	GL_FUNCTION(glGetUniformiv);
	GL_FUNCTION(glGetVertexAttribdv);
	GL_FUNCTION(glGetVertexAttribfv);
	GL_FUNCTION(glGetVertexAttribiv);
	GL_FUNCTION(glGetVertexAttribPointerv);
	GL_FUNCTION(glIsProgram);
	GL_FUNCTION(glIsShader);
	GL_FUNCTION(glLinkProgram);
	GL_FUNCTION(glShaderSource);
	GL_FUNCTION(glUseProgram);
	GL_FUNCTION(glUniform1f);
	GL_FUNCTION(glUniform2f);
	GL_FUNCTION(glUniform3f);
	GL_FUNCTION(glUniform4f);
	GL_FUNCTION(glUniform1i);
	GL_FUNCTION(glUniform2i);
	GL_FUNCTION(glUniform3i);
	GL_FUNCTION(glUniform4i);
	GL_FUNCTION(glUniform1ui);
	GL_FUNCTION(glUniform1fv);
	GL_FUNCTION(glUniform2fv);
	GL_FUNCTION(glUniform3fv);
	GL_FUNCTION(glUniform4fv);
	GL_FUNCTION(glUniform1iv);
	GL_FUNCTION(glUniform2iv);
	GL_FUNCTION(glUniform3iv);
	GL_FUNCTION(glUniform4iv);
	GL_FUNCTION(glUniformMatrix2fv);
	GL_FUNCTION(glUniformMatrix3fv);
	GL_FUNCTION(glUniformMatrix4fv);
	GL_FUNCTION(glValidateProgram);
	GL_FUNCTION(glVertexAttrib1d);
	GL_FUNCTION(glVertexAttrib1dv);
	GL_FUNCTION(glVertexAttrib1f);
	GL_FUNCTION(glVertexAttrib1fv);
	GL_FUNCTION(glVertexAttrib1s);
	GL_FUNCTION(glVertexAttrib1sv);
	GL_FUNCTION(glVertexAttrib2d);
	GL_FUNCTION(glVertexAttrib2dv);
	GL_FUNCTION(glVertexAttrib2f);
	GL_FUNCTION(glVertexAttrib2fv);
	GL_FUNCTION(glVertexAttrib2s);
	GL_FUNCTION(glVertexAttrib2sv);
	GL_FUNCTION(glVertexAttrib3d);
	GL_FUNCTION(glVertexAttrib3dv);
	GL_FUNCTION(glVertexAttrib3f);
	GL_FUNCTION(glVertexAttrib3fv);
	GL_FUNCTION(glVertexAttrib3s);
	GL_FUNCTION(glVertexAttrib3sv);
	GL_FUNCTION(glVertexAttrib4Nbv);
	GL_FUNCTION(glVertexAttrib4Niv);
	GL_FUNCTION(glVertexAttrib4Nsv);
	GL_FUNCTION(glVertexAttrib4Nub);
	GL_FUNCTION(glVertexAttrib4Nubv);
	GL_FUNCTION(glVertexAttrib4Nuiv);
	GL_FUNCTION(glVertexAttrib4Nusv);
	GL_FUNCTION(glVertexAttrib4bv);
	GL_FUNCTION(glVertexAttrib4d);
	GL_FUNCTION(glVertexAttrib4dv);
	GL_FUNCTION(glVertexAttrib4f);
	GL_FUNCTION(glVertexAttrib4fv);
	GL_FUNCTION(glVertexAttrib4iv);
	GL_FUNCTION(glVertexAttrib4s);
	GL_FUNCTION(glVertexAttrib4sv);
	GL_FUNCTION(glVertexAttrib4ubv);
	GL_FUNCTION(glVertexAttrib4uiv);
	GL_FUNCTION(glVertexAttrib4usv);
	GL_FUNCTION(glVertexAttribPointer);

	GL_FUNCTION(glGenVertexArrays);

	GL_FUNCTION(glCompressedTexImage2D);

	// Textures and framebuffers OpenGL 3.0
	GL_FUNCTION(glIsRenderbuffer);
	GL_FUNCTION(glBindRenderbuffer);
	GL_FUNCTION(glDeleteRenderbuffers);
	GL_FUNCTION(glGenRenderbuffers);
	GL_FUNCTION(glRenderbufferStorage);
	GL_FUNCTION(glGetRenderbufferParameteriv);
	GL_FUNCTION(glIsFramebuffer);
	GL_FUNCTION(glBindFramebuffer);
	GL_FUNCTION(glDeleteFramebuffers);
	GL_FUNCTION(glGenFramebuffers);
	GL_FUNCTION(glCheckFramebufferStatus);
	GL_FUNCTION(glFramebufferTexture1D);
	GL_FUNCTION(glFramebufferTexture2D);
	GL_FUNCTION(glFramebufferTexture3D);
	GL_FUNCTION(glFramebufferRenderbuffer);
	GL_FUNCTION(glGetFramebufferAttachmentParameteriv);
	GL_FUNCTION(glGenerateMipmap);
	GL_FUNCTION(glBlitFramebuffer);
	GL_FUNCTION(glRenderbufferStorageMultisample);
	GL_FUNCTION(glFramebufferTextureLayer);

// Undef helpers
#undef GL_FUNCTION
#undef MISSING_FUNCTION

	SDL_GL_SetSwapInterval(Config::get()["graphics"]["vsync"].getBool(false) ? 1 : 0); // set 0 to disable vsync	
	glViewport(0, 0, window->getWidth(), window->getHeight());
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LEQUAL);
	
	glHint(GL_PERSPECTIVE_CORRECTION_HINT, GL_NICEST);
	
	glShadeModel(GL_SMOOTH);

	glEnable(GL_CULL_FACE);
	glFrontFace(GL_CW);
	glCullFace(GL_BACK);

	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

	glClearDepth(1.0f);
	
	m_defaultMaterial = MaterialLib::get()->findByName("none");
	if (!m_defaultMaterial)
	{
		Error("Renderer", "Unable to setup default material!");
		return false;
	}
	m_defaultMaterial->acquire();

	m_simpleColorMat = MaterialLib::get()->findByName("primitive");
	if (!m_simpleColorMat)
	{
		Error("Renderer", "Unable to setup primitive material!");
		return false;
	}
	m_simpleColorMat->acquire();

	unsigned int HackVAO;
	glGenVertexArrays(1, &HackVAO);
	glBindVertexArray(HackVAO);

	// Initialize deferred rendering
	if (!m_deferredRenderer.initialize(this, (uint32)m_rect.right, (uint32)m_rect.bottom))
	{
		Error("Renderer", "Unable to initialize deferred renderer. [%d]", glGetError());
		return false;
	}

	// Initialize dynamic shadows pass
	uint32 shadowMapSize = Config::get()["graphics"]["shadowmap"]["size"].getInteger(4086);
	if (!m_dynamicShadowsPass.initialize(this, shadowMapSize, shadowMapSize))
	{
		Error("Renderer", "Unable to initialize dynamic shadows pass. [%d]", glGetError());
		return false;
	}

	return true;
}

void Renderer::preFrame()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Renderer::beginShadowPass()
{
	m_dynamicShadowsPass.begin();
}

void Renderer::endShadowPass()
{
	m_dynamicShadowsPass.end();
}

void Renderer::beginDeferredPass()
{	
	m_deferredRenderer.setShadowTexture(m_dynamicShadowsPass.getShadowTexture());
	m_deferredRenderer.begin();
}

void Renderer::endDeferredPass()
{
	m_deferredRenderer.end(m_dynamicShadowsPass.getViewProjectionMatrix());	
}

void Renderer::postFrame()
{	
	SDL_GL_SwapWindow(m_window->_window);	
	m_stats.reset();
}

Matrix4x4 Renderer::getProjectionMatrix()
{
	return m_projectionMatrix;
}

Matrix4x4 Renderer::getOrthoMatrix()
{
	return m_orthoMatrix;
}

glm::vec4 Renderer::getViewportAsVector()
{
	return m_viewport;
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

	if (!material)
		return;

	if (m_dynamicShadowsPass.isActive())
	{
		if (material->m_parameters & Material::Parameters::CAST_SHADOWS) // Check if our material is casting shadows - if so do it
			m_dynamicShadowsPass.renderGeometry(geometry, matrix);
		return;
	}

	// Render final result
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);

	ShaderProgram *program = material->m_program;
	if (!program || !program->isValid())
		return;

	program->begin();

	glm::mat4 viewMatrix = Camera::current->getViewMatrix();
	glm::mat3 normalMatrix = glm::mat3(viewMatrix * matrix);
	unsigned int normalMatrixLocation = material->m_program->getUniformLocation("normalMatrix");
	if (normalMatrixLocation != -1)
	{		
		glUniformMatrix3fv(normalMatrixLocation, 1, GL_FALSE, glm::value_ptr(normalMatrix));
	}

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

	glm::mat4x4 mvp = m_projectionMatrix * viewMatrix * matrix;

	unsigned int mvpMatrixLocation = material->m_program->getUniformLocation("mvpMatrix");
	if (mvpMatrixLocation != -1)
	{
		glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	unsigned int parametersLocation = material->m_program->getUniformLocation("mat_Parameters");
	if (parametersLocation != -1)
	{
		glUniform1ui(parametersLocation, material->m_parameters);
	}

	uint32 textureId = 0;
	if (material->m_textures.size() > 0)
	{
		for (Material::TextureData* textureData : material->m_textures)
		{
			// Validate texture
			if (!textureData->m_texture || !textureData->m_texture->isLoaded())
				continue;

			unsigned int textureLocation = material->m_program->getUniformLocation(textureData->m_name.get());
			if (textureLocation != -1)
			{
				glActiveTexture(GL_TEXTURE0 + textureId);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureData->m_texture->m_textureID);

				if (textureData->m_texture->m_mipmaps)
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

				glUniform1i(textureLocation, textureId);
				++textureId;
			}
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
	
	glDrawElements((material->m_parameters & Material::Parameters::RENDER_WIREFRAME) ? GL_LINE_STRIP : GL_TRIANGLES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);
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

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	program->end();
}

void Renderer::renderGeometry(Geometry<Vertex2d> *geometry)
{
	if (m_dynamicShadowsPass.isActive()) return;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);

	Material* material = m_currentMaterial;
	if (!material)
		material = m_defaultMaterial;

	// Shaders
	if (!material)
		return;
	
	// Validate shader program
	ShaderProgram * program = material->m_program;
	if (!program || !program->isValid())
		return;

	program->begin();

	unsigned int orthoMatrixLocation = material->m_program->getUniformLocation("orthoMatrix");
	if (orthoMatrixLocation != -1)
	{
		glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_orthoMatrix));
	}

	unsigned int parametersLocation = material->m_program->getUniformLocation("mat_Parameters");
	if (parametersLocation != -1)
	{
		glUniform1ui(parametersLocation, material->m_parameters);
	}

	uint32 textureId = 0;
	if (material->m_textures.size() > 0)
	{
		for (Material::TextureData* textureData : material->m_textures)
		{
			// Validate texture
			if (!textureData->m_texture || !textureData->m_texture->isLoaded())
				continue;

			unsigned int textureLocation = material->m_program->getUniformLocation(textureData->m_name.get());
			if (textureLocation != -1 && textureData->m_texture->isLoaded())
			{
				glActiveTexture(GL_TEXTURE0 + textureId);
				glEnable(GL_TEXTURE_2D);
				glBindTexture(GL_TEXTURE_2D, textureData->m_texture->m_textureID);

				if (textureData->m_texture->m_mipmaps)
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


				glUniform1i(textureLocation, textureId);
				++textureId;
			}
		}
	}


	unsigned int attributePosition = material->m_program->getAttributeLocation("vertexPosition");
	unsigned int attributeUV = material->m_program->getAttributeLocation("vertexUV");
	unsigned int attributeColor = material->m_program->getAttributeLocation("vertexColor");

	glEnableVertexAttribArray(attributePosition);
	if (attributeColor != -1)
		glEnableVertexAttribArray(attributeColor);
	if (attributeUV != -1)
		glEnableVertexAttribArray(attributeUV);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(attributePosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), 0);
	if (attributeColor != -1)
		glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2d), (void *)offsetof(Vertex2d, color));
	if (attributeUV != -1)
		glVertexAttribPointer(attributeUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void *)offsetof(Vertex2d, u));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements((material->m_parameters & Material::Parameters::RENDER_WIREFRAME) ? GL_LINE_STRIP : GL_TRIANGLES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);
	m_stats.m_trianglesDrawn += geometry->m_trianglesCount;
	m_stats.m_drawCalls++;
	m_stats.m_verticesDrawn += geometry->m_verticesCount;

	glDisableVertexAttribArray(attributePosition);
	if (attributeColor != -1)
		glDisableVertexAttribArray(attributeColor);
	if (attributeUV != -1)
		glDisableVertexAttribArray(attributeUV);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	program->end();
}

void Renderer::renderGeometry(Geometry<SimpleVertex2d> *geometry)
{
	if (m_dynamicShadowsPass.isActive()) return;

	Material* material = m_currentMaterial;
	if (!material)
		material = m_defaultMaterial;

	// Shaders
	if (!material)
		return;

	// Validate shader program
	ShaderProgram * program = material->m_program;
	if (!program || !program->isValid())
		return;

	program->begin();

	unsigned int orthoMatrixLocation = material->m_program->getUniformLocation("orthoMatrix");
	if (orthoMatrixLocation != -1)
	{
		glUniformMatrix4fv(orthoMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_orthoMatrix));
	}

	unsigned int parametersLocation = material->m_program->getUniformLocation("mat_Parameters");
	if (parametersLocation != -1)
	{
		glUniform1ui(parametersLocation, material->m_parameters);
	}

	unsigned int attributePosition = material->m_program->getAttributeLocation("vertexPosition");
	unsigned int attributeColor = material->m_program->getAttributeLocation("vertexColor");

	glEnableVertexAttribArray(attributePosition);
	if (attributeColor != -1)
		glEnableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(attributePosition, 2, GL_FLOAT, GL_FALSE, sizeof(SimpleVertex2d), 0);
	if (attributeColor != -1)
		glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(SimpleVertex2d), (void *)offsetof(SimpleVertex2d, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements((material->m_parameters & Material::Parameters::RENDER_WIREFRAME) ? GL_LINE_STRIP : GL_TRIANGLES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);
	m_stats.m_trianglesDrawn += geometry->m_trianglesCount;
	m_stats.m_drawCalls++;
	m_stats.m_verticesDrawn += geometry->m_verticesCount;

	glDisableVertexAttribArray(attributePosition);
	if (attributeColor != -1)
		glDisableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	program->end();
}

void Renderer::renderGeometry(Geometry<Vertex3d_pc> * geometry, const Matrix4x4& matrix)
{
	if (m_dynamicShadowsPass.isActive()) return;

	Material* material = m_simpleColorMat;

	// Shaders
	if (!material)
		return;

	ShaderProgram *program = material->m_program;
	if (!program || !program->isValid())
		return;

	program->begin();

	glm::mat4 viewMatrix = Camera::current->getViewMatrix();
	glm::mat4x4 mvp = m_projectionMatrix * viewMatrix * matrix;

	unsigned int mvpMatrixLocation = material->m_program->getUniformLocation("mvpMatrix");
	if (mvpMatrixLocation != -1)
	{
		glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(mvp));
	}

	unsigned int parametersLocation = material->m_program->getUniformLocation("mat_Parameters");
	if (parametersLocation != -1)
	{
		glUniform1ui(parametersLocation, material->m_parameters);
	}

	unsigned int attributePosition = material->m_program->getAttributeLocation("vertexPosition");
	unsigned int attributeColor = material->m_program->getAttributeLocation("vertexColor");

	glEnableVertexAttribArray(attributePosition);
	glEnableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	glVertexAttribPointer(attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d_pc), 0);	
	glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex3d_pc), (void *)offsetof(Vertex3d_pc, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements(GL_LINES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);

	glDisableVertexAttribArray(attributePosition);
	glDisableVertexAttribArray(attributeColor);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	program->end();
}

void Renderer::drawLine3D(const Vector3& start, const Vector3& end, const Color& color, const Matrix4x4& matrix)
{
	if (m_dynamicShadowsPass.isActive()) return;
	
	glDisable(GL_DEPTH_TEST);
	Geometry<Vertex3d_pc> geometry;

	Vertex3d_pc* vertices = new Vertex3d_pc[2];

	memset(vertices, 0, sizeof(Vertex3d_pc) * 2);

	vertices[0].x = start.x;
	vertices[0].y = start.y;
	vertices[0].z = start.z;

	vertices[1].x = end.x;
	vertices[1].y = end.y;
	vertices[1].z = end.z;

	vertices[0].color = vertices[1].color = ((uint8)(color.a * 255) << 24) | ((uint8)(color.b * 255) << 16) | ((uint8)(color.g * 255) << 8) | ((uint8)(color.r * 255));

	uint16 *indices = new uint16[3];
	indices[0] = 0;
	indices[1] = 1;
	indices[2] = 0;

	geometry.fillData(vertices, 2, indices, 1);
	delete[]vertices;
	delete[]indices;

	renderGeometry(&geometry, matrix);	
}

void Renderer::renderFont(const WDynString& string, const Rect& rect, const Color& color, flags32 flags, Font *font, Vector2 scale)
{
	Material* material = font->m_material;
	
	// Shaders
	if (!material)
		return;

	ShaderProgram * program = material->m_program;
	if (!program || !program->isValid())
		return;

	glDisable(GL_DEPTH_TEST);
	glDisable(GL_CULL_FACE);
	glEnable(GL_BLEND);

	uint32 drawColor = ((uint8)(color.a * 255) << 24) | ((uint8)(color.b * 255) << 16) | ((uint8)(color.g * 255) << 8) | ((uint8)(color.r * 255));

	Vertex2d * vertices = new Vertex2d[string.getLength() * 4];
	uint16 *indices = new uint16[string.getLength() * 6];

	uint32 vertexId = 0;
	uint32 indexId = 0;
	float startX = floor(rect.x);
	float startY = floor(rect.y + (font->m_size * scale.y));

	if (flags & Font::DrawFlags::HorizontalCenter)
	{
		startX = floor(rect.x + (rect.x2 - rect.x) / 2 - font->calculateWidth(string) / 2);
	}

	if (flags & Font::DrawFlags::VerticalCenter)
	{
		startY = floor(rect.y + (rect.y2 - rect.y) / 2 + font->calculateHeight(string) / 2);
	}

	float x = startX;
	float y = startY;
	for (uint32 i = 0; i < string.getLength(); ++i)
	{
		widechar charCode = string[i];
		if (charCode == '\0')
		{
			break;
		}
		
		if (charCode == '#')
		{
			// #RRGGBB (9)
			if ((i + 7) < string.getLength())
			{
				bool isColorCode = true;
				for (uint32 j = 1; j < 7; ++j)
				{
					widechar wcs = string[i + j];
					if (!iswdigit(wcs) && (wcs < 'A' || wcs > 'F') && (wcs < 'a' || wcs > 'f'))
					{
						isColorCode = false;
						break;
					}
				}

				if (isColorCode)
				{				
					if (flags & Font::DrawFlags::DisableColorCodding)
					{
						i += 6;
					}
					else 
					{
						i += 1;// skip '#' sign
						widechar color[7] = { 0 };
						for (uint32 j = 0; j < 6; ++j)
							color[j] = string[i + j];

						uint32 col = 0xFFFFFFFF;
						swscanf(color, L"%X", &col);
						uint8 a = drawColor >> 24 & 0xFF; // get alpha from base color
						uint8 r = col >> 16 & 0xFF;
						uint8 g = col >> 8 & 0xFF;
						uint8 b = col & 0xFF;

						drawColor = (a << 24) | (b << 16) | (g << 8) | r;
						i += 5; // skip RRGGBB
					}
					continue;
				}
			}
		}

		if (charCode == '\n')
		{
			y += font->m_size;
			x = startX;
			continue;
		}

		if (charCode == ' ')
		{
			x += font->m_size/2;
			continue;
		}

		Font::GlyphData data = font->getData(charCode);		
		if (!data.set)
			data = font->getData('?'); // use ? for unknown characters
		
		int32 a, b, c, d;

		// left - top
		vertices[vertexId].x = x + data.left* scale.y;
		vertices[vertexId].y = y + data.top* scale.y;
		vertices[vertexId].u = data.x;
		vertices[vertexId].v = data.y;
		vertices[vertexId].color = drawColor;
		a = vertexId;
		vertexId++;


		// left - bottom
		vertices[vertexId].x = x + data.left* scale.y;
		vertices[vertexId].y = y + (data.top + data.bmh)* scale.y;
		vertices[vertexId].u = data.x;
		vertices[vertexId].v = data.h;
		vertices[vertexId].color = drawColor;
		b = vertexId;
		vertexId++;
			
		// right - top
		vertices[vertexId].x = x + (data.left + data.bmw)* scale.y;
		vertices[vertexId].y = y + data.top * scale.y;
		vertices[vertexId].u = data.w;
		vertices[vertexId].v = data.y;
		vertices[vertexId].color = drawColor;
		c = vertexId;
		vertexId++;

		// right - bottom
		vertices[vertexId].x = x + (data.left + data.bmw) * scale.y;
		vertices[vertexId].y = y + (data.top + data.bmh) * scale.y;
		vertices[vertexId].u = data.w;
		vertices[vertexId].v = data.h;
		vertices[vertexId].color = drawColor;
		d = vertexId;
		vertexId++;

		indices[indexId++] = a;
		indices[indexId++] = b;
		indices[indexId++] = c;
		
		indices[indexId++] = b;
		indices[indexId++] = d;
		indices[indexId++] = c;

		x += data.advanceX* scale.y;
	}

	Geometry<Vertex2d> geometry;
	geometry.fillData(vertices, vertexId, indices, indexId/3);
	delete[]vertices;
	delete[]indices;

	program->begin();

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

	glVertexAttribPointer(attributePosition, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), 0);
	if (attributeUV != -1)
		glVertexAttribPointer(attributeUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex2d), (void *)offsetof(Vertex2d, u));
	if (attributeColor != -1)
		glVertexAttribPointer(attributeColor, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex2d), (void *)offsetof(Vertex2d, color));

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry.m_indexBuffer->m_bufferId);

	glDrawElements(GL_TRIANGLES, geometry.m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);
	m_stats.m_trianglesDrawn += geometry.m_trianglesCount;
	m_stats.m_drawCalls++;
	m_stats.m_verticesDrawn += geometry.m_verticesCount;

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

	program->end();
}

Rect Renderer::getRect()
{
	return m_rect;
}