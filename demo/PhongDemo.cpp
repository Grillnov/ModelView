# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
/**
@brief A compilation of how to create programs and use them to render meshes.
*/
class PhongDemo : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
public:
	PhongDemo() : Pack("../assets/Android.obj")
	{
		Pack.Attach();
		Program[GL_VERTEX_SHADER] = "../shaders/phongvert.glsl";
		Program[GL_FRAGMENT_SHADER] = "../shaders/phongfrag.glsl";
		Program.Link();
		Program["lightPosition"] = glm::vec3(1.0f, 0.0f, 0.0f);
		Program["lightColor"] = glm::vec4(1.0f);
		Program["diffuseColor"] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		Program["ambientColor"] = glm::vec4(0.3f, 0.1f, 0.0f, 1.0f);
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program["transformMatrix"] = MVP;
		Program["ModelViewMatrix"] = FPSCamera.GetModelView();
		Program.Use();
		Pack.DrawMesh();
	}
	~PhongDemo()
	{
		Pack.Detach();
	}
};
RunInstance(PhongDemo)