# Description
This is a sample code implementing a REST API for https://jsonplaceholder.typicode.com/ test server. Details about this server you can get by the link above.

# Disclaimer
I'm contious about this project is not fool-proof. I was not trying to make it so. It is a demo-program and just a sandbox to try some C++ features.

# Usage
The project is using *cmake* system.  
To build and test the project use the folowing:
``` bash
# For brief test output
cmake . && cmake --build . && ctest .
# For detailed test output
cmake . && cmake --build . && ctest . -VV
```
You can also check it manually.  
For now the following command line arguments are implemented:
### Mode selectors
``` bash
--get-posts    # Use it without modifiers to get all posts form server
--create-post
--update-post
--delete-post

--get-users    # Use it without modifiers to get all users form server
```
### Modifiers
``` bash
--user-id=<value>  # Set user ID to get user by ID, get posts by userId or to create post with this userId
--post-id=<value>  # Set post ID to get post by ID or to create post with this ID
--body=<value>     # Set post body to create or update post
--title=<value>    # Set post title to create or update post
```
### Examples
``` bash
./rest --get-users # Get all users
./rest --delete-user --user-id=2 # Delete user with ID = 2
./rest --get-posts --user-id=2 # Get all posts from user with ID = 2
./rest --update-post --post-id=10 --title="new post title" --user-id=10 # Update post of ID = 10 with new title and userId
./rest --create-post --user-id=1 --body="post body" --title="post title" # Create a post
```
### Not implemented
Some features for user entities are not implemented for 2019, may 23. At least as command line options:  
1. Delete user
2. Create/Update user
3. Processing of deep subobjects as user's address.geo
4. Modifying of some user entity fields
