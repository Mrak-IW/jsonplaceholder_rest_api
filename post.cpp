#include "post.h"

rapidjson::Document Post::serializeToJSON()
{
	rapidjson::Document doc;
	rapidjson::Value json_val;
	auto &allocator = doc.GetAllocator();
	doc.SetObject();
	
	json_val.SetUint64(this->userId);
	doc.AddMember("userId", json_val, allocator);
	
	json_val.SetUint64(this->id);
	doc.AddMember("id", json_val, allocator);
	
	json_val.SetString(this->title.c_str(), this->title.length(), allocator);
	doc.AddMember("title", json_val, allocator);
	
	return doc;
}

void Post::deserializeFromJSON(const rapidjson::Value &doc)
{
	// if (!doc.IsObject())
	// 	throw std::runtime_error("document is not an object");

	// static const char* members[] = { "id", "userId", "title", "body" };
	
	// for(size_t i = 0; i < sizeof(members)/sizeof(members[0]); i++)
	// 	if (!doc.HasMember(members[i]))
	// 		throw std::runtime_error("missing fields");

	this->id = doc["id"].GetUint64();
	this->userId = doc["userId"].GetUint64();
	this->title = doc["title"].GetString();
	this->body = doc["body"].GetString();
}

string Post::toString() const
{
	string result = 
	  "{\"userId\":" + std::to_string(this->userId) + ","
	  "\"id\":" + std::to_string(this->id) + ","
	  "\"title\":\"" + this->title + "\","
	  "\"body\":\"" + this->body + "\""
	  "}";

	return result;
}

string Post::toStringPretty() const
{
	string result = 
	  "{\n"
	  "\t\"userId\": " + std::to_string(this->userId) + ",\n"
	  "\t\"id\": " + std::to_string(this->id) + ",\n"
	  "\t\"title\": \"" + this->title + "\",\n"
	  "\t\"body\": \"" + this->body + "\"\n"
	  "}";

	return result;
}

Post Post::getById(unsigned long obj_id, RestAPI &server)
{
	Post result;
	rapidjson::Document doc;
	string jsontext = server.GET("/posts/" + std::to_string(obj_id));
	
	doc.Parse(jsontext.c_str());
	
	result.deserializeFromJSON(doc);
	
	return result;
}
