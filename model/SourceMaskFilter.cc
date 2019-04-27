/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright 2007 University of Washington
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
 */
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "SourceMaskFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <math.h>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourceMaskFilter");

NS_OBJECT_ENSURE_REGISTERED (SourceMaskFilter);

TypeId
SourceMaskFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SourceMaskFilter")
    .SetParent<Object> ()
    .SetGroupName("DiffServ")
    .AddAttribute ("Value",
                   "Filter element value",
                   Ipv4MaskValue (Ipv4Mask ()),
                   MakeIpv4MaskAccessor (&SourceMaskFilter::value),
                   MakeIpv4MaskChecker ())
  ;
  return tid;
}

// Constructors
SourceMaskFilter::SourceMaskFilter ()
{
  NS_LOG_FUNCTION (this);
}

SourceMaskFilter::~SourceMaskFilter()
{

  NS_LOG_FUNCTION (this);
}

bool 
SourceMaskFilter::Match (Ptr<ns3::Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);
  // std::cout << "THIS IS A DESTINATION IP ADDRESS FILTER ELEMENT\n";
  Ptr<ns3::Packet> copy = packet->Copy();
  if (copy->GetSize() == 0)
  {
    std::cout << "empty packet...\n";
    return false;
  }
  Ipv4Header header;
  // std::cout << "peeking header...\n";
  copy->PeekHeader(header); // Get the IPv4 header from the packet
  // if (header)
  // {
  //   std::cout << "header was null\n";
  //   return false;
  // }
  // std::cout << "checking address...\n";
  Ipv4Address srcAddress = header.GetSource();
  uint32_t srcBits = srcAddress.Get();
  uint16_t maskPrefixLength = value.GetPrefixLength();
  uint32_t lowerAddrRange = value.Get();
  uint32_t upperAddrRange = lowerAddrRange + (pow(2, 32-maskPrefixLength) - 1);
  bool matches = (srcBits >= lowerAddrRange) && (srcBits <= upperAddrRange);
  std::cout << "dest MASK: " << value << " [prefix length] " << maskPrefixLength << " [addr bits] " << lowerAddrRange << " [matches?] " << matches 
  << " [upper range] " << upperAddrRange << "\n";
  return matches;
}

void 
SourceMaskFilter::SetMask (uint32_t mask)
{
  value = Ipv4Mask(mask);
}

void 
SourceMaskFilter::SetMask (char const *mask)
{
  value = Ipv4Mask(mask);
}
} // Namespace ns3
