#pragma once

#include "json.hpp"
#include <list>
#include <fstream>
#include "Rectangle.h"

using json = nlohmann::json;

using namespace std;

class NitroExercise
{
private:
	bool DetermineIfAlreadyProcessed(std::string rect2, std::string thisname);
protected:
	bool ReadFile(std::string filename, json& jsonfile);
	void ProcessJson(json& jsonfile, std::list<Rectangle>& rectlist);
	void FindIntersections(std::list<Rectangle>& originalRectangleDefinition, std::list<Rectangle> generatedRectangleDefinition, int counter = 1);
public:

	bool PerformExercise(const std::string& filename);
};