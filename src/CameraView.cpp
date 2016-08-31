//
//  CameraView.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <CameraView.h>

ModelView::Cam::Cam() : FOV(65.0f)
{
	Location = glm::vec3(0.0f, 0.0f, 1.0f);
	UpOrientation = glm::vec3(0.0f, 1.0f, 0.0f);
	LookAtOrientation = glm::vec3(0.0f, 0.0f, -1.0f);
}

void Move(glm::vec3 offset);

void Up(glm::vec3 Up);

void Look(glm::vec3 lookat);

void SetFOV(float FOVinDegrees);

glm::mat4 GetModelView(glm::mat4 Model = glm::mat4(1.0f));

glm::mat4 GetModelViewProjection(float AspectRatio = 16.0f / 9.0f, glm::mat4 Model = glm::mat4(1.0f),
	float nearP = 0.1f, float farP = 100.0f);

void ModelView::Cam::Move(glm::vec3 offset)
{
	this->Location += offset;
}

void ModelView::Cam::Up(glm::vec3 up)
{
	this->UpOrientation = up;
}

void ModelView::Cam::Look(glm::vec3 lookat)
{
	this->LookAtOrientation = lookat;
}

void ModelView::Cam::SetFOV(float FOV)
{
	this->FOV = FOV;
}

glm::mat4 ModelView::Cam::GetModelView(glm::mat4 Model)
{
	glm::mat4 View = glm::lookAt(this->Location, this->LookAtOrientation, this->UpOrientation) * Model;
	return View;
}

glm::mat4 ModelView::Cam::GetModelViewProjection(float AspectRatio, glm::mat4 Model, float nearP, float farP)
{
	glm::mat4 Projection = glm::perspective(glm::radians(this->FOV), AspectRatio, nearP, farP);
	glm::mat4 View = glm::lookAt(this->Location, this->LookAtOrientation, this->UpOrientation) * Model;
	return Projection * View * Model;
}