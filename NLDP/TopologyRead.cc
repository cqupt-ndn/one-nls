#include "ns3/log.h"
#include "TopologyRead.h"
//#include "ns3/names.h"

namespace ns3{
namespace nldp{
NS_LOG_COMPONENT_DEFINE("TopologyRead");

TypeId TopologyRead::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::TopologyRead")
     .SetParent<Object> ()
     .SetGroupName ("TopologyRead")
    ;
  return tid;
}

TopologyRead::TopologyRead ()
{
  NS_LOG_FUNCTION (this);
}

TopologyRead::~TopologyRead ()
{
  NS_LOG_FUNCTION (this);
}

void
 TopologyRead::SetFileName (const std::string& fileName)
{
  m_fileName = fileName;
}

TopologyRead::ConstLinksIterator
TopologyRead::LinksBegin ()
{
  return m_linksList.begin();
}
TopologyRead::ConstLinksIterator
TopologyRead::LinksEnd ()
{
return m_linksList.end();
}

int 
TopologyRead::LinksSize ()
{
  return m_linksList.size();
}

NodeContainer 
TopologyRead::Read(void)
{
std::map<int, Ptr<NlsNode> > nodeMap;
NodeContainer nodes;
std::ifstream file;
if(!strcmp(static_cast<const char*>(m_fileName.c_str()),""))
 {
   NS_LOG_WARN("must input file name!!!");
   return nodes;
 }
else
{
   file.open(static_cast<const char*>(m_fileName.c_str()));
   
   if (!file.is_open ())
   {
    NS_LOG_WARN("Topology file object is not open, check file name and permissions");
    return nodes;
   }
    std::string edgeId;
    std::string length;
    std::string delay;
    std::string bandwidth;
    int from;
    int to;
    //std::string linkAttr;
   // std::string name;
    int linksNumber = 0;
    int nodesNumber = 0;

    int totnode = 0;
    int totlink = 0;
    
    std::istringstream lineBuffer;
    std::string line;
  
    getline (file,line);
    lineBuffer.str (line);
    
    lineBuffer >> totnode;
    lineBuffer >> totlink;
   // int systemId = 1;
    NS_LOG_INFO ("Topology should have " << totnode << " nodes and " << totlink << " links");
    getline (file,line);
    for (int i = 0; i < totnode && !file.eof (); i++)
      {
        getline (file,line);
        lineBuffer.str (line);
        lineBuffer.clear();
      //  lineBuffer >>name;
       // Ptr<Node> node = CreateObject<Node> (systemId);
       // ns3::Names::Add (name, node);
        //systemId++;
      }
      getline (file,line);
      getline (file,line);
      getline (file,line);
     for (int i = 0; i < totlink && !file.eof (); i++)
     {
       getline (file,line);
       lineBuffer.clear ();
       lineBuffer.str (line);

       lineBuffer >> edgeId >> from >> to >> length >> delay >>bandwidth;

       //lineBuffer >> linkAttr;
     //if ( (!from.empty ()) && (!to.empty ()) )
    //  {
        NS_LOG_INFO ( "Link " << linksNumber << " from: " << from << " to: " << to );
	if ( nodeMap[from] == 0 )
            {
               NS_LOG_INFO( "Node " << nodesNumber << " name: " << from );
               Ptr<NlsNode> tmpNode = CreateObject<NlsNode> ();
               nodeMap[from] = tmpNode;
               nodes.Add (tmpNode);
               nodesNumber++;
             }
 
           if (nodeMap[to] == 0)
             {
               NS_LOG_INFO ( "Node " << nodesNumber << " name: " << to );
               Ptr<NlsNode> tmpNode = CreateObject<NlsNode> ();
               nodeMap[to] = tmpNode;
               nodes.Add (tmpNode);
               nodesNumber++;
             }
 
           Link link ( nodeMap[from], from, nodeMap[to], to );
           if ( !length.empty () )
             {
               NS_LOG_INFO ( "Link " << linksNumber << " Attribute---length: " << length);
               link.SetAttribute ("length", length);
	       NS_LOG_INFO ( "Link " << linksNumber << " Attribute---delay: " << delay);
               link.SetAttribute ("delay", delay);
	       NS_LOG_INFO ( "Link " << linksNumber << " Attribute---bandwidth: " << bandwidth);
               link.SetAttribute ("bandwidth", bandwidth);
             }
           AddLink (link);
           linksNumber++;
    // }
 }
}
 // NS_LOG_INFO ("Topology created with " << nodesNumber << " nodes and " << linksNumber << " links");
  file.close ();

  return nodes;

}
std::string
TopologyRead::Link::GetAttribute (const std::string &name) const
{
 NS_ASSERT_MSG (m_linkAttr.find (name) != m_linkAttr.end (), "Requested topology link attribute not found");
 return m_linkAttr.find (name)->second;
}


void
TopologyRead::AddLink (Link link)
{
   m_linksList.push_back (link);
   return;
}

void
TopologyRead::Link::SetAttribute (const std::string &name, const std::string &value)
{
     m_linkAttr[name] = value;
}

TopologyRead::Link::Link (Ptr<NlsNode> fromPtr, int fromName,Ptr<NlsNode> toPtr, int toName)
{
m_fromName = fromName;
m_fromPtr = fromPtr;
m_toName = toName;
m_toPtr = toPtr;
}

TopologyRead::Link::Link ()
{

}

Ptr<NlsNode> 
TopologyRead::Link::GetFromNode (void) const	
{
	return m_fromPtr;
}

int
TopologyRead::Link::GetFromNodeName (void) const
{
	return m_fromName;
}

Ptr<NlsNode> 
TopologyRead::Link::GetToNode (void) const
{
 	return m_toPtr;
}

int
TopologyRead::Link::GetToNodeName (void) const
{
        return m_toName;
}

TopologyRead::Link::ConstAttributesIterator
TopologyRead::Link::AttributesBegin (void) const
{
    return m_linkAttr.begin();
}

TopologyRead::Link::ConstAttributesIterator
TopologyRead::Link::AttributesEnd (void) const
{
    return m_linkAttr.end();
}

}//namespace nldp
}//namespace ns3
