# include "AllinGL.h"
# include "GLApplication.h"
# include "BufferPack.hpp"
# include "Phong.hpp"

int main(void)
{
	Phong app = Phong();

	app.StartWindow("Demo");// , 640, 480);
	app.RunMainLoop();

	return 0;
}