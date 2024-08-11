#include<vector>

#include "VertexArray.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "Circle.h"
#include <glm/glm.hpp>

const unsigned int VERTEX_COUNT = 50;

std::vector<float> Circle::GetPositions(float x, float y, float r)
{
    float theta = ((360.0 / (float)VERTEX_COUNT) * 3.142) / 180.0;
    std::vector<float> positions = { x, y, (x + r), y };

    for (unsigned int i = 1; i <= VERTEX_COUNT; i++)
    {
        positions.push_back(x + (r * glm::cos(theta * i)));
        positions.push_back(y + (r * glm::sin(theta * i)));
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

    /*
        Gelis:
        In OpenGL and and any graphics API you have to manage GPU memory yourself. And with having constructors for each 
        buffer (Vertex buffer, Index buffer) you were first initialzing when you were making the circle object, then you were making a new 
        vertex buffer (only in CPU memory not in GPU memory because the empty constructor in the index and vertex buffers were empty)
        by doing this:

        m_vertexBuffer = VertexBuffer(*data*);

        which was making new memory in the GPU and returning you and id for it (The constructor that had paremeters was making GPU memory). 
        But then c++ had to the delete the old vertex buffer it made from initialzing the circle, 
        but c++ doesn't have the idea of OpenGL's and GPU's memory so you were calling:

        glGenBuffers(m_RenderID);

        and then c++ was deleting the vertex buffer object from c++ perspective and calling the destructor which was

        glDeleteBuffers(m_RenderID);

        so you were making memory and then deleting it immidietly. So by having and Init function you are making GPU memory but keeping the same
        CPU memory that c++ is managing. If you still have questions DM me on discord :)
    */


	m_vertexPosition = GetPositions(x, y, r);
    m_vertexBuffer.Init(&m_vertexPosition[0], m_vertexPosition.size() * sizeof(float));
	m_vertexIndices = GetIndices();
    m_indexBuffer.Init(&m_vertexIndices[0], m_vertexIndices.size());
    m_layout.Push<float>(2);
    m_vertexArray.AddBuffer(m_vertexBuffer, m_layout);
}

Circle::~Circle()
{
    
}

void Circle::UpdateBuffer()
{
}
