#include "core.hh"
#include <iostream>
#include <GLFW/glfw3.h>

static void glfw_error_callback(int n, const char* msg)
{
	std::cout << "[GLFW ERROR] " << n << std::hex << "( " << n << " )" << std::dec << std::endl;
}

void core::init()
{
	glfwSetErrorCallback(glfw_error_callback);
	if(!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
}

void core::terminate()
{
	glfwTerminate();
}

void core::update()
{
	glfwPollEvents();
}
