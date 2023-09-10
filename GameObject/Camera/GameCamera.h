#pragma once

//components
#include "ViewProjection.h"

class GameCamera
{
public:
	GameCamera();
	~GameCamera();

	void Initalize();
	void Update();
	//void Draw();

	ViewProjection* GetViewProjection() { return &viewProjection_; };

private:

	ViewProjection viewProjection_;

};




