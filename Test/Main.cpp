#include "CORE/Core.h"

using namespace Lobster;

class TestLayer : public Layer
{
public:
	void OnAttach() override
	{
	}
	void OnUpdate(float dt) override
	{
	}
	void OnEvent(Event& event) override
	{
	}
	void OnDetach() override
	{
	}
};

class Test : public LobsterCore
{
public:
	void OnStart() override
	{
		TestLayer* tl = new TestLayer();
		PushLayer(tl);
	}
	void OnUpdate(float dt) override
	{
	}
};

#ifdef NDEBUG
int __stdcall WinMain(HINSTANCE inst,HINSTANCE prev,LPSTR cmd_line,int cmd_show)
#else
int main(int argc,char** argv)
#endif

{
	return Test{}.Run();
}