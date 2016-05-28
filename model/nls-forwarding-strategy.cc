/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil -*- */
/*
 * Copyright (c) 2011 University of California, Los Angeles
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation;
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 *
 * Author:  Alexander Afanasyev <alexander.afanasyev@ucla.edu>
 */

#include "nls-forwarding-strategy.h"

#include "ns3/ndn-pit.h"
#include "ns3/ndn-pit-entry.h"
#include "ns3/ndn-interest.h"
#include "ns3/ndn-data.h"
#include "ns3/ndn-pit.h"
#include "ns3/ndn-fib.h"
#include "ns3/ndn-content-store.h"
#include "ns3/ndnSIM/utils/ndn-fw-hop-count-tag.h"

#include "ns3/assert.h"
#include "ns3/ptr.h"
#include "ns3/log.h"
#include "ns3/simulator.h"
#include "ns3/boolean.h"
#include "ns3/string.h"
#include <iostream>
#include "ns3/nldp-transport.h"
NS_LOG_COMPONENT_DEFINE ("ns3.nls.NlsForwardingStrategy");

namespace ns3 {
namespace nls {


NS_OBJECT_ENSURE_REGISTERED (NlsForwardingStrategy);

TypeId
NlsForwardingStrategy::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::nls::NlsForwardingStrategy")
     .SetParent<ns3::ndn::ForwardingStrategy> ()
     .AddConstructor <ns3::nls::NlsForwardingStrategy> ()
    ;
  return tid;
}
NlsForwardingStrategy::NlsForwardingStrategy()
{

}

NlsForwardingStrategy::~NlsForwardingStrategy()
{

}

void NlsForwardingStrategy::SetNls(Ptr<Nls>& nls)
{
  NS_LOG_FUNCTION (this << nls);
  m_nls = nls;
}

void
NlsForwardingStrategy::OnInterest (Ptr<ns3::ndn::Face> inFace,
                   Ptr<ns3::ndn::Interest> interest)
{
 //ndn.................................................................................
 Ptr<ns3::ndn::pit::Entry> pitEntry = m_pit->Lookup (*interest);
  bool similarInterest = true;
  if (pitEntry == 0)
    {
      similarInterest = false;
      pitEntry = m_pit->Create (interest);
      if (pitEntry != 0)
        {
          DidCreatePitEntry (inFace, interest, pitEntry);
        }
      else
        {
          FailedToCreatePitEntry (inFace, interest);
          return;
        }
    }

  bool isDuplicated = true;
  if (!pitEntry->IsNonceSeen (interest->GetNonce ()))
    {
      pitEntry->AddSeenNonce (interest->GetNonce ());
      isDuplicated = false;
    }

  if (isDuplicated)
    {
      DidReceiveDuplicateInterest (inFace, interest, pitEntry);
      return;
    }

  Ptr<ns3::ndn::Data> contentObject;
  contentObject = m_contentStore->Lookup (interest);
  if (contentObject != 0)
    { 
     std::cout<<"..................content........................"<<std::endl;
      ns3::ndn::FwHopCountTag hopCountTag;
      if (interest->GetPayload ()->PeekPacketTag (hopCountTag))
        {
          contentObject->GetPayload ()->AddPacketTag (hopCountTag);
        }

      pitEntry->AddIncoming (inFace/*, Seconds (1.0)*/);

      // Do data plane performance measurements
      super::WillSatisfyPendingInterest (0, pitEntry);

      // Actually satisfy pending interest
      super::SatisfyPendingInterest (0, contentObject, pitEntry);
      return;
    }
   else 
     { 
       m_nls = GetObject<Nls> ();    
       Ptr<Node> node = this->GetObject<Node> ();
       Ptr<Nls> nls = node->GetObject<Nls> ();

       if(nls != 0)
        {         
         // nldp::NldpTransport transport;
         // transport.ReceiveInterest(interest);   
          m_nls -> ReceiveInterest(interest);
        }
       else
        {
          super::OnInterest (inFace, interest);
        }
       return;
      }

  if (similarInterest && ShouldSuppressIncomingInterest (inFace, interest, pitEntry))
    {
      pitEntry->AddIncoming (inFace/*, interest->GetInterestLifetime ()*/);
      // update PIT entry lifetime
      pitEntry->UpdateLifetime (interest->GetInterestLifetime ());

      // Suppress this interest if we're still expecting data from some other face
      NS_LOG_DEBUG ("Suppress interests");
     // m_dropInterests (interest, inFace);

      super::DidSuppressSimilarInterest (inFace, interest, pitEntry);
      return;
    }

  if (similarInterest)
    {
      super::DidForwardSimilarInterest (inFace, interest, pitEntry);
    }
}

void
NlsForwardingStrategy::OnData (Ptr<ns3::ndn::Face> face, Ptr<ns3::ndn::Data> data)
{
  m_nls = GetObject<Nls> ();
    
  Ptr<Node> node = this->GetObject<Node> ();
  Ptr<Nls> nls = node->GetObject<Nls> ();
 
  if(nls != 0)
   {
      m_nls -> ReceiveData(data);
   }
  else
   {
    super::OnData (face, data);
   }
}

bool
NlsForwardingStrategy::DoPropagateInterest (Ptr<ns3::ndn::Face> inFace,
                       Ptr<const ns3::ndn::Interest> interest,
                       Ptr<ns3::ndn::pit::Entry> pitEntry)
 {
   std::cout<<"NlsForwardingStrategy::DoPropagateInterest"<<std::endl;
   return 1;
 }
} // namespace nls
} // namespace ns3
