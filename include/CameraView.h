//
//  CameraView.h
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <Options.h>

# ifndef __ModelView__CameraView__
# define __ModelView__CameraView__

/**
@brief Camera object serving as an utility camera.
*/
class CameraView
{
private:
	glm::vec3 Location;
	glm::vec3 UpOrientation;
	glm::vec3 LookAtOrientation;

	float FOV;

	glm::vec3 getOrientation();

	glm::vec3 getVerticalOrientation();

	glm::vec3 getLeftOrientation();

	glm::vec3 getHorizontalLeftOrientation();

	glm::vec3 getHorizontalOrientation();
public:
	/**
	@brief The default constructor.
	*/
	CameraView();

	/**
	@brief Move the camera location around.

	@param offset The delta of location.
	*/
	void Move(glm::vec3 offset);

	/**
	@brief Move the camera forward, heading the position the cam's looking at.

	@param distance The distance it travelled.
	*/
	void MoveForward(float distance);

	/**
	@brief Move backward.

	@param distance The distance it travelled.
	*/
	void MoveBackward(float distance);

	/**
	@brief Move horizontally forward, on the plane parallel to plane xOz.

	@param distance The distance it travelled.
	*/
	void MoveHorizontalForward(float distance);

	/**
	@brief Move horizontally backward.

	@param distance The distance it travelled.
	*/
	void MoveHorizontalBackward(float distance);

	/**
	@brief Move left. Left means the cross product direction of direction Up and direction LookAt.

	@param distance The distance it travelled.
	*/
	void MoveLeft(float distance);

	/**
	@brief Move right.

	@param distance The distance it travelled.
	*/
	void MoveRight(float distance);

	/**
	@brief Move horizontally left.

	@param distance The distance it travelled.
	*/
	void MoveHorizontalLeft(float distance);

	/**
	@brief Move horizontally right.

	@param distance The distance it travelled.
	*/
	void MoveHorizontalRight(float distance);

	/**
	@brief Move up.

	@param distance The distance it travelled.
	*/
	void MoveUp(float distance);

	/**
	@brief Move down.

	@param distance The distance it travelled.
	*/
	void MoveDown(float distance);

	/**
	@brief Set the 'up' direction of the camera.

	@param Up The 3 dimensional vector that tells the camera how to stand.
	*/
	void Up(glm::vec3 Up);

	/**
	@brief Set the orientation the camera's looking at.

	@param Lookat The direction it's looking at.
	*/
	void Look(glm::vec3 Lookat);

	/**
	@brief Rotate the camera so that it's looking at a new direction.

	@param Swivel: The delta value of orientation change you expect.
	*/
	void Swivel(glm::vec3 Swivel);

	/**
	@brief Zoom by setting FOV.

	@param scale The new FOV value will be the factor scale multiplied with current FOV.
	*/
	void Zoom(float scale);

	/**
	@brief Zoom in by decreasing FOV.

	@param scale The scale you want to decrease from current FOV.
	*/
	void ZoomIn(float scale);

	/**
	@brief Zoom out by increasing FOV.

	@param scale The scale you want to increase from current FOV.
	*/
	void ZoomOut(float scale);

	/**
	@brief Set the FOV value.

	@param FOVinDegrees New FOV value, measured in degrees.
	*/
	void SetFOV(float FOVinDegrees);

	/**
	@brief Get the View matrix.
	*/
	glm::mat4 GetViewMatrix();

	/**
	@brief Get the View * Model matrix.

	@param Model The model matrix provided. Set as identical by default.
	*/
	glm::mat4 GetModelView(glm::mat4 Model = glm::mat4(1.0f));

	/**
	@brief Get the Projection * View * Model matrix.

	@param AspectRatio The screen aspect ratio. You can get this by invoking GetAspectRatio() from GLApplication.
	@see GetAspectRatio()

	@param Model The model matrix provided. Set as identical by default.

	@param nearP The near plane of the field of view.

	@param farP The far plane of the field of view.
	*/
	glm::mat4 GetModelViewProjection(float AspectRatio = xWindowWidth / yWindowHeight, glm::mat4 Model = glm::mat4(1.0f),
		float nearP = 0.1f, float farP = 100.0f);
};

# endif