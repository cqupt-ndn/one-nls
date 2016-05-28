#ifndef NLS_FORWARDING_STRATEGY_H
#define NLS_FORWARDING_STRATEGY_H

#include "ns3/ndn-forwarding-strategy.h"
#include "ns3/nls.h"
namespace ns3 {
namespace nls {


class NlsForwardingStrategy :
    public ns3::ndn::ForwardingStrategy
{
private:
  typedef ns3::ndn::ForwardingStrategy super;
  
public:
  static TypeId
  GetTypeId ();
  
  NlsForwardingStrategy();
  ~NlsForwardingStrategy();
  // from super
  virtual void
  OnInterest (Ptr<ns3::ndn::Face> face, Ptr<ns3::ndn::Interest> interest);
  virtual void
  OnData (Ptr<ns3::ndn::Face> face, Ptr<ns3::ndn::Data> data);
  virtual bool
  DoPropagateInterest (Ptr<ns3::ndn::Face> inFace,
                       Ptr<const ns3::ndn::Interest> interest,
                       Ptr<ns3::ndn::pit::Entry> pitEntry);
  void SetNls(Ptr<Nls>& nls);

private:
  Ptr<Nls> m_nls;

};


} // namespace nls
} // namespace ns3

#endif
