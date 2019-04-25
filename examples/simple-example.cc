/* -*- Mode:C++; c-file-style:"gnu"; indent-tabs-mode:nil; -*- */

/* Will probably need two of files: 1 for SPQ and 1 for DRR.

This one is for SPQ

 */
#include <fstream>
#include "ns3/core-module.h"
#include "ns3/csma-module.h"
#include "ns3/packet.h"
#include "ns3/applications-module.h"
#include "ns3/point-to-point-module.h"
#include "ns3/internet-module.h"
#include "ns3/udp-app-helper.h"
#include "ns3/diffserv.h"
#include "ns3/spq.h"
#include "ns3/drr.h"
#include "ns3/Filter.h"
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
	std::string pathToConfigFile = "";
	std::string queues = "";
	std::string queue1Priority = "";
	std::string queue2Priority = "";

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

  /* Test SPQ here. Instantiate diffserv, traffic class, filters */
  Ptr<Packet> packet = Create<Packet>();
  Spq spq;
  TrafficClass<Packet> *trafficClassPointer1 = new TrafficClass<Packet>();
  TrafficClass<Packet> *trafficClassPointer2 = new TrafficClass<Packet>();

  /* Set each queue's priority level */
  int queue1PriorityInt = std::stoi(queue1Priority);
  int queue2PriorityInt = std::stoi(queue2Priority);
  trafficClassPointer1 -> SetPriorityLevel(queue1PriorityInt);
  trafficClassPointer2 -> SetPriorityLevel(queue2PriorityInt);
  spq.AddTrafficClass(trafficClassPointer1);
  spq.AddTrafficClass(trafficClassPointer2);
  Filter filter;
  Filter *filter_p = new Filter(filter);
  Filter filter2;
  Filter *filter_p2 = new Filter(filter2);
  trafficClassPointer1 -> AddFilter(filter_p);
  trafficClassPointer2 -> AddFilter(filter_p2);
  spq.DoEnqueue(packet);
  spq.DoDequeue();

  Drr drr;

  /* Create packet */
  /* Filter packet into correct queue */


  
}


