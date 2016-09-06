//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 24, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <GLApplication.h>
# include <CameraView.h>
# include <FPSApplication.h>

const static float VelocityX = 0.01f;//x axis moving speed
const static float VelocityY = 0.01f;//y axis moving speed
const static float VelocityZ = 0.01f;//z axis moving speed
const static float VelocitySwivel = 0.0015f;//camera spin speed

const static bool isYAxisReversed = true;
const static bool isXAxisReversed = false;

void FPSApplication::HandleController()
{
	if (IsKeyDown('W'))
	{
		FPSCamera.Move(glm::vec3(0, 0, -VelocityZ));
		//FPSCamera.Move()
	}
	if (IsKeyDown('A'))
	{
		FPSCamera.Move(glm::vec3(-VelocityX, 0, 0));
	}
	if (IsKeyDown('S'))
	{
		FPSCamera.Move(glm::vec3(0, 0, VelocityZ));
	}
	if (IsKeyDown('D'))
	{
		FPSCamera.Move(glm::vec3(VelocityX, 0, 0));
	}
}

void FPSApplication::MouseMove(int x, int y)
{
	float deltaX = static_cast<float>(isXAxisReversed ? GetWindowWidth() / 2 - x : x - GetWindowWidth() / 2);
	float deltaY = static_cast<float>(isYAxisReversed ? y - GetWindowHeight() / 2 : GetWindowHeight() / 2 - y);
	FPSCamera.Swivel(glm::vec3(VelocitySwivel * static_cast<float>(deltaX),
		VelocitySwivel * static_cast<float>(deltaY), 0.0f));
	glfwSetCursorPos(this->fWindow, GetWindowWidth() / 2, GetWindowHeight() / 2);
}

void FPSApplication::MouseScroll(double xoffset, double yoffset)
{
	//Log(debugMsg, "x : %f, y : %f", xoffset, yoffset);
	FPSCamera.ZoomIn(static_cast<float>(yoffset)* 0.1f);
}