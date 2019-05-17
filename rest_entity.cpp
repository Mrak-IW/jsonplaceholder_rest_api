#include "rest_entity.h"

ostream &operator<<(ostream &out, const RestEntity &obj)
{
	out << obj.toStringPretty();
	return out;
}