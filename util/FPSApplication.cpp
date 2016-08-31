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

const static float VelocityX = 0.01f;//x axis
const static float VelocityY = 0.01f;//y axis
const static float VelocityZ = 0.01f;//z axis

void FPSApplication::UpdateFromController()
{
	if (IsKeyDown('W'))
	{
		FPSCamera.Move(glm::vec3(0, 0, -VelocityZ));
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