# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class TexPlain : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program, Program2;
	Texture2D White;
public:
	TexPlain() : Pack("D:/ModelView/assets/BasePlain.obj"), White(0)
	{
		Pack.Attach();

		unsigned char simpleTex[12] =
		{
			23, 134, 32,
			45, 23, 155,
			144, 23, 12,
			2, 4, 255
		};

		White.LoadFromBMP("D:/ModelView/assets/trial.bmp");
		//White.LoadFromMemory(simpleTex, 2, 2);

		Program.AddShader("D:/ModelView/shaders/texvert.glsl", GL_VERTEX_SHADER);
		Program.AddShader("D:/ModelView/shaders/texfrag.glsl", GL_FRAGMENT_SHADER);
		Program.Link();

		Program.Uniform1("tex", 0);

		Program2.AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2.AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program2.Link();
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
	}
};

RunInstance(TexPlain)