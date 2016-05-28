#ifndef NLS_FEC_TO_NHLFE_H
#define NLS_FEC_TO_NHLFE_H

#include <ostream>

#include "nls-fec.h"
#include "nls-forwarding-information.h"
#include "nls-nhlfe.h"

namespace ns3 {
namespace nls {

class Fec;
class ForwardingInformation;
class Nhlfe;
class NhlfeSelectionPolicy;

/**
 * \ingroup mpls
 * \brief
 * The "FEC-to-NHLFE" (FTN) maps each FEC to a set of NHLFEs.
 * It is used when forwarding packets that arrive unlabeled, but which are to be labeled before being forwarded.
 * For more infomation see RFC 3031 (http://www.ietf.org/rfc/rfc3031.txt)
 */
class FecToNhlfe : public ForwardingInformation
{
public:
  /**
   * @brief Construct FTN for specified fec
   * @param fec forwarding equivalence class
   * @param nhlfe NHLFE (at least one NHLFE should be set)
   */
  FecToNhlfe (Fec *fec, const Nhlfe &nhlfe);
  /**
   * @brief Destructor
   */
  virtual ~FecToNhlfe ();
  /**
   * @brief Returns FEC
   */
  const Fec& GetFec (void) const;
  /**
   * @brief Set new FEC
   */
  void SetFec (Fec* fec);
  /**
   * @brief Print FTN
   * @param os the stream to print to
   */
  virtual void Print (std::ostream &os) const;

private:
  Fec* m_fec;
};

} // namespace nls
} // namespace ns3

#endif 
