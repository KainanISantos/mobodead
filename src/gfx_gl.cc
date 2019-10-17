#include "gfx_gl.hh"
#include <GL/glew.h>
#include <stack>
#include <iostream>
#include <string>
#include <cstdint>

using namespace gfx;

unsigned int gl::create_shader(const gl::program_source& source)
{
	unsigned int shader = glCreateShader(source.shader_type);
	
	const char* shader_sc = source.shader_source.c_str();
	int         shader_sl = source.shader_source.length();

	glShaderSource(shader, 1, &shader_sc, &shader_sl);
	glCompileShader(shader);

	int cmp;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &cmp);
	if(!cmp)
	{
		int info_log_length;
		glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &info_log_length);
		std::string info_log;
		info_log.reserve(info_log_length);
		glGetShaderInfoLog(shader, info_log_length, &info_log_length, &info_log[0]);
		std::cout << "shader compilation error!" << std::endl;
		std::cout << "shader name: " << source.shader_name << std::endl;
		std::cout << "info log: " << info_log << std::endl;

		glDeleteShader(shader);
		return -1;
	}
	
	return shader;
}

unsigned int gl::create_program(const gl::source_list& sources)
{
	unsigned int program = glCreateProgram();
	std::stack<unsigned int> c_shaders;
	for(auto& ps : sources)
	{
		unsigned int shader = create_shader(ps);
		glAttachShader(program, shader);
		c_shaders.push(shader);
	}
	glLinkProgram(program);
	int cmp;
	glGetProgramiv(program, GL_LINK_STATUS, &cmp);
	if(!cmp)
	{
		int info_log_length;
		glGetProgramiv(program, GL_INFO_LOG_LENGTH, &info_log_length);
		std::string info_log;
		info_log.reserve(info_log_length);
		glGetProgramInfoLog(program, info_log_length, &info_log_length, &info_log[0]);
		std::cout << "program link error!" << std::endl;
		std::cout << "info log: " << info_log << std::endl;
	}
	while(!c_shaders.empty())
	{
		glDetachShader(program, c_shaders.top());
		glDeleteShader(c_shaders.top());
		c_shaders.pop();
	}
	return program;
}

unsigned int gl::create_vertex_array(const gl::vao_element_list& elements)
{
	unsigned int vao;
	glGenVertexArrays(1, &vao);
	glBindVertexArray(vao);
	for(auto& e : elements)
	{
		glBindBuffer(GL_ARRAY_BUFFER, e.buffer);
		glEnableVertexAttribArray(e.index);
		glVertexAttribPointer(e.index, e.size, e.type, false, e.stride, (void*)((uintptr_t)e.offset));
		glVertexAttribDivisor(e.index, e.divisor);
	}
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
	return vao;
}
