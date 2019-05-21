#include <iostream>
#include <set>
#include "rapidjson/document.h"
#include "rapidjson/writer.h"
#include "rapidjson/prettywriter.h"

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
	
	friend std::ostream &operator << (std::ostream &out, const RestEntity &obj);

	virtual std::string toString() const;
	virtual std::string toStringPretty() const;
	
	virtual std::string operator [] (std::string key)
	{
		return data[key.c_str()].GetString();
	}
};
