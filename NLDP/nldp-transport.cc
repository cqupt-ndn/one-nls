#include "nldp-transport.h"
#include "ns3/nls-nhlfe-policy.h"
#include "ns3/nls-switch.h"
#include "ns3/nls-node.h"
#include <stack>
#include "ns3/ndn-wire.h"//为了Packet转换成Interest
#include "ns3/nls-protocol.h"

#include "ns3/nls-label-stack.h"
namespace ns3{
namespace nldp{
using namespace nls;
//Ptr<NetDevice> NldpTransport::m_netDeviceOne = NULL;
Ptr<NetDevice> NldpTransport::m_netDeviceTwo = NULL;
std::set< Ptr<NetDevice> > NldpTransport::m_set;
std::map<int,NodeHelp::Impl> NldpTransport::netmap;
Ptr<Node> NldpTransport::m_engress;
Ptr<Node> NldpTransport::m_ingress;
stack<int> NldpTransport::lstack; 

NldpTransport::NldpTransport()
{

}

NldpTransport::~NldpTransport()
{

}

stack<int> 
NldpTransport::GetNeedStack()
{
   return lstack;
}

Ptr<Node> 
NldpTransport::GetEngressNode()
{
   return m_engress;
}

Ptr<Node> 
NldpTransport::GetIngressNode()
{
   return m_ingress;
}

Ptr<Node> 
NldpTransport::GetProducerNode()
{
   return m_producer;
}

Address 
NldpTransport::GetNldpTransportAddress()
{
   return m_address;
}

Ptr<Node> 
NldpTransport::GetConsumerNode()
{
   return m_consumer;
}

Ptr<NetDevice> 
NldpTransport::GetDeviceOne()
{
   return m_netDeviceOne;
}

Ptr<NetDevice> 
NldpTransport::GetDeviceTwo()
{
   return m_netDeviceTwo;
}

std::map<int,NodeHelp::Impl> 
NldpTransport::GetNetMap()
{
  return netmap;
}

std::set< Ptr<NetDevice> > 
NldpTransport::GetSet()
{
   return m_set;
}

void
NldpTransport::ReceiveInterest(const Ptr<ns3::ndn::Interest> &interest)
{
  std::cout<<"ReceiveInterest"<<std::endl;
  
   
     Ptr<const Packet> packet = interest->GetWire ();
     Ptr< Packet > m_packet = packet -> Copy ();  
   
     uint32_t label = 100;
     LabelStack stack;
     stack.Push (label);
     m_packet->AddHeader (stack);
   
    std::cout<<"fordddddddd444444"<<std::endl;
    //GetDeviceOne() -> Send ( m_packet, Mac48Address::ConvertFrom (GetNldpTransportAddress()), Nls::NLS_PORT_NUMBER);

}
 
//要加上向producer请求数据的数据name；
void
NldpTransport::RealTransport(string& inputfile,int beginnode,int endnode)
{
   stack<int> ndnstack;
   stack< Ptr<NetDevice> > netDeviceStack;
   NodeHelp m_nodeHelp(inputfile,beginnode,endnode);
   m_nodeHelp.CreateNodeContainer();
   //得到核心节点容器
   NodeContainer m_nodeContainer = m_nodeHelp.GetCoreNodeContainer();
   //得到正确传输顺序的节点Id栈
   lstack = m_nodeHelp.GetNeedStack();
   stack<int> m_stack = m_nodeHelp.GetNeedStack();
   //得到consumer节点
   m_consumer = m_nodeHelp.GetConsumerNode();
   //得到producer节点
   m_producer = m_nodeHelp.GetProducerNode();
   //得到nls域节点容器,容器中的所有节点都安装上NlsProtocol,容器中的第一个和最后一个节点安装ndnstack;
   NodeContainer nodes = m_nodeHelp.GetCoreNodeContainer();
   int ncsize = nodes.GetN();
   m_ingress = nodes.Get(0);
   m_engress = nodes.Get(ncsize - 1);
   NlsInstaller m_nlsInstall;
   
   //获得收发节点中的NetDevice
    netmap = m_nodeHelp.GetNodeNetDeviceAndNetDevice();
  
   //node容器中的节点安装上NlsProtocol;
   for(int i = 0; i < ncsize;i++)
   {
     Ptr<NlsNode> node = DynamicCast< NlsNode >(nodes.Get(i));
     m_nlsInstall.InstallInternal(node);
   } 
  
 
   int nodeOne = m_stack.top();
   ndnstack.push(nodeOne);
   m_stack.pop();
   NodeHelp::Impl m_impl = netmap[nodeOne];

   m_netDeviceOne = m_impl.GetFromNetDevice();
   m_netDeviceTwo = m_impl.GetToNetDevice();

   //Address m_addressOne =  m_netDeviceOne -> GetAddress();
   Address m_addressTwo =  m_netDeviceTwo -> GetAddress();
  //这部分是很重要的方法  node1
   Ptr< Node > node1 = m_netDeviceOne -> GetNode ();
   Ptr< NlsNode > nlsNode1 = DynamicCast<NlsNode> (node1);
   Ptr<Nls> nls1 = nlsNode1->GetObject<Nls> ();//获得Node上的已经聚合了的Nls类；

   nls1->AddInterface (m_netDeviceOne);//net1设备添加上Nls接口

   Ptr< Node > node2 = m_netDeviceTwo -> GetNode ();
   Ptr< NlsNode > nlsNode2 = DynamicCast<NlsNode> (node2);
   Ptr<Nls> nls2 = nlsNode2->GetObject<Nls> ();//获得Node上的已经聚合了的Nls类；
   nls2->AddInterface (m_netDeviceTwo);//net1设备添加上Nls接口

   LogComponentEnable ("nls::NlsProtocol", LOG_LEVEL_DEBUG);
   NlsSwitch swIngress (DynamicCast< NlsNode >(m_ingress));
  //ingress node
   swIngress.AddFtn (NameFec("/prefix"), Nhlfe (Swap (100),m_netDeviceOne,Mac48Address::ConvertFrom (m_addressTwo)));
  netDeviceStack.push(m_netDeviceOne);//保存ingress节点的from NetDevice,对Data传输有用

  int label1 = 100;
  int label2 = 200;
  //int n = 0;
  //core node
  while(m_stack.size() > 1)
   {
    int stackdevice = m_stack.top();
    //n = stackdevice;
    
    NodeHelp::Impl impl = netmap[stackdevice];
   
    Ptr<NetDevice> stackDeviceOne = impl.GetFromNetDevice();
    Ptr<NetDevice> stackDeviceTwo = impl.GetToNetDevice();
 
    Address address =  stackDeviceTwo -> GetAddress();

    Ptr< Node > node_1 = stackDeviceOne -> GetNode ();
   Ptr< NlsNode > nlsNode_1 = DynamicCast<NlsNode> (node_1);
   Ptr<Nls> nls_1 = nlsNode_1->GetObject<Nls> ();//获得Node上的已经聚合了的Nls类；

   nls_1->AddInterface (stackDeviceOne);//net1设备添加上Nls接口

   Ptr< Node > node_2 = stackDeviceTwo -> GetNode ();
   nlsNode2 = DynamicCast<NlsNode> (node_2);
   Ptr<Nls> nls_2 = nlsNode2->GetObject<Nls> ();//获得Node上的已经聚合了的Nls类；
   nls_2->AddInterface (stackDeviceTwo);//net1设备添加上Nls接口

  // Ptr< NlsNode > nlsNode_2 = nlsNode2;
   NlsSwitch sw (DynamicCast< NlsNode >(node_1));
   sw.AddIlm (label1,Nhlfe(Swap (label2), stackDeviceOne,Mac48Address::ConvertFrom (address)));
  // int temp = label1;
   label1 = label2;
   label2 = label1 + label2;
   ndnstack.push(stackdevice);
   netDeviceStack.push(stackDeviceOne);
   m_stack.pop();
   }
   std::cout<<"...........................netDeviceStack size:"<<netDeviceStack.size()<<std::endl;
//测试：输出ndnstack中的元素
/*   while(!ndnstack.empty())
    {
      std::cout<<"ndnstack ID:"<<ndnstack.top()<<std::endl;
      ndnstack.pop();    
    }
*/
  
  // netDeviceStack.pop();

// while(!ndnstack.empty())
 // {

   int node_One = ndnstack.top();
   ndnstack.pop();
   int nlslabel1 = 1000;
   int nlslabel2 = 2000;
  while( ndnstack.size() >= 1)
   {
   std::cout<<"stack top............................................................................."<<node_One<<std::endl;
   Ptr<NetDevice> device5 = netDeviceStack.top();
    netDeviceStack.pop();
  // Ptr<NetDevice> device0 = netDeviceStack.top();
  //  netDeviceStack.pop();
   //Address m_address = device0 -> GetAddress(); 
   Ptr< Node > net_DevicenodeOne = device5 -> GetNode ();
   Ptr< NlsNode > nls_netDevicenodeOne = DynamicCast<NlsNode> (net_DevicenodeOne);

 
   int node_One0 = ndnstack.top();
  std::cout<<"Id is 0?.................................................................."<<node_One0<<std::endl;
   NodeHelp::Impl m_nlsimpl0 = netmap[node_One0];

   Ptr<NetDevice> m_nlsnetDeviceOne0 = m_nlsimpl0.GetFromNetDevice();
   Ptr<NetDevice> m_nlsnetDeviceTwo0 = m_nlsimpl0.GetToNetDevice();  
   Address m_address = m_nlsnetDeviceOne0 -> GetAddress();
   LogComponentEnable ("nls::NlsProtocol", LOG_LEVEL_DEBUG);
   //Ptr<NetDevice> m_nd = netDeviceStack.top();
   //Address m_address = m_nd -> GetAddress();
   std::cout<<"node Id is 5?"<<nls_netDevicenodeOne->GetId()<<std::endl;
   NlsSwitch sw2 (nls_netDevicenodeOne);
   sw2.AddIlm (nlslabel1,Nhlfe(Swap (nlslabel2), m_nlsnetDeviceTwo0,Mac48Address::ConvertFrom (m_address)));
   std::cout<<"label///////////////////////////////////////"<<label1<<std::endl;
   nlslabel1 = nlslabel2;
   nlslabel2 = nlslabel1 + nlslabel2;
   ndnstack.pop();
   }
 
}

}//namespace nldp
}//namespace ns3
