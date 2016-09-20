//
//  CameraView.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>

# ifndef __ModelView__Cam__
# define __ModelView__Cam__

/**
@brief An utility camera.
To prevent identifier collision it's encapsuled inside namespace ModelView.
*/
namespace ModelView
{
	class Cam
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
		@brief
		The default constructor.
		*/
		Cam();

		/**
		@brief
		Move the camera location around.
		*/
		void Move(glm::vec3 offset);

		/**
		@brief
		Move the camera forward, heading the position the cam's looking at.
		*/
		void MoveForward(float distance);

		/**
		@brief
		Move backward.
		*/
		void MoveBackward(float distance);

		/**
		@brief
		Move horizontally forward, on the plane parallel to plane xOz.
		*/
		void MoveHorizontalForward(float distance);

		/**
		@brief
		Move horizontally backward.
		*/
		void MoveHorizontalBackward(float distance);

		/**
		@brief
		Move left. Left means the cross product direction of direction Up and direction LookAt.
		*/
		void MoveLeft(float distance);

		/**
		@brief
		Move right.
		*/
		void MoveRight(float distance);

		/**
		@brief
		Move horizontally left.
		*/
		void MoveHorizontalLeft(float distance);

		/**
		@brief
		Move horizontally right.
		*/
		void MoveHorizontalRight(float distance);

		/**
		@brief
		Move up.
		*/
		void MoveUp(float distance);

		/**
		@brief
		Move down.
		*/
		void MoveDown(float distance);

		/**
		@brief
		Set the 'up' direction of the camera.
		@params
		Up: the 3 dimensional vector that tells the camera how to stand.
		*/
		void Up(glm::vec3 Up);

		/**
		@brief
		Set the orientation the camera's looking at.
		@params
		lookat: The direction it's looking at.
		*/
		void Look(glm::vec3 Lookat);

		/**
		@brief
		Rotate the camera so that it's looking at a new direction.
		@params
		Swivel: The delta value of orientation change you expect.
		*/
		void Swivel(glm::vec3 Swivel);

		/**
		@brief
		Zoom by setting FOV.
		@params:
		scale: The new FOV value will be the factor scale multiplied with current FOV.
		*/
		void Zoom(float scale);

		/**
		@brief
		Zoom in by decreasing FOV.
		@params:
		scale: The scale you want to decrease from current FOV.
		*/
		void ZoomIn(float scale);

		/**
		@brief
		Zoom out by increasing FOV.
		@params:
		scale: The scale you want to increase from current FOV.
		*/
		void ZoomOut(float scale);

		/**
		@brief
		Set the FOV value.
		@params:
		FOVinDegrees: New FOV value, in degrees.
		*/
		void SetFOV(float FOVinDegrees);

		/**
		@brief
		Get the View matrix.
		*/
		glm::mat4 GetViewMatrix();

		/**
		@brief
		Get the Model * View matrix.
		@params
		Model: The model matrix provided. Set as identical by default.
		*/
		glm::mat4 GetModelView(glm::mat4 Model = glm::mat4(1.0f));

		/**
		@brief
		Get the Model * View * Projection matrix.
		@params
		AspectRatio: The screen aspect ratio. You can get this by invoking GetAspectRatio() from GLApplication.
		@see GetAspectRatio()
		Model: The model matrix provided. Set as identical by default.
		nearP: The near plane of the field of view.
		farP: The far plane of the field of view.
		*/
		glm::mat4 GetModelViewProjection(float AspectRatio = 16.0f / 9.0f, glm::mat4 Model = glm::mat4(1.0f), 
			float nearP = 0.1f, float farP = 100.0f);
	};
}

# endif