//
//  CameraView.cpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Options.h>
# include <CameraView.h>

CameraView::CameraView() : FOV(45.0f), yaw(-90.0f), pitch(0.0f)
{
	Location = glm::vec3(0.0f, 0.0f, 1.0f);
	UpOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
}

glm::vec3 CameraView::getOrientation()
{
	glm::vec3 front;
	front.x = glm::cos(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	front.y = glm::sin(glm::radians(pitch));
	front.z = glm::sin(glm::radians(yaw)) * glm::cos(glm::radians(pitch));
	return glm::normalize(front);
}

glm::vec3 CameraView::getHorizontalOrientation()
{
	return glm::normalize(glm::vec3(getOrientation()[0], 0.0f, getOrientation()[2]));
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
	if (this->FOV > 180.0)
		this->FOV = 179.9;
}

glm::mat4 CameraView::GetModelView(glm::mat4 Model)
{
	glm::mat4 View = glm::lookAt(Location, getOrientation() + this->Location, getVerticalOrientation()) * Model;
	return View;
}

glm::mat4 CameraView::GetModelViewProjection(float AspectRatio, glm::mat4 Model, float nearP, float farP)
{
	glm::mat4 Projection = glm::perspective(glm::radians(this->FOV), AspectRatio, nearP, farP);
	glm::mat4 View = glm::lookAt(this->Location, getOrientation(), getVerticalOrientation()) * Model;
	return Projection * View * Model;
}

glm::vec3 CameraView::GetCameraOrientation()
{
	return this->getOrientation();
}

glm::vec3 CameraView::GetCameraLocation()
{
	return this->Location;
}

void CameraView::Yaw(GLfloat offset)
{
	yaw += offset;
}

void CameraView::Pitch(GLfloat offset)
{
	pitch += offset;

	// Make sure that when pitch is out of bounds, screen doesn't get flipped
	if (pitch > 89.9f)
		pitch = 89.9f;
	if (pitch < -89.9f)
		pitch = -89.9f;
}