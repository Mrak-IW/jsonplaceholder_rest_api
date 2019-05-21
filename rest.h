#include <string>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h> // I understand that libcurl is not a pure C++ way, but anyway...

class RestAPI
{
	std::string server_url;

protected:
	static size_t WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp);
	static size_t read_callback(void *dest, size_t size, size_t nmemb, void *userp);

public:
	std::string GET(std::string route) const;
	std::string POST(std::string route, std::string data) const;
	std::string PUT(std::string route, std::string data) const;

	RestAPI(const std::string server) : 
		server_url(server)
	{}
	
	virtual ~RestAPI ()
	{}
	
	const std::string getServerUrl() const
	{
		return this->server_url;
	}
	
	std::string getPostComments(unsigned long postId)
	{
		return this->GET(this->server_url + "/posts/" + std::to_string(postId) + "/comments");
	}
	
	std::string getPostComment(unsigned long postId, unsigned long commentId)
	{
		return this->GET(this->server_url + "/posts/" + std::to_string(postId) + "/comments?id=" + std::to_string(commentId));
	}
};

struct MemoryStruct {
	char *memory;
	size_t size;
public:
	MemoryStruct() : 
		memory(NULL),
		size(0)
	{}

	~MemoryStruct()
	{
		if (this->memory)
		{
			free(this->memory);
		}
	}
};

struct WriteData {
	const char *memory;
	size_t size;
};

class CURLHandle
{
	CURL *curl_handle;
public:
	CURL *getHandle()
	{
		return curl_handle;
	}
	
	CURLHandle()
	{
		curl_handle = curl_easy_init();
	}
	
	virtual ~CURLHandle ()
	{
		curl_easy_cleanup(this->curl_handle);
	}
};
