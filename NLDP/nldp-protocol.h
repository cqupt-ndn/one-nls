#ifndef NLDP_PROTOCOL_H
#define NLDP_PROTOCOL_H
#include "ns3/object.h"
#include "ns3/event-id.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/nls-fec.h"
#include "ns3/nls-protocol.h"
#include <list>
#include "nldp-pdu.h"
#include "nlslibEntry.h"

namespace ns3{
namespace nldp{
using namespace nls;


class NldpProtocol : public Object
{
public:
   static const uint16_t HELLO_MESSAGE;
   static TypeId GetTypeId(void);
   NldpProtocol();
   virtual ~NldpProtocol();
   void SetRouterId (uint32_t routerId);
   uint32_t GetRouterId() const;
   void SetKeepAliveTime(uint16_t time);
   uint16_t GetKeepAliveTime() const;
   void SetHelloInterval(uint16_t interval);
   uint16_t GetHelloInterval(void) const;
   void SetMaxPduLength (uint16_t length);
   uint16_t GetMaxPduLength (void) const;
 /**
   * \param ifIndex net device index
   * \returns ldp session if exists
   */
  Ptr<NlsLibEntry> Bind (LspType type,uint32_t inLabel, Ptr<Interface> inIfIndex, uint32_t outLabel, Ptr<Interface> outIfIndex);
  Ptr<NlsLibEntry> Bind (LspType type,const NameFec &fec, uint32_t outLabel, Ptr<Interface> outIfIndex);
  void Unbind (Ptr<NlsLibEntry> entry);
protected:
  virtual void NotifyNewAggregate (void);
  virtual void DoDispose (void);

private:
  std::list< Ptr<NlsLibEntry> > libList;
  void Initialize (void);
  void SetNode (Ptr<Node> node);
  //void SetMpls (Ptr<MplsRoutingProtocol> mpls);
  void CancelEvents (void);
  //这个函数需要做进一步的参数修改
  //Ptr<NldpPeer> FindPeer (const Address &address) const;

  //bool HandleConnectionRequest (Ptr<Socket> socket, const Address& from) const;
  //void HandleConnectionAccept (Ptr<Socket> socket, const Address& from) const;
  //void HandlePeerMessage (Ptr<NldpPeer> peer, Ptr<const Message> message);
  
  //void HandlePeerClose (Ptr<const LdpPeer> peer);

  Ptr<Message> CreateHelloMessage (void) const;
  void ReceiveHelloMessage ();
  void SendHelloMessage ();

  Ptr<Node> m_node;
  Ptr<PduReader> m_reader;
  uint32_t m_routerId;
 
  uint16_t m_helloInterval;
  uint16_t m_keepAliveTime;
  uint16_t m_maxPduLength;
  EventId m_helloEvent;

  //TracedCallback<Ptr<const LdpPeer>, Ptr<const Packet>, const Address &> m_rxTrace;
  //TracedCallback<Ptr<const LdpPeer>, Ptr<const Packet>, const Address &> m_txTrace;
  //friend class NlsProtocol;
  
};
}//namespace nldp
}//namespace ns3
#endif
