#ifndef NLS_NHLFE_H
#define NLS_NHLFE_H

#include <ostream>
#include "nls-operations.h"//马上定义出来
#include "ns3/mac48-address.h"
#include "ns3/net-device.h"
namespace ns3{
namespace nls{

class Operation;//定义了标签的各种操作，比如交换；

//这个类代表这下一跳往哪里转发NHLFE = "Next Hop Label Forwarding Entry";
class Nhlfe
{
public:
   //构造这个类，注意：NDN中不存在类似IP这种地址表示信息，这里目前单独采用节点上的输出接口作为下一表表示，即outInterface;
     Nhlfe(const Operation& op,int32_t outInterface,const Mac48Address& nextHop); //修改15.12.18
     Nhlfe(const Operation& op,Ptr< NetDevice > outNetDevice,const Mac48Address& nextHop);//添加15.12.18
   
   Ptr<NetDevice> GetOutNetDevice() const;
   //用来处理POP
   Nhlfe (const Operation& op);
   virtual ~Nhlfe();

   //获得标签数
   uint32_t GetNLabels() const;
  
   uint32_t GetLabel (uint32_t index) const;
   //获得标签的操作方式
   uint32_t GetOpCode (void) const;
   //获得下一跳的地址
   const Mac48Address& GetNextHop (void) const;
   //获得输出接口 outInterface
   int32_t GetInterface() const;
   void Print(std::ostream& os) const;

private:
   Ptr< NetDevice > m_outNetDevice;//添加15.12.18
   int32_t m_interface;
   Mac48Address m_nextHop;
   uint32_t m_count;
   uint32_t m_opcode;
   uint32_t m_labels[6];//最多存取6个标签值；
  friend class Swap;//友元函数 在Operation中的
  friend class Pop;
};
//输出NHLFE中的信息
std::ostream& operator<< (std::ostream& os, const Nhlfe& nhlfe);

}//namespcae nls
}//namespace ns3
#endif
