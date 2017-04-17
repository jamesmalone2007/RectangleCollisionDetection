#include "stdafx.h"
#include "Rectangle.h"

Rectangle::Rectangle(int sx, int sy, int h, int rx, std::string n) : start_x(sx),start_y(sy), height(h), width(rx), name(n)
{

	//Compute information for intersection computation. We want to know the lowermost, and rightmost line. 
	lowerY = start_y + height;
	rightX = start_x + width;

}


bool Rectangle::CheckForIntersect(Rectangle& r2)
{
	//Same object
	if (this == &r2)
		return false;

	//If r2's Y starts below r1's lower bound... or if r2's X starts after r1's right-most point, no collision.
	if ((r2.GetStartY() > GetLowerY()) || (r2.GetStartX() > GetRightX()))
		return false;

	auto ch1 = CheckForIntersectTopLine(r2);
	auto ch2 = CheckForIntersectBottomLine(r2);
	auto ch3 = CheckForIntersectLeftLine(r2);
	auto ch4 = CheckForIntersectRightLine(r2);

	if (ch1 && ch2 && ch3 && ch4)
		return false; //Intersects all lines. Edge case where origin is the same and it extends in all directions.

	return ch1 || ch2 || ch3 || ch4;
}

#pragma region Check Intersections
//COLLIDES WITH TOP. r2's top line starts above r1's and r2's bottom line is below r1's top line. 
bool Rectangle::CheckForIntersectTopLine(Rectangle& r2)
{
	return ((r2.GetStartY() <= GetStartY()) && (r2.GetLowerY() > GetStartY()));
}

//COLLIDES WITH BOTTOM. r2's top line is above r1's bottom line but r2's bottom line is below r1's bottom line.
bool Rectangle::CheckForIntersectBottomLine(Rectangle& r2)
{
	return ((r2.GetStartY() < GetLowerY()) && (r2.GetLowerY() >= GetLowerY()));
}

//COLLIDES WITH RIGHT. r2's starting position lies before r1's rightmost position, but r2's rightmost position is after r1's rightmost point 
bool Rectangle::CheckForIntersectRightLine(Rectangle& r2)
{
	return ((r2.GetStartX() < GetRightX()) && (r2.GetRightX() >= GetRightX()));
}

//COLLIDES WITH LEFT. r2's starting position lies before r1's, but r2's rightmost position is after r1's starting point
bool Rectangle::CheckForIntersectLeftLine(Rectangle& r2)
{
	return ((r2.GetStartX() == GetStartX()) || ((r2.GetStartX() < GetStartX()) && (r2.GetRightX() >= GetStartX())));
}
#pragma endregion

bool Rectangle::ShouldBeCompared(Rectangle& rect2)
{
	//don't compare if rect2 starts to the left of this.
	if (rect2.GetStartX() < GetStartX())
		return false;

	//don't compare if same origin but rect2 has longer width (extends past this)
	if (rect2.GetStartY() == GetStartY() && rect2.GetRightX() == GetStartX() && rect2.GetWidth() > GetWidth())
		return false;

	return true;

}

Rectangle Rectangle::FindIntersectionRectangle(Rectangle& rect2)
{
	Rectangle r(0,0,0,0,"Dummy object"); //Non-intersect or already processed rectangle
	if ((!ShouldBeCompared(rect2) || !CheckForIntersect(rect2)))
		return r;
		
	// r2 is further to the right. Use rect2 as the start point.
	
	auto start_x = (rect2.GetStartY() > GetStartY()) 
		? rect2.GetStartX() 
		: rect2.GetStartX();

	auto start_y = (rect2.GetStartY() > GetStartY()) 
		? rect2.GetStartY() 
		: GetStartY() ;
		
	auto width = ((rect2.GetRightX() > GetRightX()) 
		? GetRightX() : rect2.GetRightX()) - start_x;
		
	//If r2's lower is belowr1 ... then lowerbound is r1's lowerY value. if r2's lower is above r1's.... lowerbound is r2s.
	auto height = ((rect2.GetLowerY() >= GetLowerY()) 
		? GetLowerY() : rect2.GetLowerY()) - start_y;

	return Rectangle(start_x, start_y, height, width, std::string(GetName() + "," + rect2.GetName()));

}

//Returns formatted string representing the Rectangle object.
std::string Rectangle::ToString()
{
	return GetName() + ": Rectangle at (" + std::to_string(GetStartX())+ "," + std::to_string(GetStartY()) + "), w=" + std::to_string( GetWidth()) + ", h=" + std::to_string(GetHeight());
}