#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "cl_options.h"
#include "post.h"

using namespace std;

#define DELIMETER "============================================================"

int main(int argc, char **argv)
{
	CommandLineOptions opt(argc, argv);
	RestAPI server(opt.getServer());

	switch (opt.getOperation())
	{
	case Operations::GetPosts:
	{
		switch (opt.getOperationFlags())
		{
		case OperationFlags::ByPostId:
			cout << DELIMETER << endl
			     << "Post::getById(" << opt.getPostId() << ")" << endl
			     << DELIMETER << endl
			     << Post::getById(opt.getPostId(), server) << endl;
			break;
		case OperationFlags::None:
		{
			// posts might be any container supporting insert() method
			std::list<Post> posts;
			Post::getAll(server, posts);
			cout << DELIMETER << endl
			     << "Post::getAll()" << endl
			     << DELIMETER;
			for (auto post : posts)
			{
				cout << DELIMETER << endl
				     << post << endl;
			}
			cout << posts.size() << " posts got";
		}
		break;
		case OperationFlags::ByUserId:
		{
			// posts might be any container supporting insert() method
			std::vector<Post> posts;
			Post::getAllByParentId(opt.getUserId(), server, posts);
			cout << DELIMETER << endl
			     << "Post::getAllByParentId(" << opt.getUserId() << ")" << endl
			     << DELIMETER;
			for (auto post : posts)
			{
				cout << DELIMETER << endl
				     << post << endl;
			}
			cout << posts.size() << " posts got";
		}
		break;
		default:
			cout << "ERROR operation flags" << endl;
			break;
		}
	}
	break;
	case Operations::CreatePost:
	{
		Post post(opt.getPostId(), opt.getUserId(), opt.getTitle(), opt.getBody());

		cout << DELIMETER << endl
		     << "Post::pushToServer()" << endl
		     << post.toString() << endl
		     << DELIMETER << endl
		     << "Response:" << endl
		     // For some reason server returns only id of new post but not any of its fields.
		     // Don't know if it is a problem of my code.
		     << post.pushToServer(server) << endl
		     << DELIMETER << endl;
	}
	break;
	default:
		cout << "ERROR operation" << endl;
		break;
	}
}