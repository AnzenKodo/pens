#ifndef CCORE_HTTP_H
#define CCORE_HTTP_H

#include <errno.h>
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define HTTPS_HEADERS_MAX           50
#define HTTPS_IPV6_MAX_LENGTH       39
#define HTTPS_METHOD_MAX_LENGTH     15
#define HTTPS_PROTOCOL_MAX_LENGTH   HTTPS_METHOD_MAX_LENGTH

typedef struct Http_Request Http_Request;
struct Http_Request {
    char protocol[HTTPS_PROTOCOL_MAX_LENGTH];
    char method[HTTPS_METHOD_MAX_LENGTH];
    char path[256];
    char ip[HTTPS_IPV6_MAX_LENGTH];
    struct {
        char key[128];
        char value[512];
    } headers[HTTPS_HEADERS_MAX];
    int header_count;
};

void http_parse_request(const char* request, Http_Request* parsed) {
    char line[BUFFER_SIZE];
    const char* cursor = request;
    int line_num = 0;

    while(*cursor && parsed->header_count < HTTPS_HEADERS_MAX)
    {
        I32 i = 0;
        while (*cursor && *cursor != '\n' && i < BUFFER_SIZE - 1)
        {
            line[i++] = *cursor++;
        }
        if (*cursor == '\n') cursor++;
        line[i] = '\0';

        // Skip empty line
        if(cstr8_len(line) == 0) continue;

        if (line_num == 0) {
            char* token = strtok(line, " ");
            if (token) mem_copy(parsed->method, token, sizeof(parsed->method) - 1);
            token = strtok(NULL, " ");
            if (token) mem_copy(parsed->path, token, sizeof(parsed->path) - 1);
            token = strtok(NULL, " ");
            if (token) mem_copy(parsed->protocol, trim(token), sizeof(parsed->protocol) - 1);
        } else {
            // Parse header lines
            char* colon = strchr(line, ':');
            if (colon) {
                *colon = '\0';
                char* key = trim(line);
                char* value = trim(colon + 1);
                mem_copy(parsed->headers[parsed->header_count].key, key, sizeof(parsed->headers[0].key) - 1);
                mem_copy(parsed->headers[parsed->header_count].value, value, sizeof(parsed->headers[0].value) - 1);
                parsed->header_count++;
            }
        }
        line_num++;
    }
}

#endif // CCORE_HTTP_H
