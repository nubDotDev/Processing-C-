#include "ProcessingApp.h"

#include <iostream>

#include "glad/glad.h"

ProcessingApp::ProcessingApp()
{
	if (!glfwInit())
	{
		std::cout << "Failed to initialize GLFW" << std::endl;
	}
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	m_window = glfwCreateWindow(width, height, "Processing", NULL, NULL);
	glfwMakeContextCurrent(m_window);
	if (!m_window)
	{
		std::cout << "Failed to create window" << std::endl;
	}
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}

	glfwSetErrorCallback([](int error, const char* description)
		{
			std::fprintf(stderr, "Error: %s\n", description);
		});

	glfwSetWindowCloseCallback(m_window, [](GLFWwindow* window)
		{
			GlWindowCloseEvent event = GlWindowCloseEvent();
			EventBus::send(&event);
		});

	glfwSetWindowSizeCallback(m_window, [](GLFWwindow* window, int width, int height)
		{
			GlWindowResizeEvent event = GlWindowResizeEvent(width, height);
			EventBus::send(&event);
		});

	glfwSetWindowPosCallback(m_window, [](GLFWwindow* window, int xPos, int yPos)
		{
			GlWindowMoveEvent event = GlWindowMoveEvent(xPos, yPos);
			EventBus::send(&event);
		});

	glfwSetKeyCallback(m_window, [](GLFWwindow* window, int key, int scancode, int action, int mods)
		{
			switch (action)
			{
			case GLFW_RELEASE:
			{
				GlKeyReleaseEvent event = GlKeyReleaseEvent(key);
				EventBus::send(&event);
				break;
			}
			case GLFW_PRESS:
			{
				GlKeyPressEvent event = GlKeyPressEvent(key);
				EventBus::send(&event);
				break;
			}
			case GLFW_REPEAT:
			{
				GlKeyRepeatEvent event = GlKeyRepeatEvent(key);
				EventBus::send(&event);
				break;
			}
			}
		});

	glfwSetCharCallback(m_window, [](GLFWwindow* window, unsigned int codepoint)
		{
			GlKeyTypeEvent event = GlKeyTypeEvent(codepoint);
			EventBus::send(&event);
		});

	glfwSetCursorPosCallback(m_window, [](GLFWwindow* window, double xPos, double yPos)
		{
			GlMouseMoveEvent event = GlMouseMoveEvent(xPos, yPos);
			EventBus::send(&event);
		});

	glfwSetMouseButtonCallback(m_window, [](GLFWwindow* window, int button, int action, int mods)
		{
			switch (action)
			{
			case GLFW_PRESS:
			{
				GlMouseButtonPressEvent event = GlMouseButtonPressEvent(button);
				EventBus::send(&event);
				break;
			}
			case GLFW_RELEASE:
			{
				GlMouseButtonReleaseEvent event = GlMouseButtonReleaseEvent(button);
				EventBus::send(&event);
				break;
			}
			}
		});

	glfwSetScrollCallback(m_window, [](GLFWwindow* window, double xOffset, double yOffset)
		{
			GlMouseScrollEvent event = GlMouseScrollEvent(xOffset, yOffset);
			EventBus::send(&event);
		});

	EventBus::subscribe(this, &ProcessingApp::windowCloseListener);
	EventBus::subscribe(this, &ProcessingApp::keyPressListener);
	EventBus::subscribe(this, &ProcessingApp::keyReleaseListener);
	EventBus::subscribe(this, &ProcessingApp::keyTypeListener);
	EventBus::subscribe(this, &ProcessingApp::mouseMoveListener);
	EventBus::subscribe(this, &ProcessingApp::mouseScrollListener);
	EventBus::subscribe(this, &ProcessingApp::mouseButtonPressListener);
	EventBus::subscribe(this, &ProcessingApp::mouseButtonReleaseListener);
}

