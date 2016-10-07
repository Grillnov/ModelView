# include <BufferPack.hpp>
# include <VertexArrayPack.h>
# include <ProgramPack.h>
# include <FPSApplication.h>
/**
@brief How to send in vertices and invoke draw calls from scratch.
*/
class DrawMeshDemo : public FPSApplication
{
private:
	VertexArrayPack VertArr;
	BufferPack<GLfloat> Coords;
	BufferPack<GLuint> ElementArr;
	ProgramPack Program;
public:
	DrawMeshDemo()
	{
		Program[GL_VERTEX_SHADER] = "../shaders/simpleVertex.glsl";
		Program[GL_FRAGMENT_SHADER] = "../shaders/simpleFragment.glsl";
		Program.Link();
		
		Coords.Alloc(15);
		Coords[0] = 10.0f;
		Coords[1] = 0.0f;
		Coords[2] = 10.0f;

		Coords[3] = 10.0f;
		Coords[4] = 0.0f;
		Coords[5] = -10.0f;

		Coords[6] = -10.0f;
		Coords[7] = 0.0f;
		Coords[8] = -10.0f;

		Coords[9] = -10.0f;
		Coords[10] = 0.0f;
		Coords[11] = 10.0f;

		Coords[12] = 0.0f;
		Coords[13] = 10.0f;
		Coords[14] = 0.0f;
		Coords.Done();

		ElementArr.Alloc(18);

		ElementArr[0] = 0;
		ElementArr[1] = 3;
		ElementArr[2] = 1;

		ElementArr[3] = 1;
		ElementArr[4] = 3;
		ElementArr[5] = 2;

		ElementArr[6] = 0;
		ElementArr[7] = 1;
		ElementArr[8] = 4;

		ElementArr[9] = 1;
		ElementArr[10] = 2;
		ElementArr[11] = 4;

		ElementArr[12] = 2;
		ElementArr[13] = 3;
		ElementArr[14] = 4;

		ElementArr[15] = 0;
		ElementArr[16] = 4;
		ElementArr[17] = 3;

		ElementArr.Done();

		VertArr.AddAttribAt(Coords, 0, 3);
		glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	}
	virtual void RenderFrame()
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		glViewport(0, 0, GetWindowWidth(), GetWindowHeight());
		glm::mat4 MVP = FPSCamera.GetModelViewProjection(GetAspectRatio());
		Program["MVP"] = MVP;
		Program["color"] = glm::vec3(0.0f, 0.0f, 1.0f);
		Program.Use();

		VertArr.Bind();
		ElementArr.Bind(GL_ELEMENT_ARRAY_BUFFER);
		glDrawElements(GL_TRIANGLES, 18, GL_UNSIGNED_INT, nullptr);
	}
	~DrawMeshDemo()
	{
	}
};
//RunInstance(DrawMeshDemo)