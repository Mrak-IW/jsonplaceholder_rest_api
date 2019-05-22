#include "rest_entity.h"

using namespace std;

// ============================
// ===== class RestEntity =====
// ============================

ostream &operator<<(ostream &out, const RestEntity &obj)
{
	out << obj.toStringPretty();
	return out;
}

std::string RestEntity::operator[](std::string name)
{
	rapidjson::StringBuffer buffer;
	rapidjson::Value &value = this->data[name.c_str()];

	buffer.Clear();

	rapidjson::Writer<rapidjson::StringBuffer> writer(buffer);
	value.Accept(writer);

	return std::string(buffer.GetString());
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
		this->data[name.c_str()].SetString(value.c_str(), value.length(), allocator);
	}
	else
	{
		rapidjson::Value json_val;
		auto &allocator = this->data.GetAllocator();
		rapidjson::Value v_name(name.c_str(), allocator);

		json_val.SetString(value.c_str(), value.length(), allocator);
		data.AddMember(v_name, json_val, allocator);
	}
}

// =====================================
// ===== class RestEntitySubobject =====
// =====================================

std::string RestEntitySubobject::getString(std::string name)
{
	rapidjson::Value::MemberIterator company_iter = parent.data.FindMember("company");

	if (company_iter == parent.data.MemberEnd())
	{
		return std::string("");
	}

	rapidjson::Value::MemberIterator member_iter = company_iter->value.FindMember(name.c_str());

	if (member_iter == company_iter->value.MemberEnd())
	{
		return std::string("");
	}

	return std::string(member_iter->value.GetString());
}

void RestEntitySubobject::setString(std::string name, std::string value)
{
	auto &allocator = parent.data.GetAllocator();

	if (!parent.data.HasMember(this->getSubobjectName()))
	{
		rapidjson::Value json_name;
		json_name.SetString(this->getSubobjectName(), strlen(this->getSubobjectName()), allocator);

		parent.data.AddMember(json_name, rapidjson::Value().SetObject(), allocator);
	}

	rapidjson::Value::MemberIterator company_iter = parent.data.FindMember(this->getSubobjectName());

	if (!company_iter->value.HasMember(name.c_str()))
	{
		rapidjson::Value json_val, json_name;
		json_val.SetString(value.c_str(), value.length(), allocator);
		json_name.SetString(name.c_str(), name.length(), allocator);

		company_iter->value.AddMember(json_name, json_val, allocator);
	}
	else
	{
		rapidjson::Value::MemberIterator value_iter = company_iter->value.FindMember(name.c_str());
		value_iter->value.SetString(value.c_str(), value.length(), allocator);
	}
}
