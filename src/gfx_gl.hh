#ifndef GFX_GL_HH
#define GFX_GL_HH

#include <string>
#include <utility>

namespace gfx { 
	namespace gl {
		struct program_source { 
			unsigned int shader_type;
			const std::string shader_name;
			const std::string shader_source;
		};

		struct vertex_array_element {
			unsigned int index;
			unsigned int type;
			unsigned int size;
			unsigned int stride;
			unsigned int offset;
			unsigned int divisor;
		};

		using source_list = std::initializer_list<program_source>;
		using vao_element_list = std::initializer_list<vertex_array_element>;

		unsigned int create_shader(const program_source& source);
		unsigned int create_program(const source_list& sources);
		unsigned int create_vertex_array(const vao_element_list& elements);
	}
}
#endif
