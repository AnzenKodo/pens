#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024
#define MAX_HEADERS 50

// Structure to hold the parsed request
typedef struct {
    char method[16];
    char path[256];
    char protocol[16];
    struct {
        char key[128];
        char value[512];
    } headers[MAX_HEADERS];
    int header_count;
} HttpRequest;

// Function to trim whitespace from a string
\char* trim(char* str) {
    char* end;
    while (*str == ' ') str++;
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;
    *(end + 1) = '\0';
    return str;
}

// Function to parse the HTTP request
int parse_http_request(const char* request, HttpRequest* parsed) {
    char line[MAX_LINE_LENGTH];
    const char* cursor = request;
    int line_num = 0;

    // Initialize the parsed request
    parsed->header_count = 0;
    memset(parsed->method, 0, sizeof(parsed->method));
    memset(parsed->path, 0, sizeof(parsed->path));
    memset(parsed->protocol, 0, sizeof(parsed->protocol));

    // Read the request line by line
    while (*cursor && parsed->header_count < MAX_HEADERS) {
        // Extract one line
        int i = 0;
        while (*cursor && *cursor != '\n' && i < MAX_LINE_LENGTH - 1) {
            line[i++] = *cursor++;
        }
        if (*cursor == '\n') cursor++;
        line[i] = '\0';

        // Skip empty lines
        if (strlen(line) == 0) continue;

        // Parse the request line (first line)
        if (line_num == 0) {
            char* token = strtok(line, " ");
            if (token) strncpy(parsed->method, token, sizeof(parsed->method) - 1);
            token = strtok(NULL, " ");
            if (token) strncpy(parsed->path, token, sizeof(parsed->path) - 1);
            token = strtok(NULL, " ");
            if (token) strncpy(parsed->protocol, trim(token), sizeof(parsed->protocol) - 1);
        } else {
            // Parse header lines
            char* colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char* key = trim(line);
                char* value = trim(colon + 1);
                strncpy(parsed->headers[parsed->header_count].key, key, sizeof(parsed->headers[0].key) - 1);
                strncpy(parsed->headers[parsed->header_count].value, value, sizeof(parsed->headers[0].value) - 1);
                parsed->header_count++;
            }
        }
        line_num++;
    }

    return 0;
}

// Function to print the parsed request
void print_http_request(const HttpRequest* request) {
    printf("Method: %s\n", request->method);
    printf("Path: %s\n", request->path);
    printf("Protocol: %s\n", request->protocol);
    printf("Headers (%d):\n", request->header_count);
    for (int i = 0; i < request->header_count; i++) {
        printf("  %s: %s\n", request->headers[i].key, request->headers[i].value);
    }
}

int main() {
    const char* http_request =
        "GET / HTTP/1.1\n"
        "Host: localhost:8080\n"
        "Connection: keep-alive\n"
        "sec-ch-ua-platform: \"Linux\"\n"
        "User-Agent: Mozilla/5.0 (X11; Linux x86_64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/135.0.0.0 Safari/537.36\n"
        "sec-ch-ua: \"Brave\";v=\"135\", \"Not-A.Brand\";v=\"8\", \"Chromium\";v=\"135\"\n"
        "sec-ch-ua-mobile: ?0\n"
        "Accept: image/avif,image/webp,image/apng,image/svg+xml,image/*,*/*;q=0.8\n"
        "Sec-GPC: 1\n"
        "Sec-Fetch-Site: same-site\n"
        "Sec-Fetch-Mode: no-cors\n"
        "Sec-Fetch-Dest: image\n"
        "Referer: http://localhost:8100/\n"
        "Accept-Encoding: gzip, deflate, br, zstd\n"
        "Accept-Language: en-US,en;q=0.9\n";

    HttpRequest request;
    if (parse_http_request(http_request, &request) == 0) {
        print_http_request(&request);
    } else {
        printf("Failed to parse HTTP request\n");
    }

    return 0;
}
