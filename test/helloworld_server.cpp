/*
 * Generated by erpcgen 1.12.0 on Sat Jun 22 14:36:07 2024.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#include "helloworld_server.hpp"
#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
#include <new>
#include "erpc_port.h"
#endif
#include "erpc_manually_constructed.hpp"

#if 11200 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;
using namespace erpcShim;

#if ERPC_NESTED_CALLS_DETECTION
extern bool nestingDetection;
#endif


//! @brief Function to read struct binary_t
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data);


// Read struct binary_t function implementation
static void read_binary_t_struct(erpc::Codec * codec, binary_t * data)
{
    if(NULL == data)
    {
        return;
    }

    uint8_t * data_local;
    codec->readBinary(data->dataLength, &data_local);
    if (data->dataLength > 0)
    {
    data->data = (uint8_t *) erpc_malloc(data->dataLength * sizeof(uint8_t));
        if (data->data == NULL)
        {
            codec->updateStatus(kErpcStatus_MemoryError);
        }
        else
        {
            memcpy(data->data, data_local, data->dataLength);
        }
    }
    else
    {
        data->data = NULL;
    }
}


//! @brief Function to write struct binary_t
static void write_binary_t_struct(erpc::Codec * codec, const binary_t * data);


// Write struct binary_t function implementation
static void write_binary_t_struct(erpc::Codec * codec, const binary_t * data)
{
    if(NULL == data)
    {
        return;
    }

    codec->writeBinary(data->dataLength, data->data);
}


//! @brief Function to free space allocated inside struct binary_t
static void free_binary_t_struct(binary_t * data);


// Free space allocated inside struct binary_t function implementation
static void free_binary_t_struct(binary_t * data)
{
    erpc_free(data->data);
}



helloworld_service::helloworld_service(helloworld_interface *_helloworld_interface)
    : erpc::Service(helloworld_interface::m_serviceId)
    , m_handler(_helloworld_interface)
{
}

helloworld_service::~helloworld_service()
{
}

// return service interface handler.
helloworld_interface* helloworld_service::getHandler(void)
{
    return m_handler;
}

// Call the correct server shim based on method unique ID.
erpc_status_t helloworld_service::handleInvocation(uint32_t methodId, uint32_t sequence, Codec * codec, MessageBufferFactory *messageFactory, Transport * transport)
{
    erpc_status_t erpcStatus;
    printf("helloworld_service::handleInvocation() methodId: %d\n", methodId);
    switch (methodId)
    {
        case helloworld_interface::m_helloId:
        {
            erpcStatus = hello_shim(codec, messageFactory, transport, sequence);
            break;
        }

        default:
        {
            erpcStatus = kErpcStatus_InvalidArgument;
            break;
        }
    }

    return erpcStatus;
}

// Server shim for hello of helloworld interface.
erpc_status_t helloworld_service::hello_shim(Codec * codec, MessageBufferFactory *messageFactory, Transport * transport, uint32_t sequence)
{
    erpc_status_t err = kErpcStatus_Success;
    printf("helloworld_service::hello_shim()\n");
    binary_t *txInput = NULL;
    txInput = (binary_t *) erpc_malloc(sizeof(binary_t));
    if (txInput == NULL)
    {
        codec->updateStatus(kErpcStatus_MemoryError);
    }
    binary_t * result = NULL;

    // startReadMessage() was already called before this shim was invoked.

    read_binary_t_struct(codec, txInput);

    err = codec->getStatus();
    if (err == kErpcStatus_Success)
    {
        // Invoke the actual served function.
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = true;
#endif
        result = m_handler->hello(txInput);
#if ERPC_NESTED_CALLS_DETECTION
        nestingDetection = false;
#endif

        // preparing MessageBuffer for serializing data
        err = messageFactory->prepareServerBufferForSend(codec->getBufferRef(), transport->reserveHeaderSize());
    }

    if (err == kErpcStatus_Success)
    {
        // preparing codec for serializing data
        codec->reset(transport->reserveHeaderSize());

        // Build response message.
        codec->startWriteMessage(message_type_t::kReplyMessage, helloworld_interface::m_serviceId, helloworld_interface::m_helloId, sequence);

        write_binary_t_struct(codec, result);

        err = codec->getStatus();
    }

    if (txInput)
    {
        free_binary_t_struct(txInput);
    }
    erpc_free(txInput);

    if (result)
    {
        free_binary_t_struct(result);
    }
    erpc_free(result);

    return err;
}
