# ifndef PHONG
# define PHONG
# include "GLApplication.h"
# include "MeshPack.h"
# include "ProgramPack.h"
# include "CamPack.h"

class Phong :public GLApplication
{
private:
	MeshPack* Pack;
	ProgramPack* Program;
	CamPack camera;
public:
	virtual void CreateApplication()
	{
		glEnable(GL_DEPTH_TEST);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Pack = new MeshPack("D:/ModelView/assets/teapot.obj");
		Pack->Attach();

		Program = new ProgramPack();
		Program->AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program->AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);

		Program->Attach();
		GLfloat Color[4] = { 1.0f, 0.0f, 1.0f, 1.0f };
		Program->Uniform3("Color", Color);

		Program->Uniform1("scale", 0.4);
		//Program->Use();
	}
	virtual void RenderFrame()
	{
		glm::mat4 MVP = camera.getMVP(GetAspectRatio(), 1.0f, glm::vec2(2, 0));
		Program->UniformMat4("MVP", &MVP[0][0]);

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
};
# endif