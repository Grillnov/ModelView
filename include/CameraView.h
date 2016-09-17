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

namespace ModelView
{
	class Cam
	{
	private:
		glm::vec3 Location;
		glm::vec3 UpOrientation;
		glm::vec3 LookAtOrientation;

		float FOV;

	public:
		Cam();

		void Move(glm::vec3 offset);

		void MoveForward(float distance);

		void MoveBackward(float distance);

		void MoveLeft(float distance);

		void MoveRight(float distance);

		void MoveUp(float distance);

		void MoveDown(float distance);

		void Up(glm::vec3 Up);

		void Look(glm::vec3 lookat);

		void Swivel(glm::vec3 rotation);

		void Zoom(float scale);

		void ZoomIn(float scale);

		void ZoomOut(float scale);

		void SetFOV(float FOVinDegrees);

		glm::mat4 GetModelView(glm::mat4 Model = glm::mat4(1.0f));

		glm::mat4 GetModelViewProjection(float AspectRatio = 16.0f / 9.0f, glm::mat4 Model = glm::mat4(1.0f), 
			float nearP = 0.1f, float farP = 100.0f);
	};
}

# endif