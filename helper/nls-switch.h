#ifndef NLS_SWITCH_H
#define NLS_SWITCH_H
#include "ns3/ptr.h"
#include "ns3/nls-node.h"
#include "ns3/nls.h"
#include "nls-ftn-helper.h"
#include "nls-ilm-helper.h"

namespace ns3{

class NlsSwitch : public NlsFtnHelper,public NlsIlmHelper
{
public:
  NlsSwitch (const Ptr<NlsNode>& node);
 
  NlsSwitch (const std::string& node);
 
  virtual ~NlsSwitch();
  
  NlsSwitch (const NlsSwitch &o);

  NlsSwitch& operator= (const NlsSwitch &o);
  //对特殊的设备添加Interface;
  //@param devIfIndex Device index  
  Ptr<nls::Interface> AddInterface (uint32_t devIfIndex);

  //返回Interface
  Ptr<nls::Interface> GetInterface (uint32_t i);

  //Return true if interface is enabled
  bool IsUp (uint32_t i) const;

  void SetUp (uint32_t i);

  void SetDown (uint32_t i);
 
 // void SetSelectionPolicy(const NhlfeSelectionPolicyHelper& policy);

  //从NlsNodeHelperBase类继承而来的方法
  virtual const Ptr<Nls>& GetNls (void) const;
  virtual const Ptr<NlsNode>& GetNode (void) const;
 // virtual const NhlfeSelectionPolicyHelper& GetSelectionPolicy (void) const;
  
private:
  Ptr<NlsNode> m_node;
  Ptr<Nls> m_nls;  
  //NhlfeSelectionPolicyHelper m_nhlfeSelectionPolicy;
};

}//namespace ns3
#endif
