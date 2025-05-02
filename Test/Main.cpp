#include "CORE/Core.h"

using namespace Lobster;

class Test : public LobsterCore
{
public:
	void OnStart() override
	{
	}
	void OnUpdate(float dt) override
	{
	}
};

int main(int argc,char* argv[])
{
	return Test{}.Run();
}