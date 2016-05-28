#ifndef NLS_PACKET_DEMUX_H
#define NLS_PACKET_DEMUX_H

#include "ns3/packet.h"
#include "ns3/ndn-interest.h"
#include "ns3/name.h"

namespace ns3{
namespace nls{

class PacketDemux
{
public:
    PacketDemux();
    virtual ~PacketDemux();

    void Assign (const Ptr<const ns3::ndn::Interest>& interest);
//获得Interest的前缀
    const std::string GetName ();
  
    void Release (void);
private:
    Ptr<const ns3::ndn::Interest> m_interest;

};

}//namespace nls
}//namespace ns3
#endif
