#include "gfx.hh"
#include <GL/glew.h>

#include <iostream>

void gfx::init()
{
	int glew_error = glewInit();
	if(glew_error != GLEW_OK)
	{
		std::cout << "Could not init GLEW" << std::endl;
		std::cout << "GLEW error: " << glew_error << std::endl;
		std::exit(-1);
	}
}

void gfx::render()
{
}

void gfx::end()
{
}
