#ifndef NLS_LABEL_CC
#define NLS_LABEL_CC
#include "nls-label.h"

namespace ns3{
namespace nls{

const uint32_t Label::IMPLICIT_NULL = 3;

Label::Label(uint32_t label)
{
 m_value = label;
}
Label::Label()
{
}
Label::operator uint32_t (void) const
{
  return m_value;
}

std::ostream& operator<<(std::ostream& os, const Label& label)
{
  os<<"label value is:"<<label.m_value;
  return os;
}

LabelSpace::LabelSpace()
   :m_minlabel (0x0001),
    m_maxlabel (0xfffff),
    m_bool(true)
{
}
LabelSpace::~LabelSpace()
{
}
bool LabelSpace::IsEmpty()
{
   return m_bool;
}

void LabelSpace::SetMinValue(uint32_t label)
{
  m_minlabel = label;
}

void LabelSpace::SetMaxValue(uint32_t label)
{
 m_maxlabel = label;
}
}//namespace nls
}//namespace ns3
#endif
