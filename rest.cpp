#include "rest.h"

using namespace std;

#define DELIMETER "============================================================"

size_t RestAPI::WriteMemoryCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	size_t realsize = size * nmemb;
	struct MemoryStruct *mem = (struct MemoryStruct *)userp;

	char *ptr = (char *)realloc(mem->memory, mem->size + realsize + 1);

	if (ptr == NULL)
	{
		/* out of memory! */
		cerr << "not enough memory (realloc returned NULL)" << endl;
		return 0;
	}

	mem->memory = ptr;
	memcpy(&(mem->memory[mem->size]), contents, realsize);
	mem->size += realsize;
	mem->memory[mem->size] = 0;

	return realsize;
}

size_t RestAPI::read_callback(void *dest, size_t size, size_t nmemb, void *userp)
{
	struct WriteData *wt = (struct WriteData *)userp;
	size_t buffer_size = size * nmemb;

	if (wt->size)
	{
		/* copy as much as possible from the source to the destination */
		size_t copy_this_much = wt->size;
		if (copy_this_much > buffer_size)
			copy_this_much = buffer_size;
		memcpy(dest, wt->memory, copy_this_much);

		wt->memory += copy_this_much;
		wt->size -= copy_this_much;
		return copy_this_much; /* we copied this many bytes */
	}

	return 0; /* no more data left to deliver */
}

string RestAPI::GET(string route) const
{
	struct MemoryStruct chunk;

	CURLHandle curl_obj;
	CURLcode res;

	string url = this->server_url + route;

	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_URL, url.c_str());

	// no progress meter please
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_NOPROGRESS, 1L);
	// some servers don't like requests that are made without a user-agent
	// field, so we provide one
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_USERAGENT, "libcurl-agent/1.0");

	// send all data to this function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEFUNCTION, WriteMemoryCallback);

	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEDATA, (void *)&chunk);

	res = curl_easy_perform(curl_obj.getHandle());

	if (res != CURLE_OK)
	{
		cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;
	}

	return string(chunk.memory);
}

string RestAPI::POST(string route, string data) const
{
	CURLHandle curl_obj;
	CURLcode res;

	struct WriteData post_data;
	struct MemoryStruct chunk;
	struct curl_slist *headers = NULL;

	string url = this->server_url + route;

	post_data.memory = data.c_str();
	post_data.size = data.length();

	cerr << "POST url: \"" << url << "\"" << endl;
	cerr << "POST data: \"" << post_data.memory << "\"" << endl;

	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_URL, url.c_str());

	// Now specify we want to POST data
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_POST, 1L);
	// we want to use our own read function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_READFUNCTION, read_callback);
	// pointer to pass to our read function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_READDATA, &post_data);
	// some servers don't like requests that are made without a user-agent
	// field, so we provide one
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
	// send all data to this function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEDATA, (void *)&chunk);
	/* get verbose debug output please */
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_VERBOSE, 1L);

	headers = curl_slist_append(headers, "Content-type: application/json; charset=UTF-8");
	// headers = curl_slist_append(headers, "Host: example.com");

	/* set our custom set of headers */
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_HTTPHEADER, headers);

	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl_obj.getHandle());
	/* Check for errors */
	if (res != CURLE_OK)
		cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

	return string(chunk.memory);
}

string RestAPI::PUT(string route, string data) const
{
	CURLHandle curl_obj;
	CURLcode res;

	struct WriteData post_data;
	struct MemoryStruct chunk;
	struct curl_slist *headers = NULL;

	string url = this->server_url + route;

	post_data.memory = data.c_str();
	post_data.size = data.length();

	cerr << "PUT url: \"" << url << "\"" << endl;
	cerr << "PUT data: \"" << post_data.memory << "\"" << endl;

	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_URL, url.c_str());

	// Now specify we want to PUT data
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_PUT, 1L);
	// we want to use our own read function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_READFUNCTION, read_callback);
	// pointer to pass to our read function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_READDATA, &post_data);
	// some servers don't like requests that are made without a user-agent
	// field, so we provide one
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_USERAGENT, "libcurl-agent/1.0");
	// send all data to this function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEFUNCTION, WriteMemoryCallback);
	// we pass our 'chunk' struct to the callback function
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_WRITEDATA, (void *)&chunk);
	/* get verbose debug output please */
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_VERBOSE, 1L);

	headers = curl_slist_append(headers, "Content-type: application/json; charset=UTF-8");
	// headers = curl_slist_append(headers, "Host: example.com");

	/* set our custom set of headers */
	curl_easy_setopt(curl_obj.getHandle(), CURLOPT_HTTPHEADER, headers);

	/* Perform the request, res will get the return code */
	res = curl_easy_perform(curl_obj.getHandle());
	/* Check for errors */
	if (res != CURLE_OK)
		cerr << "curl_easy_perform() failed: " << curl_easy_strerror(res) << endl;

	return string(chunk.memory);
}