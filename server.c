#include <asm/types.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <sys/socket.h>
#include <linux/netlink.h>
#include <unistd.h>

#include "server_addr.h"

#define NETLINK_USER 31

#define MAX_PAYLOAD 1024 /* maximum payload size*/
struct sockaddr_nl src_addr, dest_addr;
struct nlmsghdr *nlh = NULL;
struct iovec iov;
int sock_fd;
struct msghdr msg;

int main()
{
    sock_fd = socket(AF_NETLINK, SOCK_RAW, NETLINK_USERSOCK);
    
    if (sock_fd < 0) {
        perror("sock_fd < 0");
        return -1;
    }

    memset(&src_addr, 0, sizeof(src_addr));
    src_addr.nl_family = AF_NETLINK;
    src_addr.nl_pid = SERVER_ADDR; /* I'm the server */

    int result = bind(sock_fd, (struct sockaddr *)&src_addr, sizeof(src_addr));
    if (result < 0) {
        perror("bind < 0");
        return -1;
    }

    memset(&dest_addr, 0, sizeof(dest_addr));
    
    dest_addr.nl_family = AF_NETLINK;
    dest_addr.nl_pid = 0; // will be filled with other process's PID
    dest_addr.nl_groups = 0; /* unicast */

    nlh = (struct nlmsghdr *)malloc(NLMSG_SPACE(MAX_PAYLOAD));
    memset(nlh, 0, NLMSG_SPACE(MAX_PAYLOAD));
    nlh->nlmsg_len = NLMSG_SPACE(MAX_PAYLOAD);
    nlh->nlmsg_pid = getpid();
    nlh->nlmsg_flags = 0;

    strcpy(NLMSG_DATA(nlh), "Hello");

    iov.iov_base = (void *)nlh;
    iov.iov_len = nlh->nlmsg_len;
    msg.msg_name = (void *)&dest_addr;
    msg.msg_namelen = sizeof(dest_addr);
    msg.msg_iov = &iov;
    msg.msg_iovlen = 1;
    
    //result = listen(sock_fd, 10);
    //if (result < 0) {
    //    perror("listen < 0");
    //    return -1;
    //}

    while (1) {

    printf("Waiting for message from process\n");

    //result = accept(sock_fd, NULL, NULL);
    //if (result < 0) {
    //    perror("couldn't accept");
    //   return -1;
    //}

    /* Read message from kernel */
    recvmsg(sock_fd, &msg, 0);
    printf("Received message payload: %s\n", NLMSG_DATA(nlh));
    }
    close(sock_fd);
}
