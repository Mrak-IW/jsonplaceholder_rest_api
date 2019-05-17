#include <iostream>
#include "rapidjson/document.h"

using namespace std;

class RestEntity
{
public:
	friend ostream &operator<<(ostream &out, const RestEntity &obj);
	
	virtual rapidjson::Document serializeToJSON() = 0;
	virtual void deserializeFromJSON(const rapidjson::Value &doc) = 0;
	
	virtual string toString() const = 0;
	virtual string toStringPretty() const = 0;
};