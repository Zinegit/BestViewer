#include "include/objLoader.hpp"

bool loadOBJ(
    const char * path,
	std::vector<float>& vertices_in_order,
	std::vector<float>& uvs_in_order,
	std::vector<float>& out_vertices,
	std::vector<float>& out_normals,
	std::vector<int>& out_indices
)
{
	setlocale(LC_NUMERIC, "C");
	std::vector<unsigned int> vertexIndices, uvIndices;
	std::vector<std::vector<float>> temp_vertices;
	std::vector<std::vector<float>> temp_uvs;

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
			out_vertices.push_back(vertex[0]);
			out_vertices.push_back(vertex[1]);
			out_vertices.push_back(vertex[2]);
			temp_vertices.push_back(vertex);
		}else if (strcmp( lineHeader, "vt" ) == 0){
			std::vector<float> uv(2, 0);
			fscanf(file, "%f %f\n", &uv[0], &uv[1] );
			uv[1] = -uv[1]; // Invert V coordinate since we will only use DDS texture, which are inverted. Remove if you want to use TGA or BMP loaders.
			uvs_in_order.push_back(uv[0]);
			uvs_in_order.push_back(uv[1]);
			temp_uvs.push_back(uv);
		}else if (strcmp( lineHeader, "vn" ) == 0){
			std::vector<float> normal(3, 0);
			fscanf(file, "%f %f %f\n", &normal[0], &normal[1], &normal[2] );
			out_normals.push_back(normal[0]);
			out_normals.push_back(normal[1]);
			out_normals.push_back(normal[2]);
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
			out_indices.push_back(vertexIndex[0]-1);
			out_indices.push_back(vertexIndex[1]-1);
			out_indices.push_back(vertexIndex[2]-1);
		}else{
			// Probably a comment, eat up the rest of the line
			char stupidBuffer[1000];
			fgets(stupidBuffer, 1000, file);
		}
	}

	// For each vertex of each triangle
	for( unsigned int i = 0; i < vertexIndices.size(); i++){
		// Get the indices of its attributes
		unsigned int vertexIndex = vertexIndices[i];
		unsigned int uvIndex = uvIndices[i];

		// Get the attributes thanks to the index
		std::vector<float> vertex = temp_vertices[ vertexIndex-1 ];
		std::vector<float> uv = temp_uvs[ uvIndex-1 ];

		// Put the attributes in buffers
		vertices_in_order.push_back(vertex[0]);
		vertices_in_order.push_back(vertex[1]);
		vertices_in_order.push_back(vertex[2]);
		uvs_in_order.push_back(uv[0]);
		uvs_in_order.push_back(uv[1]);

	}
	return true;
}
