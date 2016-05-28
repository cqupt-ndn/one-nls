#ifndef NLS_FORWARDING_INFORMATION_CC
#define NLS_FORWARDING_INFORMATION_CC

#include "nls-forwarding-information.h"

#include "ns3/log.h"
#include "ns3/assert.h"
#include <iostream>
namespace ns3 {
namespace nls {

ForwardingInformation::ForwardingInformation ()
  : m_index (0)
{
  //SetPolicy (policy);
}

ForwardingInformation::~ForwardingInformation ()
{
  m_policy = 0;
  m_nhlfe.clear ();
}

void 
ForwardingInformation::SetPolicy (const Ptr<NhlfeSelectionPolicy> policy)
{
  NS_ASSERT (policy != 0);
  m_policy = policy;
}

Ptr<NhlfeSelectionPolicy>
ForwardingInformation::GetPolicy (void) const
{
  return m_policy;
}
  
uint32_t
ForwardingInformation::AddNhlfe (const Nhlfe& nhlfe)
{
  uint32_t index = m_nhlfe.size ();
  m_nhlfe.push_back (nhlfe);
  return index;
}

void
ForwardingInformation::RemoveNhlfe (uint32_t index)
{
  NS_ASSERT_MSG (index < m_nhlfe.size (), "Invalid NHLFE index");
  m_nhlfe.erase (m_nhlfe.begin () + index);
}

uint32_t
ForwardingInformation::GetNNhlfe (void) const
{
  return m_nhlfe.size ();
}

uint32_t
ForwardingInformation::GetIndex (void) const
{
  return m_index;
}

void
ForwardingInformation::SetIndex (uint32_t index)
{
  m_index = index;
}

void
ForwardingInformation::Print (std::ostream &os) const
{
  os << "nhlfe(s): [";
  //m_policy->Print (os);
  os << "] ";
  for (NhlfeVector::const_iterator n = m_nhlfe.begin (); n != m_nhlfe.end (); ++n)
  {
    os << "(";
    n->Print (os);
    os << ") ";
  }
}

ForwardingInformation::Iterator::Iterator (const Ptr<NhlfeSelectionPolicy> &policy, const NhlfeVector *nhlfe, uint32_t index)
  : m_policy (policy),
    m_nhlfe (nhlfe),
    m_index (index)
{
}

ForwardingInformation::Iterator::~Iterator ()
{
}

ForwardingInformation::Iterator&
ForwardingInformation::Iterator::operator= (const ForwardingInformation::Iterator& iter)
{
  m_policy = iter.m_policy;
  m_nhlfe = iter.m_nhlfe;
  m_index = iter.m_index;
  return (*this);
}

//bool
//ForwardingInformation::Iterator::operator== (const ForwardingInformation::Iterator& iter)
//{
//  return (m_index == iter.m_index && m_nhlfe == iter.m_nhlfe && m_policy == iter.m_policy);
//}

//bool
//ForwardingInformation::Iterator::operator!= (const ForwardingInformation::Iterator& iter)
//{
//  return (m_index != iter.m_index || m_nhlfe != iter.m_nhlfe || m_policy != iter.m_policy);
//}

const Nhlfe&
ForwardingInformation::Iterator::Get ()
{
   return m_policy->Get (*m_nhlfe, m_index++);
}

bool
ForwardingInformation::Iterator::Select (const Ptr<const Interface> &interface, const Ptr<const Packet> &packet)
{
  return m_policy->Select (*m_nhlfe, m_index, interface, packet);
}

bool
ForwardingInformation::Iterator::HasNext (void) const
{
  return m_index < m_nhlfe->size (); 
}

ForwardingInformation::Iterator
ForwardingInformation::GetIterator (void) const
{
  return ForwardingInformation::Iterator(m_policy, &m_nhlfe);
}

std::ostream& operator<< (std::ostream& os, const Ptr<ForwardingInformation>& info)
{
  info->Print (os);
  return os;
}

} // namespace mpls
} // namespace ns3
#endif
