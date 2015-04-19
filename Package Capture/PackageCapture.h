#pragma once

#include <string>
#include <vector>
#include "NetworkDevice.h"

class PackageCapture {
public:
	PackageCapture();
	PackageCapture(const PackageCapture&) = delete;
	PackageCapture &operator=(const PackageCapture &) = delete;

private:
	bool findDevices();


private:
	bool goodState;
	std::string errorMsg;

	std::vector<NetworkDevice> devices;

};