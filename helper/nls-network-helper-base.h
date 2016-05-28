#ifndef NLS_NETWORK_HELPER_BASE_H
#define NLS_NETWORK_HELPER_BASE_H

#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/node-container.h"
#include "ns3/output-stream-wrapper.h"

namespace ns3
{
class NlsNetworkHelperBase
{
public:
  virtual ~NlsNetworkHelperBase (void);

  virtual const NodeContainer& GetNetworkNodes (void) const = 0;
  virtual const Ptr<OutputStreamWrapper>& GetOutputStream (void) const = 0;
};


}//namespace ns3


#endif
