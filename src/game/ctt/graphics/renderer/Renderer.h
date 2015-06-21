//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/Renderer.h
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#pragma once

#include <Prerequisites.h>
#include <SDL.h>
#include <SDL_opengl.h>
#include <graphics/BufferBase.h>

class Renderer
{
protected:
	Window* m_window;

	SDL_GLContext m_glContext;
	static Renderer* s_instance;

	Material * m_currentMaterial;
	Material * m_defaultMaterial;
public:
	Renderer();
	~Renderer();

	bool setup(Window * window);

	void preFrame();
	void postFrame();

	void setFullscreen(bool fullscreen);

	BufferBase * createBuffer(BufferType::Type type);

	void setMaterial(Material * material);
	void renderGeometry(Geometry *geometry, glm::mat4x4 * matrix);

	static Renderer& get();

	// Extension methods
	static PFNGLGENBUFFERSPROC glGenBuffers;
	static PFNGLBINDBUFFERPROC glBindBuffer;
	static PFNGLBUFFERDATAPROC glBufferData;
	static PFNGLMAPBUFFERPROC glMapBuffer;
	static PFNGLUNMAPBUFFERPROC glUnmapBuffer;
	static PFNGLDELETEBUFFERSPROC glDeleteBuffers;
	static PFNGLBINDVERTEXARRAYPROC glBindVertexArray;

