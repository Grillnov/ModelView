# ifndef PHONG
# define PHONG
# include "GLApplication.h"
# include "MeshPack.h"

class Phong :public GLApplication
{
public:
	virtual void MouseScroll(double x, double y)
	{
		
	}
	void fun()
	{
		MeshPack Pack("D:/ModelView/assets/teapot.obj");
		BufferPack<GLfloat> Pact2(20);
		Pact2.Detach();
		Pact2.Attach();
	}
	virtual void CreateApplication()
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		BufferPack<GLfloat> Pact1(40);
		fun();
		Pact1.Attach();
		Pact1.Detach();
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
	}
	virtual void ShutdownApplication()
	{
	}
private:
};
# endif