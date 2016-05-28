#ifndef NLS_NETWORK_CONFIGURATOR_H
#define NLS_NETWORK_CONFIGURATOR_H

#include "ns3/nls-installer.h"
#include "ns3/nls-interface-helper.h"
#include "ns3/nls-network-discoverer.h"
//#include "ns3/nls-tunnel-helper.h"

namespace ns3
{
/**
 * \brief Nls network configurator
 */
class NlsNetworkConfigurator : public NlsInstaller, public NlsNetworkDiscoverer, public NlsInterfaceHelper
{
public:
    NlsNetworkConfigurator();
    NlsNetworkConfigurator(const NlsNetworkConfigurator &o);
    NlsNetworkConfigurator& operator= (const NlsNetworkConfigurator &o);

    virtual ~NlsNetworkConfigurator(void);

    void SetOutputStream (const Ptr<OutputStreamWrapper> &stream);
    virtual const Ptr<OutputStreamWrapper>& GetOutputStream (void) const;
    virtual const NodeContainer& GetNetworkNodes (void) const;
  
private:
  Ptr<OutputStreamWrapper> m_stream;

};

}//namespace ns3
#endif
