# ifndef PHONG
# define PHONG
# include "GLApplication.h"
# include "MeshPack.h"
# include "ProgramPack.h"

class Phong :public GLApplication
{
private:
	MeshPack* Pack;
	ProgramPack* Program;
public:
	virtual void CreateApplication()
	{
		glEnable(GL_DEPTH_TEST);
		Pack = new MeshPack("D:/ModelView/assets/teapot.obj");
		Pack->Attach();

		Program = new ProgramPack();
		Program->AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program->AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);

		Program->Attach();
		Program->UseProgramPack();
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.1f, 0.2f, 0.3f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		Pack->DrawMesh();
	}
	virtual void ShutdownApplication()
	{
		Pack->Detach();
		delete Pack;
		Program->Detach();
		delete Program;
	}
private:
};
# endif