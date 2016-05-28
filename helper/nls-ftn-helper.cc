#include "ns3/assert.h"
#include "ns3/log.h"

#include "nls-ftn-helper.h"

namespace ns3 {

using namespace nls;

NlsFtnHelper::~NlsFtnHelper()
{
}

void
NlsFtnHelper::RemoveFtn (const Ptr<FecToNhlfe> &ftn)
{
  GetNode ()->GetFtnTable ()->remove (ftn);
}

void 
NlsFtnHelper::ClearFtnTable ()
{
  GetNode ()->GetFtnTable ()->clear ();
}

} // namespace nls
