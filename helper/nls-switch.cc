#include "ns3/assert.h"
#include "ns3/log.h"
#include "ns3/object.h"
#include "ns3/names.h"
#include "ns3/string.h"

#include "nls-switch.h"
#include <iostream>
NS_LOG_COMPONENT_DEFINE ("NlsSwitch");
namespace ns3{

NlsSwitch::NlsSwitch (const Ptr<NlsNode>& node)
 //: m_nhlfeSelectionPolicy ()
{
  m_node = DynamicCast<NlsNode> (node);
  NS_ASSERT_MSG (m_node != 0, "Possible you use Node instead of NlsNode");
  m_nls = node->GetObject<Nls> ();
  
  NS_ASSERT_MSG (m_nls != 0, "There is no nls installed on specified node");
}

NlsSwitch::NlsSwitch (const std::string &node)
{
  NlsSwitch (Names::Find<NlsNode> (node));
}

NlsSwitch::~NlsSwitch ()
{
}

NlsSwitch::NlsSwitch (const NlsSwitch &o)
{
  m_nls = o.m_nls;
  m_node = o.m_node;
  //m_nhlfeSelectionPolicy = o.m_nhlfeSelectionPolicy;
}

NlsSwitch& 
NlsSwitch::operator= (const NlsSwitch &o)
{
  if (this == &o)
    {
      return *this;
    }

  m_nls = o.m_nls;
  m_node = o.m_node;
  //m_nhlfeSelectionPolicy = o.m_nhlfeSelectionPolicy;
  return *this;
}

Ptr<nls::Interface> NlsSwitch::AddInterface (uint32_t devIfIndex)
{
  Ptr<NetDevice> dev = m_node->GetDevice (devIfIndex);
  NS_ASSERT_MSG (dev != 0, "NlsSwitch::AddInterface (): Bad device");
  NS_ASSERT_MSG (m_nls->GetInterfaceForDevice (dev) == 0, 
                  "NlsSwitch::AddInterface (): Interface for device already added");
  return m_nls->AddInterface (dev);
}

Ptr<nls::Interface> NlsSwitch::GetInterface (uint32_t i)
{
 return m_nls->GetInterface (i);
}

bool NlsSwitch::IsUp (uint32_t i) const
{
  Ptr<nls::Interface> iface = m_nls->GetInterface (i);
  NS_ASSERT_MSG (iface != 0, "NlsSwitch::IsUp (): Bad index of interface");
  return iface->IsUp ();
}

void NlsSwitch::SetUp (uint32_t i)
{
  Ptr<nls::Interface> iface = m_nls->GetInterface (i);
  NS_ASSERT_MSG (iface != 0, "NlsSwitch::IsUp (): Bad index of interface");
  return iface->SetUp ();
}

void NlsSwitch::SetDown (uint32_t i)
{
  Ptr<nls::Interface> iface = m_nls->GetInterface (i);
  NS_ASSERT_MSG (iface != 0, "NlsSwitch::IsUp (): Bad index of interface");
  return iface->SetDown ();
}
/*
void NlsSwitch::SetSelectionPolicy(const NhlfeSelectionPolicyHelper& policy)
{
  m_nhlfeSelectionPolicy = policy;
}
*/
const Ptr<Nls>& NlsSwitch::GetNls (void) const
{
  return m_nls;
}
const Ptr<NlsNode>& NlsSwitch::GetNode (void) const
{
 return m_node;
}
/*
const NhlfeSelectionPolicyHelper& NlsSwitch::GetSelectionPolicy (void) const
{
  return m_nhlfeSelectionPolicy;
}
*/
}//namespace ns3

