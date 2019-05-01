/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

/* Will probably need two of files: 1 for SPQ and 1 for DRR.

This one is for SPQ

 */
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/udp-app-helper.h"
#include "ns3/spq.h"
#include <nlohmann/json.hpp>
#include <iomanip>
#include <stdio.h>
#include <string.h>
#include <assert.h>

using namespace ns3;
using json = nlohmann::json;


int 
main (int argc, char *argv[])
{
  std::string pathToConfigFile = "config.json";
	std::string queues = "";
	std::string queue1Priority = "";
	std::string queue2Priority = "";

	bool useV6 = false;
  bool verbose = true;
  Address udpServerInterfaces;
  Address p2pInterfaces;
  CommandLine cmd;
  cmd.AddValue ("verbose", "Tell application to log if true", verbose);
	cmd.AddValue ("config", "Config File", pathToConfigFile);
  cmd.Parse (argc,argv);
  // Read config file; take inputstream from the file and put it all in json j
  std::ifstream jsonIn(pathToConfigFile);
  json j;
  jsonIn >> j;


	// Print the pretty json to the terminal
  // std::cout << std::setw(4) << j << std::endl;

	// Get the string value from protocolsToCompress and print it
  queues = j["numberOfQueues"].get<std::string>();
  queue1Priority = j["queue1Priority"].get<std::string>();
  queue2Priority = j["queue2Priority"].get<std::string>();
  std::string dataRate (std::to_string(4));
  std::cout << "here" << "\n";
  std::cout << queues << "\n";
  std::cout << queue1Priority << "\n";
  std::cout << queue2Priority << "\n";

  /* Set up p2p device to test application */
 // Set data rate for point to point
  //std::string dataRate (std::to_string(maxBandwidth));
  NodeContainer p2pNodes;
  p2pNodes.Create (2);

  // Setup p2p nodes for the IP link
  PointToPointHelper pointToPoint;
  //pointToPoint.SetDeviceAttribute ("DataRate", StringValue (dataRate + "Mbps"));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));
  pointToPoint.SetQueue("ns3::Spq");
//
// Explicitly create the nodes required by the topology (shown above).
//
//  NS_LOG_INFO ("Create nodes.");
  NodeContainer udpNodes;
  udpNodes.Create (2);

// p2pNetDevice container
  NetDeviceContainer p2pDevices = pointToPoint.Install (p2pNodes);

//  NS_LOG_INFO ("Create channels.");
//
// Explicitly create the channels required by the topology (shown above).
//
  CsmaHelper csma;
  csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  csma.SetDeviceAttribute ("Mtu", UintegerValue (1400));

  NetDeviceContainer udpContainer = csma.Install (udpNodes);  // Install UDP nodes

  // Internet
  InternetStackHelper internet;
  internet.Install (udpNodes);
  internet.Install (p2pNodes);

  // CsmaHelper csmaServer;
  // csmaServer.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
  // csmaServer.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
  // csmaServer.SetDeviceAttribute ("Mtu", UintegerValue (1400));
  // NetDeviceContainer udpContainer = csmaClient.Install (udpNodes);  // Install UDP nodes

//
// We've got the "hardware" in place.  Now we need to add IP addresses.
//
//  NS_LOG_INFO ("Assign IP Addresses.");
  if (useV6 == false)
    {
      Ipv4AddressHelper ipv4;
      // P2P nodes
      ipv4.SetBase ("10.1.1.0", "255.255.255.0");
      Ipv4InterfaceContainer p2pIp = ipv4.Assign (p2pDevices);
      // std::cout << "p2p address=" << p2pIp.GetAddress (1) << "\n";
      p2pInterfaces = Address (p2pIp.GetAddress (1));
      // UDP nodes
      ipv4.SetBase ("10.1.2.0", "255.255.255.0");
      Ipv4InterfaceContainer udpIp = ipv4.Assign (udpContainer);
      // Set clients address to the first udp node
      udpServerInterfaces = Address (udpIp.GetAddress (1));
    }
  else
    {
      Ipv6AddressHelper ipv6;
      ipv6.SetBase ("2001:0000:f00d:cafe::", Ipv6Prefix (64));
      Ipv6InterfaceContainer i6 = ipv6.Assign (udpContainer);
      udpServerInterfaces = Address(i6.GetAddress (1,1));
    }

//  NS_LOG_INFO ("Create Applications.");
//
// Create one udpServer applications on node one.
//
  uint16_t port = 4000;
  uint32_t maxPacketCount = 6000;
  UdpAppServerHelper server (port);
  server.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  ApplicationContainer udpApps = server.Install (udpNodes.Get (1));
  udpApps.Start (Seconds (0));
  udpApps.Stop (Seconds (3000.0));

//
// Create one UdpClient application to send UDP datagrams from node zero to
// node one.
//
  uint32_t MaxPacketSize = 1024;
  Time interPacketInterval = Seconds (0.015);
  UdpAppClientHelper appClient (udpServerInterfaces, port);
  // UdpAppClientHelper appClient (p2pInterfaces, port);
  appClient.SetAttribute ("MaxPackets", UintegerValue (maxPacketCount));
  appClient.SetAttribute ("Interval", TimeValue (interPacketInterval));
  appClient.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
  // Install udp client node into the app
  std::cout << "First round\n";
  udpApps = appClient.Install (udpNodes.Get (0));
  // udpApps.Start (Seconds (1200.0));
  // udpApps.Stop (Seconds (3000.0));

  // uint8_t fill[] = { 0, 1, 0, 1, 1, 0 };
  // appClient.SetFill (udpApps.Get (0), fill, sizeof(fill), 1024);

  // Install p2p nodes into the app
  ApplicationContainer p2pClient = appClient.Install (p2pNodes.Get (0));
  // p2pClient.Start (Seconds (2.0));
  // p2pClient.Stop (Seconds (300.0));

// #if 0
// set fill for packet data
// #endif

  // Init routers (PointToPoint devices)
  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

  AsciiTraceHelper ascii;;
  csma.EnableAsciiAll (ascii.CreateFileStream ("udp-app-l.tr"));
  csma.EnablePcapAll ("udp-app-l", false);
  pointToPoint.EnablePcapAll ("udp-p2p-l", false);

//
// Now, do the actual simulation.
//
//  NS_LOG_INFO ("Run Simulation.");
  Simulator::Run ();
  Simulator::Destroy ();
//  NS_LOG_INFO ("Done.");
}


