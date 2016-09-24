# include <MeshPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
# include <TexturePack.h>

class Phong : public FPSApplication
{
private:
	MeshPack Pack;
	ProgramPack Program;
	ProgramPack Program2;
public:
	Phong() : Pack("D:/ModelView/assets/Android.obj")
	{
		Pack.Attach();

		Program[GL_VERTEX_SHADER] = "D:/ModelView/shaders/phongvert.glsl";
		Program[GL_FRAGMENT_SHADER] = "D:/ModelView/shaders/phongfrag.glsl";

		Program.Link();

		Program["lightPosition"] = glm::vec3(1.0f, 0.0f, 0.0f);
		Program["lightColor"] = glm::vec4(1.0f);
		Program["diffuseColor"] = glm::vec4(0.0f, 1.0f, 0.0f, 1.0f);
		Program["ambientColor"] = glm::vec4(0.3f, 0.1f, 0.0f, 1.0f);

		Program2.AddShader("D:/ModelView/Shaders/simpleFragment.glsl", GL_FRAGMENT_SHADER);
		Program2.AddShader("D:/ModelView/Shaders/simpleVertex.glsl", GL_VERTEX_SHADER);

		Program2.Link();

		Program2["color"] = glm::vec3(1.0f, 0.0f, 1.0f);
	}

	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());

		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());

		Program["transformMatrix"] = MVP;
		Program["ModelViewMatrix"] = FPSCamera.GetModelView();

		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		Program.Use();
		Pack.DrawMesh();

		Program2["MVP"] = MVP;

		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		Program2.Use();
		Pack.DrawMesh();
	}

	~Phong()
	{
		Pack.Detach();
	}
};

//RunInstance(Phong)

/*int main(void)
{
	Phong app;
	app.StartMainLoop();
}*/