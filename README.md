ModelView 2.0
=======================

An Objective Oriented OpenGL wrapper library
-----------------------

# What is this thing

Not sure how to create OpenGL contexts?

Tired of binding vertexarrays around?

Confused by these tricky details of allocating buffers and fill their memory?

Don't know the way of implementing texture sampling?

ModelView's the thing you are looking for!

Get a quick grip of the abstraction through the [demo sample1](https://github.com/Grillnov/ModelView/blob/master/demo/TextureDemo.cpp) and [demo sample2](https://github.com/Grillnov/ModelView/blob/master/demo/DrawMeshDemo.cpp)!

# Further readings

For further details, You may want to refer to the [API documents](http://www.grillnov.com/modelview/index.html) here.

# How to build it:

### Clone the repository.

Clone the repository in whatever way you want.

Unzip it to whatever location you see fit as your working directory. For example, ./

### Unpack the assets and the 3rdParty libraries.

3rdParty libraries are packed in 3rdParty.rar, instead of submodules, just in case you don't really know how to use GitHub command lines.

Unzip the 3rdParty.rar and the assets.rar to the repo's working directory. This pack contains some meshes and texture pictures the project's gonna use.

After it's done, the hierarchy of the working directory should look like:

./3rdParty/gl3w

./3rdParty/glew

./3rdParty/glfw

./3rdParty/glm

./assets/BasePlain.obj

./assets/Android.obj

......

./ModelView.sln

### Open the solution file with Visual Studio.

Simply open this solution with Visual Studio.

This project file is created with Visual Studio 2013.

If your IDE complains that _MSC_VER version's too low for this project, you might have to create the project from scratch:

1. Create an empty project or a console application project(VC++).

2. Add all the source files from:
./src
./util
./demo

3. Add include paths to this project:
./3rdParty/gl3w/include
./3rdParty/glew/include
./3rdParty/glfw/include
./3rdParty/glm
./include
./util

4. Add library paths to this project:
./3rdParty/glew/lib/Release/Win32
./3rdParty/glfw/lib-vc$yourVisualStudioVersion
./3rdParty/gl3w/lib

5. Add libraries to this project:

For Release build:
glew32.lib
gl3w.lib
glfw3.lib
opengl32.lib

For Debug build:
glew32.lib
gl3wd.lib
glfw3.lib
opengl32.lib

Note that CMakeList and Makefile are coming soon, so that you don't have to create the project from scratch like this by then.

### Build the project.

Whatever way you see fit.

### Run!

Feel free to mess with the android shown on the screen.

# Known issues

### 1. Glew returns null pointers to functions and application crashes.
Solution: Run the application with your NVIDIA/ATI video card, instead of the one embedded on your CPU.

Solution2: Try and build glew/gl3w and glfw libraries under your own development environment.

### 2. Application crashes due to a glfw initiation failure/glew initiation failure.
Solution: Modify the options.h, so that it's correctly configured.

"Correctly configured" means the OpenGL context version's supported by your platform, and the resolution's appropriate.

### 3. Application initiates with a single OpenGL error 1280(Invalid enum) message.
Solution: It's an initiation bug from GLFW. Don't worry about this.

Try another version of GLFW on your platform if you have to.

# To create an OpenGL application:

#### Define a class derived from GLApplication or FPSApplication.
#### Initiate members in the construction function.
#### Override RenderFrame() to control rendering of frames.
#### Implement the destruction function to do some cleaning if you have to.
#### Define macro RunInstance($Name_of_your_class). That's the entrance.

See [./demo/PhongDemo.cpp](https://github.com/Grillnov/ModelView/blob/master/demo/PhongDemo.cpp) and learn how to implement Phong shading with a mere 40 lines!

# Common Samples

### Create a buffer and feed some data

BufferPack<GLfloat> buffer;

buffer.Alloc(4);

buffer[0] = 1.0f;

buffer[1] = 0.0f;

......

buffer.Done();
//And your buffer's ready in your video card.
### Create a buffer as element array, and draw a vertex array

VertexArray arr;

BufferPack<GLuint> elearrbuf;

elearrbuf.Alloc(18);

elearrbuf[0] = 1;

......

elearrbuf.Done();

arr.AddAttribAt(elearrbuf, 0, 3);
//And you can use these attributes in vertex shader layout 0.

arr.DrawElements(18, elearr);
//And drawcalls are invoked, 18/3=6 triangles are drawn.

### Create a program and feed some uniforms.

ProgramPack Program;

Program[GL_VERTEX_SHADER] = "../shaders/simpleVertex.glsl";

Program[GL_FRAGMENT_SHADER] = "../shaders/simpleFragment.glsl";

Program.Link();
//And your program's ready.

Program["uniform_variable"] = 1.0f;
//And a floating point uniform's fed to the program.

Program.Use();
//And the program's now being used by the drawcalls after this line.

### Create a texture.
Texture2D White = Texture2D(0);

White.LoadFromBMP("../assets/blip.bmp");

White.Activate();
//And the texture's ready at sampler slot 0.

Program["sampler"] = 0;
//And you can use the texture in GLSL now.

### Draw a mesh model.

MeshPack Pack = MeshPack("../assets/BasePlain.obj");

Pack.Attach();

Pack.DrawMesh();
//And the mesh is drawn with the current active program.