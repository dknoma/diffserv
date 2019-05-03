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
#include "ns3/ppp-header.h"
#include "ns3/uinteger.h"
#include "ns3/trace-source-accessor.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "SourcePortNumberFilter.h"
#include <chrono>
#include <thread>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <fstream>
#include <bitset>

namespace ns3 {

NS_LOG_COMPONENT_DEFINE ("SourcePortNumberFilter");

// NS_OBJECT_ENSURE_REGISTERED (SourcePortNumberFilter);

TypeId
SourcePortNumberFilter::GetTypeId (void)
{
  static TypeId tid = TypeId ("ns3::SourcePortNumberFilter")
    .SetParent<FilterElement> ()
    .SetGroupName("DiffServ")
    .AddAttribute("Port",
                   "Source port number",
                   UintegerValue (6666),
                   MakeUintegerAccessor (&SourcePortNumberFilter::value),
                   MakeUintegerChecker<uint32_t> ())
  ;
  return tid;
}

// Constructors
SourcePortNumberFilter::SourcePortNumberFilter ()
{
  std::cout << "Source port number filter constructor" << "\n";
  NS_LOG_FUNCTION (this);
}

SourcePortNumberFilter::~SourcePortNumberFilter()
{
  NS_LOG_FUNCTION (this);
}

bool 
SourcePortNumberFilter::Match (Ptr<ns3::Packet> packet)
{
  //NS_LOG_FUNCTION (this << packet);
  std::cout << "THIS IS A SOURCE PORT FILTER ELEMENT << \n";
  Ptr<ns3::Packet> copy = packet->Copy();
  if (copy->GetSize() == 0)
  {
    std::cout << "empty packet...\n";
    return false;
  }

/* One of these headers should match eventually */




  packet->Print(std::cout);
  std::cout << "\n";
      // Remove p2pHeader
  PppHeader removedp2pHeader;
  copy->RemoveHeader(removedp2pHeader);
  // Get UDP header
  UdpHeader header;
  // std::cout << "peeking header...\n";
  copy->PeekHeader(header); // Get the IPv4 header from the packet


  // Remove Ipv4Header
  Ipv4Header removedHeader;
  copy->RemoveHeader(removedHeader);
  // if (header)
  // {
  //   std::cout << "header was null\n";
  //   return false;
  // }
  // std::cout << "checking address...\n";
  uint32_t srcPort = header.GetSourcePort();
  bool matches = srcPort == value;
  std::cout << "src port: " << srcPort << " vs value: " << value << "\tmatches: "<< matches << "\n";
  return srcPort == value;
}

void 
SourcePortNumberFilter::SetPort (uint32_t port)
{
  value = port;
}
} // Namespace ns3
