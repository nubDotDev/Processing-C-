#pragma once

#include <algorithm>
#include <iostream>

#include "GLFW/glfw3.h"
#include <glm/vec2.hpp>

#include "events/WindowEvent.h"
#include "events/InputEvent.h"

// Event flavors
#define KEY 1
#define MOUSE 2

// Event modifiers
#define SHIFT 1
#define CTRL 2
#define META 4
#define ALT 8

// MouseEvent actions
#define PRESS 1
#define RELEASE 2
#define CLICK  3
#define DRAG 4
#define MOVE 5
#define ENTER 6
#define EXIT 7
#define WHEEL 8

// Mouse buttons
#define LEFT GLFW_MOUSE_BUTTON_LEFT
#define CENTER GLFW_MOUSE_BUTTON_MIDDLE
#define RIGHT GLFW_MOUSE_BUTTON_RIGHT

// KeyEvent actions
#define PRESS GLFW_PRESS;
#define RELEASE GLFW_RELEASE;
#define TYPE 2;

// Math constants
#define HALF_PI 1.5707964
#define PI 3.1415927
#define QUARTER_PI 0.7853982
#define TAU 6.2831855
#define TWO_PI 6.2831855

class Event
{
public:
	Event(int action, int modifiers) :
		action(action), modifiers(modifiers)
	{}

	int getAction() { return action; }
	virtual int getFlavor() = 0;
	int getModifiers() { return modifiers; }
	bool iAltDown() { return modifiers | ALT; }
	bool isControlDown() { return modifiers | CTRL; }
	bool isMetaDown() { return modifiers | META; }
	bool isShiftDown() { return modifiers | SHIFT; }
protected:
	int action, modifiers;
};

class KeyEvent : public Event
{
public:
	KeyEvent(int action, int modifiers, char key, int keyCode, bool autoRepeat = false) :
		Event(action, modifiers), key(key), keyCode(keyCode), autoRepeat(autoRepeat)
	{}

	int getFlavor() override { return KEY; }
	char getKey() { return key; }
	int getKeyCode() { return keyCode; }
	bool isAutoRepeat() { return autoRepeat; }
private:
	char key;
	int keyCode;
	bool autoRepeat;
};

class MouseEvent : public Event
{
public:
	MouseEvent(int action, int modifiers, int x, int y, int button, int count) :
		Event(action, modifiers), x(x), y(y), button(button), count(count)
	{}

	int getFlavor() override { return MOUSE; }
	int getButton() { return button; }
	int getCount() { return count; }
	int getX() { return x; }
	int getY() { return y; }
private:
	int button, count, x, y;
};

class ProcessingApp
{
public:
	ProcessingApp();

	void run();
protected:
	virtual void setup() {}
	virtual void draw() {}

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

	const void size(int width, int height);
	const void background(float v1, float v2, float v3, float alpha = 1);

	template<typename T>
	const void print(T what)
	{
		std::cout << what;
	}

	int width = 500, height = 500;

	int mouseButton = -1;
	double mouseX = 0, mouseY = 0, pmouseX = 0, pmouseY = 0;
	bool mousePressed = false;

	// TODO map characters
	char key = ' ';
	int keyCode = -1;
	bool keyPressed = false;
private:
	int modifiers();

	void windowCloseListener(GlWindowCloseEvent* e);
	void keyPressListener(GlKeyPressEvent* e);
	void keyReleaseListener(GlKeyReleaseEvent* e);
	void keyTypeListener(GlKeyTypeEvent* e);
	void mouseMoveListener(GlMouseMoveEvent* e);
	void mouseScrollListener(GlMouseScrollEvent* e);
	void mouseButtonPressListener(GlMouseButtonPressEvent* e);
	void mouseButtonReleaseListener(GlMouseButtonReleaseEvent* e);

	bool m_click[GLFW_MOUSE_BUTTON_LAST + 1] = {};

	bool m_running = true;

	GLFWwindow* m_window;
};

// TODO Maybe TouchEvent?