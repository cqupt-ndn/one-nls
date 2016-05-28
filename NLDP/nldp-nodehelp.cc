#include "nldp-nodehelp.h"
#include "ns3/log.h"
#include "ns3/string.h"
#include "ns3/nls-installer.h"
#include "ns3/mac48-address.h"
#include <iostream>
NS_LOG_COMPONENT_DEFINE ("NodeHelp");
namespace ns3{
namespace nldp{
//NS_OBJECT_ENSURE_REGISTERED (NodeHelp);

NodeHelp::NodeHelp()
{

}

NodeHelp::NodeHelp(string& inputfile,int beginnode,int endnode)
{
   m_inputfile = inputfile;
   m_beginnode = beginnode;
   m_endnode = endnode;
}
NodeHelp::~NodeHelp()
{

}
stack<int> 
NodeHelp::GetNeedStack()
{
   return m_needstack;
}


Ptr<Node> 
NodeHelp::GetProducerNode()
{
   return m_producer;
}
Ptr<Node> 
NodeHelp::GetConsumerNode()
{
   return m_consumer;
}
Ptr<Node> 
NodeHelp::GetEngressNode()
{
   return m_engress;
}
Ptr<Node> 
NodeHelp::GetIngressNode()
{
   return m_ingress;
}
std::map<int,NodeHelp::Impl>
NodeHelp::GetNodeNetDeviceAndNetDevice()
{
  return m_nodeNetDeviceAndNetDevice;
}
NodeHelp::Impl::Impl()
{

}

NodeHelp::Impl::~Impl()
{

}
NodeHelp::Impl::Impl(Ptr< NetDevice > devicefrom, Ptr< NetDevice > deviceto)
{
m_devicefrom = devicefrom;
m_deviceto = deviceto;
}

Ptr< NetDevice >
NodeHelp::Impl::GetFromNetDevice()
{
  return m_devicefrom;
}
Ptr< NetDevice >
NodeHelp::Impl::GetToNetDevice()
{
  return m_deviceto;
}
NodeContainer 
NodeHelp::GetCoreNodeContainer()
{
   return m_container;
}
NodeContainer 
NodeHelp::GetNodeContainer()
{
   return m_nodes;
}
void 
NodeHelp::CreateNodeContainer()
{ 
  nldp::TopologyRead topology;
  topology.SetFileName(m_inputfile);
  NodeContainer nodes;
  nodes = topology.Read();
  int node;
 if (topology.LinksSize () == 0)
    {
     std::cout<<"Problems reading the topology file. Failing."<<std::endl;
    }
  

  //选择最优路径
  Dijkstra dij;
  dij.setFilename(m_inputfile);
  //17节点作为consumer,19节点作为producer
  //17->9->2->1->6->10->19
  //其实经历的节点为17->8->1->0->5->9->19
  //除了m_beginnode和m_endnode外，其它的
  dij.setBeginNumber(m_beginnode);
  dij.setEndNumber(m_endnode);

  stack<int> s = dij.Init();
   
  //tempstack作为一个临时堆栈，保存的东西是Interest方向上传输的节点逻辑顺序
  stack<int> m_stack,tempstack;
  tempstack = s;  
  
  while(!s.empty())
  {
    m_stack.push(s.top());
    s.pop(); 
  }
  //m_needstack里面保存着正确的Interest方向传输的节点逻辑顺序
  tempstack.pop();
  while(tempstack.size() != 1)
  {
    m_needstack.push(tempstack.top() - 1);
    tempstack.pop();
  }

  stack<int> linkstack = m_stack;
  int stacksize = m_stack.size();
  //如果存在的节点数不为零，首先要生成这些节点，并且存入节点容器中； 
  if(m_stack.empty())
  {
   NS_LOG_DEBUG ("Node stack is empty");
  }
  else
  {
    //得到producer节点；
    node = m_stack.top();
    m_consumer = nodes.Get(node); 
    m_stack.pop();
    while(!m_stack.empty())
    {
       if(m_stack.size() == 1)
       {
         node = m_stack.top();
         m_producer = nodes.Get(node);
         m_stack.pop(); 
         break;                 
       }
         node = m_stack.top();
               
         m_container.Add(nodes.Get(node - 1));
         // int arraynumber = m_stack.size() - 1;
         // int nodearray[arraynumber];
         m_stack.pop();       
    }
  }
//节点大于三个时，核心内的节点链接数是一
 if(stacksize > 3)
 {
  int corelinks = stacksize - 3;
  // ------------------------------------------------------------
  // -- Create nodes and edge attribute
  // --------------------------------------------
  //每一个链接有两个节点，分别存入nc数组
  int totlinks = topology.LinksSize ();
  //这个容器保存路由容器之外的节点
  NodeContainer* nc = new NodeContainer[totlinks];
  //这个容器保存路由线路上的节点
 // NodeContainer* coreNode = new NodeContainer[corelinks];
  //将对用路由链路节点号保存在一个map容器中，申请一个map容器
  std::map<int,int> ncmap;
 //数组用来暂时保存核心节点下标值
  int tempArray[corelinks];
  linkstack.pop();//去掉栈中的第一个元素，因为它是consume
  for(int m = 0; m <= corelinks; m++)
   {
     tempArray[m] = linkstack.top() - 1;
     linkstack.pop(); 
   }
 for(int k = 1; k <=corelinks; k++)
  {
     int temp = tempArray[k-1];
         ncmap[temp] = tempArray[k]; 
  }

   std::map<int,int>::iterator itemap;
  //测试容器中的元素
/*
  for(itemap = ncmap.begin(); itemap != ncmap.end(); itemap++)
   {
     std::cout<< itemap -> first<<"  "<< itemap -> second << std::endl; 
   }
*/
  nldp::TopologyRead::ConstLinksIterator iter;
  int i = 0;
  for ( iter = topology.LinksBegin (); iter != topology.LinksEnd (); iter++, i++ )
  {
      nc[i] = NodeContainer (DynamicCast<Node>(iter->GetFromNode ()), DynamicCast<Node>(iter->GetToNode ()));
  }
  //为每个链接设置属性
  //NetDeviceContainer* ndc = new NetDeviceContainer[totlinks];
  PointToPointHelper p2p;
  nldp::TopologyRead::ConstLinksIterator iterator;
  int j;
  
  for (j = 0,iterator = topology.LinksBegin (); (j < totlinks)&&(iterator != topology.LinksEnd()); j++,iterator++)
  {   
      int oneFrom = iterator -> GetFromNodeName ();
      int twoTo = iterator -> GetToNodeName ();
      bool flag = false;
     
      for(itemap = ncmap.begin(); itemap != ncmap.end(); itemap++ )
        {
           if(((itemap->first == oneFrom) && (itemap->second == twoTo))||((itemap->first == twoTo) && (itemap->second == oneFrom)))
	     { 
                flag = true;
		std::string m_delay = iterator -> GetAttribute("delay"); 
      		std::string delay = m_delay + "ms";  
      		p2p.SetChannelAttribute ("Delay", StringValue (delay));
      		std::string m_dataRate = iterator -> GetAttribute("bandwidth");  
      		std::string dataRate = m_dataRate + "Mbps";
      		p2p.SetDeviceAttribute ("DataRate", StringValue (dataRate));
		NetDeviceContainer ndc = p2p.Install (nc[j]);
                uint32_t ndcnumber = ndc.GetN();
  		std::cout<<"number:"<<ndcnumber<<std::endl;
		Ptr< NetDevice > net1 = ndc.Get(0);
                Ptr< Node > node1 = net1 -> GetNode ();
                
                int node1Id = node1 -> GetId ();
                std::cout<<"node1Id:"<<node1Id<<std::endl; 
		Address addr1 =  net1 -> GetAddress();
		 if (Mac48Address::IsMatchingType (addr1))//地址是MAC地址
       		{
			std::cout<<"addr1"<<addr1<<std::endl;
		}
		Ptr< NetDevice > net2 = ndc.Get(1);
		Ptr< Node > node2 = net2 -> GetNode ();
                int node2Id = node2 -> GetId ();
                  std::cout<<"node2Id:"<<node2Id<<std::endl; 
		Address addr2 =  net2 -> GetAddress();
		 if (Mac48Address::IsMatchingType (addr2))//地址是MAC地址
       		{
			std::cout<<"addr2"<<addr2<<std::endl;
		}
               //m_nodeNetDeviceAndNetDevice 容器中KEY值保存的是包被发送出去时，发出节点的值。Value值是本节点和下一跳节点的NetDevice值。
	       //我们可以根据Key的值，通过选择m_needstack栈中保存的值，顺序出栈操作，来选择容器中哪个节点先发送包；代码写到这里，暂时先进行带标签的包收发工作
               if(ncmap[node1Id] == node2Id)
                 {
 			Impl implone(net1,net2);
			m_nodeNetDeviceAndNetDevice[node1Id] = implone;
                 }
               else if(ncmap[node2Id] == node1Id)
		 {
			Impl impltwo(net2,net1);
			m_nodeNetDeviceAndNetDevice[node2Id] = impltwo;
		 }
                
             }
          
        }
     if(flag == true)
        {
          continue;
        }
     else
      { 
      	std::string m_delay = iterator -> GetAttribute("delay"); 
      	std::string delay = m_delay + "ms";  
      	p2p.SetChannelAttribute ("Delay", StringValue (delay));
      	std::string m_dataRate = iterator -> GetAttribute("bandwidth");  
      	std::string dataRate = m_dataRate + "Mbps";
      	p2p.SetDeviceAttribute ("DataRate", StringValue (dataRate));
      	p2p.Install (nc[j]);
      }
  }

 }//( stacksize > 3)

 if(m_stack.size() == 2)
  {
   NS_LOG_DEBUG ("");
  }
  // nodes里面含有了所有的节点，m_container里面含有我们最佳路径上的所有节点
  m_nodes = nodes;
}
}
}
