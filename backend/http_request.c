#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <json-c/json.h>

/*
Prerequisites: sudo apt-get install libcurl4-openssl-dev libjson-c-dev
Compiling: gcc -o http_request http_request.c $(pkg-config --libs --cflags libcurl json-c)
Execution: ./http_request
*/

struct string {
    char *ptr;
    size_t len;
};

void init_string(struct string *s) {
    s->len = 0;
    s->ptr = malloc(s->len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "malloc() failed\n");
        exit(EXIT_FAILURE);
    }
    s->ptr[0] = '\0';
}

size_t writefunc(void *ptr, size_t size, size_t nmemb, struct string *s) {
    size_t new_len = s->len + size * nmemb;
    s->ptr = realloc(s->ptr, new_len + 1);
    if (s->ptr == NULL) {
        fprintf(stderr, "realloc() failed\n");
        exit(EXIT_FAILURE);
    }
    memcpy(s->ptr + s->len, ptr, size * nmemb);
    s->ptr[new_len] = '\0';
    s->len = new_len;

    return size * nmemb;
}

// Function to perform a GET request
char *perform_get_request(const char *url) {
    CURL *curl;
    CURLcode res;
    struct string s;
    init_string(&s);

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(s.ptr);
            s.ptr = NULL;
        }

        curl_easy_cleanup(curl);
    }

    return s.ptr;
}

// Function to perform a POST request
char *perform_post_request(const char *url, const char *json_payload) {
    CURL *curl;
    CURLcode res;
    struct string s;
    init_string(&s);

    struct curl_slist *headers = NULL;
    headers = curl_slist_append(headers, "Content-Type: application/json");

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url);
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, json_payload);
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writefunc);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &s);

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror(res));
            free(s.ptr);
            s.ptr = NULL;
        }

        curl_easy_cleanup(curl);
        curl_slist_free_all(headers);
    }

    return s.ptr;
}

void print_departments(){
    char *get_response = perform_get_request("http://0.0.0.0:9001/api/core/departments/");

    json_object *response = json_tokener_parse(get_response);

    if (get_response != NULL) {
        json_object *results_array;

        if (json_object_object_get_ex(response, "results", &results_array) &&
            json_object_is_type(results_array, json_type_array)) {

            // Loop through each element in the array
            int array_len = json_object_array_length(results_array);
            for (int i = 0; i < array_len; i++) {
                json_object *department = json_object_array_get_idx(results_array, i);
                json_object *id, *name;

                // Extract 'id' and 'name' from each object
                if (json_object_object_get_ex(department, "id", &id) &&
                    json_object_object_get_ex(department, "name", &name)) {
                    printf("ID: %d, Name: %s\n", json_object_get_int(id), json_object_get_string(name));
                }
            }

        }

        free(get_response);
    }
}

int main(void) {
    curl_global_init(CURL_GLOBAL_ALL);

    print_departments();

    const char *json_data = "{\"key1\":\"value1\", \"key2\":\"value2\"}";
    char *post_response = perform_post_request("http://0.0.0.0:9001/api/core/endpoint_path", json_data);
    if (post_response != NULL) {
        // Process the POST response
        // ...

        free(post_response);
    }

    curl_global_cleanup();
    return 0;
}
