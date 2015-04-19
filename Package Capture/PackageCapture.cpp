#include "PackageCapture.h"
#define HAVE_REMOTE
#include <pcap\pcap.h>
#include <remote-ext.h>
#include <iostream>

using namespace std;

PackageCapture::PackageCapture() {
	goodState = findDevices();

}

bool PackageCapture::findDevices() {
	pcap_if_t *firstDev;
	char errBuf[PCAP_ERRBUF_SIZE];

	// 获取本机网络设备列表
	if (pcap_findalldevs_ex(PCAP_SRC_IF_STRING, NULL, &firstDev, errBuf) == -1) {
		errorMsg = "Error in pcap_findalldevs_ex(). detail:" + string(errBuf);
		return false;
	}

	for (auto dev = firstDev; dev != NULL; dev = dev->next) {
		NetworkDevice networkDevice;
		networkDevice.name = dev->name;
		if (dev->description)
			networkDevice.description = dev->description;
		else
			networkDevice.description = "No description available.";
		networkDevice.isLoopback = dev->flags & PCAP_IF_LOOPBACK;

		// 找出每个设备的地址列表
		for (auto addr = dev->addresses; addr != NULL; addr = addr->next) {
			networkDevice.addressFamilyCode = addr->addr->sa_family;

			switch (addr->addr->sa_family) {
			case AF_INET:
				networkDevice.addressFamilyName = "AF_INET";

				break;

			case AF_INET6:
				networkDevice.addressFamilyName = "AF_INET6";

				break;

			default:
				networkDevice.addressFamilyName = "Unknown";
				break;
			}

		}

		devices.push_back(networkDevice);
	}

		
	if (devices.empty()) {
		errorMsg = "No interface found!";
		return false;
	}

	pcap_freealldevs(firstDev);

	return true;
}