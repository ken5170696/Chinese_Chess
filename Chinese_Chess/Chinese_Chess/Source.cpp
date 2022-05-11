#include "GameManager.h"

int main()
{
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