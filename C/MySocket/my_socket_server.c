#include <stdio.h>
#include <sys/socket.h>
#include <sys/select.h>
#include <errno.h>
#include <string.h>
#include <netinet/in.h>
#include <unistd.h>


#define TCP_PORT  4567
#define BUFFER_SIZE 120
#define MAX_CLIENTS 10

int main() {
    int status;
    struct sockaddr_in addr;
    char buffer[BUFFER_SIZE] = "\0";
    fd_set read_fds;
    int read_data;
    int opt = 1;
    int addrlen;
    int client_sockets[MAX_CLIENTS] = {0};
    int sd, max_sd, new_fd;
    int i;

    int fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd < 0) {
        printf("Error creating socket: %s(%d)\n", strerror(errno), errno);
        return -1;
    }

    status = setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));
    if (status < 0) {
        printf("Error setting socket option: %s(%d)\n", strerror(errno), errno);
        close(fd);
        return -1;
    }

    memset(&addr, 0, sizeof(struct sockaddr_in));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(TCP_PORT);
    addr.sin_addr.s_addr = INADDR_ANY;

    status = bind(fd, (struct sockaddr*)&addr, sizeof(addr));
    if (status < 0) {
        printf("Error binding to socket: %s(%d)\n", strerror(errno), errno);
        close(fd);
        return -1;
    }

    status = listen(fd, 5);
    if (status < 0) {
        printf("Error binding to socket: %s(%d)\n", strerror(errno), errno);
        close(fd);
        return -1;
    }

    addrlen = sizeof(addr);

    while (1) {
        FD_ZERO(&read_fds);
        // set server socket in the list
        FD_SET(fd, &read_fds);
        max_sd = fd;

        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (sd > 0) {
                FD_SET(sd, &read_fds);
            }

            if (sd > max_sd) {
                max_sd = sd;
            }
        }

        // printf("max_sd %d fd %d\n", max_sd, fd);
        status = select(max_sd + 1, &read_fds, NULL, NULL, NULL);
        if ((status < 0) && (errno != EINTR)) {
            printf("Socket select error: %s(%d)\n", strerror(errno), errno);
        }

        if (FD_ISSET(fd, &read_fds)) {
            new_fd = accept(fd, (struct sockaddr*)&addr,
                (socklen_t *)&addrlen);
            if (new_fd < 0) {
                printf("Error accepting connection to socket: %s(%d)\n",
                    strerror(errno), errno);
                close(fd);
                return -1;
            }

            for (i = 0; i < MAX_CLIENTS; i++) {
                if (client_sockets[i] == 0) {
                    client_sockets[i] = new_fd;
                    break;
                }
            }
        }

        for (i = 0; i < MAX_CLIENTS; i++) {
            sd = client_sockets[i];
            if (!FD_ISSET(sd, &read_fds)) {
                continue;
            }

            read_data = read(sd, buffer, BUFFER_SIZE);
            if (read_data == 0) {
                close(sd);
                client_sockets[i] = 0;
                FD_CLR(sd, &read_fds);
            } else {
                buffer[read_data] = '\0';
                printf("Read: %s\n", buffer);
            }
        }
    }

    return 0;
}