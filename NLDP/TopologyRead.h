#ifndef TOPOLOGYREAD_H
#define TOPOLOGYREAD_H

#include <fstream>
#include <cstdlib>
#include <string>
#include <map>
#include <list>
#include "ns3/object.h"
#include "ns3/node-container.h"
#include "ns3/nls-node.h"


namespace ns3{
namespace nldp{
class TopologyRead : public Object
{
 public:
   class Link{
   public:
   typedef std::map<std::string,std::string>::const_iterator ConstAttributesIterator;
   Link (Ptr<NlsNode> fromPtr,int fromName,Ptr<NlsNode> toPtr,int toName);
   Ptr<NlsNode> GetFromNode (void) const;
   int GetFromNodeName (void) const;
   Ptr<NlsNode> GetToNode (void) const;
   int GetToNodeName (void) const;
   std::string GetAttribute (const std::string& name) const;
   ConstAttributesIterator AttributesBegin (void) const;
   ConstAttributesIterator AttributesEnd (void) const;
 
   void SetAttribute (const std::string &name, const std::string &value);
   private:
      Link();
      int m_fromName;
      Ptr<NlsNode> m_fromPtr;
      int m_toName;
      Ptr<NlsNode> m_toPtr;
      std::map<std::string,std::string> m_linkAttr;      
};
void AddLink (Link link);
typedef std::list< Link >::const_iterator ConstLinksIterator;
static TypeId GetTypeId (void);

TopologyRead();
virtual ~TopologyRead();

ConstLinksIterator LinksBegin ();
ConstLinksIterator LinksEnd ();

//最主要的一个函数
NodeContainer Read(void);
void SetFileName (const std::string& filename);
int LinksSize (void);
  private:
 std::string m_fileName;
 std::list<Link> m_linksList;
};
}//namespace nldp
}//namespace ns3
#endif
