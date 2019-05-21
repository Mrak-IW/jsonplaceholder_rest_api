#ifndef REST_ENTITY_H
#define REST_ENTITY_H

#include <iostream>
#include <set>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"
#include "rest.h"

class RestEntity
{
protected:
	rapidjson::Document data;
	
	virtual void setUInt64(std::string name, unsigned long value);
	virtual void setString(std::string name, std::string value);
public:
	RestEntity()
	{
		this->data.SetObject();
	}
	
	RestEntity(const RestEntity &src)
	{
		this->data.CopyFrom(src.data, this->data.GetAllocator());
	}
	
	RestEntity &operator = (const RestEntity &src)
	{
		this->data.CopyFrom(src.data, this->data.GetAllocator());
	}
	
	std::string createOnServer(RestAPI &server)
	{
		return server.POST(this->getCreatePath(), this->toString());
	}
	
	std::string updateOnServer(RestAPI &server)
	{
		return server.PUT(this->getUpdatePath(), this->toString());
	}
	
	std::string deleteOnServer(RestAPI &server)
	{
		return server.DELETE(this->getDeletePath());
	}
	
	friend std::ostream &operator << (std::ostream &out, const RestEntity &obj);

	virtual std::string toString() const;
	virtual std::string toStringPretty() const;
	
	virtual std::string operator [] (std::string key);
	
	virtual std::string getUpdatePath() = 0;
	virtual std::string getCreatePath() = 0;
	virtual std::string getDeletePath() = 0;
};

#endif
