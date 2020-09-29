#pragma once

#include "ProcessingApp.h"

class ExampleApp : public ProcessingApp
{
public:
	void setup() {
		size(800, 200);
		background(0, .8, .7);
	}

	void draw() {
		
	}

	void onMouseDragged()
	{
		//print("drag");
	}

	void onKeyPressed()
	{
		//print("press\n");
	}

	void onKeyTyped()
	{
		print(key + "\n");
	}
};