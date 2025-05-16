#ifndef __PORT_CANARD_H__
#define __PORT_CANARD_H__

#include <canard.h>

int port_canard_init(size_t mtu_bytes, CanardNodeID node_id);
int accept_canard_frame(const CanardFrame *txf);
int publish_msg(CanardMicrosecond timestampUsec, CanardTransferKind transferKind, CanardPortID portID, CanardNodeID remoteNodeID, size_t payloadSize, const void *payload);

CanardInstance *port_canard_get_instance(void);

#endif // __PORT_CANARD_H__


