# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <Texture2D.h>
# include <FrameBuffer.h>
/**
@brief How to write to textures and buffers on the fly.
*/
class FrameBufferDemo : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
	Texture2D White;
public:
	FrameBufferDemo() : Pack("../assets/BasePlain.obj"), White(0)
	{
		Pack.Attach();
		White.LoadFromBMP("../assets/blip.bmp");
		White.Param(GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		White.Activate();
		Program[GL_VERTEX_SHADER] = "../shaders/texvert.glsl";
		Program[GL_FRAGMENT_SHADER] = "../shaders/texfrag.glsl";
		Program.Link();
		Program["tex"] = 0;
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		glm::mat4 MVP = FPSCamera.GetModelViewProjection();
		Program.Use();
		Program["transformMatrix"] = MVP;
		Pack.DrawMesh();
	}
	~FrameBufferDemo()
	{
		Pack.Detach();
	}
};
//RunInstance(FrameBufferDemo)