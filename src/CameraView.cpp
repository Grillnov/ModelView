//
//  CameraView.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <CameraView.h>

using namespace ModelView;

Cam::Cam() : FOV(45.0f)
{
	Location = glm::vec3(0.0f, 0.0f, 1.0f);
	UpOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
	LookAtOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 Cam::getOrientation()
{
	return glm::normalize(this->LookAtOrientation);
}

glm::vec3 Cam::getHorizontalOrientation()
{
	return glm::normalize(glm::vec3(LookAtOrientation[0], 0.0f, LookAtOrientation[2]));
}

glm::vec3 Cam::getVerticalOrientation()
{
	return glm::normalize(this->UpOrientation);
}

glm::vec3 Cam::getLeftOrientation()
{
	return glm::normalize(glm::cross(getVerticalOrientation(), getOrientation()));
}

glm::vec3 Cam::getHorizontalLeftOrientation()
{
	return glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), getHorizontalOrientation()));
}

void Cam::Move(glm::vec3 offset)
{
	this->Location += offset;
}

void Cam::MoveForward(float distance)
{
	Move(distance*getOrientation());
}

void Cam::MoveBackward(float distance)
{
	Move(-distance*getOrientation());
}

void Cam::MoveHorizontalForward(float distance)
{
	Move(distance*getHorizontalOrientation());
}

void Cam::MoveHorizontalBackward(float distance)
{
	Move(-distance*getHorizontalOrientation());
}

void Cam::MoveHorizontalLeft(float distance)
{
	Move(distance*getHorizontalLeftOrientation());
}

void Cam::MoveHorizontalRight(float distance)
{
	Move(-distance*getHorizontalLeftOrientation());
}

void Cam::MoveLeft(float distance)
{
	Move(distance*getLeftOrientation());
}

void Cam::MoveRight(float distance)
{
	Move(-distance*getLeftOrientation());
}

void Cam::MoveUp(float distance)
{
	Move(distance*getVerticalOrientation());
}

void Cam::MoveDown(float distance)
{
	Move(-distance*getVerticalOrientation());
}

void Cam::Up(glm::vec3 up)
{
	this->UpOrientation = up;
}

void Cam::Look(glm::vec3 lookat)
{
	this->LookAtOrientation = lookat;
}

void Cam::Swivel(glm::vec3 rotation)
{
	this->LookAtOrientation += rotation;
}

void Cam::SetFOV(float FOV)
{
	this->FOV = FOV;
}

void Cam::Zoom(float scale)
{
	this->FOV *= scale;
}

void Cam::ZoomIn(float scale)
{
	this->FOV *= 1.0f - scale;
}

void Cam::ZoomOut(float scale)
{
	this->FOV *= 1.0f + scale;
}

glm::mat4 Cam::GetModelView(glm::mat4 Model)
{
	glm::mat4 View = glm::lookAt(Location, getOrientation(), getVerticalOrientation()) * Model;
	return View;
}

glm::mat4 Cam::GetModelViewProjection(float AspectRatio, glm::mat4 Model, float nearP, float farP)
{
	glm::mat4 Projection = glm::perspective(glm::radians(this->FOV), AspectRatio, nearP, farP);
	glm::mat4 View = glm::lookAt(this->Location, getOrientation(), getVerticalOrientation()) * Model;
	return Projection * View * Model;
}