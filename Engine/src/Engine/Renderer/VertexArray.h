#pragma once
#include <cstdint>

class VertexArray
{
public:
	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

private:
	uint32_t m_RendererID;
};