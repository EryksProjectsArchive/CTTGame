//////////////////////////////////////////////
//
//		   City Transport Tycoon
//	   Copyright (C) Black Ice Mountains
//		 	All rights reserved
//
// File		: graphics/renderer/DynamicShadowsPass.cpp
// Author	: Eryk Dwornicki
//
//////////////////////////////////////////////

#include <resources/materials/MaterialLib.h>
#include "../ShaderProgram.h"

#include "DynamicShadowsPass.h"
#include <graphics/Camera.h>

DynamicShadowsPass::DynamicShadowsPass()
	: m_fbo(0), m_depthShadowRenderBuffer(0), m_depthShadowTexture(0), m_material(0), m_active(false)
{

}

DynamicShadowsPass::~DynamicShadowsPass()
{

}

bool DynamicShadowsPass::isActive()
{
	return m_active;
}

bool DynamicShadowsPass::initialize(Renderer *renderer, uint32 width, uint32 height)
{
	m_material = MaterialLib::get()->findByName("dynamicShadowsPass");
	if (!m_material)
		return false;

	m_width = width;
	m_height = height;

	m_material->acquire();

	Renderer::glGenFramebuffers(1, &m_fbo);

	Renderer::glGenRenderbuffers(1, &m_depthShadowRenderBuffer);
	glGenTextures(1, &m_depthShadowTexture);

	Renderer::glBindFramebuffer(GL_FRAMEBUFFER, m_fbo);

	Renderer::glBindRenderbuffer(GL_RENDERBUFFER, m_depthShadowRenderBuffer);
	Renderer::glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT24, width, height);
	Renderer::glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, m_depthShadowRenderBuffer);

	glGenTextures(1, &m_depthShadowTexture);
	glBindTexture(GL_TEXTURE_2D, m_depthShadowTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_DEPTH_COMPONENT24, width, height, 0, GL_DEPTH_COMPONENT, GL_FLOAT, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

	Renderer::glFramebufferTexture2D(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_TEXTURE_2D, m_depthShadowTexture, 0);

	// Check if all worked fine and unbind the FBO
	GLenum status = Renderer::glCheckFramebufferStatus(GL_FRAMEBUFFER);
	if (status != GL_FRAMEBUFFER_COMPLETE_EXT)
	{
		Renderer::glBindFramebuffer(GL_FRAMEBUFFER, 0);
		return false;
	}

	Renderer::glBindFramebuffer(GL_FRAMEBUFFER, 0);
	return true;
}

void DynamicShadowsPass::destroy()
{
	if (m_material)
		m_material->release();

	if (m_depthShadowRenderBuffer)
		Renderer::glDeleteRenderbuffers(1, &m_depthShadowRenderBuffer);

	m_depthShadowRenderBuffer = 0;


	if (m_depthShadowTexture)
		glDeleteTextures(1, &m_depthShadowTexture);

	m_depthShadowTexture = 0;

	if (m_fbo)
		Renderer::glDeleteFramebuffers(1, &m_fbo);

	m_fbo = 0;
}

void DynamicShadowsPass::begin()
{
	// Compute shadow View Projection matrix
	
	Vector3 cam = CameraManager::get()->getCurrent()->getPosition();
	Vector3 lightPosition = cam + Vector3(20, 25, 0);
	Vector3 lightDirection = cam - Vector3(40, 50, 0);

	Matrix4x4 projection = glm::ortho<float>(-100, 100, -100, 100, 0.1f, 1000.0f);
	Matrix4x4 view = glm::lookAt(lightPosition, lightDirection, glm::vec3(0, 1, 0));
	m_viewProjectionMatrix = projection * view;

	// Setup render states
	glFrontFace(GL_CW);

	m_active = true;

	Renderer::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, m_fbo);
	glPushAttrib(GL_VIEWPORT_BIT);

	glViewport(0, 0, m_width, m_height);

	// Clear the render targets
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	Renderer::glActiveTexture(GL_TEXTURE0);
	glEnable(GL_TEXTURE_2D);
}

void DynamicShadowsPass::end()
{
	Renderer::glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
	glPopAttrib();

	glCullFace(GL_BACK);


	m_active = false;
}

void DynamicShadowsPass::renderGeometry(Geometry<Vertex3d> *geometry, const Matrix4x4& matrix)
{	
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glDisable(GL_BLEND);
	glFrontFace(GL_CCW);
	glCullFace(GL_BACK);

	ShaderProgram *program = m_material->m_program;
	if (!program || !program->isValid())
		return;

	program->begin();

	unsigned int mvpMatrixLocation = m_material->m_program->getUniformLocation("mvpMatrix");
	if (mvpMatrixLocation != -1)
	{
		Renderer::glUniformMatrix4fv(mvpMatrixLocation, 1, GL_FALSE, glm::value_ptr(m_viewProjectionMatrix * matrix));
	}
	unsigned int attributePosition = m_material->m_program->getAttributeLocation("vertexPosition");

	Renderer::glEnableVertexAttribArray(attributePosition);
	Renderer::glBindBuffer(GL_ARRAY_BUFFER, geometry->m_vertexBuffer->m_bufferId);

	Renderer::glVertexAttribPointer(attributePosition, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex3d), 0);

	Renderer::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, geometry->m_indexBuffer->m_bufferId);

	glDrawElements(GL_TRIANGLES, geometry->m_trianglesCount * 3, GL_UNSIGNED_SHORT, 0);

	Renderer::glDisableVertexAttribArray(attributePosition);

	Renderer::glBindBuffer(GL_ARRAY_BUFFER, 0);
	Renderer::glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

	program->end();
}

uint32 DynamicShadowsPass::getShadowTexture()
{
	return m_depthShadowTexture;
}