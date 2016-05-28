
#include "nls-fec-to-nhlfe.h"
#include <iostream>
namespace ns3 {
namespace nls {

FecToNhlfe::FecToNhlfe (Fec* fec, const Nhlfe &nhlfe)
  //: ForwardingInformation (policy),
    :m_fec (fec)
{
  
NS_ASSERT (fec != 0);

  AddNhlfe (nhlfe);
}

FecToNhlfe::~FecToNhlfe ()
{
  delete m_fec;
}

const Fec&
FecToNhlfe::GetFec (void) const
{
  return *m_fec;
}

void
FecToNhlfe::SetFec (Fec* fec)
{
  NS_ASSERT (fec != 0);
  delete m_fec;
  m_fec = fec;
}

void
FecToNhlfe::Print (std::ostream &os) const
{
  os << "ftn" << GetIndex () << " ";
  m_fec->Print (os);
  os << ", ";
  ForwardingInformation::Print (os);
}

} // namespace nls
} // namespace ns3
