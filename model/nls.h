/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
#ifndef NLS_H
#define NLS_H
#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/net-device.h"
#include "ns3/node.h"
#include "ns3/packet.h"
#include "ns3/ndn-interest.h"
#include "nls-interface.h"
#include "ns3/ndn-data.h"
//#include "ns3/nls-node.h"
namespace ns3 {

class NlsNode;

namespace nls{
 class Interface;
}

using namespace nls;

class Nls : public Object
{
public :
  static TypeId GetTypeId(void);
  static const uint16_t NLS_PORT_NUMBER;//point-point-net-device.cc文件中添加协议PORT
  Nls();
  virtual ~Nls();
  
  //获得Nls节点;
  virtual Ptr<NlsNode> GetNlsNode() const = 0;
  
  //设备中添加NlS Interface;
  virtual Ptr<Interface> AddInterface (Ptr<NetDevice>& device)  = 0;
 
  //根据index获得Nls Interface
  virtual Ptr<Interface> GetInterface (uint8_t index) const = 0;

  //获得某一设备上的Interface
  virtual Ptr<Interface> GetInterfaceForDevice (const Ptr<const NetDevice>& device) const = 0;
  //获得添加的Interface数量
  virtual uint32_t GetNInterfaces (void) const = 0;
  
  virtual bool ReceiveInterest (const Ptr<ns3::ndn::Interest> &interest) = 0;
  
  virtual void ReceiveData (const Ptr<ns3::ndn::Data> data) = 0;
  
  virtual bool ReceiveInterest (const Ptr<ns3::ndn::Interest> &interest,bool flag) = 0;
  
};
}//namespace ns3

#endif /* NLS_H */

