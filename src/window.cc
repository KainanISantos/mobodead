#include "window.hh"
#include <GLFW/glfw3.h>

namespace wnd {
	struct { 
		GLFWwindow *window;
		int w, h;
		std::string title;
	} data;

	static void create(GLFWwindow* window)
	{
		glfwDefaultWindowHints();
		glfwWindowHint(GLFW_RESIZABLE, GLFW_FALSE);
		glfwWindowHint(GLFW_VISIBLE,   GLFW_FALSE);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
		data.window = glfwCreateWindow(data.w, data.h, data.title.c_str(), nullptr, window);
	}
}

void wnd::create()
{
	create(nullptr);
}

void wnd::destroy()
{
	glfwDestroyWindow(data.window);
}

void wnd::recreate()
{
	create(data.window);
}

void wnd::set_size(int w, int h) 
{
	data.w = w;
	data.h = h;
	if(data.window)
		glfwSetWindowSize(data.window, data.w, data.h);
}

void wnd::get_size(int* w, int* h)
{
	*w = data.w;
	*h = data.h;
}

void wnd::set_title(const std::string& title)
{
	data.title = title;
	if(data.window)
		glfwSetWindowTitle(data.window, title.c_str());
}

void wnd::show()
{
	glfwShowWindow(data.window);
}

void wnd::hide()
{
	glfwHideWindow(data.window);
}

void wnd::make_context_current()
{
	glfwMakeContextCurrent(data.window);
}

void wnd::swap_buffers()
{
	glfwSwapBuffers(data.window);
}

bool wnd::should_close()
{
	return glfwWindowShouldClose(data.window);
}
