//
// Created by guillem on 7/24/25.
//

#include "JsonData.h"

#include <fstream>

#include "spdlog/spdlog.h"

namespace GEngine
{
	JsonData JsonData::LoadFromFile(const std::string& filepath)
	{
		const std::ifstream file(filepath);
		if (!file) return {};

		std::stringstream buffer;
		buffer << file.rdbuf();
		std::string contents = buffer.str();

		nlohmann::json json;

		try
		{
			json = nlohmann::json::parse(contents);
		}
		catch (const nlohmann::json::parse_error& error)
		{
			//std::cerr << "JSON parse error: " << e.what() << std::endl;
			//std::cerr << "Exception ID: " << e.id << "\n";
			//std::cerr << "Byte position: " << e.byte << "\n";
			spdlog::error("JSON parse error");
			return {};
		}

		JsonData data(json);
		return data;
	}

	JsonData::JsonData() = default;

	JsonData::JsonData(const nlohmann::json &json)
	{
		_hasData = json.is_object();
		_json = json;
	}

	bool JsonData::HasData() const
	{
		return _hasData;
	}

	bool JsonData::GetBool(const char *name, const bool defaultValue) const
	{
		if (!_hasData) return defaultValue;
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_boolean()) return defaultValue;
		return value.get<bool>();
	}

	int JsonData::GetInt(const char *name, const int defaultValue) const
	{
		if (!_hasData) return defaultValue;
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_number_integer()) return defaultValue;
		return value.get<int>();
	}

	int JsonData::GetFloat(const char *name, const float defaultValue) const
	{
		if (!_hasData) return defaultValue;
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_number_float()) return defaultValue;
		return value.get<float>();
	}

	std::string JsonData::GetString(const char *name, const std::string& defaultValue) const
	{
		if (!_hasData) return defaultValue;
		if (!_json.contains(name)) return defaultValue;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_string()) return defaultValue;
		return value.get<std::string>();
	}

	JsonData JsonData::GetJsonObject(const char *name) const
	{
		if (!_hasData) return JsonData();
		if (!_json.contains(name)) return JsonData();
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_object()) return JsonData();
		return JsonData(value);
	}

	glm::i32vec2 JsonData::GetIVec2(const char* name, const glm::i32vec2& defaultValue) const
	{
		if (!_hasData) return defaultValue;
		if (!_json.contains(name)) return defaultValue;

		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_object()) return defaultValue;

		const nlohmann::basic_json<>& xValue = value["x"];
		if (!xValue.is_number_integer()) return defaultValue;

		const nlohmann::basic_json<>& yValue = value["y"];
		if (!yValue.is_number_integer()) return defaultValue;

		return { xValue.get<int>(), yValue.get<int>() };
	}

	int JsonData::GetArrayCount(const char *name) const
	{
		if (!_hasData) return 0;
		if (!_json.contains(name)) return 0;
		const nlohmann::basic_json<>& value = _json[name];
		if (!value.is_array()) return 0;
		return value.size();
	}

	bool JsonData::GetArrayBool(const char *name, const int index) const
	{
		if (!_hasData) return false;
		if (!_json.contains(name)) return false;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return false;
		if (index < 0 || index >= array.size()) return false;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_boolean()) return false;
		return value.get<bool>();
	}

	int JsonData::GetArrayInt(const char *name, const int index) const
	{
		if (!_hasData) return 0;
		if (!_json.contains(name)) return 0;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return 0;
		if (index < 0 || index >= array.size()) return 0;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_number_integer()) return 0;
		return value.get<int>();
	}

	float JsonData::GetArrayFloat(const char *name, const int index) const
	{
		if (!_hasData) return 0.0f;
		if (!_json.contains(name)) return 0.0f;
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return 0.0f;
		if (index < 0 || index >= array.size()) return 0.0f;

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_number_float()) return 0.0f;
		return value.get<float>();
	}

	std::string JsonData::GetArrayString(const char *name, const int index) const
	{
		if (!_hasData) return "";
		if (!_json.contains(name)) return "";
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return "";
		if (index < 0 || index >= array.size()) return "";

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_string()) return "";
		return value.get<std::string>();
	}

	JsonData JsonData::GetArrayJsonObject(const char *name, const int index) const
	{
		if (!_hasData) return JsonData();
		if (!_json.contains(name)) return JsonData();
		const nlohmann::basic_json<>& array = _json[name];
		if (!array.is_array()) return JsonData();
		if (index < 0 || index >= array.size()) return JsonData();

		const nlohmann::basic_json<>& value = array[index];
		if (!value.is_object()) return JsonData();
		return JsonData(value);
	}

	std::string JsonData::Dump(const int indent) const
	{
		return _json.dump(indent);
	}
} // GEngine