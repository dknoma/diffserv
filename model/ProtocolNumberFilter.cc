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
#include "ns3/log.h"
#include "ns3/packet.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/ipv4-header.h"
#include "ProtocolNumberFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("ProtocolNumberFilter");

// NS_OBJECT_ENSURE_REGISTERED (ProtocolNumberFilter);

TypeId
ProtocolNumberFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::ProtocolNumberFilter")
    .SetParent<FilterElement> ()
    .SetGroupName("DiffServ")
    .AddAttribute("Protocol",
                   "Protocol number",
                   UintegerValue (32),
                   MakeUintegerAccessor (&ProtocolNumberFilter::value),
                   MakeUintegerChecker<uint32_t> ())
  ;
  return tid;
}

// Constructors
ProtocolNumberFilter::ProtocolNumberFilter ()
{
  NS_LOG_FUNCTION (this);
}

ProtocolNumberFilter::~ProtocolNumberFilter()
{

  NS_LOG_FUNCTION (this);
}

bool 
ProtocolNumberFilter::Match (Ptr<ns3::Packet> packet)
{
  NS_LOG_FUNCTION (this << packet);
  // std::cout << "THIS IS A PROTOCOL NUMBER FILTER ELEMENT\n";
  Ptr<ns3::Packet> copy = packet->Copy();
  if (copy->GetSize() == 0)
  {
    std::cout << "empty packet...\n";
    return false;
  }
  Ipv4Header header;
  std::cout << "peeking header...\n";
  copy->PeekHeader(header); // Get the udp header from the packet
  std::cout << "checking protocol...\n";
  uint32_t protocol = header.GetProtocol();
  bool matches = protocol == value;
  std::cout << "protocol: " << protocol << " vs value: " << value << "\tmatches: "<< matches << "\n";
  return protocol == value;
}

void 
ProtocolNumberFilter::SetProtocol (uint32_t protocol)
{
  value = protocol;
}
} // Namespace ns3
