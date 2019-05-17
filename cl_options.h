#include <iostream>
#include <stdlib.h>
// #include <unistd.h>
#include <getopt.h>

#define DEFAULT_SERVER "https://jsonplaceholder.typicode.com"

enum class Operations : int
{
	None = 0,
	GetPosts,
	GetComments,
	CreatePost,
	UpdatePost,
	DeletePost,
};

enum class OperationFlags : int
{
	None = 0,
	ByUserId,
	ByPostId,
	ByCommentId,
};

class CommandLineOptions
{
	char *server;
	unsigned long user_id;
	unsigned long post_id;
	unsigned long comment_id;
	std::string title;
	std::string body;
	Operations operation;
	OperationFlags flags;
public:
	CommandLineOptions(int argc, char *argv[]);
	
	const std::string getServer() const
	{
		return std::string(this->server ? this->server : DEFAULT_SERVER);
	}
	const Operations &getOperation() const
	{
		return this->operation;
	}
	const OperationFlags &getOperationFlags() const
	{
		return this->flags;
	}
	const int getPostId() const
	{
		return this->post_id;
	}
	const int getUserId() const
	{
		return this->user_id;
	}
	const int getCommentId() const
	{
		return this->comment_id;
	}
	const std::string getTitle() const
	{
		return this->title;
	}
	const std::string getBody() const
	{
		return this->body;
	}
};