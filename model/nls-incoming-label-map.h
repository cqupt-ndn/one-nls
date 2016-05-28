#ifndef NLS_INCOMING_LABEL_MAP_H
#define NLS_INCOMING_LABEL_MAP_H

#include <ostream>

#include "nls-label.h"
#include "nls-nhlfe.h"
#include "nls-nhlfe-policy.h"
#include "nls-forwarding-information.h"

namespace ns3{
namespace nls{

class NhlfeSelectionPolicy;
class ForwardingInformation;
class Nhlfe;

//The "Incoming Label Map" (ILM) maps each incoming label to a set of NHLFEs.
class IncomingLabelMap : public ForwardingInformation
{
public:
    /**
   * @brief Construct ILM for specified incoming interface and label
   * @param interface incoming interface
   * @param label incoming label
   * @param nhlfe NHLFE (at least one NHLFE should be set)
   */
  IncomingLabelMap (int32_t interface, Label label, const Nhlfe &nhlfe);
  /**
   * @brief Construct ILM for specified incoming label
   * @param label incoming label
   * @param nhlfe NHLFE (at least one NHLFE should be set)
   */
  IncomingLabelMap (Label label, const Nhlfe &nhlfe);
  /**
   * @brief Destuctor
   */
  virtual ~IncomingLabelMap ();
 
  Label GetLabel (void);

  int32_t GetInterface (void) const;
 
  void SetLabel (Label label);

  void SetInterface (int32_t interface);

  virtual void Print (std::ostream &os) const;

  private:
  IncomingLabelMap ();

private:
  int32_t m_interface;
  Label m_label;
};
}//namespace nls
}//namespace ns3
#endif
