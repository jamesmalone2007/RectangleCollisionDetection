#pragma once

#include "stdafx.h"
#include <iostream>
#include <string>
#include <list>

class Rectangle {
private:
	int start_x = 0;
	int start_y = 0;

	int width = 0;
	int height = 0;

	int lowerY = 0;
	int rightX = 0;
	std::string name;

public:
	Rectangle(int startx, int starty, int height, int width, std::string name);
	int GetStartX() { return start_x; }
	int GetStartY() { return start_y; }

	int GetHeight() { return height; }
	int GetWidth() { return width; }

	int GetLowerY() { return lowerY; }
	int GetRightX() { return rightX; }
	std::string GetName() { return name; }

	bool CheckForIntersect(Rectangle& r2);
	
	std::string ToString();

	bool CheckForIntersectTopLine(Rectangle& r2);
	bool CheckForIntersectBottomLine(Rectangle& r2);
	bool CheckForIntersectRightLine(Rectangle& r2);
	bool CheckForIntersectLeftLine(Rectangle& r2);

	bool ShouldBeCompared(Rectangle& r2);
	Rectangle FindIntersectionRectangle(Rectangle& rect2);

};