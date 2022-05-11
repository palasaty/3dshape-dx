#pragma once

#include "input_manager.h"
#include "window.h"
#include "render.h"

class Framework
{
public:
	Framework() :
		m_wnd(nullptr),
		m_render(nullptr),
		m_input(nullptr),
		m_init(false)
	{}
	~Framework() {}

	bool Init();
	void Run();
	void Close();

	void SetRender(Render* render) { m_render = render; }
	void AddInputListener(InputListener* listener);
protected:
	bool m_frame();

	Window* m_wnd;
	Render* m_render;
	InputManager* m_input;
	bool m_init;		
};