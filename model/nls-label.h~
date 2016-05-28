#ifndef NLS_LABEL_H
#define NLS_LABEL_H

#include <stdint.h>
#include <ostream>

namespace ns3{
namespace nls{

class Label
{
public:
  static const uint32_t IMPLICIT_NULL;
  Label(uint32_t label);
  Label();
  operator uint32_t (void) const;//这个地方比较有意思 注意

private:

  uint32_t m_value;
 friend std::ostream& operator<< (std::ostream& os, const Label &label);
};//label
std::ostream& operator<< (std::ostream& os, const Label &label);


class LabelSpace
{
public:

LabelSpace();
virtual ~LabelSpace();

bool IsEmpty();

void SetMinValue(uint32_t label);

void SetMaxValue(uint32_t label);

private:
 uint32_t m_minlabel;
 uint32_t m_maxlabel;
  bool   m_bool;//暂时预设这个值是true
};//label space

namespace shim {

/**
 * @brief Calculates and returns the shim
 */
inline uint32_t Get (Label label)
{
  return uint32_t(label) << 12;
}

///**
// * @brief Calculates and returns the shim
// */  
//inline uint32_t Get (Label label, uint8_t exp)
//{
//  return (uint32_t(label) << 12) | (exp << 9);
//}

/**
 * @brief Returns the label value
 */ 
inline uint32_t GetLabel (uint32_t s)
{
  return s >> 12;
}

/**
 * @Brief Returns the value of 'Experimental Use' field
 */
inline uint8_t GetExp (uint32_t s)
{
  return (s >> 9) & 0x7;
}

/**
 * @brief Returns the shim with new 'Time To Live' field value
 */
inline uint8_t GetTtl (uint32_t s)
{
  return s;
}

/**
 * @brief Returns the value of 'Time To Live' field
 */
inline bool IsBos (uint32_t s)
{
  return (s >> 8) & 1;
}

/**
 * @brief Set value of 'Time To Live' field
 */
inline void SetTtl (uint32_t& s, uint8_t ttl)
{
  s = (s & 0xffffff00) | ttl;
}

/**
 * @brief Set value of 'Time To Live' field
 */
inline uint32_t SetTtl2 (uint32_t s, uint8_t ttl)
{
  return (s & 0xffffff00) | ttl;
}


/**
 * @brief Returns the new shim with bos set
 */
inline uint32_t SetBos (uint32_t s)
{
  return s | 0x100;
}

/**
 * @brief Returns the new shim with bos clear
 */
inline uint32_t ClearBos (uint32_t s)
{
  return s & 0xfffffeff;
}

}// namespace shim
}//namespace nls
}//namespace ns3
#endif
