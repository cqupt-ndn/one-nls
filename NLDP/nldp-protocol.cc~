#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/simulator.h"
#include "ns3/uinteger.h"

#include "nldp-protocol.h"
#include "nldp-common-hello-params-tlv.h"

NS_LOG_COMPONENT_DEFINE ("NldpProtocol");

namespace ns3{
namespace nldp{

NS_OBJECT_ENSURE_REGISTERED (NldpProtocol);
const uint16_t NldpProtocol::HELLO_MESSAGE = 0x0100;
TypeId
NldpProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::nldp::NldpProtocol")
    .SetParent<Object> ()
    .AddConstructor<NldpProtocol> ()
    .AddAttribute ("HelloInterval", "NlDP Hello Message interval",
                   UintegerValue (15),
                   MakeUintegerAccessor (&NldpProtocol::m_helloInterval),
                   MakeUintegerChecker<uint16_t> (1, 32767))
    .AddAttribute ("MaxPduLength", "Maximum PDU length",
                   UintegerValue (512),
                   MakeUintegerAccessor (&NldpProtocol::m_maxPduLength),
                   MakeUintegerChecker<uint16_t> (256, 4096))
    .AddAttribute ("KeepAliveTime", "NLDP session KeepAlive time",
                   UintegerValue (20),
                   MakeUintegerAccessor (&NldpProtocol::m_keepAliveTime),
                   MakeUintegerChecker<uint16_t> (1))
    ;
  return tid;
}

NldpProtocol::NldpProtocol()
:m_node(0),
 m_reader(0),
 m_routerId(0)
{
  NS_LOG_FUNCTION_NOARGS ();
  Simulator::Schedule (Seconds (0), &NldpProtocol::Initialize, this);
}

NldpProtocol::~NldpProtocol()
{
  NS_LOG_FUNCTION_NOARGS ();
}
void
NldpProtocol::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  
  m_node = 0;
  m_reader = 0;

  Object::DoDispose ();
}


void
NldpProtocol::NotifyNewAggregate ()
{
  if (m_node == 0)
    {
      Ptr<Node> node = GetObject<Node> ();
      if (node != 0)
        {
          this->SetNode (node);
        }
    }
/*
  if (m_mpls == 0)
    {
      Ptr<MplsRoutingProtocol> mpls = GetObject<MplsRoutingProtocol> ();
      if (mpls != 0)
        {
          this->SetMpls (mpls);
        }
    }
*/
  Object::NotifyNewAggregate ();
}

uint32_t
NldpProtocol::GetRouterId (void) const
{
  return m_routerId;
}
void 
NldpProtocol::SetRouterId (uint32_t routerId)
{
  m_routerId = routerId;
}
void
NldpProtocol::SetKeepAliveTime (uint16_t time)
{
  NS_LOG_FUNCTION (this << time);
  NS_ASSERT (time > 0);
  m_keepAliveTime = time;
}

uint16_t
NldpProtocol::GetKeepAliveTime (void) const
{
  return m_keepAliveTime;
}

void
NldpProtocol::SetHelloInterval (uint16_t interval)
{
  NS_LOG_FUNCTION (this << interval);
  NS_ASSERT (interval > 0);
  m_helloInterval = interval;
}

uint16_t
NldpProtocol::GetHelloInterval (void) const
{
  return m_helloInterval;
}

void
NldpProtocol::SetMaxPduLength (uint16_t length)
{
  NS_LOG_FUNCTION (this << length);
  NS_ASSERT (length >= 256 && length <= 4096);
  m_maxPduLength = length;
}

