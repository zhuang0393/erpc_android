/*
 * Generated by erpcgen 1.12.0 on Sat Jun 22 14:36:07 2024.
 *
 * AUTOGENERATED - DO NOT EDIT
 */


#if ERPC_ALLOCATION_POLICY == ERPC_ALLOCATION_POLICY_DYNAMIC
#include "erpc_port.h"
#endif
#include "erpc_codec.hpp"
#include "helloworld_client.hpp"
#include "erpc_manually_constructed.hpp"

#if 11200 != ERPC_VERSION_NUMBER
#error "The generated shim code version is different to the rest of eRPC code."
#endif

using namespace erpc;
using namespace std;
using namespace erpcShim;

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




helloworld_client::helloworld_client(ClientManager *manager)
:m_clientManager(manager)
{
}

helloworld_client::~helloworld_client()
{
}

// helloworld interface hello function client shim.
binary_t * helloworld_client::hello(const binary_t * txInput)
{
    erpc_status_t err = kErpcStatus_Success;

    binary_t * result = NULL;

#if ERPC_PRE_POST_ACTION
    pre_post_action_cb preCB = m_clientManager->getPreCB();
    if (preCB)
    {
        preCB();
    }
#endif

    // Get a new request.
    RequestContext request = m_clientManager->createRequest(false);

    // Encode the request.
    Codec * codec = request.getCodec();

    if (codec == NULL)
    {
        err = kErpcStatus_MemoryError;
    }
    else
    {
        codec->startWriteMessage(message_type_t::kInvocationMessage, m_serviceId, m_helloId, request.getSequence());

        write_binary_t_struct(codec, txInput);

        // Send message to server
        // Codec status is checked inside this function.
        m_clientManager->performRequest(request);

        result = (binary_t *) erpc_malloc(sizeof(binary_t));
        if (result == NULL)
        {
            codec->updateStatus(kErpcStatus_MemoryError);
        }
        read_binary_t_struct(codec, result);

        err = codec->getStatus();
    }

    // Dispose of the request.
    m_clientManager->releaseRequest(request);

    // Invoke error handler callback function
    m_clientManager->callErrorHandler(err, m_helloId);

#if ERPC_PRE_POST_ACTION
    pre_post_action_cb postCB = m_clientManager->getPostCB();
    if (postCB)
    {
        postCB();
    }
#endif


    return result;
}
