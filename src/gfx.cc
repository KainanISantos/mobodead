#include "gfx.hh"
#include <GL/glew.h>

#include <vector>
#include <iostream>
#include <stack>

namespace gfx {
	std::vector<renderer*> renderers;
	std::stack<renderer_factory*> factories;

	void add_renderer_factory(renderer_factory* f)
	{
		factories.push(f);
	}
}

void gfx::init()
{
	int glew_error = glewInit();
	if(glew_error != GLEW_OK)
	{
		std::cout << "Could not init GLEW" << std::endl;
		std::cout << "GLEW error: " << glew_error << std::endl;
		std::exit(-1);
	}

	while(!factories.empty())
	{
		renderers.push_back(factories.top()->create_renderer());
		delete factories.top();
		factories.pop();
	}
}

void gfx::render()
{	
	for(renderer* rend : renderers)
	{
		rend->render();
	}
}

void gfx::end()
{
}
