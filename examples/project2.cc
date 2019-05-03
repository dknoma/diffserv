/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */
/*
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

// Network topology
//
// (S)-----(R1)[compression]<--->compression-link<---->[decompression](R2)-----(R)
//
// - UDP flows from S to the R1 P2P IP Link where compression may occur
//       R1 then relays packets, compressed or not, to R2 who then relays them to
//       receiver node R.

#include <fstream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/applications-module.h"
#include "ns3/udp-client-server-helper.h"
// #include "ns3/project2-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/Filter.h"
#include "ns3/FilterElement.h"
#include "ns3/object-vector.h"
#include "ns3/SourceIPAddressFilter.h"
#include "ns3/DestinationIPAddressFilter.h"
#include "ns3/SourcePortNumberFilter.h"
#include "ns3/DestinationPortNumberFilter.h"
#include "ns3/DestinationMaskFilter.h"
#include "ns3/SourceMaskFilter.h"
#include "ns3/ProtocolNumberFilter.h"
#include "ns3/ipv4-address.h"
#include "ns3/ipv4-header.h"
#include "ns3/udp-header.h"
#include "ns3/spq.h"
#include "ns3/drr.h"
#include "ns3/ptr.h"
#include "ns3/packet.h"
#include "ns3/project2-module.h"
#include "ns3/uinteger.h"

using namespace ns3;

NS_LOG_COMPONENT_DEFINE ("PROJECT_2_SCRATCH");

int
main (int argc, char *argv[])
{
  LogComponentEnable ("UdpClient", LOG_LEVEL_INFO);
  LogComponentEnable ("UdpServer", LOG_LEVEL_INFO);

  bool usingSpq = true;
  uint16_t maxBandwidth = 4;
  Address udpAInterfaces;
  Address udpBInterfaces;
  Address p2pInterfaces;

// command line interface. Allow for additional parameters to change application.
  CommandLine cmd;
  cmd.AddValue ("maxBandwidth", "Maximum bandwidth", maxBandwidth);
  cmd.AddValue ("usingSpq", "Do SPQ simulation or DRR simulation", usingSpq);
  cmd.Parse (argc, argv);
  printf("Specified maximum bandwidth: %d\n", maxBandwidth);

// Set data rate for point to point
  std::string dataRate (std::to_string(maxBandwidth));
  NodeContainer preP2p;
  preP2p.Create(1);
  NodeContainer postP2p;
  postP2p.Create(1);
  NodeContainer p2pNodes;
  // p2pNodes.Create (2);
  p2pNodes.Add (preP2p.Get (0));
  p2pNodes.Add (postP2p.Get (0));

  // Spq spq;
  // Ptr<ns3::Packet> packet = Ptr<ns3::Packet>(&dummyPacket);
  // Setup p2p nodes for the IP link
  PointToPointHelper pointToPoint;
  pointToPoint.SetDeviceAttribute ("DataRate", StringValue (dataRate + "Mbps"));
  pointToPoint.SetDeviceAttribute ("Compression", BooleanValue (false));
  pointToPoint.SetChannelAttribute ("Delay", StringValue ("2ms"));

  switch(usingSpq) 
    {
  	  case true:
  	    {
  		// doing SPQ
  		  std::cout << "Doing SPQ\n";
  		  pointToPoint.SetQueue("ns3::Spq");

  		  // TODO: Instantiate SPQ and set p2p queue to SPQ
  		  //	   SPQ: requires app low prio app A and high prio app B (starts later)
  		  //			total of 2 udp client server apps
  		  //	   DRR: requires 3 apps that start at same time
  		  //			set differen ip, port, etc to determine which queue they go into

		  // NodeContainer comp;
		  // comp.Create(1);
		  // NodeContainer decomp;
		  // decomp.Create(1);
		//
		// Explicitly create the nodes required by the topology (shown above).
		//
		  NS_LOG_INFO ("Create nodes.");
		  NodeContainer appA;
		  appA.Create(2);
		  NodeContainer appB;
		  appB.Create(2);
		  // NodeContainer udpNodes;
		  // udpNodes.Add (sender.Get (0));
		  // udpNodes.Add (receiver.Get (0));
		  // udpNodes.Create (2);

		// p2pNetDevice container
		  NetDeviceContainer p2pDevices = pointToPoint.Install (p2pNodes);

		  NS_LOG_INFO ("Create channels.");
		//
		// Explicitly create the channels required by the topology (shown above).
		//
		  CsmaHelper csma;
		  csma.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
		  csma.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
		  csma.SetDeviceAttribute ("Mtu", UintegerValue (1400));

		  NetDeviceContainer udpContainerA = csma.Install (appA);  // Install UDP nodes
		  NetDeviceContainer udpContainerB = csma.Install (appB);  // Install UDP nodes

		  // Internet
		  InternetStackHelper internet;
		  internet.Install (p2pNodes);
		  internet.Install (appA);
		  internet.Install (appB);

		  // CsmaHelper csmaServer;
		  // csmaServer.SetChannelAttribute ("DataRate", DataRateValue (DataRate (5000000)));
		  // csmaServer.SetChannelAttribute ("Delay", TimeValue (MilliSeconds (2)));
		  // csmaServer.SetDeviceAttribute ("Mtu", UintegerValue (1400));
		  // NetDeviceContainer udpContainer = csmaClient.Install (udpNodes);  // Install UDP nodes

		//
		// We've got the "hardware" in place.  Now we need to add IP addresses.
		//
		  NS_LOG_INFO ("Assign IP Addresses.");
	      Ipv4AddressHelper ipv4;
	      // P2P nodes
	      ipv4.SetBase ("10.1.1.0", "255.255.255.0");
	      Ipv4InterfaceContainer p2pIp = ipv4.Assign (p2pDevices);
	      // std::cout << "p2p address=" << p2pIp.GetAddress (1) << "\n";
	      p2pInterfaces = Address (p2pIp.GetAddress (1));
	      // UDP nodes
	      ipv4.SetBase ("10.1.2.0", "255.255.255.0");
	      Ipv4InterfaceContainer udpAIp = ipv4.Assign (udpContainerA);
	      udpAInterfaces = Address (udpAIp.GetAddress (1));
	      // Set clients address to the first udp node
	      ipv4.SetBase ("10.1.3.0", "255.255.255.0");
	      Ipv4InterfaceContainer udpBIp = ipv4.Assign (udpContainerB);
	      // Set clients address to the first udp node
	      udpBInterfaces = Address (udpBIp.GetAddress (1));

		  NS_LOG_INFO ("Create Applications.");
		  // // ApplicationContainer p2pRouter = pointToPoint.Install (p2pNodes.Get(0));
		  // pointToPoint.Start (Seconds (1.0));
		  // pointToPoint.Stop (Seconds (300.0));
		//
		// Create one UDP A applications on node one.
		//
		  uint16_t portA = 4000;
		  UdpServerHelper serverA (portA);
		  // serverA.Install (p2pNodes.Get (1));
		  ApplicationContainer appAServer = serverA.Install (appA.Get (1));
		  appAServer.Start (Seconds (1.0));
		  appAServer.Stop (Seconds (300.0));
		//
		// Create one UdpClient application to send UDP datagrams from node zero to
		// node one.
		//
		  uint32_t MaxPacketSize = 1024;
		  Time interPacketInterval = Seconds (0.015);
		  UdpClientHelper clientA (udpAInterfaces, portA);
		  clientA.SetAttribute ("Interval", TimeValue (interPacketInterval));
		  clientA.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
		  ApplicationContainer appAClient = clientA.Install (p2pNodes.Get (0));
		  appAClient.Start (Seconds (1.0));
		  appAClient.Stop (Seconds (300.0));

		  //
		  // APP B
		  //
		  uint16_t portB = 6000;
		  UdpServerHelper serverB (portB);
		  ApplicationContainer appBServer = serverB.Install (appB.Get (1));
		  appBServer.Start (Seconds (5.0));
		  appBServer.Stop (Seconds (300.0));
		//
		// Create one UdpClient application to send UDP datagrams from node zero to
		// node one.
		//
		  UdpClientHelper clientB (udpBInterfaces, portB);
		  clientB.SetAttribute ("Interval", TimeValue (interPacketInterval));
		  clientB.SetAttribute ("PacketSize", UintegerValue (MaxPacketSize));
		  ApplicationContainer appBClient = clientB.Install (p2pNodes.Get (0));
		  appBClient.Start (Seconds (5.0));
		  appBClient.Stop (Seconds (300.0));


		  // p2pServer.Start (Seconds (1.0));
		  // p2pServer.Stop (Seconds (300.0));

		  // // Install p2p nodes into the app
		  // ApplicationContainer p2pClient = appClient.Install (p2pNodes.Get (0));
		  // p2pClient.Start (Seconds (2.0));
		  // p2pClient.Stop (Seconds (300.0));

		// #if 0
		// set fill for packet data
		// #endif

		  // Init routers (PointToPoint devices)
		  Ipv4GlobalRoutingHelper::PopulateRoutingTables ();

		  AsciiTraceHelper ascii;;
		  csma.EnableAsciiAll (ascii.CreateFileStream ("udp.tr"));
		  // pointToPoint.EnableAsciiAll (ascii.CreateFileStream ("p2p.tr"));

		  // receiver.EnablePcapAll("UDPreceiver", false);
		  // sender.EnablePcapAll("UDPsender", false);
		  // decomp.EnablePcapAll("Decompression", false);
		  // comp.EnablePcapAll("Compression", false);
		  // csma.EnablePcap ("UDPreceiver", receiver, false);
		  // csma.EnablePcap ("UDPsender", sender, false);
		  pointToPoint.EnablePcap ("Pre_SPQ", preP2p, false);
		  pointToPoint.EnablePcap ("Post_SPQ", postP2p, false);
		  // csma.EnablePcapAll ("udp-app", false);
		  // pointToPoint.EnablePcapAll ("project2", false);

		//
		// Now, do the actual simulation.
		//
		  NS_LOG_INFO ("Run Simulation.");
		  Simulator::Run ();
		  Simulator::Destroy ();
		  NS_LOG_INFO ("Done.");
  		  break;
  	    }
	  case false:
	    {
		  // doing DRR
  		  std::cout << "Doing DRR\n";
  		  // pointToPoint.SetQueue("ns3::Drr");
		  break;
		}
    }
	// Filter filter;
	// std::string srcAddrStr = "66.66.66.66";
	// std::string destAddrStr = "222.1.1.56";
	// const char* srcAddr = srcAddrStr.c_str();
	// const char* destAddr = destAddrStr.c_str();
	// uint32_t srcPort = 6666;
	// uint32_t destPort = 4200;
	// uint32_t protocol = 111;

	// // Ipv4Mask masku = Ipv4Mask("222.1.1.0");
	// // uint16_t prefixLength = masku.GetPrefixLength();
	// // uint32_t addrBits = masku.Get();
	// // // Ipv4Address base = Ipv4Address(masku.GetInverse());
	// // std::cout << masku << " | | | | " << prefixLength << " [] " << addrBits << " [][] " 
	// // 	<< ((addrBits >> 24) & 0xff) << "\n";

	// // ip address filters
	// SourceIPAddressFilter srcAddrFilter;
	// srcAddrFilter.SetAddress(srcAddr);
	// DestinationIPAddressFilter destAddrFilter;
	// destAddrFilter.SetAddress(destAddr);
	// // mask filters
	// DestinationMaskFilter destMaskFilter;
	// destMaskFilter.SetMask("222.1.1.0");
	// SourceMaskFilter srcMaskFilter;
	// srcMaskFilter.SetMask("67.66.67.0");
	// // port number filters
	// SourcePortNumberFilter srcPortFilter;
	// srcPortFilter.SetPort(srcPort);
	// DestinationPortNumberFilter destPortFilter;
	// destPortFilter.SetPort(destPort);
	// // protocol number filter
	// ProtocolNumberFilter protocolFilter;
	// protocolFilter.SetProtocol(protocol);

	// std::vector<FilterElement*> elements;
	// elements.push_back(&srcAddrFilter);
	// elements.push_back(&destAddrFilter);
	// elements.push_back(&srcPortFilter);
	// elements.push_back(&destPortFilter);
	// elements.push_back(&protocolFilter);
	// elements.push_back(&destMaskFilter);
	// elements.push_back(&srcMaskFilter);

	// // filter.SetAttribute ("FilterElements", ObjectVectorValue ());
	// filter.SetFilterElements(elements);

	// ns3::Packet::EnablePrinting();

	// Packet dummyPacket;
	// Ipv4Address srcAddress = Ipv4Address(srcAddr);
	// Ipv4Address destAddress = Ipv4Address(destAddr);



	// Ipv4Header ipv4Header;
	// ipv4Header.SetSource(srcAddress);
	// ipv4Header.SetDestination(destAddress);
	// ipv4Header.SetProtocol(111);

	// UdpHeader udpHeader;
	// udpHeader.SetSourcePort(6666);
	// udpHeader.SetDestinationPort(4200);
	// // udpHeader.InitializeChecksum(srcAddress, destAddress, protocol);

	// dummyPacket.AddHeader(udpHeader);
	// dummyPacket.AddHeader(ipv4Header);

	// Ptr<ns3::Packet> packet = Ptr<ns3::Packet>(&dummyPacket);

	// // Print out the packet contents
	// packet->Print(std::cout);
	// std::cout << "\n";

	// bool a = filter.Match(packet);
	// std::cout << "Packet matches filter: " << a << "\n";
}
