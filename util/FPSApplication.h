//
//  FPSApplication.h
//  ModelView
//
//  Created by Bowen Yang on Aug 24, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# ifndef __ModelView__FPSApplication__
# define __ModelView__FPSApplication__

# include <AllinGL.h>
# include <GLApplication.h>
# include <CameraView.h>

/**
@brief Variant of GLApplication with a FPS camera implemented in advance.
*/
class FPSApplication : public GLApplication
{
public:
	CameraView FPSCamera;

	void HandleController() override;

	void MouseMove(int x, int y) override;

	void MouseScroll(double xoffset, double yoffset) override;
};

# endif