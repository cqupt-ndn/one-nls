#ifndef NLS_ILM_HELPER_H
#define NLS_ILM_HELPER_H

#include "ns3/ptr.h"
#include "ns3/nls.h"

#include "ns3/nls-label.h"
#include "ns3/nls-incoming-label-map.h"
#include "ns3/nls-nhlfe.h"

#include "nls-node-helper-base.h"

namespace ns3{
using namespace nls;

class NlsIlmHelper : public NlsNodeHelperBase
{
public:

  virtual ~NlsIlmHelper();  

  void RemoveIlm (const Ptr<IncomingLabelMap> &ilm);

  void ClearIlmTable ();

  Ptr<IncomingLabelMap> AddIlm (uint32_t interface, Label label, const Nhlfe &nhlfe);

//  Ptr<IncomingLabelMap> AddIlm (uint32_t interface, Label label, const Nhlfe &nhlfe,const NhlfeSelectionPolicyHelper& policy);
 
  Ptr<IncomingLabelMap> AddIlm (Label label, const Nhlfe &nhlfe);
 
 // Ptr<IncomingLabelMap> AddIlm (Label label, const Nhlfe &nhlfe,const NhlfeSelectionPolicyHelper &policy);
};


}
#endif
