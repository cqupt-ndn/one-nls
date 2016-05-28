#include <iomanip>

#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/string.h"
#include "ns3/nls-interface.h"

#include "ns3/mac48-address.h"

#include "nls-interface-helper.h"

namespace ns3{

NlsInterfaceHelper::NlsInterfaceHelper()
{

}

NlsInterfaceHelper::~NlsInterfaceHelper()
{

}

void 
NlsInterfaceHelper::ShowConfig() const
{
   const NodeContainer& nodes = GetNetworkNodes ();
   for (NodeContainer::Iterator node = nodes.Begin (), end = nodes.End (); node != end; ++node)
    {
      PrintInterfacesInternal (*node);
    }
}

//打印接口信息
void 
NlsInterfaceHelper::PrintInterfacesInternal (const Ptr<Node> &node) const
{
 std::ostream &os = *(GetOutputStream ()->GetStream ());
 Ptr<Nls> nls = node->GetObject<Nls> ();
 os << "Node " << node->GetId () << " interfaces:" << std::endl;

 for (uint32_t i = 0, c = node->GetNDevices (); i < c; ++i)
    {
      Ptr<NetDevice> dev = node->GetDevice (i);
      Address hwaddr = dev->GetAddress ();

      os << std::setiosflags(std::ios::left) << "dev"  << std::setw (5) << i << " ";
      os << std::resetiosflags(std::ios::left)
         << "Type " << dev->GetInstanceTypeId ().GetName () << "  "
         << "HWaddr ";


      if (Mac48Address::IsMatchingType (hwaddr))
        {
          os << Mac48Address::ConvertFrom (hwaddr);
        }
      else
        {
          os << hwaddr;
        }
        
      os << std::endl;
      if (nls != 0)
        {
          PrintNlsInfo (os, dev, nls);
        }

      PrintDeviceInfo (os, dev);
      
      os << std::endl;
    }

}

void 
NlsInterfaceHelper::PrintNlsInfo (std::ostream &os, const Ptr<NetDevice> &dev, const Ptr<Nls> &nls) const
{
 Ptr<nls::Interface> iface = nls->GetInterfaceForDevice (dev);
  if (iface != 0) 
    {
      os << std::setw (9) << " " 
         << "nls:" << (iface->IsUp () ? "enabled" : "disabled") << "  "
         << "Interface:" << iface->GetIfIndex ()
         << std::endl;
    }  
}
void
NlsInterfaceHelper::PrintDeviceInfo (std::ostream &os, const Ptr<NetDevice> &dev) const
{
  os << std::setw (9) << " " 
     << (dev->IsLinkUp () ? "UP" : "DOWN");

  if (dev->IsPointToPoint ())
    {
      os << " PPP";
    }

  if (dev->IsBridge ())
    {
      os << " BRIDGE";
    }

  if (dev->IsMulticast ())
    {
      os << " MULTICAST";
    }

  if (dev->IsBroadcast ())
    {
      os << " BROADCAST";
    }
    
  if (dev->NeedsArp ())
    {
      os << " ARP";
    }

  os << "  MTU:" << dev->GetMtu ();
  os << std::endl;
}

}//namespace ns3
