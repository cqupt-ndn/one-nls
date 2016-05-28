#ifndef NLS_NODE_HELPER_BASE_H
#define NLS_NODE_HELPER_BASE_H

#include "ns3/ptr.h"
#include "ns3/nls.h"
#include "ns3/nls-node.h"

#include "nls-nhlfe-selection-policy-helper.h"

namespace ns3{

class NlsNodeHelperBase
{
public:
  virtual ~NlsNodeHelperBase();

  virtual const Ptr<Nls>& GetNls (void) const = 0;
  virtual const Ptr<NlsNode>& GetNode () const = 0;
  //virtual const NhlfeSelectionPolicyHelper& GetSelectionPolicy (void) const = 0;
};

}//namespace ns3

#endif
