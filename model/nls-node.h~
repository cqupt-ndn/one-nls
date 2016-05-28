#ifndef NLS_NODE_H
#define NLS_NODE_H

#include <ostream>

#include "ns3/object.h"
#include "ns3/ptr.h"
#include "ns3/node.h"
#include "nls-incoming-label-map.h"
#include "nls-fec-to-nhlfe.h"
#include "nls-label.h"
#include "nls.h"

namespace ns3{
class Nls;

namespace nls {
class IncomingLabelMap;
class FecToNhlfe;
}
using namespace nls;

class NlsNode : public Node
{
public:
  typedef std::list<Ptr<IncomingLabelMap> > IlmTable;
  typedef std::list<Ptr<FecToNhlfe> > FtnTable;
  
  enum LabelSpaceType {
    PLATFORM = 0,
    INTERFACE
  };
  
  static TypeId GetTypeId (void);

  NlsNode ();
  virtual ~NlsNode ();

  /**
   * 返回IlmTable
   */
  IlmTable* GetIlmTable (void);
  /**
   * 返回IlmTable
   */
  FtnTable* GetFtnTable (void);
  /**
   * 查找ILM
   */
  Ptr<IncomingLabelMap> LookupIlm (Label label, int32_t interface);
  // Ptr<IncomingLabelMap> LookupIlm (Label label);
  /**
   * 查找FTN
   */
  Ptr<FecToNhlfe> LookupFtn (PacketDemux& demux);
  /**
   * 返回特定Interface的LabelSpace
   */
  LabelSpace* GetLabelSpace (uint32_t ifIndex);
  /**
   * 设置LabelSpace的类型
   */
  void SetLabelSpaceType (LabelSpaceType type);
  /**
   * 设置最小的标签值
   */
  void SetMinLabelValue (uint32_t value);
  /**
   * 设置最大的标签值
   */
  void SetMaxLabelValue (uint32_t value);

protected:
  void NotifyNewAggregate (void);
  void DoDispose (void);

private:
  Ptr<Nls> m_nls;
  IlmTable m_ilmTable;
  FtnTable m_ftnTable;
  LabelSpaceType m_labelSpaceType;
  LabelSpace m_labelSpace;
  bool m_interfaceAutoInstall;
};

}//namespace ns3
#endif
