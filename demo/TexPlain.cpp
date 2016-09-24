# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class TexPlain : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
	Texture2D White;
public:
	TexPlain() : Pack("D:/ModelView/assets/BasePlain.obj"), White(0)
	{
		Pack.Attach();

		White.LoadFromBMP("D:/ModelView/assets/trial.bmp");

		Program[GL_VERTEX_SHADER] = "D:/ModelView/shaders/texvert.glsl";
		Program[GL_FRAGMENT_SHADER] = "D:/ModelView/shaders/texfrag.glsl";
		Program.Link();

		Program["tex"] = 0;

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program.Use();
		Program["transformMatrix"] = MVP;
		
		Pack.DrawMesh();
	}

	~TexPlain()
	{
		Pack.Detach();
	}
};

RunInstance(TexPlain)