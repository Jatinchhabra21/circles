#pragma once

#include<vector>
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "IndexBuffer.h"

class Circle
{
private:
	std::vector<float> GetPositions(float x, float y, float r);
	std::vector<unsigned int> GetIndices();
	VertexBuffer m_vertexBuffer;

public:
	VertexBufferLayout m_layout;
	VertexArray m_vertexArray;
	IndexBuffer m_indexBuffer;
	std::vector<float> m_vertexPosition;
	std::vector<unsigned int> m_vertexIndices;
	Circle(float x = 0.0f, float y = 0.0f, float r = 0.5f);
	~Circle();
	void UpdateBuffer();
};
