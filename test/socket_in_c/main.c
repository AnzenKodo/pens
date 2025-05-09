#include "base/base_include.h"
#include "os/os_include.h"

#include "base/base_include.c"
#include "os/os_include.c"

#include <stdio.h>
#include <string.h>

#include "http.h"

#define PORT        8080
#define BACKLOG     10
#define BUFFER_SIZE 1024

typedef enum HttpErrors {
    HttpErrors_None,
} HttpErrors;

char* trim(char* str) {
    char* end;
    while (*str == ' ') str++;
    end = str + strlen(str) - 1;
    while (end > str && *end == ' ') end--;
    *(end + 1) = '\0';
    return str;
}

void print_http_request(const Http_Request* request) {
    printf("IP: %s\n", request->ip);
    printf("Method: %s\n", request->method);
    printf("Path: %s\n", request->path);
    printf("Protocol: %s\n", request->protocol);
    printf("Headers (%d):\n", request->header_count);
    for (int i = 0; i < request->header_count; i++) {
        printf("  %s: %s\n", request->headers[i].key, request->headers[i].value);
    }
}

void http_send_image_file(
    int client_sock, const char *image_filename, const char *image_type
) {
    FILE *image_file = fopen(image_filename, "rb");
    if (!image_file) {
        // Send 404 if image not found
        const char *not_found_response =
            "HTTP/1.1 404 Not Found\r\n"
            "Content-Length: 0\r\n"
            "Connection: close\r\n"
            "\r\n";
        send(client_sock, not_found_response, strlen(not_found_response), 0);
        return;
    }

    // Get image file size
    fseek(image_file, 0, SEEK_END);
    long image_size = ftell(image_file);
    fseek(image_file, 0, SEEK_SET);

    // Prepare HTTP response headers
    char header[BUFFER_SIZE];
    snprintf(header, sizeof(header),
             "HTTP/1.1 200 OK\r\n"
             "Content-Type: image/%s\r\n"
             "Content-Length: %ld\r\n"
             "Connection: close\r\n"
             "\r\n", image_type, image_size);

    // Send headers
    send(client_sock, header, strlen(header), 0);

    // Send image data
    char buffer[BUFFER_SIZE];
    size_t bytes_read;
    while ((bytes_read = fread(buffer, 1, sizeof(buffer), image_file)) > 0) {
        send(client_sock, buffer, bytes_read, 0);
    }

    fclose(image_file);
}

I32 main(void)
{
    I32 server_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (server_fd < 0)
    {
        printf("Error socket: %s", strerror(errno));
        goto exit;
    }

    I32 opt = 1;
    if (setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
    {
        printf("Error setsockopt: %s", strerror(errno));
        goto exit;
    }

    struct sockaddr_in server_addr;
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    if (bind(server_fd, (struct sockaddr*)&server_addr, sizeof(server_addr)) < 0)
    {
        printf("Error bind: %s", strerror(errno));
        goto exit;
    }

    if (listen(server_fd, BACKLOG) < 0)
    {
        printf("Error listen: %s", strerror(errno));
        goto exit;
    }

    struct sockaddr_in client_addr;
    socklen_t client_len = sizeof(client_addr);
    char buffer[BUFFER_SIZE];
    Http_Request request = {0};

    while (true)
    {
        I32 client_fd = accept(server_fd, (struct sockaddr*)&client_addr, &client_len);
        if (client_fd < 0) continue;

        char* client_ip = inet_ntoa(client_addr.sin_addr);
        mem_copy(request.ip, client_ip, sizeof(request.ip));

        int bytes_read = read(client_fd, buffer, BUFFER_SIZE - 1);
        if (bytes_read < 0)
        {
            close(client_fd);
            continue;
        }
        buffer[bytes_read] = '\0';
        http_parse_request(buffer, &request);
        // print_http_request(&request);

        http_send_image_file(client_fd, "img.png", "png");

        close(client_fd);
    }

exit:
    close(server_fd);
    return 0;
}
