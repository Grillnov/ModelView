# ifndef PHONG
# define PHONG

# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class Phong :public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
	ProgramPack Program2;
public:
	virtual void CreateApplication()
	{
		glEnable(GL_DEPTH_TEST);
		Pack = MeshPack("D:/ModelView/assets/Android.obj");
		Pack.Attach();

		Program.AddShader("D:/ModelView/shaders/phongfrag.glsl", GL_FRAGMENT_SHADER);
		Program.AddShader("D:/ModelView/shaders/phongvert.glsl", GL_VERTEX_SHADER);
		Program.Attach();
		Program.Use();
		Program.Uniform3("lightPosition", glm::vec3(0.0f, 0.0f, 1.0f));
		Program.Uniform4("lightColor", glm::vec4(1.0f));
		Program.Uniform4("diffuseColor", glm::vec4(0.0f, 1.0f, 0.0f, 1.0f));
		Program.Uniform4("ambientColor", glm::vec4(0.3f, 0.1f, 0.0f, 1.0f));

		Program2.AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2.AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program2.Attach();
		Program2.Use();
		Program2.Uniform3("color", glm::vec3(0.0f, 0.0f, 1.0f));
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program.Use();
		Program.UniformMat4("transformMatrix", MVP);
		Program.UniformMat4("ModelViewMatrix", FPSCamera.GetModelView());

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Pack.DrawMesh();

		Program2.Use();
		Program2.UniformMat4("MVP", MVP);

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Pack.DrawMesh();
	}

	virtual void ShutdownApplication()
	{
		Pack.Detach();
		Program.Detach();
	}
};

RunInstance(Phong, 640, 480)
# endif