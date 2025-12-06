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
		static JsonData LoadFromFile(const char* filepath);

	public:
		JsonData();
		explicit JsonData(const nlohmann::json &json);

		[[nodiscard]] bool HasData() const;

		[[nodiscard]] bool GetBool(const char* name, bool defaultValue = false) const;
		[[nodiscard]] int GetInt(const char* name, int defaultValue = 0) const;
		[[nodiscard]] int GetFloat(const char* name, float defaultValue = 0) const;
		[[nodiscard]] std::string GetString(const char* name, const std::string& defaultValue = "") const;
		[[nodiscard]] JsonData GetObject(const char* name) const;

		[[nodiscard]] int GetArrayCount(const char* name) const;
		[[nodiscard]] bool GetArrayBool(const char* name, int index) const;
		[[nodiscard]] int GetArrayInt(const char* name, int index) const;
		[[nodiscard]] float GetArrayFloat(const char* name, int index) const;
		[[nodiscard]] std::string GetArrayString(const char* name, int index) const;
		[[nodiscard]] JsonData GetArrayObject(const char* name, int index) const;

		[[nodiscard]] std::string Dump(int indent) const;

	private:
		bool _hasData = false;
		nlohmann::json _json;
	};
}

#endif //JSONDATA_H
