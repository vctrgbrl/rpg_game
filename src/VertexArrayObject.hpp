#include <vector>

namespace Lone {
	class VertexArrayObject
	{
	public:
		struct Attribute {
			int type;
			int count;
			int size;
		};
		
	public:
		VertexArrayObject(uint32_t size_vertices, float* vertices, std::vector<Attribute>& attributes, uint32_t size_indices, uint32_t* indices);
		~VertexArrayObject();
		void Bind();
	private:
		uint32_t vao;
		uint32_t vbo;
		uint32_t ebo;
	};
}