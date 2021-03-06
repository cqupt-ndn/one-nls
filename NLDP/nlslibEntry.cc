#include "nlslibEntry.h"

namespace ns3{
namespace nldp{

NlsLibEntry::NlsLibEntry()
{
}
NlsLibEntry::~NlsLibEntry()
{

}
void
NlsLibEntry::SetInIfIndex (Ptr<Interface> inIfIndex)
{
  m_infaceIndex = inIfIndex;
}
void
NlsLibEntry::SetInLabel (int inLabel)
{
   m_inLabel = inLabel;
}
void
NlsLibEntry::SetOutIfIndex (Ptr<Interface> outIfIndex)
{
   m_outfaceIndex = outIfIndex;
}
void
NlsLibEntry::SetOutLabel (int outLabel)
{
  m_outLabel = outLabel;
}
void
NlsLibEntry::SetLspType (LspType type)
{
  m_type = type;
}

Ptr<Interface>
NlsLibEntry::GetInFaceIndex()
{
  return  m_infaceIndex;
}
Ptr<Interface> 
NlsLibEntry::GetOutFaceIndex()
{
  return m_outfaceIndex;
}
nls::Label 
NlsLibEntry::GetInLabel()
{
  return m_inLabel;
}
nls::Label 
NlsLibEntry::GetOutLabel()
{
  return m_outLabel;
}
LspType 
NlsLibEntry::GetLspType()
{
  return m_type;
}
NlsLibEntry::NlsLibEntry(LspType type,uint32_t inLabel,Ptr<Interface> inIfIndex, uint32_t outLabel,Ptr<Interface> outIfIndex)
{
  m_inLabel = inLabel;
  m_outLabel = outLabel;
  m_infaceIndex = inIfIndex;
  m_outfaceIndex = outIfIndex;
  m_type = type;
}
NlsLibEntry::NlsLibEntry(LspType type,const nls::NameFec &fec, uint32_t outLabel, Ptr<Interface> outIfIndex)
{
  m_type = type;
  //m_fec = fec;
  m_outLabel = outLabel;
  m_outfaceIndex = outIfIndex;
}
}//namespace ns3
}//namespace nldp
