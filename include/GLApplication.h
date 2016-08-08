//
//  GLApplication.h
//  ModelView
//
//  Created by Haoyan Huo on 3/19/15.
//  Copyright (c) 2015 Haoyan Huo. All rights reserved.
//
//  Modified by Bowen Yang

# ifndef GLAPPLICATION
# define GLAPPLICATION

# include "AllinGL.h"
# include "GLObject.h"

/**
 * @brief GLApplication class is the base class of a complete OpenGL application. 
 *
 * GLApplication registers the OpenGL context and GLUT, installs callbacks, and 
 * dispachs every call of drawing of a frame. There should always be only one
 * GLApplication instance during the lifecycle of application.
 *
 * GLApplication also has a reference to the window created by GLUT. Also the input
 * events will be received by GLApplication and send to client codes.
 */
class GLApplication : public GLObject
{
public:
	/** @brief default constructor */
	GLApplication();
	/** @brief default destructor */
	virtual ~GLApplication();

	/** @brief this method creates the GLUT window, also initializes the OpenGL context. */
	void WindowCreation(const char* title, int width, int height);
	/** @brief enter the main GLUT event loop. */
	void RunMainLoop();

	/** @brief Gets the key state. */
	bool IsKeyDown(unsigned char chr) {return fKeyState[chr] == 1;}
	/** @brief Gets the mouse key state. */
	bool IsMouseKeyDown(int which)
	{return (which <= 2 && which >= 0) ? (fMouseState[which] == 1) : false;}

	/** @brief Gets the window width.
	 * @see GetWindowHeight()
	 */
	int GetWindowWidth() {return fWindowSize[0];}
	/** @brief Gets the window height.
	 * @see GetWindowWidth()
	 */
	int GetWindowHeight() {return fWindowSize[1];}
	/** @brief Gets the framebuffer width.
	 * @see GetWindowFramebufferHeight().
	 */
	int GetWindowFramebufferWidth() {return fWindowFramebufferSize[0];}
	/** @brief Gets the framebuffer height.
	 * @see GetWindowFramebufferWidth().
	 */
	int GetWindowFramebufferHeight() {return fWindowFramebufferSize[1];}
	/** @brief Gets the pointer X coordinate.
	 * @see GetPointerY()
	 */
	int GetPointerX() {return fMousePosition[0];}
	/** @brief Gets the pointer Y coordinate.
	 * @see GetPointerX()
	 */
	int GetPointerY() {return fMousePosition[1];}

	GLFWwindow* getWindow(){ return this->fWindow; };

protected:

	 /** @brief Event callback when the application is created and OpenGL context
	 * initialized.
	 *
	 * Initialize important objects and get ready for rendering during this callback.
	 * Three fundamental callbacks that child classes must implement are CreateApplication(),
	 * RenderFrame(), and ShutdownApplication(). And those virtual methods could be 
	 * implemented for conveience:
	 *  - WindowSizeChanged()
	 *  - MouseKeyDown()
	 *  - MouseKeyUp()
	 *  - KeyDown()
	 *  - KeyUp()
	 *  - MouseMove()
	 *  - MouseScrollUp()
	 *  - MouseScrollDown()
	 */
	virtual void CreateApplication() = 0;
	/** @brief Event callback of every frame draw event.
	 *
	 * Draw the framebuffer in this callback. But try not doing heavy works.
	 */
	virtual void RenderFrame() = 0;
	/** @brief Event callback when the application is going to die.
	 *
	 * Free the objects created in CreateApplication() during this callback.
	 */
	virtual void ShutdownApplication() = 0;

	 /** @brief Event callback when the window size has changed.
	 * @param[in] width the new window width.
	 * @param[in] height the new window height.
	 * @see WindowFramebufferSizeChanged()
	 */
	virtual void WindowSizeChanged(int width, int height) {return;}

	 /**
	 * @brief Event callback when the framebuffer size of window has changed.
	 *
	 * This is different from WindowSizeChanged, while window size is measured in
	 * screen coordinates, framebuffer size is measured in pixels, this is especially
	 * important on retina displays, the window size may not be equal to framebuffer
	 * size.
	 * @param[in] width the new framebuffer width.
	 * @param[in] height the new framebuffer height.
	 * @see WindowSizeChanged()
	 */
	virtual void WindowFramebufferSizeChanged(int width, int height) {return;}

	 /** @brief Event callback when a mouse key is pressed.
	 * @param[in] which the key id, 0 stands for left button, and 1 the
	 * middle button, 2 the right button.
	 * @see MouseKeyUp()
	 */
	virtual void MouseKeyDown(int which) {return;}

	 /** @brief Event callback when a mouse key is released.
	 * @param[in] which the key id.
	 * @see MouseKeyDown()
	 */
	virtual void MouseKeyUp(int which) {return;}

	 /** @brief Event callback when a keyboard key is pressed.
	 * @param[in] which the key char.
	 * @see KeyUp()
	 */
	virtual void KeyDown(unsigned char which) {return;}

	 /** @brief Event callback when a keyboard key is release.
	 * @param[in] which the key char.
	 * @see KeyDown()
	 */
	virtual void KeyUp(unsigned char which) {return;}

	 /** @brief Event callback when the pointer moves in window.
	 * @param[in] x the x coordinate of pointer.
	 * @param[in] y the y coordinate of pointer.
	 */
	virtual void MouseMove(int x, int y) {return;}

	 /** @brief Event callback when scrolls.
	 *
	 */
	virtual void MouseScroll(double xoffset, double yoffset) {return;}

private:
	 /** @brief The singleton pointer of GLApplication. */
	static GLApplication* fInstance;

	 /** @brief Gets the unique GLApplication of this process. */
	static GLApplication* instance(){return fInstance;}

	void Resize(GLFWwindow* window, int width, int height);
	void Keyboard(GLFWwindow* window, int key, int scancode, int action, int mods);
	void Mouse(GLFWwindow* window, int button, int action, int mods);
	void Scroll(GLFWwindow* window, double xoffset, double yoffset);
	void Motion(GLFWwindow* window, double x, double y);
	void FramebufferSize(GLFWwindow* window, int width, int height);

	// static callbacks
	static void ErrorCallback(int err, const char* desc)
	{
		instance()->Info(debugMsg, "GLFW callback error at %s", desc);
	}
	static void ResizeCallback(GLFWwindow* window, int width, int height)
	{
		instance()->Resize(window, width, height);
	}
	static void KeyboardCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
	{
		instance()->Keyboard(window, key, scancode, action, mods);
	}
	static void MouseCallback(GLFWwindow* window, int button, int action, int mods)
	{
		instance()->Mouse(window, button, action, mods);
	}
	static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset)
	{
		instance()->Scroll(window, xoffset, yoffset);
	}
	static void MotionCallback(GLFWwindow* window, double x, double y)
	{
		instance()->Motion(window, x, y);
	}
	static void FramebufferSizeCallback(GLFWwindow* window, int width, int height)
	{
		instance()->FramebufferSize(window, width, height);
	}

	GLFWwindow* fWindow;
	int fWindowSize[2];
	int fWindowFramebufferSize[2];
	unsigned char fKeyState[GLFW_KEY_LAST], fMouseState[3];
	int fMousePosition[2];
};

# endif /* defined(__GLApplication_H__) */