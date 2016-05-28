#ifndef NLS_INSTALLER_H
#define NLS_INSTALLER_H

#include "ns3/ptr.h"
#include "ns3/object-factory.h"
#include "ns3/node-container.h"
#include "ns3/callback.h"
#include "ns3/nls.h"

#include "ns3/nls-node.h"
//#include "mpls-enum-helper.h"
#include "nls-network-helper-base.h"
#include "ns3/ndn-forwarding-strategy.h"
#include "ns3/ndn-stack-helper.h"
namespace ns3
{
class NlsInstaller //: public NlsNetworkHelperBase
{
public:
/**
   * @brief Create a new NlsInstaller
   */
  NlsInstaller(void);

  /**
   * @brief Destroy the MplsInstaller
   */
  virtual ~NlsInstaller(void);

  NlsInstaller (const NlsInstaller &o);
  NlsInstaller &operator = (const NlsInstaller &o);

  NodeContainer CreateAndInstall (uint32_t count);

  /**
   * @brief Aggregate implementations of NLS, NDN and  onto the provided node.
   * 
   * @param node node, node name or node container
   */
  template <class T>
  void Install (T node)
  {
    ForEachNode (node, MakeCallback (&NlsInstaller::InstallInternal, this));
  }
  
  /**
   * @brief Returns all nodes with MPLS installed
   */
  virtual const NodeContainer& GetNetworkNodes (void) const;

  static void CreateAndAggregateObjectFromTypeId (Ptr<NlsNode> node, const std::string typeId);

  void Initialize (void);
  void InstallInternal (Ptr<NlsNode> node);

  
  

  //ObjectFactory m_strategyFactory;

  //ns3::ndn::StackHelper m_stackHelper;
  NodeContainer m_networkNodes;
};

}//namespace ns3

#endif
