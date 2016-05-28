#ifndef NLS_PACKET_DEMUX_CC
#define NLS_PACKET_DEMUX_CC

#include "nls-packet-demux.h"

#include "ns3/ndnSIM/model/wire/ndn-wire.h"
#include "ns3/ndn-name.h"
namespace ns3{
namespace nls{

PacketDemux::PacketDemux()
  :m_interest(0)
{
}

PacketDemux::~PacketDemux()
{

}

void PacketDemux::Release (void)
{
m_interest = 0;
}

void PacketDemux::Assign (const Ptr<const ns3::ndn::Interest>& interest)
{
 m_interest = interest;
}

const std::string PacketDemux::GetName ()
{

 const ns3::ndn::Name& name = m_interest -> GetName ();
 std::string s = name.toUri ();
 int arrayNumber = 0;
 for(uint32_t i = 0; i < s.size();i++)
  {
    if(s[i] == '%')
       {
         arrayNumber = i - 1;
         break;
       }
  }
  std::string returnName= s.substr(0,arrayNumber);
  return returnName;
}

}//namespace nls
}//namespace ns3
#endif
