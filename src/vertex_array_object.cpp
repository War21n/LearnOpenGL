#include "vertex_array_object.h"

#include <glad/glad.h>

VertexArrayObject::VertexArrayObject()
{
    glGenVertexArrays(1, &_id);
}

VertexArrayObject::~VertexArrayObject()
{
    glDeleteVertexArrays(1, &_id);
}

void VertexArrayObject::AddBuffer(const VertexBufferObject& vbo, const VertexBufferLayout& layout)
{
    Bind();
	vbo.Bind();
	const auto& elements = layout.GetElements();
	unsigned int offset = 0;
	for (unsigned int i = 0; i < elements.size(); i++) {
		const auto& element = elements[i];
		glEnableVertexAttribArray(i);
		glVertexAttribPointer(i, element.count, element.type, element.normalized, layout.GetStride(), (const void*)offset);
		offset += element.count * VertexBufferElement::GetSizeOfType(element.type);
	}
}

void VertexArrayObject::Bind() const
{
    glBindVertexArray(_id);
}

void VertexArrayObject::Unbind() const
{
    glBindVertexArray(0);
}