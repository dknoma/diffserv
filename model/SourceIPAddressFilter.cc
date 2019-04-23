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
#include "SourceIPAddressFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourceIPAddressFilter");

// NS_OBJECT_ENSURE_REGISTERED (SourceIPAddressFilter);

TypeId
SourceIPAddressFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SourceIPAddressFilter")
    .SetParent<Object> ()
    .SetGroupName("DiffServ")
    .AddAttribute ("Value",
                   "Filter element value",
                   Ipv4AddressValue (Ipv4Address ()),
                   MakeIpv4AddressAccessor (&SourceIPAddressFilter::value),
                   MakeIpv4AddressChecker ())
  ;
  return tid;
}

// Constructors
SourceIPAddressFilter::SourceIPAddressFilter ()
{
  NS_LOG_FUNCTION (this);
}

SourceIPAddressFilter::~SourceIPAddressFilter()
{

  NS_LOG_FUNCTION (this);
}

bool 
SourceIPAddressFilter::Match (Ptr<ns3::Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);
  std::cout << "THIS IS A SOURCE IP ADDRESS FILTER ELEMENT\n";
  if (packet->GetSize() == 0)
  {
    std::cout << "empty packet...\n";
    return false;
  }
  Ipv4Header header;
  std::cout << "peeking header...\n";
  packet->PeekHeader(header); // Get the IPv4 header from the packet
  // if (header)
  // {
  //   std::cout << "header was null\n";
  //   return false;
  // }
  std::cout << "checking address...\n";
  Ipv4Address srcAddress = header.GetSource();
  bool matches = srcAddress == value;
  std::cout << "src: " << srcAddress << " vs. value " << value << "\tmatches: "<< matches << "\n";
  return srcAddress == value;
}

void 
SourceIPAddressFilter::SetAddress (uint32_t addr)
{
  value = Ipv4Address(addr);
}
} // Namespace ns3
