#include "cl_options.h"

using namespace std;

CommandLineOptions::CommandLineOptions(int argc, char *argv[]) :
	server(NULL),
	operation(Operations::None),
	flags(OperationFlags::None),
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
			{"get-posts",    no_argument,       (int *)&operation,  (int)Operations::GetPosts },
			{"server",       required_argument, &server_fl,         1 },
			{"user-id",      required_argument, (int *)&flags,      (int)OperationFlags::ByUserId },
			{"post-id",      required_argument, (int *)&flags,      (int)OperationFlags::ByPostId },
			{"comment-id",   required_argument, (int *)&flags,      (int)OperationFlags::ByCommentId },
			{"create-post",  no_argument,       (int *)&operation,  (int)Operations::CreatePost },
			{"body",         required_argument, 0,                  0 },
			{"title",        required_argument, 0,                  0 },
			{0,              0,                 0,                  0 }
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
			case 1:	// server
				if (optarg)
				{
					this->server = optarg;
				}
				break;
			case 2:	// user-id
				if (optarg)
				{
					this->user_id = std::strtol(optarg, NULL, 0);
				}
				break;
			case 3:	// post-id
				if (optarg)
				{
					this->post_id = std::strtol(optarg, NULL, 0);
				}
				break;
			case 4:	// comment-id
				if (optarg)
				{
					this->comment_id = std::strtol(optarg, NULL, 0);
				}
				break;
			case 6:	// body
				if (optarg)
				{
					this->body = optarg;
					if(this->body[0] == '"')
						this->body.erase(0, 1);
					if(this->body[this->body.length() - 1] == '"')
						this->body.erase(this->body.length() - 1, 1);
				}
				break;
			case 7:	// title
				if (optarg)
				{
					this->title = optarg;
					if(this->title[0] == '"')
						this->title.erase(0, 1);
					if(this->title[this->title.length() - 1] == '"')
						this->title.erase(this->title.length() - 1, 1);
				}
				break;
			default:
				break;
			}
			break;
		}
	}
}