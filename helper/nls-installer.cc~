#include "ns3/assert.h"
#include "ns3/log.h"
//#include "ns3/object.h"
//#include "ns3/names.h"
//#include "ns3/ipv4.h"
#include "ns3/packet-socket-factory.h"
#include "ns3/config.h"
#include "ns3/simulator.h"
#include "ns3/string.h"
#include "ns3/node.h"
#include "ns3/nls-node.h"
#include "ns3/node-list.h"
#include "ns3/core-config.h"

/*#include "ns3/arp-l3-protocol.h"
#include "ns3/ipv4-list-routing-helper.h"
#include "ns3/ipv4-static-routing-helper.h"
#include "ns3/ipv4-global-routing-helper.h"
#include "ns3/ipv6-list-routing-helper.h"
#include "ns3/ipv6-static-routing-helper.h"
*/
#include "ns3/nls-protocol.h"
#include "ns3/nls-installer.h"
#include <ostream>

#include "ns3/ndn-l3-protocol.h"
#include "ns3/ndn-forwarding-strategy.h"
#include "ns3/ndn-fib.h"
#include "ns3/ndn-pit.h"
#include "ns3/ndn-name.h"
#include "ns3/ndn-content-store.h"

#include "ns3/nls-forwarding-protocol.h"
namespace ns3
{
NlsInstaller::NlsInstaller()
{

}

NlsInstaller::~NlsInstaller()
{

}

NlsInstaller::NlsInstaller (const NlsInstaller &o)
{

  m_networkNodes = o.m_networkNodes;
}

NlsInstaller &
NlsInstaller::operator = (const NlsInstaller &o)
{
  if (this == &o)
    {
      return *this;
    }
  m_networkNodes = o.m_networkNodes;
  return *this;
}

const NodeContainer& 
NlsInstaller::GetNetworkNodes (void) const
{
  return m_networkNodes;
}

void
NlsInstaller::CreateAndAggregateObjectFromTypeId (Ptr<NlsNode> node, const std::string typeId)
{
  ObjectFactory factory;
  factory.SetTypeId (typeId);
  Ptr<Object> protocol = factory.Create <Object> ();
  node->AggregateObject (protocol);
}

//创建并安装节点
NodeContainer 
NlsInstaller::CreateAndInstall (uint32_t count)
{
 NS_ASSERT_MSG (count > 0, "Invalid nodes count");
  NodeContainer c;
  for (uint32_t i = 0; i < count; ++i)
    {
      Ptr<NlsNode> node = CreateObject<NlsNode> ();
      InstallInternal (node);
      c.Add (node);
    }
  return c;
}

void 
NlsInstaller::InstallInternal (Ptr<NlsNode> node)
{
NS_ASSERT_MSG (node != 0, "Possible you use Node instead of NlsNode");

  if (node->GetObject<NlsProtocol> () != 0)
    {
      NS_FATAL_ERROR ("NlsInstaller::Install (): Aggregating "
                      "an Nls to a node with an existing Nls object");
      return;
    }


  CreateAndAggregateObjectFromTypeId (node, "ns3::nls::NlsProtocol");
    
  m_networkNodes.Add (node);

}
}//namespace ns3
