Mesh* MeshBuilder::GenerateCylinder(const std::string& meshName, Color color, unsigned height, unsigned sliceCount, float radius) 
{
	Vertex v;
	std::vector<Vertex> vertex_buffer_data;
	std::vector<GLuint> index_buffer_data;



	float anglePerSlice = 360 / sliceCount;

	// circle 1 vertices
	v.pos.Set(0,   (height / 2), 0);
	v.color.Set(color.r, color.g, color.b);
	vertex_buffer_data.push_back(v);
	/*v.pos.Set(0, -1 * (height / 2), 0);
	v.color.Set(color.r, color.g, color.b);*/
	vertex_buffer_data.push_back(v);
	for (unsigned slice = 0; slice <= sliceCount; slice++) {
		float theta = anglePerSlice * slice;
		// set positional vertice to (x = cos theta, y = height, z = sin theta)
		v.pos.Set(radius * cos(theta * (Math::PI / 180)), (height / 2), radius * sin(theta * (Math::PI / 180)));
		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);

	}

	// circle 2 vertices
	v.pos.Set(0, ((height / 2) - height), 0);
	v.color.Set(color.r, color.g, color.b);
	vertex_buffer_data.push_back(v);
	for (unsigned slice = sliceCount; slice <= sliceCount * 2; slice++) {
		float theta = anglePerSlice * slice;
		// set positional vertice to (x = cos theta, y = height, z = sin theta)
		v.pos.Set(radius * cos(theta * (Math::PI / 180)), ((height / 2) - height) + 1, radius * sin(theta * (Math::PI / 180)));
		v.color.Set(color.r, color.g, color.b);
		vertex_buffer_data.push_back(v);

	}
	// winding order circle 1
	for (unsigned slice = 0; slice < sliceCount; slice++) {
		index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 2);
		index_buffer_data.push_back(slice + 1);
		// this code loads the bottom face of this circle
		/*index_buffer_data.push_back(0);
		index_buffer_data.push_back(slice + 1);
		index_buffer_data.push_back(slice + 2);*/
	}

	/*for (unsigned slice = sliceCount; slice < sliceCount * 2 ; slice++) {
		index_buffer_data.push_back(sliceCount);
		index_buffer_data.push_back(slice + 2);
		index_buffer_data.push_back(slice + 1);
		
	}*/

	




	// Create the new mesh
	Mesh* mesh = new Mesh(meshName);
	glBindBuffer(GL_ARRAY_BUFFER, mesh->vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertex_buffer_data.size() *
		sizeof(Vertex), &vertex_buffer_data[0], GL_STATIC_DRAW);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, index_buffer_data.size()
		* sizeof(GLuint), &index_buffer_data[0], GL_STATIC_DRAW);
	mesh->indexSize = index_buffer_data.size();
	mesh->mode = Mesh::DRAW_TRIANGLES;
	return mesh;
}