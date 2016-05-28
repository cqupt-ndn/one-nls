#ifndef LDP_TEST_H
#define LDP_TEST_H
#include "TopologyRead.h"
#include "ospf.h"
#include "ns3/node-container.h"
#include "ns3/node.h"
#include "ns3/ptr.h"
#include "ns3/names.h"
#include "ns3/point-to-point-helper.h"
#include "ns3/ndnSIM-module.h"
#include "ns3/nls-protocol.h"
namespace ns3{
namespace nldp{
class NodeHelp
{
public:
   class Impl
    {
      public:   
         Impl();
         virtual~Impl();
         Impl(Ptr< NetDevice > devicefrom, Ptr< NetDevice > deviceto);
         Ptr< NetDevice > GetFromNetDevice();
         Ptr< NetDevice > GetToNetDevice();
      private:
        Ptr< NetDevice > m_devicefrom;
        Ptr< NetDevice > m_deviceto;
    };

   NodeHelp();
   NodeHelp(string& inputfile,int beginnode,int endnode);
   virtual~NodeHelp();
   void CreateNodeContainer();
   Ptr<Node> GetProducerNode();
   Ptr<Node> GetConsumerNode();
   Ptr<Node> GetEngressNode();
   Ptr<Node> GetIngressNode();
   NodeContainer GetCoreNodeContainer();
   NodeContainer GetNodeContainer();
   std::map<int,Impl> GetNodeNetDeviceAndNetDevice();
   stack<int> GetNeedStack();
   
private:
 //这个顺序，是Interest对用着的顺序
  std::map<int,Impl> m_nodeNetDeviceAndNetDevice; 


  stack<int> m_needstack;  
  string m_inputfile;
  int m_beginnode;
  int m_endnode;
  Ptr<Node> m_consumer;//这个节点作为consumer
  Ptr<Node> m_producer;//这个节点作为producer
  Ptr<Node> m_engress;//作为nls出节点
  Ptr<Node> m_ingress;//作为nls入节点
  NodeContainer m_container;//容器用来保存NLS核心节点
  NodeContainer m_nodes;
};
}//namespace nldp
}//namespace ns3
#endif
