#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <string>
#include <erpc_client_setup.h>
#include <erpc_port.h>
#include "c_helloworld_client.h"

static void free_binary_t_struct(binary_t *data)
{
    if (data->data) {
        erpc_free(data->data);
    }
}

int main(int argc, char *argv[])
{
    (void)argc;
    (void)argv;
    printf("erpc client start\n");
    erpc_transport_t transport = erpc_transport_tcp_init("127.0.0.1", 7861, false);
    erpc_mbf_t message_buffer_factory = erpc_mbf_dynamic_init();
    erpc_client_t client = erpc_client_init(transport, message_buffer_factory);
    inithelloworld_client(client);
    std::string str1 = "hello, erpc server!";
    str1 += " my pid:";
    str1 += std::to_string(getpid());
    str1 += " \0";
    const char *msg = str1.c_str();

    binary_t b = {(uint8_t *)msg, (uint32_t)strlen(msg)};
    printf("Request: %s\n", msg);
    while (1) {
        sleep(1);
        binary_t *resp = hello(&b);
        if (resp != NULL) {
            char *buf = (char *)malloc(resp->dataLength + 1);
            strncpy(buf, (const char *)resp->data, resp->dataLength);
            buf[resp->dataLength] = '\0';
            printf("Respond: %s\n", buf);
            free_binary_t_struct(resp);
            free(buf);
        }
    }

    deinithelloworld_client();
    erpc_client_deinit(client);
    erpc_transport_tcp_close(transport);
    printf("erpc client end\n");
    return 0;
}