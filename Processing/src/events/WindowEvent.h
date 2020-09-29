#pragma once

#include "Event.h"

class GlWindowCloseEvent : public GlEvent
{
public:
	GlWindowCloseEvent() {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowCloseEvent";
		return ss.str();
	}
};

class GlWindowResizeEvent : public GlEvent
{
public:
	GlWindowResizeEvent(unsigned int width, unsigned int height) : m_width(width), m_height(height) {}

	unsigned int getWidth() const { return m_width; }
	unsigned int getHeight() const { return m_height; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowResizeEvent: " << m_width << ", " << m_height;
		return ss.str();
	}
private:
	unsigned int m_width, m_height;
};

class GlWindowMoveEvent : public GlEvent
{
public:
	GlWindowMoveEvent(int xPos, int yPos) : m_xPos(xPos), m_yPos(yPos) {}

	int getXPos() const { return m_xPos; }
	int getYPos() const { return m_yPos; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "WindowMoveEvent: " << m_xPos << ", " << m_yPos;
		return ss.str();
	}
private:
	int m_xPos, m_yPos;
};