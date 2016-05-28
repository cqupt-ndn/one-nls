#ifndef NLS_FORWARDING_INFORMATION_H
#define NLS_FORWARDING_INFORMATION_H

#include <vector>
#include <ostream>

#include "ns3/simple-ref-count.h"
#include "nls-nhlfe.h"
#include "nls-nhlfe-policy.h"

namespace ns3{
namespace nls{

class ForwardingInformation : public SimpleRefCount<ForwardingInformation>
{
public:
  //析构函数
  virtual ~ForwardingInformation ();
  //添加新的Nhlfe;
  uint32_t AddNhlfe (const Nhlfe& nhlfe);

  const Nhlfe& GetNhlfe (uint32_t index);

  void RemoveNhlfe (uint32_t index);

  uint32_t GetNNhlfe (void) const;

  uint32_t GetIndex (void) const;
  /**
   * @brief Set object index
   */
  void SetIndex (uint32_t index);
  /**
   * @brief Set nhlfe selection policy
   */
  void SetPolicy (const Ptr<NhlfeSelectionPolicy> policy);
  /**
   * @brief Set nhlfe selection policy
   */
  Ptr<NhlfeSelectionPolicy> GetPolicy (void) const;
  /**
   * @brief Print NHLFE
   */
  virtual void Print (std::ostream &os) const = 0;
//增加12.20 begin
  std::vector<Nhlfe> GetNhlfeVector()
  {
     return m_nhlfe;
   }
//end
  typedef std::vector<Nhlfe> NhlfeVector;
  
  class Iterator// : public std::iterator<std::input_iterator_tag, Nhlfe> 
  {
  public:
    Iterator(const Ptr<NhlfeSelectionPolicy> &policy, const NhlfeVector *nhlfe, uint32_t index=0);
    ~Iterator();

    Iterator& operator=(const Iterator& iter);
//    bool operator==(const Iterator& iter);
//    bool operator!=(const Iterator& iter);
    bool HasNext (void) const;
    const Nhlfe& Get (void);
    bool Select (const Ptr<const Interface> &interface, const Ptr<const Packet> &packet);

  private:
    Ptr<NhlfeSelectionPolicy> m_policy;
    const NhlfeVector *m_nhlfe;
    uint32_t m_index;
  };

  Iterator GetIterator (void) const;

protected: 
  ForwardingInformation ();
  NhlfeVector m_nhlfe;
  uint32_t m_index;
  
  Ptr<NhlfeSelectionPolicy> m_policy;
};

std::ostream& operator<< (std::ostream& os, const Ptr<ForwardingInformation>& info);
  
}//namespace nls
}//namespace ns3
#endif
