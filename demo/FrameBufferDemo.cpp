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
	MeshPack Android, Plain;
	ProgramPack ProgramRender;
	ProgramPack ProgramDraw;
	FrameBuffer FBO;
	GLuint fbo, textureID;
	Texture2D Text1;
	unsigned int flow;
public:
	FrameBufferDemo() : Android("../assets/Android.obj"), Plain("../assets/Baseplain.obj")
		, flow(10), Text1(0)
	{
		ProgramRender[GL_VERTEX_SHADER] = "../shaders/simpleVertexFBO.glsl";
		ProgramRender[GL_FRAGMENT_SHADER] = "../shaders/simpleFragmentFBO.glsl";
		ProgramRender.Link();

		ProgramDraw[GL_VERTEX_SHADER] = "../shaders/texvert.glsl";
		ProgramDraw[GL_FRAGMENT_SHADER] = "../shaders/texfrag.glsl";
		ProgramDraw.Link();
		ProgramDraw["tex"] = 0;

		Android.Attach();
		Plain.Attach();

		Text1.Alloc(GetWindowWidth(), GetWindowHeight());
		FBO.AddRenderTargetAt(Text1, GL_COLOR_ATTACHMENT0);
	}
	virtual void RenderFrame()
	{
		FBO.Bind();
		FBO.DrawFrameBuffer();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		float r = flow / 100.0f;
		ProgramRender["varyingcolor"] = glm::vec4(r, 0.0f, 1.0f, 1.0f);
		ProgramRender["MVP"] = FPSCamera.GetModelViewProjection();
		ProgramRender.Use();
		Android.DrawMesh();

		FBO.UnBind();

		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		Text1.Activate();
		ProgramDraw.Use();
		glm::mat4 MVP = FPSCamera.GetModelViewProjection();
		ProgramDraw["transformMatrix"] = MVP;
		Android.DrawMesh();

		if (flow >= 100)
		{
			flow = 0;
		}
		flow++;
	}
	~FrameBufferDemo()
	{
		Android.Detach();
		Plain.Detach();
	}
};
RunInstance(FrameBufferDemo)