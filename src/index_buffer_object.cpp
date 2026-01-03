#include "index_buffer_object.h"

#include <glad/glad.h>

IndexBufferObject::IndexBufferObject(const unsigned int* data, unsigned int count) : _count(count)
{
    glGenBuffers(1, &_id);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW);
}

IndexBufferObject::~IndexBufferObject()
{
    glDeleteBuffers(1, &_id);
}

void IndexBufferObject::Bind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, _id);
}

void IndexBufferObject::Unbind() const
{
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}