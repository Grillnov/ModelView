# include "AllinGL.h"
# include "GLApplication.h"
# include "BufferPack.hpp"
# include "Demo.hpp"

int main(void)
{
	GLApplication* app = new Phong();

	app->WindowCreation("Demo", 640, 480);
	app->RunMainLoop();
	
	system("pause");// Shall be commented
	delete app;

	return 0;
}