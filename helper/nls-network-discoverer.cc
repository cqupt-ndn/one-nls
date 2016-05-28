#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/channel.h"
#include "ns3/mac48-address.h"
//#include "ns3/ipv4-interface.h"
#include "ns3/nls-protocol.h"
#include "ns3/loopback-net-device.h"

#include "nls-network-discoverer.h"
#include <iostream>
NS_LOG_COMPONENT_DEFINE ("NlsNetworkDiscoverer");
namespace ns3{
using namespace nls;

//简单构造函数
NlsNetworkDiscoverer::NlsNetworkDiscoverer ()
{
}
//析够函数
NlsNetworkDiscoverer::~NlsNetworkDiscoverer ()
{
  NS_LOG_FUNCTION_NOARGS ();
}



NlsNetworkDiscoverer::Vertex::Vertex (const Mac48Address& hwaddr, const Ptr<Interface> &interface)
  : m_hwaddr (hwaddr),
    m_interface (interface)
{
  NS_LOG_FUNCTION (this << hwaddr << interface);
}

NlsNetworkDiscoverer::Vertex::~Vertex ()
{
  NS_LOG_FUNCTION (this);
}

void
NlsNetworkDiscoverer::Vertex::Clear ()
{
  m_interface = 0;
}

const Mac48Address&
NlsNetworkDiscoverer::Vertex::GetHwAddr (void) const
{
  return m_hwaddr;
}

const Ptr<Interface>&
NlsNetworkDiscoverer::Vertex::GetInterface (void) const
{
  return m_interface;
}
//非常重要的方法
void
NlsNetworkDiscoverer::DiscoverNetwork (void)
{

const NodeContainer& nodes = GetNetworkNodes ();//得到NLS节点

std::list<Ptr<Vertex> > cache;//声明 链表，链表中存着的是指向Vertex类的指针（Vertex对象），存取节点MACAddress和Iterface；
for (NodeContainer::Iterator i = nodes.Begin (), k = nodes.End (); i != k; ++i)//遍历NLS Node
{
 Ptr<Nls> nls = (*i)->GetObject<Nls> ();//获得Node上的已经聚合了的Nls类；
      uint32_t nDevices = (*i)->GetNDevices ();//获得节点上的Device数量；
    for(uint32_t j = 0;j < nDevices;j++)
    {
      Ptr<NetDevice> dev = (*i)->GetDevice (j);//获得第几个节点上的第几个Device;
      if (DynamicCast<LoopbackNetDevice> (dev) != 0)//如果是LoopbackNetDevice则结束，直接进行下一次循环；
            {
              continue;
            }
      Address addr = dev->GetAddress ();//获得对用Device上的地址（MAC）
      if (Mac48Address::IsMatchingType (addr))//地址是MAC地址
       {
         Ptr<Interface> nlsIf = nls->GetInterfaceForDevice (dev);//获得设备上的接口
         if (nlsIf == 0)//如果接口等于0，则在此设备上添加接口
                {
                  nlsIf = nls->AddInterface (dev);//调用的是NlsProtocol类中的AddInterface(dev)函数;
                }
         Ptr<NlsNetworkDiscoverer::Vertex> vertex = 
                  Create<NlsNetworkDiscoverer::Vertex> (Mac48Address::ConvertFrom (addr), nlsIf);//创建Vertex对象;                    
                  cache.push_back (vertex);//vertex存取到链表cache中;
               
       }     
    } 
}
/*
   for(std::list<Ptr<Vertex> >::iterator i = cache.begin(), k = cache.end(); i != k; ++i)
    {
      std::cout<<"MACAddress:"<<(*i) -> GetHwAddr()<<"   "<<"Interface:"<<(*i) -> GetInterface() -> GetIfIndex() <<std::endl;
    }    
 */    
   for (std::list<Ptr<Vertex> >::iterator i = cache.begin (), k = cache.end (); i != k; ++i)
    {
      Ptr<Interface> nlsIf = (*i)->GetInterface ();//获得interface
      Ptr<NetDevice> dev1 = nlsIf->GetDevice ();//获得Device
      Ptr<Channel> channel = dev1->GetChannel ();//获得Channel Channel 才知道谁和自己链接在了一起 so like this；
      uint32_t nDevices = channel->GetNDevices ();//获得Channel中的设备数量

      for (uint32_t j = 0; j < nDevices; ++j)
        {
          Ptr<NetDevice> dev2 = channel->GetDevice (j);

          if (dev1 == dev2) continue;

          if (UpdateVertex (dev1, dev2, *i)) 
            {
              nlsIf->SetUp ();
            }
          else 
            {
              nlsIf->SetDown ();
            }
        }
    }
}//DiscoverNetwork (void)函数end

bool NlsNetworkDiscoverer::UpdateVertex (const Ptr<NetDevice> &dev1, const Ptr<NetDevice> &dev2,const Ptr<Vertex> &vertex)
{
  Ptr<Node> node = dev2->GetNode ();
  Ptr<Nls>  nls = node->GetObject<Nls> ();
   // 没有安装Nls
  if (nls == 0) return 0;
  
  Ptr<Interface> nlsIf = nls->GetInterfaceForDevice (dev2);

  // 无效的接口
  if (nlsIf == 0) return 0;
   
  std::cout<<"NetworkDiscoverer: found link " <<
                    "from node" << dev1->GetNode()->GetId() << ":dev" << dev1->GetIfIndex () << " " << vertex->GetHwAddr () << 
                    " to node" << dev2->GetNode()->GetId() << ":dev" << dev2->GetIfIndex () << " "<<std::endl;
  return 1;
}

}//namespace ns3
