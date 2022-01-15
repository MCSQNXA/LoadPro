#include "LoadPro.h"
#include <vector>

bool LoadPro::load(const char* file)
{
	std::vector<std::string> lines;

	FILE* flags;
	fopen_s(&flags, file, "r");

	if (flags == NULL) {
		return false;
	}

	fseek(flags, 0, SEEK_END);
	size_t len = ftell(flags);
	fseek(flags, 0, SEEK_SET);

	if (len > 0) {
		char* data = new char[len];
		len = fread(data, sizeof(char), len, flags);

		if (len > 0) {
			for (size_t last = 0, i = 0; i < len; i++) {
				if (i + 1 == len) {
					lines.push_back(std::string(data, last, i - last + 1));
				}
				else if (data[i] == '\n') {
					lines.push_back(std::string(data, last,i - last)); last = i + 1;
				}
			}
		}

		delete[] data;
	}

	fclose(flags);

	for (size_t i = 0; i < lines.size(); i++) {
		const std::string& line = lines[i];
		const size_t position = line.find("=");

		if (line.find("#") == 0 || position == 0 || position == std::string::npos) {
			continue;
		}

		const size_t len = line.length();
		const std::string& key = line.substr(0, position);

		this->pro[key] = (position + 1 == len ? "" : line.substr(position + 1, len - position - 1));
	}

	return true;
}

int LoadPro::size()
{
	return (int)this->pro.size();
}

bool LoadPro::has(const char* key)
{
	return this->pro.count(key);
}

void LoadPro::clear()
{
	this->pro.clear();
}

int LoadPro::getInt(const char* key, int devalue)
{
	if (this->has(key)) {
		return atoi(this->pro[key].c_str());
	}

	return devalue;
}

long long LoadPro::getLong(const char* key, long long devalue)
{
	if (this->has(key)) {
		return atoll(this->pro[key].c_str());
	}

	return devalue;
}

bool LoadPro::getBoolean(const char* key, bool devalue)
{
	if (this->has(key)) {
		return strcmp(this->pro[key].c_str(), "true") == 0 ? true : false;
	}

	return devalue;
}

double LoadPro::getDouble(const char* key, double devalue)
{
	if (this->has(key)) {
		return atof(this->pro[key].c_str());
	}

	return devalue;
}

std::string LoadPro::getString(const char* key, std::string devalue)
{
	if (this->has(key)) {
		return this->pro[key];
	}

	return devalue;
}