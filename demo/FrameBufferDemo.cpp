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
	FrameBuffer FBO;
	ProgramPack ProgramRender;
	ProgramPack ProgramDraw;
	Texture2D Text;
public:
	FrameBufferDemo() : Text(0)
	{
		
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		glm::mat4 MVP = FPSCamera.GetModelViewProjection();
	}
	~FrameBufferDemo()
	{
	}
};
//RunInstance(FrameBufferDemo)