#ifndef USER_H
#define USER_H

#include <list>
#include <set>
#include <string>
#include "rest_entity.h"

typedef class User User;

class UserCompany : public RestEntitySubobject
{
protected:
	virtual const char *getSubobjectName() const override
	{
		return "company";
	}
public:
	UserCompany(User &parent) : RestEntitySubobject((RestEntity &)parent)
	{}
	
	std::string getName();
	std::string getCatchPhrase();
	std::string getBs();
	void setName(std::string name);
	void setCatchPhrase(std::string catchPhrase);
	void setBs(std::string bs);
};

class User : public RestEntity
{
private:
	/*! \brief Return posts to a generic container link in arguments
	 *
	 * Specify the type of container in template specialization or just by using argument of the type needed.
	 * Container must support insert() method.
	 * 
	 * Throws exceptions if parsing of json plaintext goes wrong.
	 * 
	 * \param route  Route to get some posts from server
	 * \param server Server instance to get data from
	 * \param output Link to an existing container to be filled with the posts gained
	 */
	template <template <typename TObject, typename TAllocator = std::allocator<TObject>> class TContainer>
	static void getUsers(std::string route, RestAPI &server, TContainer<User> &output)
	{
		TContainer<User> result;
		rapidjson::Document doc;
		rapidjson::Document::AllocatorType& a = doc.GetAllocator();
		std::string jsontext = server.GET(route);
		unsigned long arr_size;

		doc.Parse(jsontext.c_str());
		arr_size = doc.Size();

		if (!doc.IsArray())
			throw std::runtime_error("document is not an array");

		for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
		{
			User buf;
			buf.data.CopyFrom(*itr, a);
			result.insert(result.end(), buf);
		}

		output.swap(result);
	}

public:
	UserCompany company;

	/*! \brief Get User from server by User id */
	User(unsigned long post_id, RestAPI &server);
	User() :
		RestEntity(),
		company(*this)
	{}
	
	void setId(unsigned long id);
	void setName(std::string name);
	void setUsername(std::string username);
	void setEmail(std::string email);
	
	virtual std::string getUpdatePath() override
	{
		return std::string("/users/") + (*this)["id"];
	}
	virtual std::string getCreatePath() override
	{
		return "/users";
	}
	virtual std::string getDeletePath() override
	{
		return std::string("/users/") + (*this)["id"];
	}

	/*! \brief Return all posts to a generic container link in arguments
	 *
	 * Specify the type of container in template specialization or just by using argument of the type needed.
	 * Container must support insert() method.
	 * 
	 * Throws exceptions if parsing of json plaintext goes wrong.
	 * 
	 * \param server Server instance to get data from
	 * \param output Link to an existing container to be filled with the posts gained
	 */
	template <template <typename TObject, typename TAllocator = std::allocator<TObject>> class TContainer>
	static void getAll(RestAPI &server, TContainer<User> &output)
	{
		getUsers("/users", server, output);
	}
};

#endif
