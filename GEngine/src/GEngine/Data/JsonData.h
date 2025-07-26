//
// Created by guillem on 7/24/25.
//

#ifndef JSONDATA_H
#define JSONDATA_H
#include "json.hpp"

namespace GEngine
{
	class JsonData
	{
	public:
		explicit JsonData(const nlohmann::json &json);
		JsonData();

		bool GetBool(const char* name, bool defaultValue = false) const;
		int GetInt(const char* name, int defaultValue = 0) const;
		int GetFloat(const char* name, float defaultValue = 0) const;
		std::string GetString(const char* name, const std::string& defaultValue = "") const;
		JsonData GetObject(const char* name) const;

		int GetArrayCount(const char* name) const;
		bool GetArrayBool(const char* name, int index) const;
		int GetArrayInt(const char* name, int index) const;
		float GetArrayFloat(const char* name, int index) const;
		std::string GetArrayString(const char* name, int index) const;
		JsonData GetArrayObject(const char* name, int index) const;

	private:
		nlohmann::json _json;
	};
}

#endif //JSONDATA_H
