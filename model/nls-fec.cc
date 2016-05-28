#ifndef NLS_FEC_CC
#define NLS_FEC_CC

#include "nls-fec.h"
#include <iostream>
namespace ns3{
namespace nls{

Fec::~Fec ()
{

}

NameFec::NameFec(const std::string& string)
       :m_string(string)  
{
}
NameFec::NameFec()
{
}
bool
NameFec::operator ()(PacketDemux &pd) const
{
  const std::string s = pd.GetName();
  
  if(m_string == s)
     return true;
  else
     return false;
}

void 
NameFec::Print (std::ostream &os) const
{

os <<"Fec Stream Is："<<m_string;

}
}//namespace nls
}//namespace ns3
#endif
