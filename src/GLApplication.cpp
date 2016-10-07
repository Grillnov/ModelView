//
//  GLApplication.cpp
//  ModelView
//
//  Created by Haoyan Huo on 3/19/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# include <GLApplication.h>
# include <Options.h>
# include <BenchmarkTimer.h>

GLApplication* GLApplication::fInstance = nullptr;

# ifdef __llvm__
# pragma clang diagnostic push
# pragma clang diagnostic ignored "-Wdeprecated-declarations"
# endif // __llvm__

GLApplication::GLApplication() : fWindow(nullptr)
{
	Log(debugMsg, "Initialization may take some time. Please wait...");

	fWindowSize[0] = xWindowWidth;
	fWindowSize[1] = yWindowHeight;

	fMousePosition[0] = 0;
	fMousePosition[1] = 0;

	fWindowFramebufferSize[0] = 0;
	fWindowFramebufferSize[1] = 0;

	memset(fKeyState, 0, sizeof(fKeyState));
	memset(fMouseState, 0, sizeof(fMouseState));

	if (fInstance)
		Error(debugMsg, "More than one GL app is instantiated!");

	fInstance = this;

	if (!glfwInit())
		Error(debugMsg, "GLFW initialization failed!");

	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, GLMajorVer);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, GLMinorVer);
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWmonitor* primaryMonitor = glfwGetPrimaryMonitor();

	if (isFullScreened)
	{
		fWindow = glfwCreateWindow(xWindowWidth, yWindowHeight, titleofWindow, primaryMonitor, nullptr);
	}
	else
	{
		fWindow = glfwCreateWindow(xWindowWidth, yWindowHeight, titleofWindow, nullptr, nullptr);
	}

	glfwMakeContextCurrent(fWindow);

# ifdef USEGL3W
	/*
	Initiate Gl3w to retrieve function pointers to OpenGL interfaces.
	*/
	if (0 != gl3wInit())
	{
		Error(debugMsg, "Gl3w initialization failed!");
	}
# endif

	std::string device = reinterpret_cast<const char*>(glGetString(GL_RENDERER));
	std::string vendor = reinterpret_cast<const char*>(glGetString(GL_VENDOR));

	/*
	An Intel integrated graphics device is detected.
	Certain Intel drivers are not supported by glew, and null function pointers might be retrieved.
	*/
	if (vendor.find("Intel") != -1)
	{
		Warning(debugMsg, "Running this framework on Windows platform with an Intel device may cause crashing due to glew support.");
	}

# ifdef USEGLEW
	/*
	It might be troublesome if a laptop video card is detected on windows platform.
	Glew expects global flag glewExperimental to be on so that function pointers are retrieved properly.
	*/
	if (device.find('M') != -1)
	{
		Warning(debugMsg, "Notebook video card was detected. GlewExperimental flag is now switched on.");
		glewExperimental = GL_TRUE;
	}

	/*
	Initiate Glew to retrieve function pointers to OpenGL interfaces.
	*/
	if (GLEW_OK != glewInit())
	{
		Error(debugMsg, "Glew initialization failed!");
	}
# endif

	Info(debugMsg, "OpenGL version: %s", glGetString(GL_VERSION));
	Info(debugMsg, "Running on rendering device: %s", device.c_str());
	Info(debugMsg, "GPU Vendor: %s", vendor.c_str());

	fWindowSize[0] = xWindowWidth;
	fWindowSize[1] = yWindowHeight;
	windowName = titleofWindow;

	glfwGetFramebufferSize(fWindow, fWindowFramebufferSize, fWindowFramebufferSize + 1);

	if (!fWindow)
		Error(debugMsg, "Failed to create window %s!", titleofWindow);

	glfwSwapInterval(1);

	glfwSetInputMode(fWindow, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	glfwSetErrorCallback(GLApplication::ErrorCallback);
	glfwSetMouseButtonCallback(fWindow, GLApplication::MouseCallback);
	glfwSetWindowSizeCallback(fWindow, GLApplication::ResizeCallback);
	glfwSetKeyCallback(fWindow, GLApplication::KeyboardCallback);
	glfwSetScrollCallback(fWindow, GLApplication::ScrollCallback);
	glfwSetCursorPosCallback(fWindow, GLApplication::MotionCallback);
	glfwSetFramebufferSizeCallback(fWindow, GLApplication::FramebufferSizeCallback);
	glfwSetWindowCloseCallback(fWindow, GLApplication::WindowClosedCallback);

	/*
	Initialization complete!
	*/
	CheckStatus(__FUNCTION__);

	Log(debugMsg, "Initialization complete!");
}

