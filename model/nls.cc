/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

#include "nls.h"

namespace ns3 {

NS_OBJECT_ENSURE_REGISTERED (Nls);

const uint16_t Nls::NLS_PORT_NUMBER = 0x8888;

TypeId 
Nls::GetTypeId(void)
{
 static TypeId tid = TypeId ("ns3::Nls")
    .SetParent<Object> ()
  ;
  return tid;
}

Nls::Nls()
{

}

Nls::~Nls()
{

}

}//namespace ns3

