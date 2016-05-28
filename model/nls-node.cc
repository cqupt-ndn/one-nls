#define NS_LOG_APPEND_CONTEXT \
  std::clog << Simulator::Now ().GetSeconds () << " [node " << GetId () << "] ";

#include "ns3/log.h"
#include "ns3/assert.h"
#include "ns3/callback.h"
#include "ns3/simulator.h"
#include "ns3/uinteger.h"
#include "ns3/enum.h"

#include "nls-node.h"

#include <iostream>
NS_LOG_COMPONENT_DEFINE ("NlsNode");

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (NlsNode);

using namespace nls;

TypeId
NlsNode::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::NlsNode")
    .SetParent<Node> ()
    .AddConstructor<NlsNode> ()
    .AddAttribute ("LabelSpaceType",
                   "Label space type to use.",
                   EnumValue (PLATFORM),
                   MakeEnumAccessor (&NlsNode::SetLabelSpaceType),
                   MakeEnumChecker (PLATFORM, "Platform",
                                    INTERFACE, "Interface"))
    .AddAttribute ("MinLabelValue", 
                   "The minimum label value.",
                   UintegerValue (0x1000),
                   MakeUintegerAccessor (&NlsNode::SetMinLabelValue),
                   MakeUintegerChecker<uint32_t> (0x10, 0xfffff))
    .AddAttribute ("MaxLabelValue", 
                   "The maximum label value.",
                   UintegerValue (0xfffff),
                   MakeUintegerAccessor (&NlsNode::SetMaxLabelValue),
                   MakeUintegerChecker<uint32_t> (0x10, 0xfffff))
  ;
  return tid;
}

NlsNode::NlsNode ()
  : m_nls (0),
    m_labelSpaceType (PLATFORM)
{
  NS_LOG_FUNCTION (this);
}

NlsNode::~NlsNode ()
{
  NS_LOG_FUNCTION_NOARGS ();
}

void
NlsNode::NotifyNewAggregate (void)
{
  if (m_nls == 0)
    {
      m_nls = GetObject<Nls> ();
    }

  Object::NotifyNewAggregate ();
}

void
NlsNode::DoDispose (void)
{
  m_nls = 0;
  Object::DoDispose ();
}

LabelSpace*
NlsNode::GetLabelSpace (uint32_t ifIndex)
{
  NS_ASSERT (m_nls != 0);

  if (m_labelSpaceType == PLATFORM) {
    return &m_labelSpace;
  }
  
  return m_nls->GetInterface (ifIndex)->GetLabelSpace ();
}

void
NlsNode::SetLabelSpaceType (LabelSpaceType type)
{
  if (m_nls != 0)
    {
      if (type == PLATFORM)
        {
          uint32_t nInterfaces = m_nls->GetNInterfaces ();
          for (uint32_t i = 0; i < nInterfaces; i++)
            {
              NS_ASSERT_MSG (!m_nls->GetInterface (i)->GetLabelSpace ()->IsEmpty (), 
                            "Clear interface label space before change type");
            }
        }
      else
        {
          NS_ASSERT_MSG (m_labelSpace.IsEmpty (), "Clear platform label space before set type");
        }
    }

  m_labelSpaceType = type;
}

void
NlsNode::SetMinLabelValue (uint32_t value)
{
  NS_ASSERT_MSG (m_labelSpace.IsEmpty (), "Clear platform label space before set label range");
  m_labelSpace.SetMinValue (value);
}

void
NlsNode::SetMaxLabelValue (uint32_t value)
{
  NS_ASSERT_MSG (m_labelSpace.IsEmpty (), "Clear platform label space before set label range");
  m_labelSpace.SetMaxValue (value);
}

NlsNode::IlmTable*
NlsNode::GetIlmTable (void)
{
  return &m_ilmTable;
}

NlsNode::FtnTable*
NlsNode::GetFtnTable (void)
{
  return &m_ftnTable;
}

Ptr<IncomingLabelMap>
NlsNode::LookupIlm (Label label, int32_t interface)
//NlsNode::LookupIlm (Label label)
{
  NS_LOG_FUNCTION (this << label );
//查找有两种情况 找到interface或者interface<0
  for (IlmTable::const_iterator i = m_ilmTable.begin (); i != m_ilmTable.end (); ++i)
    {
      //if ((*i)->GetLabel () == label && (*i)->GetInterface () == interface)
	if ((*i)->GetLabel () == label && (*i)->GetInterface () == -1)
        {
          return *i;
        }
    }
/*
  for (IlmTable::const_iterator i = m_ilmTable.begin (); i != m_ilmTable.end (); ++i)
    {
      if ((*i)->GetLabel () == label && (*i)->GetInterface () < 0)
        {
          return *i;
        }
    }
*/
  return 0;
}

Ptr<FecToNhlfe>
NlsNode::LookupFtn (PacketDemux &demux)
{
  NS_LOG_FUNCTION (this);  
  for (FtnTable::const_iterator i = m_ftnTable.begin (); i != m_ftnTable.end (); ++i)
    { 
      
      if (((*i)->GetFec ()) (demux))//获得有相同匹配的FEC时，返回FTN
        {
          return *i;
        }
    }

  return 0;
}

} // namespace ns3
