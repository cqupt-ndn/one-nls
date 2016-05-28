#include "ns3/assert.h"
#include "ns3/log.h"

#include "nls-forwarding-protocol.h"
#include "ns3/ndn-stack-helper.h"
#include <iostream>
NS_LOG_COMPONENT_DEFINE ("nls::NlsForwardingProtocol");

namespace ns3 {
namespace nls {

NS_OBJECT_ENSURE_REGISTERED (NlsForwardingProtocol);

TypeId
NlsForwardingProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::nls::NlsForwardingProtocol")
      .SetParent<Object> ()
      .AddConstructor<NlsForwardingProtocol> ()
    ;
  return tid;
}

NlsForwardingProtocol::NlsForwardingProtocol()
{

}

NlsForwardingProtocol::~NlsForwardingProtocol()
{

}

void 
NlsForwardingProtocol::NotifyNewAggregate ()
{
if (m_nls == 0)
    {
      Ptr<Nls> nls = GetObject<Nls> ();
      if (nls != 0)
        {
          m_nls = nls;   
          Ptr<Node> node = this->GetObject<Node> ();
         
          ns3::ndn::StackHelper ndnHelper;
          ndnHelper.SetForwardingStrategy("ns3::nls::NlsForwardingStrategy");
          ndnHelper.Install(node);
        }
    
    }
  Object::NotifyNewAggregate ();
}

}//namespace nls
}//namespace ns3
