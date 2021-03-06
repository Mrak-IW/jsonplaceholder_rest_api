#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include <getopt.h>
#include "cl_options.h"
#include "post.h"
#include "user.h"

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
			     << Post(opt.getPostId(), server) << endl;
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
			cout << posts.size() << " posts got" << endl;
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
		     << "Post::createOnServer()" << endl
		     << post.toString() << endl
		     << DELIMETER << endl
		     << "Response:" << endl
		     // For some reason server returns only id of new post but not any of its fields.
		     // Don't know if it is a problem of my code.
		     << post.createOnServer(server) << endl
		     << DELIMETER << endl;
	}
	break;
	case Operations::UpdatePost:
	{
		if (!opt.isFieldsPresent(FL_POST_ID))
		{
			cout << "ERROR: Post to be updated must be found by id" << endl;
		}

		Post post;

		post.setId(opt.getPostId());
		if (opt.isFieldsPresent(FL_BODY))
		{
			post.setBody(opt.getBody());
		}
		if (opt.isFieldsPresent(FL_TITLE))
		{
			post.setTitle(opt.getTitle());
		}
		if (opt.isFieldsPresent(FL_USER_ID))
		{
			post.setUserId(opt.getUserId());
		}

		cout << DELIMETER << endl
		     << "Post::updateOnServer()" << endl
		     << post << endl
		     << DELIMETER << endl
		     << "Response:" << endl
		     << post.updateOnServer(server) << endl
		     << DELIMETER << endl;
	}
	break;
	case Operations::DeletePost:
	{
		switch (opt.getOperationFlags())
		{
		case OperationFlags::ByPostId:
		{
			Post post;
			post.setId(opt.getPostId());
			cout << DELIMETER << endl
			     << "Post::deleteOnServer(" << opt.getPostId() << ")" << endl
			     << DELIMETER << endl
			     << "Response:" << endl
			     << post.deleteOnServer(server) << endl
			     << DELIMETER << endl;
		}
		break;
		default:
			cout << "ERROR --post-id must be set to delete a post" << endl;
			break;
		}
	}
	break;
	case Operations::GetUsers:
	{
		switch (opt.getOperationFlags())
		{
		case OperationFlags::None:
		{
			std::list<User> users;
			User::getAll(server, users);

			cout << DELIMETER << endl
			     << "User::getAll()" << endl
			     << DELIMETER;

			for (auto user : users)
			{
				cout << DELIMETER << endl
				     << user << endl;
			}
			cout << users.size() << " users got" << endl;
		}
		break;
		case OperationFlags::ByUserId:
		{
			User user(opt.getUserId(), server);
			// User user;
			// user.setName("test user");
			// user.setId(100500);
			// user.company.setName("CCCCCCC");
			// user.company.setCatchPhrase("CFCFCFCFCFCFCF");

			cout << DELIMETER << endl
			     << "User get by ID(" << opt.getUserId() << ")" << endl
			     << DELIMETER << endl
			     << "Response:" << endl
			     << user << endl;
			// user.company.setName("NNNNNNN");
			cout << DELIMETER << endl
			     << "User.company.name = '" << user.company.getName() << "'" << endl
			     << "User.company.catchPhrase = '" << user.company.getCatchPhrase() << "'" << endl
			     << "User.company.bs = '" << user.company.getBs() << "'" << endl
			     << "User.address = " << user["address"] << endl
			     << DELIMETER << endl;
		}
		break;
		default:
			cout << "ERROR --post-id must be set to delete a post" << endl;
			break;
		}
	}
	break;
	default:
		cout << "ERROR operation" << endl;
		break;
	}
}