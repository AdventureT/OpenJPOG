#include <catch2/catch_session.hpp>
#include "TApplication/TApplication.h"

TOSHI_NAMESPACE_USING

class AApplication : public Toshi::TApplication
{
};

static AApplication g_oTheApp;

int main(int argc, char* argv[]) 
{
	int result;
	if (g_oTheApp.Create("UnitTests", argc, argv)) {
		//g_oTheApp.Execute();
		result = Catch::Session().run(argc, argv);
	}

	g_oTheApp.Destroy();

	return result;
}