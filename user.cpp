#include "user.h"

using namespace std;

// =============================
// ======== class User =========
// =============================

User::User(unsigned long obj_id, RestAPI &server) : 
	company(*this)
{
	data.Parse(server.GET("/users/" + std::to_string(obj_id)).c_str());
}

void User::setId(unsigned long id)
{
	this->setUInt64("id", id);
}

void User::setName(std::string name)
{
	this->setString("name", name);
}

void User::setUsername(std::string username)
{
	this->setString("username", username);
}

void User::setEmail(std::string email)
{
	this->setString("body", email);
}

// =============================
// ===== class UserCompany =====
// =============================

std::string UserCompany::getName()
{
	return this->getString("name");
}

std::string UserCompany::getCatchPhrase()
{
	return this->getString("catchPhrase");
}

std::string UserCompany::getBs()
{
	return this->getString("bs");
}

void UserCompany::setName(std::string name)
{
	this->setString("name", name);
}

void UserCompany::setCatchPhrase(std::string catchPhrase)
{
	this->setString("catchPhrase", catchPhrase);
}

void UserCompany::setBs(std::string bs)
{
	this->setString("bs", bs);
}