#include "GameManager.h"

int main()
{
	GameServer gs;
	try
	{
		GameManager app;
		app.run();
	}
	catch (std::exception& e)
	{
		std::cout << "\nEXCEPTION: " << e.what() << std::endl;
	}
}