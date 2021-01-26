#pragma once

#include "Renderable.h"

class GraphicsSystem
{
public:
	static GraphicsSystem& Get()
	{
		static GraphicsSystem instance;
		return instance;
	}

	bool Init();
	void Draw();
	void Close();
private:
};