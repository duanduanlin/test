#include <stdint.h>
#include <canard.h>
#include <o1heap.h>
// #include <ua_def.h>
#include "../cfg.h"
#include "port_canard.h"

#define LOG_TAG "port_uavcan"
#include <elog.h>

#include <board.h>
#define DELAY_MS(ms) HAL_Delay(ms)

#define O1HEAP_SIZE CFG_O1HEAP_MEMORY_SIZE

static uint8_t o1heapbytes[O1HEAP_SIZE] __attribute__((aligned(O1HEAP_ALIGNMENT)));
static O1HeapInstance *g_o1heap_ins = NULL;

static CanardInstance g_canard_ins = {0};

static void *__memAllocate(CanardInstance *const ins, const size_t amount)
{
    (void)ins;
    return o1heapAllocate(g_o1heap_ins, amount);
}

static void __memFree(CanardInstance *const ins, void *const pointer)
{
    (void)ins;
    o1heapFree(g_o1heap_ins, pointer);
}

extern void ecb_process_received_canard_transfer(CanardTransfer *transfer);
extern int canard_subscription_init(CanardInstance *ins);

CanardInstance *port_canard_get_instance(void)
{
    return &g_canard_ins;
}

static int __send(const CanardFrame *txf)
{
    extern int can_send_msg(uint32_t id, const uint8_t *data, uint8_t len);
    return can_send_msg(txf->extended_can_id, txf->payload, txf->payload_size);
}

int publish_msg(CanardMicrosecond timestampUsec, CanardTransferKind transferKind, CanardPortID portID, CanardNodeID remoteNodeID, size_t payloadSize, const void *payload)
{
    static uint8_t my_message_transfer_id; // Must be static or heap-allocated to retain state between calls.
    int sta;
    CanardInstance *ins = &g_canard_ins;
    const CanardTransfer transfer = {
        .timestamp_usec = timestampUsec, // Zero if transmission deadline is not limited.
        .priority = CanardPriorityExceptional,
        .transfer_kind = transferKind,
        .port_id = portID,                        // This is the subject-ID.
        .remote_node_id = remoteNodeID, // Messages cannot be unicast, so use UNSET.
        .transfer_id = my_message_transfer_id,
        .payload_size = payloadSize,
        .payload = payload,
    };
    ++my_message_transfer_id; // The transfer-ID shall be incremented after every transmission on this subject.
    int32_t result = canardTxPush(ins, &transfer);
    if (result < 0)
    {
        // An error has occurred: either an argument is invalid or we've ran out of memory.
        // It is possible to statically prove that an out-of-memory will never occur for a given application if the
        // heap is sized correctly; for background, refer to the Robson's Proof and the documentation for O1Heap.
        log_d("Fatal error (w");
        return 1;
    }
    for (const CanardFrame *txf = NULL; (txf = canardTxPeek(ins)) != NULL;) // Look at the top of the TX queue.
    {
        do {
            sta =  __send(txf);
            if (sta != 0) {
                DELAY_MS(1);
            }
        }while(sta != 0);

        canardTxPop(ins);                         // Remove the frame from the queue after it's transmitted.
        ins->memory_free(ins, (CanardFrame *)txf); // Deallocate the dynamic memory afterwards.

    }

    return 0;
}

//Process received frames
int accept_canard_frame(const CanardFrame *txf)
{
    CanardInstance *ins = &g_canard_ins;
    CanardTransfer transfer;
    int8_t result;
    result = canardRxAccept(ins,
                            txf, // The CAN frame received from the bus.
                            0,   // If the transport is not redundant, use 0.
                            &transfer);
    if (result < 0)
    {
        // An error has occurred: either an argument is invalid or we've ran out of memory.
        // It is possible to statically prove that an out-of-memory will never occur for a given application if
        // the heap is sized correctly; for background, refer to the Robson's Proof and the documentation for O1Heap.
        // Reception of an invalid frame is NOT an error.
        log_d("Fatal error (r");
        return 1;
    }
    else if (result == 1)
    {
        // A transfer has been received, process it.
        ecb_process_received_canard_transfer(&transfer);
        ins->memory_free(ins, (void *)transfer.payload); // Deallocate the dynamic memory afterwards.
    }
    else
    {
        // Nothing to do.
        // The received frame is either invalid or it's a non-last frame of a multi-frame transfer.
        // Reception of an invalid frame is NOT reported as an error because it is not an error.
        
        // log_i("nothing");
    }

    return 0;
}

int port_canard_init(size_t mtu_bytes, CanardNodeID node_id)
{
    int status = 0;

    g_o1heap_ins = o1heapInit(o1heapbytes, O1HEAP_SIZE, NULL, NULL);
    if (NULL == g_o1heap_ins)
    {
        log_e("o1heap init failed");
        return 1;
    }
    else {
        log_d("o1heap init success");
    }

    g_canard_ins.memory_allocate = __memAllocate;
    g_canard_ins.memory_free = __memFree;

    g_canard_ins.mtu_bytes = mtu_bytes;     // Defaults to 64 (CAN FD); here we select Classic CAN.
    g_canard_ins.node_id = node_id;         // Defaults to anonymous; can be set up later at any point.

    canard_subscription_init(&g_canard_ins);

    return status;
}

void port_canard_print_o1heap_info(void)
{
    O1HeapDiagnostics info = o1heapGetDiagnostics(g_o1heap_ins);
    log_i("total-memory:%ld", info.capacity);
    log_i("used-fragment:%ld", info.allocated);
    log_i("peak_allocated:%ld", info.peak_allocated);
    log_i("peak_request_size:%ld", info.peak_request_size);
    log_i("oom_count:%ld", info.oom_count);
}

CanardInstance get_cancard_ins(void)
{
    return g_canard_ins;
}
