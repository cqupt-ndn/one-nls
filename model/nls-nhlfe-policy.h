#ifndef NLS_NHLFE_POLICY_H
#define NLS_NHLFE_POLICY_H

#include <ostream>
#include <vector>
#include "ns3/object.h"
#include "ns3/packet.h"
#include "nls-nhlfe.h"
#include "nls-interface.h"

namespace ns3{
namespace nls{

class Nhlfe;
class Interface;
//Nhlfe的选择策略
class NhlfeSelectionPolicy : public Object
{
public:
   static TypeId GetTypeId (void);

   NhlfeSelectionPolicy ();
   virtual ~NhlfeSelectionPolicy ();
   //返回index下的特定Nhlfe
   const Nhlfe& Get (const std::vector<Nhlfe> &nhlfe, uint32_t index);

    bool Select (const std::vector<Nhlfe> &nhlfe, uint32_t index, 
                const Ptr<const Interface> &interface, const Ptr<const Packet> &packet); 
   //输出policy
   virtual void Print (std::ostream &os) const;

protected:
  virtual void DoStart (uint32_t size);
  virtual const Nhlfe& DoGet (const std::vector<Nhlfe> &nhlfe, uint32_t index);
  virtual bool DoSelect (const std::vector<Nhlfe> &nhlfe, uint32_t index, 
                          const Ptr<const Interface> &interface, const Ptr<const Packet> &packet);   
  //template <class T> Ptr<Queue> GetQueue (const Ptr<T> &device) { return device->GetQueue (); };
private:
  int32_t m_maxPackets;
  int32_t m_maxBytes;
};
}//namespace nls
}//namespace ns3
#endif
