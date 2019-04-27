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
#include "DestinationIPAddressFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("DestinationIPAddressFilter");

NS_OBJECT_ENSURE_REGISTERED (DestinationIPAddressFilter);

TypeId
DestinationIPAddressFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::DestinationIPAddressFilter")
    .SetParent<Object> ()
    .SetGroupName("DiffServ")
    .AddAttribute ("Value",
                   "Filter element value",
                   Ipv4AddressValue (Ipv4Address ()),
                   MakeIpv4AddressAccessor (&DestinationIPAddressFilter::value),
                   MakeIpv4AddressChecker ())
  ;
  return tid;
}

// Constructors
DestinationIPAddressFilter::DestinationIPAddressFilter ()
{
  NS_LOG_FUNCTION (this);
}

DestinationIPAddressFilter::~DestinationIPAddressFilter()
{

  NS_LOG_FUNCTION (this);
}

bool 
DestinationIPAddressFilter::Match (Ptr<ns3::Packet> packet)
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
  std::cout << "peeking header...\n";
  copy->PeekHeader(header); // Get the IPv4 header from the packet
  // if (header)
  // {
  //   std::cout << "header was null\n";
  //   return false;
  // }
  std::cout << "checking address...\n";
  Ipv4Address destAddress = header.GetDestination();
  bool matches = destAddress == value;
  std::cout << "dest: " << destAddress << " vs. value: " << value << "\tmatches: "<< matches << "\n";
  return destAddress == value;
}

void 
DestinationIPAddressFilter::SetAddress (uint32_t addr)
{
  value = Ipv4Address(addr);
}

void 
DestinationIPAddressFilter::SetAddress (char const *addr)
{
  value = Ipv4Address(addr);
}
} // Namespace ns3
