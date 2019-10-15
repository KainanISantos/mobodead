#include <iostream>
#include "core.hh"
#include "window.hh"

int main(void)
{
	core::init();
	wnd::set_size(800, 600);
	wnd::set_title("mobodead");
	wnd::create();
	
	wnd::show();
	while(!wnd::should_close())
	{
		wnd::swap_buffers();
		core::update();
	}

	wnd::destroy();
	core::terminate();
	return 0;
}
