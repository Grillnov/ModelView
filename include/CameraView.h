//
//  CameraView.hpp
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>

# ifndef CAMERAVIEW
# define CAMERAVIEW

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

		void Up(glm::vec3 Up);

		void Look(glm::vec3 lookat);

		void SetFOV(float FOVinDegrees);

		glm::mat4 GetModelView(glm::mat4 Model = glm::mat4(1.0f));

		glm::mat4 GetModelViewProjection(float AspectRatio = 16.0f / 9.0f, glm::mat4 Model = glm::mat4(1.0f), 
			float nearP = 0.1f, float farP = 100.0f);
	};
}

# endif