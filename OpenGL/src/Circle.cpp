#include<vector>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Circle.h"


const unsigned int VERTEX_COUNT = 50;

std::vector<float> Circle::GetPositions(float x, float y, float r)
{
    float theta = ((360.0 / (float)VERTEX_COUNT) * 3.142) / 180.0;
    std::vector<float> positions = { x, y, (x + r), y };

    for (unsigned int i = 1; i <= VERTEX_COUNT; i++)
    {
        positions.push_back(x + (r * cos(theta * i)));
        positions.push_back(y + (r * sin(theta * i)));
    }
    positions.push_back((x + r));
    positions.push_back(y);
    return positions;
}

std::vector<unsigned int> Circle::GetIndices()
{
    std::vector<unsigned int> indices = {};

    for (unsigned int i = 1, j = 2; i < VERTEX_COUNT + 2 && j <= VERTEX_COUNT + 2; i++, j++)
    {
        indices.push_back(0);
        indices.push_back(i);
        indices.push_back(j);
    }

    return indices;
}

Circle::Circle(float x, float y, float r)
{
	m_vertexPosition = GetPositions(x, y, r);
    m_vertexBuffer = VertexBuffer(&m_vertexPosition[0], m_vertexPosition.size() * sizeof(float));
	m_vertexIndices = GetIndices();
    m_indexBuffer = IndexBuffer(&m_vertexIndices[0], m_vertexIndices.size());
    m_layout.Push<float>(2);
    m_vertexArray = VertexArray();
    m_vertexArray.AddBuffer(m_vertexBuffer, m_layout);
}

Circle::~Circle()
{
}

void Circle::UpdateBuffer()
{
}