void ProcessingApp::run()
{
	setup();
	while (m_running)
	{
		glClear(GL_COLOR_BUFFER_BIT);
		glfwSwapBuffers(m_window);
		glfwPollEvents();

		pmouseX = mouseX;
		pmouseY = mouseY;
		glfwGetCursorPos(m_window, &mouseX, &mouseY);
		mousePressed = false;
		for (int i = GLFW_MOUSE_BUTTON_1; i < GLFW_MOUSE_BUTTON_LAST + 1; i++)
		{
			if (glfwGetMouseButton(m_window, i))
			{
				mousePressed = true;
				break;
			}
		}

		keyPressed = false;
		for (int i = GLFW_KEY_SPACE; i < GLFW_KEY_LAST + 1; i++)
		{
			if (glfwGetKey(m_window, i))
			{
				keyPressed = true;
				break;
			}
		}

		draw();
	}
	glfwTerminate();
}

const void ProcessingApp::size(int width, int height)
{
	this->width = width;
	this->height = height;
	glfwSetWindowSize(m_window, width, height);
	glViewport(0, 0, width, height);
}

const void ProcessingApp::background(float v1, float v2, float v3, float alpha)
{
	glClearColor(v1, v2, v3, alpha);
	glClear(GL_COLOR_BUFFER_BIT);
}

int ProcessingApp::modifiers()
{
	int modifiers = 0;
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_SHIFT) || glfwGetKey(m_window, GLFW_KEY_RIGHT_SHIFT))
	{
		modifiers |= SHIFT;
	}
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_CONTROL) || glfwGetKey(m_window, GLFW_KEY_RIGHT_CONTROL))
	{
		modifiers |= CTRL;
	}
	// TODO meta support?
	if (glfwGetKey(m_window, GLFW_KEY_LEFT_ALT) || glfwGetKey(m_window, GLFW_KEY_RIGHT_ALT))
	{
		modifiers |= ALT;
	}
	return modifiers;
}

void ProcessingApp::windowCloseListener(GlWindowCloseEvent* e)
{
	m_running = false;
}

void ProcessingApp::keyPressListener(GlKeyPressEvent* e)
{
	keyCode = e->getKey();
	onKeyPressed();
	onKeyPressed(KeyEvent(1, modifiers(), key, keyCode));
}

void ProcessingApp::keyReleaseListener(GlKeyReleaseEvent* e)
{
	keyCode = e->getKey();
	onKeyReleased();
	onKeyReleased(KeyEvent(0, modifiers(), key, keyCode));
}

void ProcessingApp::keyTypeListener(GlKeyTypeEvent* e)
{
	key = e->getKey();
	onKeyTyped();
	onKeyPressed(KeyEvent(2, modifiers(), key, keyCode));
}

void ProcessingApp::mouseMoveListener(GlMouseMoveEvent* e)
{
	if (mousePressed)
	{
		std::fill(m_click, m_click + GLFW_MOUSE_BUTTON_LAST + 1, false);
		onMouseDragged();
		onMouseDragged(MouseEvent(4, modifiers(), e->getXPos(), e->getYPos(), -1, mouseButton));
	}
	else
	{
		onMouseMoved();
		onMouseMoved(MouseEvent(5, modifiers(), e->getXPos(), e->getYPos(), -1, 0));
	}
}

void ProcessingApp::mouseScrollListener(GlMouseScrollEvent* e)
{
	onMouseWheel();
	onMouseWheel(MouseEvent(8, modifiers(), mouseX, mouseY, mouseButton, e->getYOffset()));
}

void ProcessingApp::mouseButtonPressListener(GlMouseButtonPressEvent* e)
{
	mouseButton = e->getButton();
	onMousePressed();
	onMousePressed(MouseEvent(1, modifiers(), mouseX, mouseY, mouseButton, 0));
	m_click[e->getButton()] = true;
}

void ProcessingApp::mouseButtonReleaseListener(GlMouseButtonReleaseEvent* e)
{
	mouseButton = e->getButton();
	onMouseReleased();
	onMouseReleased(MouseEvent(0, modifiers(), mouseX, mouseY, mouseButton, 0));
	if (m_click[e->getButton()])
	{
		onMouseClicked();
		onMouseClicked(MouseEvent(3, modifiers(), mouseX, mouseY, mouseButton, 0));
	}
}
