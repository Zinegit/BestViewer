#include "include/objLoader.hpp"

bool loadOBJ(
    const char * path,
	std::vector<float>& vertices_in_order,
	std::vector<float>& uvs_in_order,
	std::vector<float>& normals_in_order
//	std::vector<float>& out_vertices,
)
{
	setlocale(LC_NUMERIC, "C");
	std::vector<unsigned int> vertexIndices, uvIndices, normalIndices;
	std::vector<std::vector<float>> temp_vertices;
	std::vector<std::vector<float>> temp_uvs;
	std::vector<std::vector<float>> temp_normals;

	FILE * file = fopen(path, "r");
	if( file == NULL ){
		std::cout << "Impossible to open the file ! Are you in the right path?" << std::endl;
		getchar();
		return false;
	}
	while(1)
	{
		char lineHeader[128];
		// read the first word of the line
		int res = fscanf(file, "%s", lineHeader);
		if (res == EOF)
			break; // EOF = End Of File. Quit the loop.

		// else : parse lineHeader

		if ( strcmp( lineHeader, "v" ) == 0 ){
			std::vector<float> vertex(3, 0);
			fscanf(file, "%f %f %f\n", &vertex[0], &vertex[1], &vertex[2]);
//			out_vertices.push_back(vertex[0]);
//			out_vertices.push_back(vertex[1]);
//			out_vertices.push_back(vertex[2]);
			temp_vertices.push_back(vertex);
		}else if (strcmp( lineHeader, "vt" ) == 0){
			std::vector<float> uv(2, 0);
			fscanf(file, "%f %f\n", &uv[0], &uv[1] );
			uv[1] = -uv[1]; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			temp_uvs.push_back(uv);
		}else if (strcmp( lineHeader, "vn" ) == 0){
			std::vector<float> normal(3, 0);
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2] );
			temp_normals.push_back(normal);
		}else if ( strcmp( lineHeader, "f" ) == 0 ){
			unsigned int vertexIndex[3], uvIndex[3], normalIndex[3];
			int matches = fscanf(file, "%d/%d/%d %d/%d/%d %d/%d/%d\n", &vertexIndex[0], &uvIndex[0], &normalIndex[0], &vertexIndex[1], &uvIndex[1], &normalIndex[1], &vertexIndex[2], &uvIndex[2], &normalIndex[2] );
			if (matches != 9){
				std::cout << "File can't be read by our simple parser :-( Try exporting with other options" << std::endl;
				return false;
			}
			vertexIndices.push_back(vertexIndex[0]);
			vertexIndices.push_back(vertexIndex[1]);
			vertexIndices.push_back(vertexIndex[2]);
			uvIndices.push_back(uvIndex[0]);
			uvIndices.push_back(uvIndex[1]);
			uvIndices.push_back(uvIndex[2]);
			normalIndices.push_back(normalIndex[0]);
			normalIndices.push_back(normalIndex[1]);
			normalIndices.push_back(normalIndex[2]);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}
	// For each vertex of each triangle
	for(unsigned int i = 0; i < vertexIndices.size(); i++)
	{
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];
		unsigned int normalIndex = normalIndices[i];

		// Get the attributes thanks to the index
		std::vector<float> vertex = temp_vertices[vertexIndex-1];
		std::vector<float> uv = temp_uvs[uvIndex-1];
		std::vector<float> normal = temp_normals[normalIndex-1];

		// Put the attributes in buffers
		vertices_in_order.push_back(vertex[0]);
		vertices_in_order.push_back(vertex[1]);
		vertices_in_order.push_back(vertex[2]);
		uvs_in_order.push_back(uv[0]);
		uvs_in_order.push_back(uv[1]);
		normals_in_order.push_back(normal[0]);
		normals_in_order.push_back(normal[1]);
		normals_in_order.push_back(normal[2]);
	}
	return true;
}

// Returns true iif v1 can be considered equal to v2
bool is_near(float v1, float v2){
	return fabs( v1-v2 ) < 0.01f;
}

// Searches through all already-exported vertices
// for a similar one.
// Similar = same position + same UVs + same normal
bool getSimilarVertexIndex(
	std::vector<float>& in_vertex,
	std::vector<float>& in_uv,
	std::vector<float>& in_normal,
	std::vector<float>& out_vertices,
	std::vector<float>& out_uvs,
	std::vector<float>& out_normals,
	int& index
){
	// linear search
	unsigned int j = 0;
	for (unsigned int i = 0; i < out_vertices.size()/3; i++, j++)
	{
		if (is_near(in_vertex[0], out_vertices[3 * i]) &&
			is_near(in_vertex[1], out_vertices[3 * i + 1]) &&
			is_near(in_vertex[2], out_vertices[3 * i + 2]) &&
			is_near(in_uv[0], out_uvs[3 * j]) &&
			is_near(in_uv[1], out_uvs[3 * j + 1]))
//			is_near(in_normal[0], out_normals[3 * i]) &&
//			is_near(in_normal[1], out_normals[3 * i + 1]) &&
//			is_near(in_normal[2], out_normals[3 * i + 2]))
		{
			index = i;
			return true;
		}
	}
	// No other vertex could be used instead.
	// Looks like we'll have to add it to the VBO.
	return false;
}

void indexVBO(
	std::vector<float>& in_vertices,
	std::vector<float>& in_uvs,
	std::vector<float>& in_normals,
	std::vector<int>& out_indices,
	std::vector<float>& out_vertices,
	std::vector<float>& out_uvs,
	std::vector<float>& out_normals
){
	// For each input vertex
	unsigned int j = 0;
	for (unsigned int i = 0; i < in_vertices.size()/3; i++, j++)
	{
		// Try to find a similar vertex in out_XXXX
		int index;
		std::vector<float> in_vertex;
		std::vector<float> in_uv;
		std::vector<float> in_normal;
		in_vertex.push_back(in_vertices[3 * i]);
		in_vertex.push_back(in_vertices[3 * i + 1]);
		in_vertex.push_back(in_vertices[3 * i + 2]);
		in_uv.push_back(in_uvs[2 * j]);
		in_uv.push_back(in_uvs[2 * j + 1]);
		in_normal.push_back(in_normals[3 * i]);
		in_normal.push_back(in_normals[3 * i + 1]);
		in_normal.push_back(in_normals[3 * i + 2]);
		bool found = getSimilarVertexIndex(in_vertex, in_uv, in_normal, out_vertices, out_uvs, out_normals, index);

		if (found){ // A similar vertex is already in the VBO, use it instead !
			out_indices.push_back(index);
		}else{ // If not, it needs to be added in the output data.
			out_vertices.push_back(in_vertices[3 * i]);
			out_vertices.push_back(in_vertices[3 * i + 1]);
			out_vertices.push_back(in_vertices[3 * i + 2]);
			out_uvs.push_back(in_uvs[2 * i]);
			out_uvs.push_back(in_uvs[2 * i + 1]);
			out_normals.push_back(in_normals[3 * i]);
			out_normals.push_back(in_normals[3 * i + 1]);
			out_normals.push_back(in_normals[3 * i + 2]);
			out_indices.push_back((int)out_vertices.size()/3 - 1);
		}
	}
}
