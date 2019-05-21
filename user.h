#ifndef USER_H
#define USER_H

#include <list>
#include <set>
#include <string>
#include "rest_entity.h"

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
	/*! \brief Get User from server by User id */
	User(unsigned long post_id, RestAPI &server);
	User(unsigned long id, unsigned long userId, std::string title, std::string body);
	User() : RestEntity()
	{}
	
	void setId(unsigned long id);
	void setUserId(unsigned long userId);
	void setTitle(std::string body);
	void setBody(std::string title);
	
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
		getPosts("/users", server, output);
	}

	/*! \brief Return all posts with specified userId to a generic container link in arguments
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
	static void getAllByParentId(unsigned long userId, RestAPI &server, TContainer<User> &output)
	{
		getPosts(std::string("/posts?userId=") + std::to_string(userId), server, output);
	}
};

#endif