	static PFNGLBLENDEQUATIONSEPARATEPROC glBlendEquationSeparate;
	static PFNGLDRAWBUFFERSPROC glDrawBuffers;
	static PFNGLSTENCILOPSEPARATEPROC glStencilOpSeparate;
	static PFNGLSTENCILFUNCSEPARATEPROC glStencilFuncSeparate;
	static PFNGLSTENCILMASKSEPARATEPROC glStencilMaskSeparate;
	static PFNGLATTACHSHADERPROC glAttachShader;
	static PFNGLBINDATTRIBLOCATIONPROC glBindAttribLocation;
	static PFNGLCOMPILESHADERPROC glCompileShader;
	static PFNGLCREATEPROGRAMPROC glCreateProgram;
	static PFNGLCREATESHADERPROC glCreateShader;
	static PFNGLDELETEPROGRAMPROC glDeleteProgram;
	static PFNGLDELETESHADERPROC glDeleteShader;
	static PFNGLDETACHSHADERPROC glDetachShader;
	static PFNGLDISABLEVERTEXATTRIBARRAYPROC glDisableVertexAttribArray;
	static PFNGLENABLEVERTEXATTRIBARRAYPROC glEnableVertexAttribArray;
	static PFNGLGETACTIVEATTRIBPROC glGetActiveAttrib;
	static PFNGLGETACTIVEUNIFORMPROC glGetActiveUniform;
	static PFNGLGETATTACHEDSHADERSPROC glGetAttachedShaders;
	static PFNGLGETATTRIBLOCATIONPROC glGetAttribLocation;
	static PFNGLGETPROGRAMIVPROC glGetProgramiv;
	static PFNGLGETPROGRAMINFOLOGPROC glGetProgramInfoLog;
	static PFNGLGETSHADERIVPROC glGetShaderiv;
	static PFNGLGETSHADERINFOLOGPROC glGetShaderInfoLog;
	static PFNGLGETSHADERSOURCEPROC glGetShaderSource;
	static PFNGLGETUNIFORMLOCATIONPROC glGetUniformLocation;
	static PFNGLGETUNIFORMFVPROC glGetUniformfv;
	static PFNGLGETUNIFORMIVPROC glGetUniformiv;
	static PFNGLGETVERTEXATTRIBDVPROC glGetVertexAttribdv;
	static PFNGLGETVERTEXATTRIBFVPROC glGetVertexAttribfv;
	static PFNGLGETVERTEXATTRIBIVPROC glGetVertexAttribiv;
	static PFNGLGETVERTEXATTRIBPOINTERVPROC glGetVertexAttribPointerv;
	static PFNGLISPROGRAMPROC glIsProgram;
	static PFNGLISSHADERPROC glIsShader;
	static PFNGLLINKPROGRAMPROC glLinkProgram;
	static PFNGLSHADERSOURCEPROC glShaderSource;
	static PFNGLUSEPROGRAMPROC glUseProgram;
	static PFNGLUNIFORM1FPROC glUniform1f;
	static PFNGLUNIFORM2FPROC glUniform2f;
	static PFNGLUNIFORM3FPROC glUniform3f;
	static PFNGLUNIFORM4FPROC glUniform4f;
	static PFNGLUNIFORM1IPROC glUniform1i;
	static PFNGLUNIFORM2IPROC glUniform2i;
	static PFNGLUNIFORM3IPROC glUniform3i;
	static PFNGLUNIFORM4IPROC glUniform4i;
	static PFNGLUNIFORM1FVPROC glUniform1fv;
	static PFNGLUNIFORM2FVPROC glUniform2fv;
	static PFNGLUNIFORM3FVPROC glUniform3fv;
	static PFNGLUNIFORM4FVPROC glUniform4fv;
	static PFNGLUNIFORM1IVPROC glUniform1iv;
	static PFNGLUNIFORM2IVPROC glUniform2iv;
	static PFNGLUNIFORM3IVPROC glUniform3iv;
	static PFNGLUNIFORM4IVPROC glUniform4iv;
	static PFNGLUNIFORMMATRIX2FVPROC glUniformMatrix2fv;
	static PFNGLUNIFORMMATRIX3FVPROC glUniformMatrix3fv;
	static PFNGLUNIFORMMATRIX4FVPROC glUniformMatrix4fv;
	static PFNGLVALIDATEPROGRAMPROC glValidateProgram;
	static PFNGLVERTEXATTRIB1DPROC glVertexAttrib1d;
	static PFNGLVERTEXATTRIB1DVPROC glVertexAttrib1dv;
	static PFNGLVERTEXATTRIB1FPROC glVertexAttrib1f;
	static PFNGLVERTEXATTRIB1FVPROC glVertexAttrib1fv;
	static PFNGLVERTEXATTRIB1SPROC glVertexAttrib1s;
	static PFNGLVERTEXATTRIB1SVPROC glVertexAttrib1sv;
	static PFNGLVERTEXATTRIB2DPROC glVertexAttrib2d;
	static PFNGLVERTEXATTRIB2DVPROC glVertexAttrib2dv;
	static PFNGLVERTEXATTRIB2FPROC glVertexAttrib2f;
	static PFNGLVERTEXATTRIB2FVPROC glVertexAttrib2fv;
	static PFNGLVERTEXATTRIB2SPROC glVertexAttrib2s;
	static PFNGLVERTEXATTRIB2SVPROC glVertexAttrib2sv;
	static PFNGLVERTEXATTRIB3DPROC glVertexAttrib3d;
	static PFNGLVERTEXATTRIB3DVPROC glVertexAttrib3dv;
	static PFNGLVERTEXATTRIB3FPROC glVertexAttrib3f;
	static PFNGLVERTEXATTRIB3FVPROC glVertexAttrib3fv;
	static PFNGLVERTEXATTRIB3SPROC glVertexAttrib3s;
	static PFNGLVERTEXATTRIB3SVPROC glVertexAttrib3sv;
	static PFNGLVERTEXATTRIB4NBVPROC glVertexAttrib4Nbv;
	static PFNGLVERTEXATTRIB4NIVPROC glVertexAttrib4Niv;
	static PFNGLVERTEXATTRIB4NSVPROC glVertexAttrib4Nsv;
	static PFNGLVERTEXATTRIB4NUBPROC glVertexAttrib4Nub;
	static PFNGLVERTEXATTRIB4NUBVPROC glVertexAttrib4Nubv;
	static PFNGLVERTEXATTRIB4NUIVPROC glVertexAttrib4Nuiv;
	static PFNGLVERTEXATTRIB4NUSVPROC glVertexAttrib4Nusv;
	static PFNGLVERTEXATTRIB4BVPROC glVertexAttrib4bv;
	static PFNGLVERTEXATTRIB4DPROC glVertexAttrib4d;
	static PFNGLVERTEXATTRIB4DVPROC glVertexAttrib4dv;
	static PFNGLVERTEXATTRIB4FPROC glVertexAttrib4f;
	static PFNGLVERTEXATTRIB4FVPROC glVertexAttrib4fv;
	static PFNGLVERTEXATTRIB4IVPROC glVertexAttrib4iv;
	static PFNGLVERTEXATTRIB4SPROC glVertexAttrib4s;
	static PFNGLVERTEXATTRIB4SVPROC glVertexAttrib4sv;
	static PFNGLVERTEXATTRIB4UBVPROC glVertexAttrib4ubv;
	static PFNGLVERTEXATTRIB4UIVPROC glVertexAttrib4uiv;
	static PFNGLVERTEXATTRIB4USVPROC glVertexAttrib4usv;
	static PFNGLVERTEXATTRIBPOINTERPROC glVertexAttribPointer;
	static PFNGLGENVERTEXARRAYSPROC glGenVertexArrays;
};