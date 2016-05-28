#ifndef NLS_INTERFACE_HELPER_H
#define NLS_INTERFACE_HELPER_H
#include <ostream>

#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/nls.h"

#include "nls-network-helper-base.h"
namespace ns3{
class NlsInterfaceHelper:public NlsNetworkHelperBase
{
public:
  NlsInterfaceHelper ();
  virtual ~NlsInterfaceHelper ();

  /**
   * @brief Show Nls interfaces
   */
  void ShowConfig (void) const;

private:
  void PrintInterfacesInternal (const Ptr<Node> &node) const;
  void PrintNlsInfo (std::ostream &os, const Ptr<NetDevice> &dev, const Ptr<Nls> &nls) const;
//  void PrintIpv4Info (std::ostream &os, const Ptr<NetDevice> &dev, const Ptr<Ipv4> &ipv4) const;
  void PrintDeviceInfo (std::ostream &os, const Ptr<NetDevice> &dev) const;

};

}//namespace ns3

#endif
