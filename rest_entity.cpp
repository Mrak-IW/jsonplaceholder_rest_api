#include "rest_entity.h"

using namespace std;

ostream &operator<<(ostream &out, const RestEntity &obj)
{
	out << obj.toStringPretty();
	return out;
}

std::string RestEntity::toString() const
{
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	this->data.Accept(writer);
	
	return std::string(buffer.GetString());
}

std::string RestEntity::toStringPretty() const
{
	rapidjson::StringBuffer buffer;

	buffer.Clear();

	rapidjson::PrettyWriter<rapidjson::StringBuffer> writer(buffer);
	this->data.Accept(writer);
	
	return std::string(buffer.GetString());
}

void RestEntity::setUInt64(std::string name, unsigned long value)
{
	if (this->data.HasMember(name.c_str()))
	{
		this->data[name.c_str()].SetUint64(value);
	}
	else
	{
		rapidjson::Value json_val;
		rapidjson::Value v_name(name.c_str(), this->data.GetAllocator());
		auto &allocator = this->data.GetAllocator();
		
		json_val.SetUint64(value);
		data.AddMember(v_name, json_val, allocator);
	}
}

void RestEntity::setString(std::string name, std::string value)
{
	if (this->data.HasMember(name.c_str()))
	{
		auto &allocator = this->data.GetAllocator();
		this->data[name.c_str()].SetString(name.c_str(), name.length(), allocator);
	}
	else
	{
		rapidjson::Value json_val;
		auto &allocator = this->data.GetAllocator();
		rapidjson::Value v_name(name.c_str(), allocator);

		json_val.SetString(name.c_str(), name.length(), allocator);
		data.AddMember(v_name, json_val, allocator);
	}
}