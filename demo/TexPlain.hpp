# ifndef TEXPLAIN
# define TEXPLAIN

# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class TexPlain :public FPSApplication
{
private:
	MeshPack* Pack;
	ProgramPack* Program, *Program2;
	Texture2D* White;
public:
	virtual void CreateApplication()
	{
		glEnable(GL_DEPTH_TEST);
		Pack = new MeshPack("D:/ModelView/assets/BasePlain.obj");
		Pack->Attach();

		White = new Texture2D("D:/ModelView/assets/trial.bmp", 0);
		White->Attach();

		Program = new ProgramPack();

		Program->AddShader("D:/ModelView/shaders/texvert.glsl", GL_VERTEX_SHADER);
		Program->AddShader("D:/ModelView/shaders/texfrag.glsl", GL_FRAGMENT_SHADER);
		Program->Attach();
		Program->Use();

		Program->Uniform1("tex", 0);

		Program2 = new ProgramPack();
		Program2->AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2->AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);
		Program2->Attach();
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program->Use();
		Program->UniformMat4("transformMatrix", MVP);
		
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