uint16_t
NldpProtocol::GetMaxPduLength (void) const
{
  return m_maxPduLength;
}
/*
Ptr<LdpPeer>
NldpProtocol::GetPeerForDeviceIfIndex (int32_t ifIndex) const
{
  for (PeerList::const_iterator i = m_peers.begin (); i != m_peers.end (); ++i)
    {
      if ((*i)->GetIfIndex () == ifIndex)
        {
          return *i;
        }
    }

  return 0;
}
*/
Ptr<NlsLibEntry>
NldpProtocol::Bind (LspType type,uint32_t inLabel, Ptr<Interface> inIfIndex, uint32_t outLabel, Ptr<Interface> outIfIndex)
{
  Ptr<NlsLibEntry> entry = Create<NlsLibEntry> ();
  entry->SetInIfIndex (inIfIndex);
  entry->SetInLabel (inLabel);
  entry->SetOutIfIndex (outIfIndex);
  entry->SetOutLabel (outLabel);
  entry->SetLspType (type);

//Lib条目添加到LIB表中
 libList.push_back(entry);
 return entry;
}

Ptr<NlsLibEntry>
NldpProtocol::Bind (LspType type,const NameFec &fec, uint32_t outLabel, Ptr<Interface> outIfIndex)
{
  Ptr<NlsLibEntry> entry = Create<NlsLibEntry> ();
  //entry->SetFec (fec);暂时不调用这个方法
  entry->SetOutIfIndex (outIfIndex);
  //entry->SetOperation (NlsLibEntry::PUSH);
  entry->SetOutLabel (outLabel);
  entry->SetLspType (type);

  libList.push_back(entry);
  return entry;
}
//不再绑定的标签则删除
void
NldpProtocol::Unbind (Ptr<NlsLibEntry> entry)
{
 // libList.erase ();
 //这里需要重新设计
}

void
NldpProtocol::Initialize ()
{
  NS_LOG_FUNCTION (this);

  NS_ASSERT_MSG (m_node != 0, "NldpProtocol::Initialize (): Bad node");
  CancelEvents ();
  m_reader = Create<PduReader> ();
//初始化的时候，读取节点上的所有的NetDevice,然后向这些节点发送Hello消息，来得到输出的Interface;routId大的先发Hello消息。依次发送吧，互相对着发送，不容易操作；
  m_helloEvent = Simulator::Schedule (Seconds (0.0), &NldpProtocol::SendHelloMessage, this);
}

void
NldpProtocol::CancelEvents (void)
{
  NS_LOG_FUNCTION (this);

  Simulator::Cancel (m_helloEvent);
}
//这里面的node是否考虑换成NlsNode
void
NldpProtocol::SetNode (Ptr<Node> node)
{
  NS_LOG_FUNCTION (node);
  m_node = node;
}
//设置NLS
/*
void
NldpProtocol::SetMpls (Ptr<MplsRoutingProtocol> mpls)
{
  NS_LOG_FUNCTION (mpls);
  m_mpls = mpls;
}
*/

Ptr<Message>
NldpProtocol::CreateHelloMessage () const
{
  Ptr<CommonHelloParamsTLV> params = Create<CommonHelloParamsTLV> ();
  params->SetHoldTime (m_helloInterval * 3 / 2); // request hello adjacency hold time = 3/2 * helloInterval
  Ptr<Message> message = Create<Message> (HELLO_MESSAGE);
  message->AddValue (params);
  return message;
}


//向对等方发送LDP消息,怎样设计实现类似兴趣包发送的情况呢？不许要地址的。
void
NldpProtocol::SendHelloMessage (void)
{
  NS_LOG_FUNCTION (this);

  Ptr<PduWriter> writer = Create<PduWriter> ();
  writer->SetLdpId (GetRouterId ());
  //组成Hello消息，调用Write()方法编码；
  writer->AddMessage (CreateHelloMessage ());
  Ptr<Packet> packet = writer->Write ();
  
  //这部分考虑发送着兴趣包，可以通过添加包头的方法，这部分定义出一个兴趣包，兴趣包的名字确定是比如/HelloMessage，然后把包发出去，然后LDPpeer返回一个Data包进行确认，里面带有验证消息。
  //这部分是发送消息，需要书写代码

 //outface
  m_helloEvent = Simulator::Schedule (Seconds (m_helloInterval), &NldpProtocol::SendHelloMessage, this);
}
void 
NldpProtocol::ReceiveHelloMessage(void)
{


}
}//namespace nldp
}//namespace ns3
