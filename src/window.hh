#ifndef WINDOW_HH
#define WINDOW_HH

#include <string>

namespace wnd {
	void set_size(int w, int h);
	void get_size(int* w, int* h);
	void set_title(const std::string& title);
	
	void create();
	void destroy();
	void recreate();

	void swap_buffers();
	bool should_close();
	
	void make_context_current();
	
	void show();
	void hide();
}
#endif
