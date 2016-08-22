# include "AllinGL.h"
# include "GLApplication.h"
# include "BufferPack.hpp"
# include "Demo.hpp"

int main(void)
{
	Phong app = Phong();

	app.WindowCreation("Demo", 640, 480);
	app.RunMainLoop();

	return 0;
}