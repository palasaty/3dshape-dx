#include "input_listener.h"
#include "framework.h"

class AppInput : public InputListener
{
public:
	bool KeyPressed(const KeyEvent& arg)
	{
		printf("key press %c\n", arg.wc);
		return false;
	}
	bool MouseMove(const MouseEvent& arg)
	{
		printf("mouse %d - %d\n", arg.x, arg.y);
		return false;
	}
};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	Framework framework;

	framework.SetRender(new AppRender());
	framework.Init();
	framework.AddInputListener(new AppInput());

	framework.Run();

	framework.Close();
	return 0;
}