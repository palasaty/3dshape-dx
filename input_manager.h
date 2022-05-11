#pragma once

#include "input_codes.h"
#include "common.h"

class InputListener;

class InputManager
{
public:
	void Init();
	void Close();

	void Run(const UINT& msg, WPARAM wParam, LPARAM lParam);

	void AddListener(InputListener* Listener);

	void SetWinRect(const RECT& winrect);

private:
	void m_eventcursor();
	void m_eventmouse(const eMouseKeyCodes KeyCode, bool press);
	void m_mousewheel(short Value);
	void m_eventkey(const eKeyCodes KeyCode, const wchar_t ch, bool press);

private:

	std::list<InputListener*> m_Listener;

	RECT m_windowrect;
	int m_curx;
	int m_cury;
	int m_MouseWheel;
};
