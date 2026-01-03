#include "vertex_buffer_object.h"

VertexBufferObject::VertexBufferObject(const void* data, unsigned int size)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ARRAY_BUFFER, _id);
    glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW);
}

VertexBufferObject::~VertexBufferObject()
{
    glDeleteBuffers(1, &_id);
}

void VertexBufferObject::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, _id);
}

void VertexBufferObject::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

template<typename T>
void VertexBufferLayout::Push(unsigned int count)
{
    static_assert(false);
}

template<>
void VertexBufferLayout::Push<float>(unsigned int count)
{
    _elements.push_back({ GL_FLOAT, count, GL_FALSE });
    _stride += VertexBufferElement::GetSizeOfType(GL_FLOAT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned int>(unsigned int count)
{
    _elements.push_back({ GL_UNSIGNED_INT, count, GL_FALSE });
    _stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_INT) * count;
}

template<>
void VertexBufferLayout::Push<unsigned char>(unsigned int count)
{
    _elements.push_back({ GL_UNSIGNED_BYTE, count, GL_TRUE });
    _stride += VertexBufferElement::GetSizeOfType(GL_UNSIGNED_BYTE) * count;
}
