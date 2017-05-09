#include "stdafx.h"
#include "TestUtility.h"

std::wstring StringToWString(const std::string &s)
{
	std::wstring wsTmp(s.begin(), s.end());

	return wsTmp;
};

std::wstring BuildErrorMessage(std::string expected, std::string returned, std::string message)
{
	if (expected == returned)
		return L"";

	

	auto errormsg = L"Expected: " + StringToWString(expected) + L". Returned: " + StringToWString(returned);

	if (!message.empty())
	{
		errormsg.append(L". Message: " + StringToWString(message));
	}
	return errormsg;
}

std::wstring BuildErrorMessage(bool expected, bool returned, std::string message)
{
	if (expected == returned)
		return L"";

	auto errormsg = L"Expected: " + std::to_wstring(expected) + L". Returned: " + std::to_wstring(returned);

	if (!message.empty())
	{
		errormsg.append(L". Message: " + StringToWString(message));
	}

	return errormsg;
}

std::wstring BuildErrorMessage(int expected, int returned, std::string message)
{
	if (expected == returned)
		return L"";

	auto errormsg = L"Expected: " + std::to_wstring(expected) + L". Returned: " + std::to_wstring(returned);

	if (!message.empty())
	{
		errormsg.append(L". Message: " + StringToWString(message));
	}

	return errormsg;
}