# ifndef PHONG
# define PHONG
# include "GLApplication.h"
# include "MeshPack.h"
# include "ProgramPack.h"
# include "CameraView.h"
# include <FPSApplication.h>

class Phong :public FPSApplication
{
private:
	MeshPack* Pack;
	ProgramPack* Program, *Program2;
public:
	virtual void CreateApplication()
	{
		glEnable(GL_DEPTH_TEST);
		Pack = new MeshPack("D:/ModelView/assets/test.obj");
		Pack->Attach();

		Program = new ProgramPack();
		Program->AddShader("D:/ModelView/Shaders/phongfrag.glsl", GL_FRAGMENT_SHADER);
		Program->AddShader("D:/ModelView/Shaders/phongvert.glsl", GL_VERTEX_SHADER);
		Program->Attach();
		Program->Use();

		Program->Uniform3("lightPosition", glm::vec3(0.0f, 0.0f, 1.0f));
		Program->Uniform4("lightColor", glm::vec4(1.0f));
		Program->Uniform4("diffuseColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Program->Uniform4("ambientColor", glm::vec4(0.3f, 0.15f, 0.0f, 1.0f));

		Program2 = new ProgramPack();
		Program2->AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2->AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program2->Attach();
	}

	virtual void RenderFrame()
	{
		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program->Use();
		Program->UniformMat4("transformMatrix", MVP);
		Program->UniformMat4("ModelViewMatrix", FPSCamera.GetModelView());

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Pack->DrawMesh();

		Program2->Use();
		GLfloat color[3] = { 0.0, 0.0, 1.0 };
		Program2->Uniform3("color", color);
		Program2->UniformMat4("MVP", MVP);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
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