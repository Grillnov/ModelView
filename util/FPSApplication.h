//
//  VertexArrayPack.h
//  ModelView
//
//  Created by Bowen Yang on Aug 24, 2016.
//  Copyright (c) 2016 Bowen Yang. All rights reserved.
//

# include <AllinGL.h>
# include <GLApplication.h>
# include <CameraView.h>

class FPSApplication : public GLApplication
{
public:
	ModelView::Cam FPSCamera;

	void HandleController() override;

	void MouseMove(int x, int y) override;

	void MouseScroll(double xoffset, double yoffset) override;
};