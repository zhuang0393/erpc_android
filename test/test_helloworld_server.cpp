#include <sys/time.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <erpc_server_setup.h>
#include "c_helloworld_server.h"

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    printf("erpc server start\n");
    erpc_transport_t transport = erpc_transport_tcp_init("127.0.0.1", 7861, true);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_server_t server = erpc_server_init(transport, message_buffer_factory);
    erpc_add_service_to_server(server, create_helloworld_service());
    while(1){
        erpc_server_run(server);
    }
    erpc_transport_tcp_close(transport);
    printf("erpc server end\n");
    return 0;
}