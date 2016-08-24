//
//  CamPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 23, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include "AllinGL.h"


class CamPack
{
private:
public:
	glm::mat4 getMVP(float AspectRatio, float Translate, glm::vec2 const & Rotate)
	{
		glm::mat4 Projection = glm::perspective(glm::radians(75.0f), AspectRatio, 0.1f, 100.f);
		glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
		View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
		View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		return Projection * View * Model;
	}
	glm::mat4 getMV(float AspectRatio, float Translate, glm::vec2 const & Rotate)
	{
		glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
		View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
		View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
		glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(1.0f));
		return View * Model;
	}
};