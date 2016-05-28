#include "nls-incoming-label-map.h"

namespace ns3{
namespace nls{

IncomingLabelMap::IncomingLabelMap (Label label, const Nhlfe &nhlfe)
  : ForwardingInformation (),
    m_interface (-1),
    m_label (label)
{
  AddNhlfe (nhlfe);
}

IncomingLabelMap::IncomingLabelMap (int32_t interface, Label label, const Nhlfe &nhlfe)
  : ForwardingInformation (),
    m_interface (interface),
    m_label (label)
{
  AddNhlfe (nhlfe);
}

IncomingLabelMap::~IncomingLabelMap ()
{
}

Label 
IncomingLabelMap::GetLabel (void)
{
  return m_label;
}

int32_t 
IncomingLabelMap::GetInterface (void) const
{
  return m_interface;
}

void 
IncomingLabelMap::SetLabel (Label label)
{
   m_label = label; 
}

void 
IncomingLabelMap::SetInterface (int32_t interface)
{
   m_interface = interface;
}

void
IncomingLabelMap::Print (std::ostream &os) const
{
  os << "ilm" << GetIndex () << " ";

  if (m_interface >= 0)
    {
      os << "if" << m_interface << " ";
    }

  os << "label " << m_label << ", ";

  ForwardingInformation::Print (os);
}

}//namespace ns3
}//namespace nls


