#ifndef NLSLIBENTRY_H
#define NLSLIBENTRY_H

#include "ns3/nls-label.h"
#include "ns3/nls-fec.h"
#include "ns3/nls-interface.h"
enum LspType
{
  Interest = 0,
  Data = 1
};
namespace ns3{
namespace nldp{

class NlsLibEntry : public SimpleRefCount<NlsLibEntry>
{
  public:
      NlsLibEntry(); 
      virtual ~NlsLibEntry();
      NlsLibEntry(LspType type,uint32_t inLabel,Ptr<Interface> inIfIndex, uint32_t outLabel,Ptr<Interface> outIfIndex);
      NlsLibEntry(LspType type,const nls::NameFec &fec, uint32_t outLabel, Ptr<Interface> outIfIndex);
      Ptr<Interface> GetInFaceIndex();
      Ptr<Interface> GetOutFaceIndex();
      nls::Label GetInLabel();
      nls::Label GetOutLabel();
      LspType GetLspType();
      void SetInIfIndex (Ptr<Interface> inIfIndex);
      void SetInLabel (int inLabel);
      void SetOutIfIndex (Ptr<Interface> outIfIndex);
      void SetOutLabel (int outLabel);
      void SetLspType (LspType type);
  private:
     nls::Label m_inLabel;
     nls::Label m_outLabel;
     nls::NameFec m_fec;
     Ptr<Interface> m_infaceIndex;
     Ptr<Interface> m_outfaceIndex;
     LspType m_type;
};
}//namespace nldp
}//namespace ns3
#endif
