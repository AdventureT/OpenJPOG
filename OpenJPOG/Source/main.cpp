#include "TApplication/TApplication.h"
#include "TMemory.h"

class AApplication : public Toshi::TApplication
{
	virtual TBOOL OnCreate(TINT argc, TPCHAR* const argv) override
	{
		return TTRUE;
	}
};

static AApplication g_oTheApp;

int main(int argc, char** argv)
{
	if (g_oTheApp.Create("Jurassic Park: Operation Genesis - (c) Blue Tongue Software", argc, argv)) {
		Toshi::TMemory::DebugPrintHALMemInfo(TNULL);
		g_oTheApp.Execute();
	}
	g_oTheApp.Destroy();
	return 0;
}