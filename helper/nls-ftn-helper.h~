#ifndef NLS_FTN_HELPER_H
#define NLS_FTN_HELPER_H

#include "ns3/ptr.h"
#include "ns3/nls.h"
#include "ns3/nls-label.h"
#include "ns3/nls-fec-to-nhlfe.h"
#include "ns3/nls-fec.h"
#include "ns3/nls-nhlfe.h"

#include "nls-node-helper-base.h"

#include <iostream>
namespace ns3{

using namespace nls;
class NlsFtnHelper : public NlsNodeHelperBase
{
public:
  virtual ~NlsFtnHelper();
  /**
   * @brief Remove FTN
   */
  void RemoveFtn (const Ptr<FecToNhlfe> &ftn);
  /**
   * @brief Clear FTN table
   */
  void ClearFtnTable ();
  /**
   * @brief Add a new FTN
   * @param fec FEC
   * @param nhlfe NHLFE
   * @return FTN 
   */
  template<class T>
  Ptr<FecToNhlfe> AddFtn (const T &fec, const Nhlfe &nhlfe);
 /* 
  template<class T>
  Ptr<FecToNhlfe> AddFtn (const T &fec, const Nhlfe &nhlfe, const NhlfeSelectionPolicyHelper& policy);
*/

};

template<class T>
Ptr<FecToNhlfe>
NlsFtnHelper::AddFtn (const T &fec, const Nhlfe &nhlfe)
{
  Ptr<FecToNhlfe> ftn = Create<FecToNhlfe> (Fec::Build (fec), nhlfe);//注意此处
  GetNode ()->GetFtnTable ()->push_back (ftn);
  return ftn;
}
/*
template<class T>
Ptr<FecToNhlfe> 
NlsFtnHelper::AddFtn (const T &fec, const Nhlfe &nhlfe)
{ 
  return AddFtn (fec, nhlfe, GetSelectionPolicy ());
}
*/
}//namespace ns3
#endif
