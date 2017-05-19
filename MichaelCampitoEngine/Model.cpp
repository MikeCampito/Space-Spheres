#include "Model.h"
#include <iostream>
#include <sstream>

struct Vertex {
	vec3 location;
	vec2 uv;
	vec3 normal;
};

struct VertInd {
	unsigned int locInd, uvInd, normInd;
};

Model::Model()
{
	vertCount = 6;
	vertArr = 0;
}


Model::~Model()
{
}

bool Model::buffer(std::string objFile) {
	std::ifstream objStream;
	objStream.open(objFile);
	std::vector<glm::vec3> locs;
	std::vector<glm::vec2> uvs;
	std::vector<glm::vec3> norms;
	std::vector<VertInd> verts;

	if (objStream.is_open()) {
		std::string line;
		std::string str1;
		while (getline(objStream, line))
		{
			std::stringstream ss(line);
			ss >> str1;
			if (str1 == "v") {
				float vs[3];
				ss >> vs[0] >> vs[1] >> vs[2];
				locs.push_back(vec3(vs[0], vs[1], vs[2]));
			}
			else if (str1 == "vt") {
				float vs[2];
				ss >> vs[0] >> vs[1];
				uvs.push_back(vec2(vs[0], vs[1]));
			}
			else if (str1 == "vn") {
				float vs[3];
				ss >> vs[0] >> vs[1] >> vs[2];
				norms.push_back(
					vec3(vs[0],vs[1],vs[2]));
			}
			else if (str1 == "f") {
				for (int i = 0; i < 3; i++) {
					unsigned int ind[3];
					char slash;
					ss >> ind[0] >> slash >> ind[1] >> slash >> ind[2];
					for (int i = 0; i < 3; i++) {
						ind[i]--;
					}
					VertInd myVert = { ind[0], ind[1], ind[2] };
					verts.push_back(myVert);
				}
			}
		}
		if (objStream.is_open()) {
			objStream.close();
		}
	}
	vertCount = verts.size();
	//Duplicate vertices into a single buffer
	std::vector<Vertex> vertBufData(vertCount);

	for (unsigned int i = 0; i < vertCount; i++) {
		vertBufData[i] = { locs[verts[i].locInd],uvs[verts[i].uvInd],norms[verts[i].normInd] };
	}

	GLuint vertBuf;
	glUniform2f(1, 800, 600);
	glGenVertexArrays(1, &vertArr);
	glGenBuffers(1, &vertBuf);

	glBindVertexArray(vertArr);
	glBindBuffer(GL_ARRAY_BUFFER, vertBuf);

	glBufferData(GL_ARRAY_BUFFER,
		sizeof(Vertex) * vertCount,
		&vertBufData[0],
		GL_STATIC_DRAW);

	// vert location attribute
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		0);

	//vert normal attribute
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)(sizeof(vec3)+sizeof(vec2)));

	//vert uv attribute
	glEnableVertexAttribArray(5);
	glVertexAttribPointer(5,
		2,
		GL_FLOAT,
		GL_FALSE,
		sizeof(Vertex),
		(GLvoid*)(sizeof(vec3)));

	glBindVertexArray(0);
	return true;
}

void Model::render() {
	//Render game objects
	glBindVertexArray(vertArr);
	glDrawArrays(GL_TRIANGLES, 0, vertCount);
	glBindVertexArray(0);
	//Unbind an object after drawing it
}