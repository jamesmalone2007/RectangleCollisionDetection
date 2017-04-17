#pragma once


#include <iostream>
#include <sstream>

#include "stdafx.h"

std::wstring BuildErrorMessage(std::string expected, std::string returned, std::string message = "");
std::wstring BuildErrorMessage(bool expected, bool returned, std::string message = "");
std::wstring BuildErrorMessage(int expected, int returned, std::string message = "");