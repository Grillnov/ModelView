# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class TexPlain : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
	Texture2D SimplePic;
public:
	TexPlain() : Pack("D:/ModelView/assets/BasePlain.obj"), SimplePic(0)
	{
		Pack.Attach();

		unsigned char simpleTex[12] =
		{
			23, 134, 32,
			45, 23, 155,
			144, 23, 12,
			2, 4, 255
		};

		SimplePic.LoadFromBMP("D:/ModelView/assets/trial.bmp");
		//White.LoadFromMemory(simpleTex, 2, 2);

		Program[GL_VERTEX_SHADER] = ("D:/ModelView/shaders/texvert.glsl");
		Program[GL_FRAGMENT_SHADER] = ("D:/ModelView/shaders/texfrag.glsl");
		Program.Link();

		Program["tex"] = 0;
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program.Use();
		Program["transformMatrix"] = MVP;
		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Pack.DrawMesh();
	}

	virtual void ShutdownApplication()
	{
		Pack.Detach();
	}
};

RunInstance(TexPlain)