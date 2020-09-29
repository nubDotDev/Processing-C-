#pragma once

#include "Event.h"

// Key events

class GlKeyEvent : public GlEvent
{
public:
	int getKey() const { return m_key; }
protected:
	GlKeyEvent(int key) : m_key(key) {}

	int m_key;
};

class GlKeyPressEvent : public GlKeyEvent
{
public:
	GlKeyPressEvent(int key) : GlKeyEvent(key) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyPressEvent: " << m_key;
		return ss.str();
	}
};

class GlKeyReleaseEvent : public GlKeyEvent
{
public:
	GlKeyReleaseEvent(int key) : GlKeyEvent(key) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyReleaseEvent: " << m_key;
		return ss.str();
	}
};

class GlKeyRepeatEvent : public GlKeyEvent
{
public:
	GlKeyRepeatEvent(int key) : GlKeyEvent(key) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyRepeatEvent: " << m_key;
		return ss.str();
	}
};

// TODO Make this not a keyevent because the key code is different
class GlKeyTypeEvent : public GlKeyEvent
{
public:
	GlKeyTypeEvent(int key) : GlKeyEvent(key) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "KeyTypeEvent: " << m_key;
		return ss.str();
	}
};

// Mouse events

class GlMouseMoveEvent : public GlEvent
{
public:
	GlMouseMoveEvent(double xPos, double yPos) : m_xPos(xPos), m_yPos(yPos) {}

	double getXPos() const { return m_xPos; }
	double getYPos() const { return m_yPos; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseMoveEvent: " << m_xPos << ", " << m_yPos;
		return ss.str();
	}
private:
	double m_xPos, m_yPos;
};

class GlMouseScrollEvent : public GlEvent
{
public:
	GlMouseScrollEvent(double xOffset, double yOffset) : m_xOffset(xOffset), m_yOffset(yOffset) {}

	double getXOffset() const { return m_xOffset; }
	double getYOffset() const { return m_yOffset; }

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseScrollEvent: " << m_xOffset << ", " << m_yOffset;
		return ss.str();
	}
private:
	double m_xOffset, m_yOffset;
};

class GlMouseButtonEvent : public GlEvent
{
public:
	int getButton() { return m_button; }
protected:
	GlMouseButtonEvent(int button) : m_button(button) {}

	int m_button;
};

class GlMouseButtonPressEvent : public GlMouseButtonEvent
{
public:
	GlMouseButtonPressEvent(int button) : GlMouseButtonEvent(button) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonPressEvent: " << m_button;
		return ss.str();
	}
};

class GlMouseButtonReleaseEvent : public GlMouseButtonEvent
{
public:
	GlMouseButtonReleaseEvent(int button) : GlMouseButtonEvent(button) {}

	std::string toString() const override
	{
		std::stringstream ss;
		ss << "MouseButtonReleaseEvent: " << m_button;
		return ss.str();
	}
};