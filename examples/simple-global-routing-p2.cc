/* -*-  Mode: C++; c-file-style: "gnu"; indent-tabs-mode:nil; -*- */
/*
 * Copyright (c) 2008-2009 Strasbourg University
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
 * Author: David Gross <gdavid.devel@gmail.com>
 *         Sebastien Vincent <vincent@clarinet.u-strasbg.fr>
 */

// Network topology
// //
// //             n0   r    n1
// //             |    _    |
// //             ====|_|====
// //                router
// //
// // - Tracing of queues and packet receptions to file "simple-routing-ping6.tr"

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/internet-module.h"
#include "ns3/csma-module.h"
#include "ns3/internet-apps-module.h"
#include "ns3/ipv6-static-routing-helper.h"
#include "ns3/ipv6-routing-table-entry.h"
#include "ns3/diffserv.h"
#include "ns3/spq.h"
#include "ns3/applications-module.h"
#include "ns3/udp-app-helper.h"


using namespace ns3;


NS_LOG_COMPONENT_DEFINE ("SimpleGlobalRoutingExamplep2");

int main (int argc, char** argv)
{
  #if 0 
    LogComponentEnable ("Ipv6L3Protocol", LOG_LEVEL_ALL);
    LogComponentEnable ("Icmpv6L4Protocol", LOG_LEVEL_ALL);
    LogComponentEnable ("Ipv6StaticRouting", LOG_LEVEL_ALL);
    LogComponentEnable ("Ipv6Interface", LOG_LEVEL_ALL);
    LogComponentEnable ("Ping6Application", LOG_LEVEL_ALL);
  #endif



  Address origin;
  Address destination;
  Address router;



  // Print the pretty json to the terminal

  /* Default Stuff */


  NS_LOG_INFO ("Create nodes.");
  /* n0 is the client */
  Ptr<Node> n0 = CreateObject<Node> ();
  /* r is the router */
  Ptr<Node> r = CreateObject<Node> ();
  /* n1 is the server */
  Ptr<Node> n1 = CreateObject<Node> ();

  /* From client to router node */
  NodeContainer net1 (n0, r);

  /* From router to server node */
  NodeContainer net2 (r, n1);

  /* All the nodes */
  NodeContainer all (n0, r, n1);

  NS_LOG_INFO ("Create IPv6 Internet Stack");
  InternetStackHelper internetv4;
  internetv4.Install (all);

  NS_LOG_INFO ("Create channels.");
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (5000000));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  /* Add our own queue */
  csma.SetQueue("ns3::Spq<Packet>");

  NetDeviceContainer d1 = csma.Install (net1);
  NetDeviceContainer d2 = csma.Install (net2);

  /* So now we have created the nodes and CSMA with the correct queue.

  We want to send UDP packets now */

  Ipv4AddressHelper ipv4;
  // This should be n0 (origin)
  ipv4.SetBase ("10.1.1.0", "255.255.255.0");
  Ipv4InterfaceContainer i1 = ipv4.Assign (d1);
  origin = Address (i1.GetAddress (1));
  std::cout << "Origin: " << origin << "\n";

  // This should be routing node?
  //ipv4.SetBase ("10.1.2.0", "255.255.255.0");
  //Ipv4InterfaceContainer i1 = ipv4.Assign (d1);
  //origin = Address (i1.GetAddress (1));
  //std::cout << "Origin: " << origin << "\n";

  // This should be n1 (destination)
  ipv4.SetBase ("10.1.3.0", "255.255.255.0");
  Ipv4InterfaceContainer i2 = ipv4.Assign (d2);
  // Set clients address to the first udp node
  destination = Address (i2.GetAddress (1));
  std::cout << "Destination: " << destination << "\n";

  /* Create an application to send UDP packets from n0 to n1 via r */

  //
  // Create one udpServer applications on node one and start
  //

  uint16_t port = 4000;
  UdpServerHelper server (port);
  ApplicationContainer apps = server.Install (n1);
  apps.Start (Seconds (1.0));
  apps.Stop (Seconds (10.0));

  //
  // Create one UdpClient application to send UDP datagrams from node zero to
  // node one.
  //
  
  uint32_t MaxPacketSize = 1024;
  Time interPacketInterval = Seconds (0.05);
  uint32_t maxPacketCount = 320;
  UdpClientHelper client (destination, port);
  client.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  client.SetAttribute ("Interval", TimeValue (interPacketInterval));
  client.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  apps = client.Install (n0);
  apps.Start (Seconds (2.0));
  apps.Stop (Seconds (10.0));


/* Tracing */
  AsciiTraceHelper ascii;
  csma.EnableAsciiAll (ascii.CreateFileStream ("simple-routing-ping6.tr"));
  csma.EnablePcapAll ("simple-routing-ping6", true);

  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
  NS_LOG_INFO ("Done.");
}