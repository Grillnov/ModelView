//
//  CameraView.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <CameraView.h>

CameraView::CameraView() : FOV(45.0f)
{
	Location = glm::vec3(0.0f, 0.0f, 1.0f);
	UpOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
	LookAtOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
}

glm::vec3 CameraView::getOrientation()
{
	return glm::normalize(this->LookAtOrientation);
}

glm::vec3 CameraView::getHorizontalOrientation()
{
	return glm::normalize(glm::vec3(LookAtOrientation[0], 0.0f, LookAtOrientation[2]));
}

glm::vec3 CameraView::getVerticalOrientation()
{
	return glm::normalize(this->UpOrientation);
}

glm::vec3 CameraView::getLeftOrientation()
{
	return glm::normalize(glm::cross(getVerticalOrientation(), getOrientation()));
}

glm::vec3 CameraView::getHorizontalLeftOrientation()
{
	return glm::normalize(glm::cross(glm::vec3(0.0f, 1.0f, 0.0f), getHorizontalOrientation()));
}

void CameraView::Move(glm::vec3 offset)
{
	this->Location += offset;
}

void CameraView::MoveForward(float distance)
{
	Move(distance*getOrientation());
}

void CameraView::MoveBackward(float distance)
{
	Move(-distance*getOrientation());
}

void CameraView::MoveHorizontalForward(float distance)
{
	Move(distance*getHorizontalOrientation());
}

void CameraView::MoveHorizontalBackward(float distance)
{
	Move(-distance*getHorizontalOrientation());
}

void CameraView::MoveHorizontalLeft(float distance)
{
	Move(distance*getHorizontalLeftOrientation());
}

void CameraView::MoveHorizontalRight(float distance)
{
	Move(-distance*getHorizontalLeftOrientation());
}

void CameraView::MoveLeft(float distance)
{
	Move(distance*getLeftOrientation());
}

void CameraView::MoveRight(float distance)
{
	Move(-distance*getLeftOrientation());
}

void CameraView::MoveUp(float distance)
{
	Move(distance*getVerticalOrientation());
}

void CameraView::MoveDown(float distance)
{
	Move(-distance*getVerticalOrientation());
}

void CameraView::Up(glm::vec3 up)
{
	this->UpOrientation = up;
}

void CameraView::Look(glm::vec3 lookat)
{
	this->LookAtOrientation = lookat;
}

void CameraView::Swivel(glm::vec3 rotation)
{
	this->LookAtOrientation += rotation;
}

void CameraView::SetFOV(float FOV)
{
	this->FOV = FOV;
}

void CameraView::Zoom(float scale)
{
	this->FOV *= scale;
}

void CameraView::ZoomIn(float scale)
{
	this->FOV *= 1.0f - scale;
}

void CameraView::ZoomOut(float scale)
{
	this->FOV *= 1.0f + scale;
}

glm::mat4 CameraView::GetModelView(glm::mat4 Model)
{
	glm::mat4 View = glm::lookAt(Location, getOrientation(), getVerticalOrientation()) * Model;
	return View;
}

glm::mat4 CameraView::GetModelViewProjection(float AspectRatio, glm::mat4 Model, float nearP, float farP)
{
	glm::mat4 Projection = glm::perspective(glm::radians(this->FOV), AspectRatio, nearP, farP);
	glm::mat4 View = glm::lookAt(this->Location, getOrientation(), getVerticalOrientation()) * Model;
	return Projection * View * Model;
}