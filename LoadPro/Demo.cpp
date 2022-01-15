#include "LoadPro.h"
#include <iostream>


int main() {
	LoadPro pro;
	pro.load("M:\\Welcome to MCSQ\\server.properties");

	std::cout << "=" << pro.getString("server-portv6", "0") << "=" << std::endl;;
}