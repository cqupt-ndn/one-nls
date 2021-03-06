#ifndef NLS_OPERATION_CC
#define NLS_OPERATION_CC

#include "ns3/assert.h"

#include "nls-operations.h"

namespace ns3 {
namespace nls {

Operation::~Operation ()
{
}

Pop::Pop ()
{
}

Pop::~Pop ()
{
}

void
Pop::Accept (Nhlfe& nhlfe) const
{
  nhlfe.m_opcode = OP_POP;
}

Swap::Swap (Label label1)
  : m_count (1)
{
  m_labels[0] = label1;
}

Swap::Swap (Label label1, Label label2)
  : m_count (2)
{
  m_labels[0] = label1;
  m_labels[1] = label2;
}

Swap::Swap (Label label1, Label label2, Label label3)
  : m_count (3)
{
  m_labels[0] = label1;
  m_labels[1] = label2;
  m_labels[2] = label3;
}

Swap::Swap (Label label1, Label label2, Label label3, Label label4)
  : m_count (4)
{
  m_labels[0] = label1;
  m_labels[1] = label2;
  m_labels[2] = label3;
  m_labels[3] = label4;
}

Swap::Swap (Label label1, Label label2, Label label3, Label label4, 
            Label label5)
  : m_count (5)
{
  m_labels[0] = label1;
  m_labels[1] = label2;
  m_labels[2] = label3;
  m_labels[3] = label4;
  m_labels[4] = label5;
}

Swap::Swap (Label label1, Label label2, Label label3, Label label4, 
            Label label5, Label label6)
  : m_count (6)
{
  m_labels[0] = label1;
  m_labels[1] = label2;
  m_labels[2] = label3;
  m_labels[3] = label4;
  m_labels[4] = label5;
  m_labels[5] = label6;
}

Swap::~Swap ()
{
}

void
Swap::Accept (Nhlfe& nhlfe) const
{
  nhlfe.m_opcode = OP_SWAP;
  nhlfe.m_count = m_count;
  for (uint32_t i = 0; i < m_count; ++i) 
    {
      nhlfe.m_labels[i] = m_labels[i];
    }
}

} // namespace mpls
} // namespace ns3
#endif
