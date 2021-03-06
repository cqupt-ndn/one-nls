#include "ns3/assert.h"
#include "ns3/log.h"
#include "nls-nhlfe-selection-policy-helper.h"
#include <iostream>
namespace ns3{

NhlfeSelectionPolicyHelper::NhlfeSelectionPolicyHelper ()
{
  ObjectFactory::SetTypeId ("ns3::nls::NhlfeSelectionPolicy");
}

NhlfeSelectionPolicyHelper::NhlfeSelectionPolicyHelper (const std::string &id)
{
  ObjectFactory::SetTypeId (id);
}

NhlfeSelectionPolicyHelper::~NhlfeSelectionPolicyHelper()
{
}

void 
NhlfeSelectionPolicyHelper::SetAttribute (std::string name, const AttributeValue &value)
{
  ObjectFactory::Set (name, value);
}

Ptr<nls::NhlfeSelectionPolicy> 
NhlfeSelectionPolicyHelper::Create (void) const
{
  
  return ObjectFactory::Create<nls::NhlfeSelectionPolicy> ();  
}



}//namespace ns3


