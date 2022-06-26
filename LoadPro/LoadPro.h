#pragma once

#include <map>
#include <string>


class LoadPro {
private:
	std::map<std::string, std::string> pro;

public:
	bool load(const char* file);

public:
	int size();

public:
	bool has(const char* key);

public:
	void clear();

public:
	int getInt(const char* key, int devalue);
	long long getLong(const char* key, long long devalue);
	bool getBoolean(const char* key, bool devalue);
	double getDouble(const char* key, double devalue);
	std::string getString(const char* key, std::string devalue);
};