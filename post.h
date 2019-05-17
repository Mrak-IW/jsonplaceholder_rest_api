#include <list>
#include <string>
#include "rest.h"
#include "rest_entity.h"

class Post : public RestEntity
{
	unsigned long userId;
	unsigned long id;
	string title;
	string body;

private:
	Post() : 
		Post(0, 0, "", "")
	{}

	virtual rapidjson::Document serializeToJSON() override;
	virtual void deserializeFromJSON(const rapidjson::Value &doc) override;
	
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
	template< template< typename TObject, typename TAllocator = std::allocator <TObject> > class TContainer>
	static void getPosts(string route, RestAPI &server, TContainer<Post> &output)
	{
		TContainer<Post> result;
		rapidjson::Document doc;
		string jsontext = server.GET(route);
		unsigned long arr_size;
		
		doc.Parse(jsontext.c_str());
		arr_size = doc.Size();
		
		if(!doc.IsArray())
			throw std::runtime_error("document is not an array");

		for (rapidjson::Value::ConstValueIterator itr = doc.Begin(); itr != doc.End(); ++itr)
		{
			Post buf;
			buf.deserializeFromJSON(*itr);
			result.insert(result.end(), buf);
		}

		output.swap(result);
	}

public:
	Post(unsigned long id, unsigned long userId, string title, string body) : 
		id(id),
		userId(userId),
		title(title),
		body(body)
	{}

	string toString() const;
	string toStringPretty() const;

	std::string pushToServer(RestAPI &server)
	{
		// string test_post = "{title: '" + title + "', body: '" + body + "', userId: " + std::to_string(userId) + "}";
		return server.POST("/posts", this->toString());
	}
	
	static Post getById(unsigned long obj_id, RestAPI &server);
	
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
	template< template< typename TObject, typename TAllocator = std::allocator <TObject> > class TContainer>
	static void getAll(RestAPI &server, TContainer<Post> &output)
	{
		getPosts("/posts", server, output);
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
	template< template< typename TObject, typename TAllocator = std::allocator <TObject> > class TContainer>
	static void getAllByParentId(unsigned long userId, RestAPI &server, TContainer<Post> &output)
	{
		getPosts(std::string("/posts?userId=") + std::to_string(userId), server, output);
	}
};
