#include <catch2/catch_session.hpp>
#include "TApplication/TApplication.h"

TOSHI_NAMESPACE_USING

class AApplication : public Toshi::TApplication
{
	virtual TBOOL OnCreate(TINT argc, TPCHAR* const argv) override
	{
		return TApplication::OnCreate(argc, argv);
	}

	virtual TBOOL OnUpdate(TFLOAT a_fDelta)
	{
		// Skip Updating
		return TFALSE;
	}
};

static AApplication g_oTheApp;

int main(int argc, char* argv[])
{
	int result = 0;
	if (g_oTheApp.Create("UnitTests", argc, argv)) {
		g_oTheApp.Execute();
		result = Catch::Session().run(argc, argv);
	}

	g_oTheApp.Destroy();

	return result;
}
