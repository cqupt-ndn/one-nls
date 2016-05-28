#ifndef NLS_LABEL_STACK_H
#define NLS_LABEL_STACK_H

#include <stdint.h>
#include <ostream>
#include <deque>

#include "ns3/header.h"
#include "nls-label.h"

namespace ns3{
namespace nls{
/**
 * \ingroup nls
 * \brief
 * Label stack entry
 *  0                   1                   2                   3
 *  0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1 2 3 4 5 6 7 8 9 0 1
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Label
 *  |                Label                  | Exp |S|       TTL     | Stack
 *  +-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+-+ Entry
 *
 *这种标签栈命名方式是从MPLS学习而来的;
 */

class LabelStack :public Header
{
public:
  static TypeId GetTypeId (void);
  virtual TypeId GetInstanceTypeId (void) const;
  /**
   * 创建一个空栈
   */
  LabelStack ();
  /**
   * 析构
   */
  virtual ~LabelStack ();
  /**
   * 删掉堆最顶上的条目
   */
  void Pop (void);
  /**
   * 在堆顶添加一个新的条目
   */
  void Push (uint32_t s);
  /**
   * @brief Swap an entry on the stack's top交换一个条目到堆顶上
   */
  void Swap (uint32_t s);
  /**
   * @brief Retrieves the stack's top entry检索堆顶上的条目
   */
  uint32_t& Peek (void);
  /**
   * @brief Retrieves the stack's top entry检索堆顶上的条目
   */
  uint32_t Peek (void) const;
  /**
   * 堆是否为空
   */
  bool IsEmpty (void) const;
  /**
   * 返回堆大小
   */
  uint32_t GetSize (void) const;  
  /**
   * 测试堆是否损坏. 如果损坏了，我们应该丢包
   */
  bool IsBroken (void) const;

  // Functions defined in base class Header 从Header中继承而来的虚函数；
  virtual uint32_t GetSerializedSize (void) const;
  virtual void Serialize (Buffer::Iterator start) const;
  virtual uint32_t Deserialize (Buffer::Iterator start);
  virtual void Print (std::ostream &os) const;

private:
  typedef std::deque<uint32_t> Stack;
  Stack m_entries;
  bool m_broken;
};
}//namespace nls
}//namespace ns3

#endif
