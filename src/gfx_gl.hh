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
		using source_list = std::initializer_list<program_source>;
		unsigned int create_shader(const program_source& source);
		unsigned int create_program(const source_list& sources);
	}
}
#endif
