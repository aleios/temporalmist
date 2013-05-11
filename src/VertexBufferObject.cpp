#include <VertexBufferObject.hpp>
#include <iostream>

VertexBufferObject::VertexBufferObject()
{
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
}

VertexBufferObject::VertexBufferObject(const std::vector<Vertex>& vertices, GLenum usage)
{
	glGenVertexArrays(1, &vaoID);
	glGenBuffers(1, &vboID);
	SetData(vertices, usage);
}

VertexBufferObject::~VertexBufferObject()
{
	// TODO: confirm issues.
	glDeleteBuffers(1, &vboID);
	glDeleteVertexArrays(1, &vaoID);
}

void VertexBufferObject::Clear(GLenum usage)
{
	glBindVertexArray(vaoID);

	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, 0, 0, usage);

	glBindVertexArray(0);
}

void VertexBufferObject::SetData(const std::vector<Vertex>& vertices, GLenum usage)
{
	vertexCount = vertices.size();
	// Bind the Vertex Array Object
	glBindVertexArray(vaoID);

	// Bind the Vertex Buffer Object
	glBindBuffer(GL_ARRAY_BUFFER, vboID);
	glBufferData(GL_ARRAY_BUFFER, vertexCount * sizeof(Vertex), &vertices.front(), usage);
	
	// Positions
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, pos.x));
	glEnableVertexAttribArray(0);

	// Normals
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, normal.x));
	glEnableVertexAttribArray(1);

	// Colors
	glVertexAttribPointer(2, 4, GL_UNSIGNED_BYTE, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, col.r));
	glEnableVertexAttribArray(2);

	// TexCoords
	glVertexAttribPointer(3, 2, GL_FLOAT, GL_TRUE, sizeof(Vertex), (GLvoid*)offsetof(Vertex, texcoords.x));
	glEnableVertexAttribArray(3);

	//glBindBuffer(GL_VERTEX_ARRAY, 0);
	glBindVertexArray(0);
}

void VertexBufferObject::ReplaceData(const std::vector<Vertex>& vertices, GLintptr offset)
{
	glBindBuffer(GL_VERTEX_ARRAY, vboID);
	glBufferSubData(GL_VERTEX_ARRAY, offset, vertices.size() * sizeof(Vertex), &vertices.front());
	glBindBuffer(GL_VERTEX_ARRAY, 0);
}

void VertexBufferObject::Bind() const
{
	glBindVertexArray(vaoID);
}

void VertexBufferObject::Unbind() const
{
	glBindVertexArray(0);
}

int VertexBufferObject::GetNumVertices() const
{
	return vertexCount;
}

GLuint VertexBufferObject::GetVAOID() const
{
	return vaoID;
}

GLuint VertexBufferObject::GetVBOID() const
{
	return vboID;
}

void VertexBufferObject::Draw(int offset) const
{
	Bind();
	glDrawArrays(GL_TRIANGLES, offset, vertexCount);
	Unbind();
}

void VertexBufferObject::DrawIndexed(const IndexBufferObject& ibo) const
{
	Bind();
	ibo.Bind();
	glDrawElements(GL_TRIANGLES, ibo.GetNumIndices(), GL_UNSIGNED_SHORT, 0);
	Unbind();
}