GLApplication::~GLApplication()
{
	glfwDestroyWindow(fWindow);
	glfwTerminate();
}

void GLApplication::StartMainLoop()
{
	/*
	* OpenGL does not have depth test switched on by default.
	* But it seems better off to do it for you.
	*/
	glEnable(GL_DEPTH_TEST);

	if (enableMultiSampling == 1)
	{
		GLint isMSsupported = 0;
		glGetIntegerv(GL_SAMPLE_BUFFERS, &isMSsupported);
		if (isMSsupported == 1)
		{
			glEnable(GL_MULTISAMPLE);
			Log(debugMsg, "Multisampling now activated.");
		}
		else
		{
			Warning(debugMsg, "Multisampling is not supported by this OpenGL implementation.");
		}
	}
	CheckStatus(__FUNCTION__);

	while ((!glfwWindowShouldClose(fWindow)))
	{
		RenderFrame();

		glfwSwapBuffers(fWindow);

		glfwPollEvents();
		PollController();

		CheckStatus(__FUNCTION__);

		if (IsKeyDown('Q'))
		{
			break;
		}
	}
}

void GLApplication::Resize(GLFWwindow *window, int width, int height)
{
	fWindowSize[0] = width;
	fWindowSize[1] = height;

	WindowSizeChanged(width, height);
}

void GLApplication::Keyboard(GLFWwindow *window, int key, int scancode, int action, int mods)
{
	switch (action) 
	{
	case GLFW_PRESS:
		fKeyState[key] = GLFW_PRESS;
		KeyDown(key);
		break;
	case GLFW_REPEAT:
		fKeyState[key] = GLFW_REPEAT;
		KeyDown(key);
		break;
	case GLFW_RELEASE:
		fKeyState[key] = GLFW_RELEASE;
		KeyUp(key);
		break;
	default:
		break;
	}
}

void GLApplication::Motion(GLFWwindow *window, double x, double y)
{
	fMousePosition[0] = static_cast<int>(x);
	fMousePosition[1] = static_cast<int>(y);
	MouseMove(static_cast<int>(x), static_cast<int>(y));
}

void GLApplication::Mouse(GLFWwindow *window, int button, int action, int mods)
{
	int which;
	switch (button) 
	{
	case GLFW_MOUSE_BUTTON_LEFT:
		which = 0;
		break;

	case GLFW_MOUSE_BUTTON_MIDDLE:
		which = 1;
		break;

	case GLFW_MOUSE_BUTTON_RIGHT:
		which = 2;
		break;

	default:
		Warning(debugMsg, "Unknown mouse button %d from GLFW", button);
		return;
	}

	switch (action) 
	{
	case GLFW_PRESS:
		fMouseState[which] = 1;
		MouseButtonDown(which);
		break;

	case GLFW_RELEASE:
		fMouseState[which] = 0;
		MouseButtonUp(which);
		break;

	default:
		Warning(debugMsg, "Unknown mouse button state %d from GLFW", action);
		return;
	}
}

void GLApplication::Scroll(GLFWwindow *window, double xoffset, double yoffset)
{
	MouseScroll(xoffset, yoffset);
}

void GLApplication::FramebufferSize(GLFWwindow *window, int width, int height)
{
	fWindowFramebufferSize[0] = width;
	fWindowFramebufferSize[1] = height;
	WindowFramebufferSizeChanged(width, height);
}

# ifdef __llvm__
# pragma clang diagnostic pop
# endif // __llvm__