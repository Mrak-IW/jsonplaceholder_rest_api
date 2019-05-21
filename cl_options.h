#ifndef CL_OPTIONS_H
#define CL_OPTIONS_H

#include <iostream>
#include <stdlib.h>
// #include <unistd.h>
#include <getopt.h>

#define DEFAULT_SERVER "https://jsonplaceholder.typicode.com"
#define FL_TITLE 1
#define FL_BODY (1 << 1)
#define FL_USER_ID (1 << 2)
#define FL_POST_ID (1 << 3)
#define FL_COMMENT_ID (1 << 4)

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
	int fieldFlags;
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
	const bool isFieldsPresent(int fieldFlags) const
	{
		return (this->fieldFlags & fieldFlags) == fieldFlags;
	}
};

#endif
