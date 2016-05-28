#ifndef NLS_TRACES_H
#define NLS_TRACES_H

#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/net-device.h"
#include "ns3/packet.h"
#include "ns3/traced-callback.h"

#include "nls-interface.h"

namespace ns3 {
namespace nls {
namespace traces {

/**
 * \ingroup mpls
 * @enum DropReason
 * @brief Reason why a packet has been dropped.
 */
enum DropReason
  {
    DROP_TTL_EXPIRED = 1,            /**< Packet TTL has expired */
    DROP_MTU_EXCEEDED,               /**< Packet size is greater than the device MTU */
    DROP_FTN_NOT_FOUND,              /**< An FTN matching the packet has not been found */
    DROP_ILM_NOT_FOUND,              /**< An ILM matching the label has not been found */
    DROP_NO_SUITABLE_NHLFE,          /**< An NHLFE suitable to process the packet has not been found */
    DROP_EMPTY_STACK,                /**< Empty label stack */
    DROP_BROADCAST_NOT_SUPPORTED,    /**< Received a broadcast packet */
    DROP_MULTICAST_NOT_SUPPORTED,    /**< Received a multicast packet */  
    DROP_INTERFACE_DOWN,             /**< Interface is down so can not send packet */
    DROP_SEND_FAILED,                /**< Sending the packet through the identified interface failed */
  };


typedef TracedCallback<const Ptr<const Packet>&, int32_t > RxTracedCallback;
typedef TracedCallback<const Ptr<const Packet>&, int32_t > TxTracedCallback;
typedef TracedCallback<const Ptr<const Packet>&, DropReason, int32_t > DropTracedCallback;

} // namespace traces
} // namespace nls
} // namespace ns3
#endif /* NLS_TRACES_H */
