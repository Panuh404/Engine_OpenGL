#include "Buffer.h"

#include <algorithm>
#include <glad/glad.h>

//-----------------------------------------------------------------------------
// [Section] Vertex Buffer
//-----------------------------------------------------------------------------
VertexBuffer::VertexBuffer(float* vertices, uint32_t size)
{
	glGenBuffers(1, &m_RendererID);							// Create Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);					// Bind Object as Array Buffer
	glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);	// Initialize Buffer Object data store
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
}

void VertexBuffer::Unbind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}

//-----------------------------------------------------------------------------
// [Section] Index Buffer
//-----------------------------------------------------------------------------
IndexBuffer::IndexBuffer(uint32_t* indices, uint32_t count) : m_Count(count)
{
	glGenBuffers(1, &m_RendererID);															// Create Buffer Object
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);										// Bind Object as Index Buffer
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(uint32_t), indices, GL_STATIC_DRAW);	// Initialize Buffer Object data store
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RendererID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID);
}

void IndexBuffer::Unbind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}
