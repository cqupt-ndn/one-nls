#ifndef NLS_NHLFE_SELECTION_POLICY_HELPER_H
#define NLS_NHLFE_SELECTION_POLICY_HELPER_H

#include "ns3/string.h"
#include "ns3/ptr.h"
#include "ns3/object-factory.h"

#include "ns3/nls-nhlfe-policy.h"

namespace ns3{

class NhlfeSelectionPolicyHelper: private ObjectFactory
{
protected:
  using ObjectFactory::Create;
  NhlfeSelectionPolicyHelper (const std::string &id);
public:
 //构造函数和析够函数 
  NhlfeSelectionPolicyHelper ();
  virtual ~NhlfeSelectionPolicyHelper ();
  
  virtual Ptr<nls::NhlfeSelectionPolicy> Create (void) const;
  void SetAttribute (std::string name, const AttributeValue &value);
};


}//namespace ns3

#endif
