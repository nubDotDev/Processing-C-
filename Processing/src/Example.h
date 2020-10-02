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

	/* Here are the input methods I have implemented:
	virtual void onMouseClicked() {}
	virtual void onMouseClicked(MouseEvent event) {}
	virtual void onMouseDragged() {}
	virtual void onMouseDragged(MouseEvent event) {}
	virtual void onMouseMoved() {}
	virtual void onMouseMoved(MouseEvent event) {}
	virtual void onMousePressed() {}
	virtual void onMousePressed(MouseEvent event) {}
	virtual void onMouseReleased() {}
	virtual void onMouseReleased(MouseEvent event) {}
	virtual void onMouseWheel() {}
	virtual void onMouseWheel(MouseEvent event) {}

	virtual void onKeyPressed() {}
	virtual void onKeyPressed(KeyEvent event) {}
	virtual void onKeyReleased() {}
	virtual void onKeyReleased(KeyEvent event) {}
	virtual void onKeyTyped() {}
	virtual void onKeyTyped(KeyEvent event) {}
	*/
};