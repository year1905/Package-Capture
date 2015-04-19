#pragma once

#include <string>

struct NetworkDevice {
	std::string name;
	std::string description;

	bool isLoopback;
	unsigned short addressFamilyCode;
	std::string addressFamilyName;
};