#ifndef NLS_FEC_H
#define NLS_FEC_H

#include <ostream>

#include "nls-packet-demux.h"

namespace ns3{
namespace nls{
class PacketDemux;

class Fec
{
public:
  virtual ~Fec ();
  virtual bool operator() (PacketDemux &pd) const = 0;
  virtual void Print (std::ostream &os) const = 0;

  template <class T> static Fec* Build (const T &fec) { return new T(fec); }
};

class NameFec : public Fec
{
 public:
    NameFec();
    NameFec(const std::string& string);
    bool operator() (PacketDemux &pd) const;
    void Print (std::ostream &os) const ;
 private:
    const std::string m_string;

};

}//namespace nls
}//namespace ns3
#endif
