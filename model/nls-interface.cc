#ifndef NLS_INTERFACE_CC
#define NLS_INTERFACE_CC

#include "nls-interface.h"

namespace ns3{
namespace nls{

TypeId
Interface::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::mpls::Interface")
    .SetParent<Object> ()
    ;
  return tid;
}

Interface::Interface()
  : m_nls (0),
    m_device (0),
    m_ifup (false),
    m_ifIndex (0)
{
}
Interface::~Interface()
{
}

void Interface::DoDispose (void)
{
  m_nls = 0;
  m_device = 0;
  Object::DoDispose ();
}

void Interface::SetNls (const Ptr<Nls>& nls)
{
  m_nls = nls;
}

void Interface::SetDevice (const Ptr<NetDevice> &device)
{
  m_device = device;
}

void Interface::SetIfIndex (uint32_t index)
{
  m_ifIndex = index;
}

Ptr<NetDevice> Interface::GetDevice () const
{
  return m_device;
}

LabelSpace*
Interface::GetLabelSpace (void)
{
  return &m_labelSpace;
}

Ptr<Nls> Interface::GetNls (void) const
{
  return m_nls;
}
uint32_t Interface::GetIfIndex (void) const
{
  return m_ifIndex;
}

bool Interface::IsUp () const
{
  return m_ifup;
}

bool
Interface::IsDown () const
{
  return !m_ifup;
}

void
Interface::SetUp ()
{
  m_ifup = true;
}

void
Interface::SetDown ()
{
  m_ifup = false;
}
//将数据包发送出去；
void Interface::Send (const Ptr<Packet>& packet, const Mac48Address &dest)
{
  m_device->Send (packet, dest, Nls::NLS_PORT_NUMBER);
}

}//namespace nls
}//namespace ns3
#endif
