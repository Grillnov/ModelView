//
//  FPSApplication.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 24, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <FPSApplication.h>

const static float VelocityDirect = 0.01f;//Forward/Backward moving speed
const static float VelocityFlank = 0.01f;//Flanking moving speed
const static float VelocityVertical = 0.01f;//Vertical moving speed
const static float MouseSensitivity = 0.05f;//camera spin speed

const static bool isYAxisReversed = true;
const static bool isXAxisReversed = false;

void FPSApplication::PollController()
{
	if (IsKeyDown('W'))
	{
		FPSCamera.MoveForward(VelocityDirect);
	}
	if (IsKeyDown('A'))
	{
		FPSCamera.MoveLeft(VelocityFlank);
	}
	if (IsKeyDown('S'))
	{
		FPSCamera.MoveBackward(VelocityDirect);
	}
	if (IsKeyDown('D'))
	{
		FPSCamera.MoveRight(VelocityFlank);
	}
	if (IsKeyDown(static_cast<unsigned char>(GLFW_KEY_SPACE)))
	{
		FPSCamera.MoveUp(VelocityVertical);
	}
	if (IsKeyDown('C'))
	{
		FPSCamera.MoveDown(VelocityVertical);
	}
}

void FPSApplication::MouseMove(int x, int y)
{
	float deltaX = static_cast<float>(isXAxisReversed ? GetWindowWidth() / 2 - x : x - GetWindowWidth() / 2);
	float deltaY = static_cast<float>(isYAxisReversed ? y - GetWindowHeight() / 2 : GetWindowHeight() / 2 - y);

	FPSCamera.Yaw(deltaX*MouseSensitivity);
	FPSCamera.Pitch(deltaY*MouseSensitivity);

	glfwSetCursorPos(this->fWindow, GetWindowWidth() / 2, GetWindowHeight() / 2);
}

void FPSApplication::MouseScroll(double xoffset, double yoffset)
{
	yoffset > 0.0 ? FPSCamera.ZoomIn(static_cast<float>(yoffset)*0.1f) 
		: FPSCamera.ZoomOut(static_cast<float>(-yoffset)*0.1f);
}