#ifndef NLDP_TRANSPORT_H
#define NLDP_TRANSPORT_H
#include "nldp-nodehelp.h"
#include "nldp-protocol.h"
#include "ns3/nls-installer.h"
#include "ns3/ndn-interest.h"
#include "ns3/net-device.h"
#include "ns3/nls-protocol.h"
#include "ns3/log.h"
#include <set>
namespace ns3{
namespace nldp{
class NldpTransport
{
 public:
   NldpTransport();
  
   virtual ~NldpTransport();
   //主要方法，用来建立传输用的LSP
   void RealTransport(string& inputfile,int beginnode,int endnode);
   static Ptr<Node> GetEngressNode();
   static Ptr<Node> GetIngressNode();
   Ptr<Node> GetProducerNode();
   Ptr<Node> GetConsumerNode();
   Ptr<NetDevice> GetDeviceOne();
   static Ptr<NetDevice> GetDeviceTwo();
   Address GetNldpTransportAddress();
   static std::set< Ptr<NetDevice> > GetSet();
   static std::map<int,NodeHelp::Impl> GetNetMap();
 //接受到兴趣包了怎么办
   void ReceiveInterest(const Ptr<ns3::ndn::Interest> &interest);
   static stack<int> GetNeedStack();
 private:
  static Ptr<Node> m_engress;//作为nls出节点
  static Ptr<Node> m_ingress;//作为nls入节点
  Ptr<Node> m_consumer;
  Ptr<Node> m_producer;
  Ptr<NetDevice> m_netDeviceOne;
  static Ptr<NetDevice> m_netDeviceTwo; 
  static std::set< Ptr<NetDevice> > m_set;
  static std::map<int,NodeHelp::Impl> netmap;
  static stack<int> lstack;
  Address m_address; 
  friend class NlsProtocol;
};
}//namespace nldp
}//namespace ns3
#endif
