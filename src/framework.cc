#include "framework.h"

void Framework::AddInputListener(InputListener* listener)
{
	if (m_input)
		m_input->AddListener(listener);
}

void Framework::Run()
{
	if (m_init)
		while (m_frame());
}

bool Framework::Init()
{
	m_wnd = new Window();
	m_input = new InputManager();

	if (!m_wnd || !m_input)	return false;
	m_input->Init();

	DescWindow desc;
	if (!m_wnd->Create(desc)) return false;
	m_wnd->SetInputManager(m_input);

	if (!m_render->CreateDevice(m_wnd->GetHWND())) return false;

	m_init = true;
	return true;
}

bool Framework::m_frame()
{
	m_wnd->RunEvent();
	if (!m_wnd->IsActive())
		return true;

	if (m_wnd->IsExit())
		return false;

	if (m_wnd->IsResize())
	{
	}

	m_render->BeginFrame();
	if (!m_render->Draw())
		return false;
	m_render->EndFrame();

	return true;
}

void Framework::Close()
{
	m_init = false;
	m_render->Shutdown();
	_DELETE(m_render);
	_CLOSE(m_wnd);
	_CLOSE(m_input);
}