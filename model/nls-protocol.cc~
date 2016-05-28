#include "nls-protocol.h"
#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/callback.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/simulator.h"
#include "ns3/ppp-header.h"//For PPP
#include "ns3/point-to-point-net-device.h"//For EtherToPpp
#include "ns3/address.h"

#include "nls-protocol.h"
#include "ns3/ndn-stack-helper.h"
#include "ns3/ndn-wire.h"//为了Packet转换成Interest
#include "ns3/ndn-face.h"
#include "ns3/ndn-l3-protocol.h"
#include "ns3/ndn-forwarding-strategy.h"

#include "ns3/ndn-pit.h"
#include "ns3/ndn-content-store.h"
//#include "ns3/ndn-stack-helper.h"
#include "ns3/ndn-header-helper.h"
//在声明接口的时候调用“nldp-protocol.h”中的方法。
//#include "ns3/nldp-protocol.h"
#include "ns3/nldp-transport.h"
#include <iostream>
NS_LOG_COMPONENT_DEFINE ("nls::NlsProtocol");
namespace ns3{
namespace nls{
NS_OBJECT_ENSURE_REGISTERED (NlsProtocol);

using namespace traces;

TypeId
NlsProtocol::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::nls::NlsProtocol")
    .SetParent<Nls> ()
    .AddConstructor<NlsProtocol> ()
    .AddTraceSource ("Tx", "Send packet to outgoing interface.",
                        MakeTraceSourceAccessor (&NlsProtocol::m_txTrace))
    .AddTraceSource ("Rx", "Receive packet from incoming interface.",
                        MakeTraceSourceAccessor (&NlsProtocol::m_rxTrace))
    .AddTraceSource ("Drop", "Drop packet",
                        MakeTraceSourceAccessor (&NlsProtocol::m_dropTrace))
  ;
  return tid;
}

NlsProtocol::NlsProtocol ()
  : m_node (0)
{
  NS_LOG_FUNCTION (this);
}

NlsProtocol::~NlsProtocol ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

Ptr<NlsNode> 
NlsProtocol::GetNlsNode() const
{
return m_node;
}

void
NlsProtocol::NotifyNewAggregate ()
{
  if (m_node == 0)
    {
      Ptr<Node> node = this->GetObject<Node> ();

      if (node != 0)
        {
          m_node = DynamicCast<NlsNode> (node);
          //NS_ASSERT_MSG (m_node != 0, "Use NlsNode instead of Node");
        }
    }
  Object::NotifyNewAggregate ();
}

Ptr<Interface> 
NlsProtocol::AddInterface (Ptr<NetDevice>& device) 
{
  NS_LOG_FUNCTION (this << &device);

  m_node->RegisterProtocolHandler (MakeCallback (&NlsProtocol::ReceiveNls, this), Nls::NLS_PORT_NUMBER, device);
  //NldpProtocol
 // m_node->RegisterProtocolHandler (MakeCallback (&NldpProtocol::ReceiveHelloMessage, this), Nls::NLS_PORT_NUMBER, device);
  Ptr<Interface> interface = CreateObject<Interface> ();
  interface->SetIfIndex (m_interfaces.size ());
  interface->SetDevice (device);
  interface->SetNls (this);
  m_interfaces.push_back (interface);

  return interface;
}

Ptr<Interface> 
NlsProtocol::GetInterface (uint8_t index) const
{
 if(index >= 0&& index < m_interfaces.size())
    return m_interfaces[index];
 return 0;
}

Ptr<Interface> 
NlsProtocol::GetInterfaceForDevice (const Ptr<const NetDevice>& device) const
{
 for(InterfaceList::const_iterator i = m_interfaces.begin();i != m_interfaces.end();i++)
   {
     if((*i)->GetDevice() == device)
        return (*i);
   }
   return 0;
}

uint32_t
NlsProtocol::GetNInterfaces (void) const
{
  return m_interfaces.size ();
}
bool
NlsProtocol::ReceiveInterest (const Ptr<ns3::ndn::Interest> &interest,bool flag)
{
  if(flag == false)
     return false;
  std::cout<<"ReceiveInterest1"<<std::endl;
 /*
  Ptr<const Packet> packet = interest -> GetWire ();
  Ptr< Packet > m_packet = packet -> Copy ();  
  std::cout<<"packet size<ReceiveInterest>1:"<<m_packet -> GetSize ()<<std::endl;
  //Ptr<Interface> outInterface;
  //Mac48Address hwaddr;
  Ptr<NetDevice> netDeviceOne = nldp::NldpTransport::GetDeviceOne();
  Ptr<NetDevice> netDeviceTwo = nldp::NldpTransport::GetDeviceTwo();
  Address addr =  netDeviceTwo -> GetAddress();
*/
 /* 
  uint32_t label = 100;
  LabelStack stack;
  stack.Push (label);
  m_packet->AddHeader (stack);
  */
/*
  std::cout<<"packet size<ReceiveInterest>2:"<<m_packet -> GetSize ()<<std::endl;
  netDeviceOne ->Send ( m_packet, Mac48Address::ConvertFrom (addr), Nls::NLS_PORT_NUMBER);
*/ 
/*
  uint32_t label = 100;
  nls::LabelStack stack;
  stack.Push (label);
  uint32_t stackSize = stack.GetSize ();
  std::cout<<"stackSize:"<<stackSize<<std::endl;
  m_packet->AddHeader (stack);
  
  InterfaceList::iterator ite,it;
  ite = m_interfaces.begin();
  it = ite;
  ite++;
  Ptr<NetDevice> device = (*ite) -> GetDevice ();
  Address addr =  device -> GetAddress();
  hwaddr = Mac48Address::ConvertFrom (addr);
  (*it) ->Send (m_packet, hwaddr);
  */
  return true;
}
 
bool
NlsProtocol::ReceiveInterest (const Ptr<ns3::ndn::Interest> &interest)
{ 
  std::cout<<"nls ReceiveInterest"<<std::endl;
  Ptr<Node> node = this->GetObject<Node> ();
  NS_LOG_DEBUG("Node " << node->GetId ());
  NS_LOG_DEBUG ("Classification of the received packet --(interest' name ： " << interest -> GetName()<< ")");
 //Interest转换成Packet形式 有利AddHeader操作
  Ptr<const Packet> packet = interest -> GetWire ();
  Ptr< Packet > m_packet = packet -> Copy ();  

  m_demux.Assign (interest);
      
  Ptr<FecToNhlfe> ftn = m_node->LookupFtn (m_demux);
  
  m_demux.Release ();

  if (ftn == 0)
    {
      NS_LOG_DEBUG ("Dropping received packet -- ftn not found");
      return false;
    }
 //输出FTN的消息;
  NS_LOG_DEBUG ("Found suitable entry--"<< Ptr<ForwardingInformation> (ftn));
  std::cout<<"Found suitable entry--"<< Ptr<ForwardingInformation> (ftn)<<std::endl;   
   //" with " << ftn->GetNNhlfe () << " available nhlfe");

  LabelStack stack;
  NlsForward (m_packet, ftn, stack);
  return true;
}

void NlsProtocol::NlsForward (const Ptr<Packet> &packet, const Ptr<ForwardingInformation> &fwd, LabelStack &stack)
{
  std::cout<<"NlsForward1"<<std::endl;
  NS_LOG_FUNCTION ("[NlsForward]" << packet << fwd << stack);
  
  Ptr<Interface> outInterface;
  Mac48Address hwaddr;
  uint32_t stackSize = stack.GetSize ();
  NS_LOG_DEBUG ("Search of the suitable nhlfe for " << fwd);

  uint32_t idx = 0;
 //从ForwardingInformation找到合适的NHLFE条目
  std::vector<Nhlfe> nhlfeVector = fwd -> GetNhlfeVector();
  ForwardingInformation::Iterator i = fwd->GetIterator ();
   while (i.HasNext ())
    {
	std::cout<<"NlsForward2"<<std::endl;
      std::vector<Nhlfe>::iterator ite = nhlfeVector.begin();
      const Nhlfe& nhlfe = (*ite);

      uint32_t opCode = nhlfe.GetOpCode ();//获得标签的操作方式，POP(0)或和SWAP(1);
      std::cout<<"标签操作方式:"<<opCode<<std::endl;
      int32_t outIfIndex = nhlfe.GetInterface ();//获得输出接口
      Ptr<NetDevice> outNetDevice = nhlfe.GetOutNetDevice();

       if (stackSize == 0 && opCode == OP_POP)
        {
          NS_LOG_WARN ("nhlfe " << idx << " " << nhlfe << " -- invalid nhlfe");
          continue;
        }
       if (outIfIndex < 0 && stackSize == 1 && nhlfe.GetOpCode () == OP_POP)
        {
          NS_LOG_DEBUG ("nhlfe " << idx << " " << nhlfe << " selected (*)");
          NS_LOG_DEBUG ("Stack is empty -- ndn based forwarding must be used");
          NdnForward (packet,0);// 查看相应调用方法
          return;
        }
      //获得下一跳的地址
       const Mac48Address& hwaddr = nhlfe.GetNextHop ();
   /*    if (outIfIndex >= 0)
        {std::cout<<"NlsForward3"<<std::endl;
          outInterface = GetInterface (outIfIndex);

          NS_ASSERT_MSG (outInterface != 0, "Invalid outgoing interface index -- " << 
                                            "nhlfe " << idx << " " << nhlfe);
       
        }
      if (outInterface == 0)
        {
          NS_LOG_WARN ("nhlfe " << idx << " " << nhlfe << " -- next-hop is unavailable");
          continue;
        }
       if (!outInterface->IsUp ())
        {
          NS_LOG_DEBUG ("nhlfe " << idx << " " << nhlfe << " -- Nls interface disabled");
        }
    */
      //add 15.12.20 begin
       if(outNetDevice == NULL)
         {
	   NS_LOG_WARN ("nhlfe " << idx << " " << nhlfe << " -- next-hop is unavailable");
	 }
       //add 15.12.20 end
       else 
        {
          NS_LOG_DEBUG ("nhlfe " << idx << " " << nhlfe << " -- selected (*)");

          if (!RealNlsForward (packet, nhlfe, stack,outNetDevice, hwaddr))
            {
              NdnForward (packet, outInterface->GetDevice ());
            }
            
          return;
        }
      
    }//while

}//NlsForward

bool NlsProtocol::RealNlsForward (const Ptr<Packet> &packet, const Nhlfe &nhlfe, LabelStack &stack,const Ptr<NetDevice> & outNetDevice, const Mac48Address &hwaddr)
{
  std::cout<<"RealNlsForward"<<std::endl;
  NS_LOG_FUNCTION ("[RealNlsForward]" << packet << nhlfe << stack << hwaddr);
  switch (nhlfe.GetOpCode ())
    {
      case OP_POP:
        NS_ASSERT_MSG (!stack.IsEmpty (), "POP operation on the empty stack");
        stack.Pop ();
        std::cout<<"stack.Pop ()........................;"<<std::endl;
        break;

      case OP_SWAP:
        for (uint32_t i = 0, c = nhlfe.GetNLabels (); i < c; ++i)
          {
           
            Label label = nhlfe.GetLabel (i);
            if (label == Label::IMPLICIT_NULL)
              {
                // Penultimate Hop Popping
                NS_LOG_DEBUG ("Pop the stack, implicit_null label was encountered -- "
                              "NDN based forwarding must be used");
                return false;
              }
            if (i)
              {
                stack.Push (shim::Get (label));//左移12位 刚好最前面的20个为留做Label字段使用
              }
            else  
              {
                stack.Swap (shim::Get (label));
              }
          }
        break;

      default:
        NS_ASSERT_MSG (0, "Invalid operation code");
    }

  //shim::SetTtl (stack.Peek (), ttl);//这一点和之前操作相似，就是将一位的ttl值添加到相应字段中；
  packet->AddHeader (stack);
/*
  Ptr<NetDevice> device = outInterface->GetDevice ();
  int32_t ifIndex = outInterface->GetIfIndex ();
  //判断数据包大小
  if (packet->GetSize () > outInterface->GetDevice ()->GetMtu ())
    {
      NS_LOG_LOGIC ("dropping received packet -- MTU size exceeded");
      m_dropTrace (packet, DROP_MTU_EXCEEDED, ifIndex);
    }

  NS_LOG_DEBUG ("Sending labeled packet via if" << ifIndex << 
                  " dev" << device->GetIfIndex () << " hwaddr " << hwaddr);

  outInterface->Send (packet, hwaddr);
  m_txTrace (packet, outInterface->GetIfIndex ());
*/  
  outNetDevice ->Send (packet, hwaddr, Nls::NLS_PORT_NUMBER);
  return true;
}
//outDev是本节点输出Device, ingress 节点收到packets后要转换成interest然后按照传统的NDN方式转发
//或者去掉标签转换成data转发出去时
void NlsProtocol::NdnForward (const Ptr<Packet> &packet, Ptr<NetDevice> outDev)
{
 Ptr<Packet> m_packet = packet -> Copy();
 LabelStack stack;
 m_packet->RemoveHeader (stack);

 ns3::ndn::Wire m_wire;
 ns3::ndn::HeaderHelper m_headerHelper;
 ns3::ndn::HeaderHelper::Type packet_Type = m_headerHelper.GetNdnHeaderType(m_packet);
 
 if(packet_Type == ns3::ndn::HeaderHelper::INTEREST_NDNSIM)
   {
//[This part is for Interest;]
 NS_LOG_DEBUG ("NdnForward --" << "    "<<"outDev:"<<outDev);
 //Ptr<packet> m_packet = packet -> Copy();
 //LabelStack stack;
 //packet->RemoveHeader (stack);
//[XXX] 当Interest传输到出口边缘节点时 这里不许要再进行上述注释掉的操作了 因为在ReceiveNls函数中已经有这部分操作了
 
 Ptr<ns3::ndn::Interest> m_interest = m_wire.ToInterest(m_packet); 
 /* std::cout<<"name>..................:"<<(m_interest -> GetName()).toUri()<<std::endl;
  if ((m_interest -> GetName()).toUri() == "/prefix1")
 {

 }
*/
//获得节点 并且设置该节点
 
  Ptr<ns3::ndn::L3Protocol> m_ndn = this->GetObject<ns3::ndn::L3Protocol>();
 
  //获得Face Ptr<Face>  GetFaceById (uint32_t face)
  //通过Face_ID获得Face,[XXX],1这个值是可以通过参数调用获得 目前这里先不做改进，【XXX】(Ptr<NetDevice> outDev)留做LDP时 添加。
  Ptr<ns3::ndn::Face> m_face1 = m_ndn -> GetFaceById(3);//这个数字暂时手动改一下
  //发送Interest

  InterestForward(m_interest, m_face1);

  }
 else
  {
  NS_LOG_DEBUG ("NdnForward --" << "    "<<"outDev:"<<outDev);
  std::cout<<"forward ndn data--------------------------"<<std::endl;
 //Ptr<packet> m_packet = packet -> Copy();
  Ptr<ns3::ndn::Data> m_data = m_wire.ToData(m_packet);
  
  Ptr<ns3::ndn::L3Protocol> m_ndn = this->GetObject<ns3::ndn::L3Protocol>();
  //uint32_t m_size = m_ndn -> GetNFaces ();
  Ptr<ns3::ndn::Face> m_face = m_ndn -> GetFaceById(5);//这个地方需要进一步调整
  m_face -> SendData(m_data);
  }

}
//在NLS域到NDN域时，发送Interest的边缘节点处理函数

void NlsProtocol::InterestForward(const Ptr<ns3::ndn::Interest> &interest, Ptr<ns3::ndn::Face> &m_face)
{
 std::cout<<"InterestForward"<<std::endl;

 Ptr<ns3::ndn::Pit> m_pit = this->GetObject<ns3::ndn::Pit>();
 Ptr<ns3::ndn::pit::Entry> pitEntry = m_pit->Lookup (*interest);
   if (pitEntry == 0)
    { 
    pitEntry = m_pit->Create (interest);
      if (pitEntry != 0)
        {          
          NS_LOG_DEBUG("Sucessful create  pitEntry");
        }
      else
        {
          NS_LOG_DEBUG("Failed To Create Pit Entry");
          return;
        }
    }
  Ptr<ns3::ndn::Data> contentObject;
  Ptr<ns3::ndn::ContentStore> m_contentStore = this -> GetObject<ns3::ndn::ContentStore>();
  contentObject = m_contentStore->Lookup (interest);
   int number = 0;
  if( contentObject != 0)
    {
    //直接返回Data Packet
    NS_LOG_DEBUG("Incoming Interest is found in ContentStore,return Data");
    ReceiveData (contentObject);//直接返回Data数据包
    number++;
    std::cout<<"number:"<<number<<std::endl;
    }
  else
   {//转发到下一个节点
  
     m_face -> SendInterest(interest);
     
   }
}
//egress节点收到data后要做的处理
void 
NlsProtocol::ReceiveData (const Ptr<ns3::ndn::Data> data)
{
  std::cout<<"ReceiveData...................."<<std::endl;
 Ptr<Node> node = this->GetObject<Node> ();
 NS_LOG_DEBUG("Node " << node->GetId ());

 Ptr<const Packet> packet = data -> GetWire ();
 Ptr<Packet> m_packet = packet -> Copy();
 //[XXX] 注意这里应该是获得传输INTEREST方向来的相应标签的，目前先手动配置一下了 之后要做修改；还要注意传输的Device;
 //outIfIndex设定为0；
  Ptr<Interface> outInterface;
  Mac48Address hwaddrnode3("00:00:00:00:00:0c");
  
  uint32_t outIfIndex = 0;
  outInterface = GetInterface (outIfIndex);
//transport dataNldpTransport
  LabelStack stack;
  //uint8_t ttl = 64;
  Label label(1000);
  stack.Push (shim::Get (label));
  //shim::SetTtl (stack.Peek (), ttl);//这一点和之前操作相似，就是将一位的ttl值添加到相应字段中；
  m_packet-> AddHeader (stack);
  outInterface->Send (m_packet, hwaddrnode3);

}

void
NlsProtocol::ReceiveNls (Ptr<NetDevice> device, Ptr<const Packet> p, uint16_t protocol, const Address &from,const Address &to, NetDevice::PacketType packetType)
{
  std::cout<<"ReceiveNls"<<std::endl;
  
  Ptr<Node> m_needEgressNode = nldp::NldpTransport::GetEngressNode();
  uint32_t needEgressNodeId = m_needEgressNode -> GetId();

  Ptr<Node> m_needInEgressNode = nldp::NldpTransport::GetIngressNode();
  uint32_t needInEgressNodeId = m_needInEgressNode -> GetId();
  Ptr< Packet > m_packet = p -> Copy ();
//获得相应节点号 主要是为了方便查看终端显示的输出
  Ptr<Node> node = this->GetObject<Node> ();
  uint32_t nodeId = node->GetId ();
  NS_LOG_DEBUG("EgressNodeId"<<needInEgressNodeId<<"------"<<"Node "<< nodeId);
  std::cout<<"packet size before NdnForward:"<<m_packet->GetSize()<<std::endl;
  
  if( (needEgressNodeId == nodeId)||(needInEgressNodeId == nodeId))
   {
     NdnForward ( m_packet, 0);   
   }
  NS_LOG_FUNCTION (this << &device << p << protocol << from);
//获得关键切入点 Interface
  NS_LOG_DEBUG ("Packet from " << from << " received on node " << m_node->GetId ()<<" to "<<to);
  Ptr<Interface> interface = GetInterfaceForDevice (device);
  int32_t ifIndex = interface->GetIfIndex ();
/*
   if (interface->IsUp ())
    {
      m_rxTrace (p, ifIndex);
    }
  else
    {
      NS_LOG_DEBUG ("Dropping received packet -- interface " << ifIndex << " is disabled");
      m_dropTrace (p, DROP_INTERFACE_DOWN, ifIndex);
      return;
    }
*/
   //packetType
   switch (packetType)
    {
      case NetDevice::PACKET_BROADCAST:
        NS_LOG_DEBUG ("Dropping received packet -- broadcast");
       // m_dropTrace (p, DROP_BROADCAST_NOT_SUPPORTED, ifIndex);
        return;

      case NetDevice::PACKET_MULTICAST:
        NS_LOG_DEBUG ("Dropping received packet -- multicast");
      //  m_dropTrace (p, DROP_MULTICAST_NOT_SUPPORTED, ifIndex);
        return;

      default:
        break;
    }
  Ptr<Packet> packet = p->Copy ();
  LabelStack stack;
  packet->RemoveHeader (stack);
  //获取之前数据包中的ttl， 主要是为了继续ttl的计数
  uint32_t sh = stack.Peek ();
 // uint8_t ttl = shim::GetTtl (sh);
  NS_LOG_DEBUG ("Stack top label:" << (Label)shim::GetLabel (sh) );

/*
  if (ttl <= 1)
    {
      NS_LOG_WARN ("Dropping received packet -- TTL exceeded");
      m_dropTrace (packet, DROP_TTL_EXPIRED, ifIndex);
      return;
    }
*/
 // ttl--;

  uint32_t label = shim::GetLabel (sh);
  NS_LOG_DEBUG ("ILM label:" << label);
  if (stack.IsEmpty ()) {
    NS_LOG_WARN ("Dropping received packet -- empty label stack");
   // m_dropTrace (packet, DROP_EMPTY_STACK, ifIndex);
    return;
  }
  NS_LOG_DEBUG ("Searching of label mapping for label " << (Label)label << 
                " if" << ifIndex << " dev" << device->GetIfIndex ());
  
  Ptr<IncomingLabelMap> ilm = m_node->LookupIlm (label,ifIndex);
  if (ilm == 0)
    {
      NS_LOG_DEBUG ("Dropping received packet -- ILM not found");
      m_dropTrace (packet, DROP_ILM_NOT_FOUND, ifIndex);
      return;
    }

  NS_LOG_DEBUG ("Found suitable entry -- " << Ptr<ForwardingInformation> (ilm));// << 
                //" with " << ilm->GetNNhlfe () << " available nhlfe");

  NlsForward (packet, ilm, stack);
}

void
NlsProtocol::DoDispose (void)
{
  NS_LOG_FUNCTION_NOARGS ();

  for (InterfaceList::iterator i = m_interfaces.begin (); i != m_interfaces.end (); ++i)
    {
      *i = 0;
    }

  m_interfaces.clear ();
  m_node = 0;

  Object::DoDispose ();
}

}//namespace nls
}//namespace ns3
