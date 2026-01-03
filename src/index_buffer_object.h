#pragma once

class IndexBufferObject {
public:
    IndexBufferObject(const unsigned int* data, unsigned int count);
	~IndexBufferObject();

	void Bind() const;
	void Unbind() const;

	inline unsigned int GetCount() const { return _count; }

private:
    unsigned int _id;
	unsigned int _count;
};