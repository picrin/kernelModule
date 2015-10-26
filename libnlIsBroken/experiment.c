#include <stdlib.h>
#include <stdio.h>
#include <netlink/socket.h>
//#include <netlink/netlink.h>
//#include <netlink/genl/genl.h>

int main() {
  struct nl_sock* my_socket = nl_socket_alloc();
  nl_socket_free(my_socket);
}
