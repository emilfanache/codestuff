#include <stdio.h>
#include <sys/socket.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define TCP_PORT  4567
#define BUFFER_SIZE 120

int main() {
    int status;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE] = "\0";

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printf("Error creating socket: %s(%d)\n", strerror(errno), errno);
        return -1;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_PORT);
    inet_aton("127.0.0.1", &addr.sin_addr);

    status = connect(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (status < 0) {
        printf("Error connecting to socket: %s(%d)\n", strerror(errno), errno);
        close(fd);
        return -1;
    }

    printf("Conected to server, ready to send data...\n");
    snprintf(buffer, BUFFER_SIZE, "This is a message placeholder");
    status = send(fd, buffer, strlen(buffer), 0);
    if (status < 0) {
        printf("Error sending message: %s(%d)\n", strerror(errno), errno);
        close(fd);
        return -1;
    }

    close(fd);
    return 0;
}