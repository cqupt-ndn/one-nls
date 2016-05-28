#include "ns3/assert.h"
#include "ns3/log.h"

#include "nls-network-configurator.h"
NS_LOG_COMPONENT_DEFINE ("NlsNetworkConfigurator");
namespace ns3
{
NlsNetworkConfigurator::NlsNetworkConfigurator ()
{
  m_stream = Create<OutputStreamWrapper> (&std::cout);
}

NlsNetworkConfigurator::~NlsNetworkConfigurator ()
{
}

NlsNetworkConfigurator::NlsNetworkConfigurator (const NlsNetworkConfigurator &o)
  : NlsInstaller (o), 
    NlsNetworkDiscoverer (o)
{
  m_stream = o.m_stream;
}

NlsNetworkConfigurator&
NlsNetworkConfigurator::operator= (const NlsNetworkConfigurator &o)
{
  if (this == &o)
    {
      return *this;
    }

  NlsInstaller::operator= (o);
 // NlsTunnelHelper::operator= (o);
  NlsNetworkDiscoverer::operator= (o);

  m_stream = o.m_stream;
  
  return *this;
}

void
NlsNetworkConfigurator::SetOutputStream (const Ptr<OutputStreamWrapper> &stream)
{
  NS_ASSERT_MSG (stream != 0, "NlsNetworkConfigurator::SetOutputStream (): invalid stream");
  m_stream = stream;
}

const NodeContainer& 
NlsNetworkConfigurator::GetNetworkNodes (void) const
{
  return NlsInstaller::GetNetworkNodes ();
}

const Ptr<OutputStreamWrapper>&
NlsNetworkConfigurator::GetOutputStream (void) const
{
  return m_stream;
}



}//namespace ns3s
