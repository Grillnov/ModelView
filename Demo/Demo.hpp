# ifndef PHONG
# define PHONG
# include "GLApplication.h"
# include "MeshPack.h"

class Phong :public GLApplication
{
private:
	MeshPack* Pack;
public:
	virtual void MouseScroll(double x, double y)
	{
		
	}
	
	virtual void CreateApplication()
	{
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glEnable(GL_DEPTH_TEST);
		Pack = new MeshPack("D:/ModelView/assets/BasePlain.obj");
		Pack->Attach();
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		Pack->DrawMesh();
	}
	virtual void ShutdownApplication()
	{
		Pack->Detach();
		delete Pack;
	}
private:
};
# endif