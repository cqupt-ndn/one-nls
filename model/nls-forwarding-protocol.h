#ifndef NLS_FORWARDING_PROTOCOL_H
#define NLS_FORWARDING_PROTOCOL_H

#include "nls-forwarding-strategy.h"
#include "ns3/nls.h"
#include "ns3/object-factory.h"
#include "ns3/ndn-l3-protocol.h"

namespace ns3{
class Nls;
namespace nls{
class NlsForwardingStrategy;

class NlsForwardingProtocol:public Object
{
public:
   static TypeId GetTypeId (void);
   NlsForwardingProtocol();
   virtual ~NlsForwardingProtocol();
  
protected:

   void NotifyNewAggregate ();

private:
    Ptr<NlsForwardingStrategy> m_nlsForwardingStrategy;
    Ptr<Nls> m_nls;
    ObjectFactory m_strategyFactory;
    ObjectFactory m_ndnFactory;
};


}//namespace nls
}//namespace ns3

#endif

