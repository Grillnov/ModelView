# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class TexPlain : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program, Program2;
	Texture1D White;
public:
	virtual void CreateApplication()
	{
		Pack = MeshPack("D:/ModelView/assets/BasePlain.obj");
		Pack.Attach();

		unsigned char simpleTex[12] =
		{
			23, 134, 32,
			45, 23, 155,
			144, 23, 12,
			2, 4, 255
		};

		White = Texture1D("D:/ModelView/assets/trial.bmp", 0);
		//White = Texture1D(&simpleTex[0], 2, 0);
		White.Attach();

		Program.AddShader("D:/ModelView/shaders/texvert.glsl", GL_VERTEX_SHADER);
		Program.AddShader("D:/ModelView/shaders/texfrag.glsl", GL_FRAGMENT_SHADER);
		Program.Attach();
		Program.Use();

		Program.Uniform1("tex", 0);

		Program2.AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2.AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program2.Attach();
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program.Use();
		Program.UniformMat4("transformMatrix", MVP);
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Pack.DrawMesh();

		Program2.Use();
		Program2.Uniform3("color", glm::vec3(0.0f, 0.0f, 1.0f));
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

//RunInstance(TexPlain, 640, 480)