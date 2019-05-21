#include "cl_options.h"

using namespace std;

CommandLineOptions::CommandLineOptions(int argc, char *argv[]) :
	server(NULL),
	operation(Operations::None),
	flags(OperationFlags::None),
	fieldFlags(0),
	title("default title"),
	body("default body"),
	user_id(0),
	post_id(0),
	comment_id(0)
{
	int res;
	
	int c;
	int digit_optind = 0;
	int server_fl = 0;
	while (1)
	{
		int this_option_optind = optind ? optind : 1;
		int option_index = 0;
		static struct option long_options[] = {
			{.name = "server",       .has_arg = required_argument, .flag = &server_fl,         .val = 1 },
			{.name = "user-id",      .has_arg = required_argument, .flag = (int *)&flags,      .val = (int)OperationFlags::ByUserId },
			{.name = "post-id",      .has_arg = required_argument, .flag = (int *)&flags,      .val = (int)OperationFlags::ByPostId },
			{.name = "comment-id",   .has_arg = required_argument, .flag = (int *)&flags,      .val = (int)OperationFlags::ByCommentId },
			{.name = "body",         .has_arg = required_argument, .flag = 0,                  .val = 0 },
			{.name = "title",        .has_arg = required_argument, .flag = 0,                  .val = 0 },
			{.name = "get-posts",    .has_arg = no_argument,       .flag = (int *)&operation,  .val = (int)Operations::GetPosts },
			{.name = "update-post",  .has_arg = no_argument,       .flag = (int *)&operation,  .val = (int)Operations::UpdatePost },
			{.name = "delete-post",  .has_arg = no_argument,       .flag = (int *)&operation,  .val = (int)Operations::DeletePost },
			{.name = "create-post",  .has_arg = no_argument,       .flag = (int *)&operation,  .val = (int)Operations::CreatePost },
			{.name = 0,              .has_arg = 0,                 .flag = 0,                  .val = 0 }
		};
		c = getopt_long(argc, argv, "abc:d:012",
		long_options, &option_index);
		if (c == -1)
			break;
		switch (c)
		{
		case 0:
			std::cerr << long_options[option_index].name << " option found" << std::endl;
			
			switch (option_index)
			{
			case 0:	// server
				if (optarg)
				{
					this->server = optarg;
				}
				break;
			case 1:	// user-id
				if (optarg)
				{
					this->user_id = std::strtol(optarg, NULL, 0);
					fieldFlags |= FL_USER_ID;
				}
				break;
			case 2:	// post-id
				if (optarg)
				{
					this->post_id = std::strtol(optarg, NULL, 0);
					fieldFlags |= FL_POST_ID;
				}
				break;
			case 3:	// comment-id
				if (optarg)
				{
					this->comment_id = std::strtol(optarg, NULL, 0);
					fieldFlags |= FL_COMMENT_ID;
				}
				break;
			case 4:	// body
				if (optarg)
				{
					this->body = optarg;
					if(this->body[0] == '"')
						this->body.erase(0, 1);
					if(this->body[this->body.length() - 1] == '"')
						this->body.erase(this->body.length() - 1, 1);
					
					fieldFlags |= FL_BODY;
				}
				break;
			case 5:	// title
				if (optarg)
				{
					this->title = optarg;
					if(this->title[0] == '"')
						this->title.erase(0, 1);
					if(this->title[this->title.length() - 1] == '"')
						this->title.erase(this->title.length() - 1, 1);
					
					fieldFlags |= FL_TITLE;
				}
				break;
			default:
				break;
			}
			break;
		}
	}
}