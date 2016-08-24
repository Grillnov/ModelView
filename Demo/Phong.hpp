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
		//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Pack = new MeshPack("D:/ModelView/assets/BT-7.obj");
		Pack->Attach();

		Program = new ProgramPack();
		Program->AddShader("D:/ModelView/Shaders/phongfrag.glsl", GL_FRAGMENT_SHADER);
		Program->AddShader("D:/ModelView/Shaders/phongvert.glsl", GL_VERTEX_SHADER);

		Program->Attach();
		Program->Uniform3("lightPosition", glm::vec3(0.0f, 0.0f, 1.0f));
		Program->Uniform1("scale", 0.2f);
		
		Program->Uniform4("lightColor", glm::vec4(1.0f));
		Program->Uniform4("diffuseColor", glm::vec4(1.0f, 1.0f, 0.0f, 1.0f));
		Program->Uniform4("ambientColor", glm::vec4(1.0f, 0.0f, 0.0f, 0.0f));
	}

	virtual void RenderFrame()
	{
		glm::mat4 MVP = camera.getMVP(GetAspectRatio(), 1.0f, glm::vec2(-0.5, -0.5));
		Program->UniformMat4("transformMatrix", camera.getMVP(GetAspectRatio(), 1.0f, glm::vec2(-0.5, 0)));
		Program->UniformMat4("ModelViewMatrix", camera.getMV(GetAspectRatio(), 1.0f, glm::vec2(0, 0)));

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