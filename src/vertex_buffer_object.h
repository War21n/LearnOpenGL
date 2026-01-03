#pragma once

#include <iostream>
#include <vector>

#include <glad/glad.h>

struct VertexBufferElement {
    unsigned int type;
	unsigned int count;
	unsigned char normalized;

	static unsigned int GetSizeOfType(unsigned int type)
	{
		switch (type) {
            case GL_FLOAT:
                return 4;
            case GL_UNSIGNED_INT:
                return 4;
            case GL_UNSIGNED_BYTE:
                return 1;
		}
        std::cout << "VertexBufferElement::GetSizeOfType: '" << type << "' not valid." << std::endl;
		return 0;
	}
};

class VertexBufferObject
{
public:
	VertexBufferObject(const void* data, unsigned int size);
	~VertexBufferObject();

	void Bind() const;
	void Unbind() const;

private:
	unsigned int _id;
};

class VertexBufferLayout {
public:
    VertexBufferLayout(): _stride(0) {}

    template<typename T>
    void Push(unsigned int count);

    const std::vector<VertexBufferElement> GetElements() const { return _elements; }
	unsigned int GetStride() const { return _stride; }

private:
    std::vector<VertexBufferElement> _elements;
	unsigned int _stride;
};
