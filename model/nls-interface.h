#ifndef NLS_INTERFACE_H
#define NLS_INTERFACE_H
#include <ostream>
#include <stdint.h>

#include "ns3/object.h"
#include "ns3/net-device.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/arp-cache.h"
#include "ns3/mac48-address.h"
#include "ns3/ptr.h"
#include "ns3/sgi-hashmap.h"

#include "nls-label.h"
#include "nls.h"

namespace ns3{
class Nls;

namespace nls{

class Interface :public Object
{
public:
   static TypeId GetTypeId (void);
  
  Interface ();
  virtual ~Interface ();
  
  void SetNls (const Ptr<Nls> &nls); 
  void SetDevice (const Ptr<NetDevice> &device);
  void SetIfIndex (uint32_t index);

  Ptr<NetDevice> GetDevice () const;
  //返回NLS
  Ptr<Nls> GetNls (void) const;

  LabelSpace* GetLabelSpace (void);
  /**
   *返回interface的号码
   */
  uint32_t GetIfIndex (void) const;
  /**
   * 如果接口OK则返回true；
   */
  bool IsUp () const;
  /**
   * 如果接口false则返回true；
   */
  bool IsDown () const;
  /**
   * Enable interface
   */
  void SetUp ();
  /**
   * Disable interface
   */
  void SetDown ();
  /**
   *  【XXX】非常重要的一个函数,dest即是输出的下一跳；
   */
  void Send (const Ptr<Packet>& packet, const Mac48Address &dest);

protected:
  virtual void DoDispose (void);

private:
  Ptr<Nls> m_nls;
  Ptr<NetDevice> m_device;
  bool m_ifup;
  uint32_t m_ifIndex;
  LabelSpace m_labelSpace;
  //LabelSpace m_labelSpace;
};
}//namespace nls
}//namespace ns3

#endif
