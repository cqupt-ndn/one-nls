#include "ns3/assert.h"
#include "nls-ilm-helper.h"

namespace ns3 {

using namespace nls;

NlsIlmHelper::~NlsIlmHelper()
{
}

void
NlsIlmHelper::RemoveIlm (const Ptr<IncomingLabelMap> &ilm)
{
  GetNode ()->GetIlmTable ()->remove (ilm);
}

void 
NlsIlmHelper::ClearIlmTable ()
{
  GetNode ()->GetIlmTable ()->clear ();
}
/*
Ptr<IncomingLabelMap>
NlsIlmHelper::AddIlm (uint32_t interface, nls::Label label, const nls::Nhlfe &nhlfe)
{
  return AddIlm (interface, label, nhlfe);
}
*/
Ptr<IncomingLabelMap>
NlsIlmHelper::AddIlm (uint32_t interface, nls::Label label, const nls::Nhlfe &nhlfe)
{
  Ptr<nls::IncomingLabelMap> ilm = Create<nls::IncomingLabelMap> (interface, label, nhlfe);
  GetNode ()->GetIlmTable ()->push_back (ilm);
  return ilm;
}
/*
Ptr<IncomingLabelMap>
NlsIlmHelper::AddIlm (nls::Label label, const nls::Nhlfe &nhlfe)
{
  return AddIlm (label, nhlfe,);
}
*/
Ptr<IncomingLabelMap>
NlsIlmHelper::AddIlm (nls::Label label, const nls::Nhlfe &nhlfe)
{
  return AddIlm (-1, label, nhlfe);
}

}//namespace ns3
