#include "stdafx.h"

#include "NitroExercise.h"


#pragma once

bool NitroExercise::ReadFile(std::string filename, json& jsonfile)
{
	//Read the contents of the file and return json object.
	ifstream myfile(filename);
	std::string filecontents = "";

	if (!myfile.is_open())
	{
		//File could not be found.
		return false;
	}

	//try {
	try
	{
		myfile >> jsonfile;
		myfile.close();
	}
	catch (const exception&)
	{
		return false;
	}
	

	return true;
}

void NitroExercise::ProcessJson(json& jsonfile, std::list<Rectangle>& rectlist)
{
	//Select element "rects"
	auto defrects = jsonfile.find("rects");

	if (defrects != jsonfile.end())
	{
		auto element = defrects.value();

		//We need to name each rectangle to track them.
		int name = 1;
		for (auto& subelement : element)
		{
			/*
			JSON library was unsuitable for converting integer json to integer data types.
			Data types of type 'int' were parsed in as "unsigned", and there was no json-develop -> unsigned int conversion available.
			Instead, I wrote a llambda function to isolate desired value, "dump" it (convert to string), and parse the integer out.
			Since all values dealt with should be positive (rectangles should not have negative length or width, invalid numbers return "-1"
			*/
			auto SelectRectValue = [](json element, std::string term, bool forcepos, int& to_ret)
			{
				auto checkH = element.find(term);

				if (checkH != element.end())
				{
					auto foundval = checkH.value();
					auto val = foundval.dump();

					istringstream(val) >> to_ret;

					if (forcepos && to_ret < 0)
						to_ret = INT_MAX;

				}
				else
					to_ret = INT_MAX; // Not found, return false val.
				

			};

			//Gather the values of each rectangle from the JSON
			int height, width, x, y = 0;
			SelectRectValue(subelement, "h", true, height);
			SelectRectValue(subelement, "w", true, width);
			SelectRectValue(subelement, "x", false, x);
			SelectRectValue(subelement, "y", false, y);

			auto invalidnum = INT_MAX;

			if(height != invalidnum && width != invalidnum && x != invalidnum && y != invalidnum) // If any values are not valid, don't add it.
			{
				//Store in a list.
				rectlist.push_back(Rectangle(x, y, height, width, std::to_string(name)));
			}

			//Increment so that the next rectangle is identifiable.
			name++;
		}

	}
}

bool NitroExercise::DetermineIfAlreadyProcessed(std::string rect2, std::string thisname)
{
	/*
		FOR THIS EXERCISE, WE NEED TO REMOVE DUPLICATION.
		Given: Rectangles A,B and C which intersect.

		A^C and B^C.
		We need to ensure that we don't get A^B^C and B^A^C as different rectangles. 
	*/

	//Naming conventions of this assignment. All rectangles added from NitroExercise are done so by number. Parse out the number of the current rectangle.
	auto thisrectname = std::stoi(thisname);
	
	/*
		rect2 is a set of names, load them in as a stringstream, parse them out one by one. Since we are going in order 1..2..3... if we find that we have a lower number, we know it is already processed 
		(if we are considering comparing rectangle B with rectangle AC, it shouldn't, as the computation for this was done while we were considering BC with A. 
	*/
	std::stringstream stream(rect2);
	while (true)
	{
		int n;
		stream >> n;
		if (!stream)
			break;

		if (n <= thisrectname)
			return false;
	}

	return true;

}

void NitroExercise::FindIntersections(std::list<Rectangle>& originalRectangleDefinition, std::list<Rectangle> generatedRectangleDefinition, int counter)
{
	//We have searched through all possible contributors.
	if (counter == originalRectangleDefinition.size())
		return;

	std::list<Rectangle> temp_generated_list;
	temp_generated_list.clear();

	//Iterate through all input rectangles.
	for (auto& rect : originalRectangleDefinition)
	{
		/*
			Input through all comparator rectangles. 
			1st pass: original input rectangles.
			2nd pass: all A ^ B rectangles
			3rd pass: all A ^  B ^ C rectangles...
		*/
		for (auto& rect2 : generatedRectangleDefinition)
		{
			/*
			checkOnRight:			Ensures no duplication. Only reports on rectangle if rectangle2 is to the right.
			checkForIntersection:	Checks if rect2 crosses any of rect1's lines.
			searchname:				Ensures A doesn't match against a A^B rectangle
			*/
			if ((rect.ShouldBeCompared(rect2)) && 
				(rect.CheckForIntersect(rect2)) && 
				(DetermineIfAlreadyProcessed(rect2.GetName(), rect.GetName())))
			{
				//Get the rectangle contained.
				Rectangle boundat = rect.FindIntersectionRectangle(rect2);
				cout << "\t" << "Between rectangle " << rect.GetName() << " and " << rect2.GetName()
					<< " at (" << boundat.GetStartX() << "," << boundat.GetStartY() << "), w=" << boundat.GetWidth() << ", h=" << boundat.GetHeight() << "\n";

				temp_generated_list.push_back(boundat);
			}

		}
	}

	//Search through the generated list.
	FindIntersections(originalRectangleDefinition, temp_generated_list, ++counter );
}

/*
	Function is to act as runner. Contains the main flow of logic for the program.
*/
bool NitroExercise::PerformExercise(const std::string& filename)
{
	json jsonfile;

	//Attempt to read file and create valid JSON.
	if (!ReadFile(filename, jsonfile))
		return false;

	std::list<Rectangle> rectlist;
	rectlist.clear();

	std::cout << "Input:\n";

	//Process the json-develop file, generate a list object of type<Rectangle>
	ProcessJson(jsonfile, rectlist);

	//Print rectangle definitions.
	for (auto& rect : rectlist)
		cout << "\t" << rect.ToString() << "\n";

	cout << "\n" << "Intersections: " << "\n";

	//Find and print all sub rectangles contained.
	FindIntersections(rectlist, rectlist);
	
	return true;
}