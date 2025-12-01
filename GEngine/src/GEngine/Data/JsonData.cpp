//
// Created by guillem on 7/24/25.
//

#include "JsonData.h"

namespace GEngine
{
	JsonData::JsonData(const nlohmann::json &json)
	{
		_json = json;
	}

	JsonData::JsonData()
	{
	}

	bool JsonData::GetBool(const char *name, const bool defaultValue) const
	{
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_boolean()) return defaultValue;
		return value.get<bool>();
	}

	int JsonData::GetInt(const char *name, const int defaultValue) const
	{
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_number_integer()) return defaultValue;
		return value.get<int>();
	}

	int JsonData::GetFloat(const char *name, const float defaultValue) const
	{
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_number_float()) return defaultValue;
		return value.get<float>();
	}

	std::string JsonData::GetString(const char *name, const std::string& defaultValue) const
	{
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_string()) return defaultValue;
		return value.get<std::string>();
	}

	JsonData JsonData::GetObject(const char *name) const
	{
		if (!_json.contains(name)) return JsonData();
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_object()) return JsonData();
		return JsonData(value);
	}

	int JsonData::GetArrayCount(const char *name) const
	{
		if (!_json.contains(name)) return 0;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_array()) return 0;
		return value.size();
	}

	bool JsonData::GetArrayBool(const char *name, const int index) const
	{
		if (!_json.contains(name)) return false;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return false;
		if (!array.size() <= index) return false;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_boolean()) return false;
		return value.get<bool>();
	}

	int JsonData::GetArrayInt(const char *name, const int index) const
	{
		if (!_json.contains(name)) return 0;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return 0;
		if (!array.size() <= index) return 0;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_number_integer()) return 0;
		return value.get<int>();
	}

	float JsonData::GetArrayFloat(const char *name, const int index) const
	{
		if (!_json.contains(name)) return 0.0f;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return 0.0f;
		if (!array.size() <= index) return 0.0f;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_number_float()) return 0.0f;
		return value.get<float>();
	}

	std::string JsonData::GetArrayString(const char *name, const int index) const
	{
		if (!_json.contains(name)) return "";
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return "";
		if (!array.size() <= index) return "";

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_string()) return "";
		return value.get<std::string>();
	}

	JsonData JsonData::GetArrayObject(const char *name, const int index) const
	{
		if (!_json.contains(name)) return JsonData();
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return JsonData();
		if (array.size() <= index) return JsonData();

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_object()) return JsonData();
		return JsonData(value);
	}
} // GEngine