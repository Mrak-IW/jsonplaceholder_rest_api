#include "post.h"

using namespace std;

Post::Post(unsigned long obj_id, RestAPI &server)
{
	data.Parse(server.GET("/posts/" + std::to_string(obj_id)).c_str());
}

Post::Post(unsigned long id, unsigned long userId, string title, string body) :
Post()
{
	rapidjson::Value json_val;
	auto &allocator = data.GetAllocator();
	
	json_val.SetUint64(userId);
	data.AddMember("userId", json_val, allocator);
	
	json_val.SetUint64(id);
	data.AddMember("id", json_val, allocator);
	
	json_val.SetString(title.c_str(), title.length(), allocator);
	data.AddMember("title", json_val, allocator);
	
	json_val.SetString(body.c_str(), body.length(), allocator);
	data.AddMember("body", json_val, allocator);
}

void Post::setId(unsigned long id)
{
	this->setUInt64("id", id);
}

void Post::setUserId(unsigned long id)
{
	this->setUInt64("userId", id);
}

void Post::setTitle(std::string title)
{
	this->setString("title", title);
}

void Post::setBody(std::string body)
{
	this->setString("body", body);
}
