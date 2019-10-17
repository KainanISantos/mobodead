#ifndef GFX_HH
#define GFX_HH

#include "gfx_gl.hh"
#include <functional>

namespace gfx { 
	class renderer
	{
	public:
		virtual void render() = 0;
		virtual void* create() = 0;
		virtual void  destroy(void* object) = 0;
	};
	
	class renderer_factory
	{
	public:
		virtual renderer* create_renderer() = 0;
	};
	
	template<class T>
	void register_renderer()
	{
		class renderer_factory_impl : public renderer_factory
		{
			renderer* create_renderer() override
			{
				return new T;
			}
		};
		extern void add_renderer_factory(renderer_factory* factory);
		
		add_renderer_factory(new renderer_factory_impl);
	}

	void init();
	void render();
	void end();
}

#endif
