cmake_minimum_required(VERSION 2.8)

set (CMAKE_CXX_STANDARD 14)
set (CMAKE_BUILD_TYPE Debug)
set (RAPID_JSON_INCLUDE rapidjson/include/)
set (APP_NAME rest)

add_executable(
	${APP_NAME}
	rest_entity.cpp
	cl_options.cpp
	rest.cpp
	post.cpp
	main.cpp
	user.cpp
)

target_include_directories(${APP_NAME} PRIVATE ${RAPID_JSON_INCLUDE})
target_link_libraries(${APP_NAME} curl)

# Tests section:

enable_testing()

add_test(
	NAME GetPostsAll
	COMMAND ./rest --get-posts
)
set_tests_properties(
	GetPostsAll PROPERTIES
	PASS_REGULAR_EXPRESSION "100 posts got"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME GetPostById
	COMMAND ./rest --get-posts --post-id=2
)
set_tests_properties(
	GetPostById PROPERTIES
	PASS_REGULAR_EXPRESSION "\"id\": 2"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME GetPostsByUserId
	COMMAND ./rest --get-posts --user-id=1
)
set_tests_properties(
	GetPostsByUserId PROPERTIES
	PASS_REGULAR_EXPRESSION "10 posts got"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME CreatePost
	COMMAND ./rest --create-post --user-id=1 --title=post_title --body="post body"
)
set_tests_properties(
	CreatePost PROPERTIES
	PASS_REGULAR_EXPRESSION "\"id\": 101"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME UpdatePost
	COMMAND ./rest --update-post --post-id=10 --user-id=55 --body="updated post body"
)
set_tests_properties(
	UpdatePost PROPERTIES
	PASS_REGULAR_EXPRESSION "updated"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME DeletePost
	COMMAND ./rest --delete-post --post-id=10
)
set_tests_properties(
	DeletePost PROPERTIES
	PASS_REGULAR_EXPRESSION "DELETE /posts/10"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME GetAllUses
	COMMAND ./rest --get-users
)
set_tests_properties(
	GetAllUses PROPERTIES
	PASS_REGULAR_EXPRESSION "10 users got"
	FAIL_REGULAR_EXPRESSION "ERROR"
)

add_test(
	NAME GetUserById
	COMMAND ./rest --get-users --user-id=2
)
set_tests_properties(
	GetUserById PROPERTIES
	PASS_REGULAR_EXPRESSION "User.company.name = 'Deckow-Crist'"
	FAIL_REGULAR_EXPRESSION "ERROR"
)
