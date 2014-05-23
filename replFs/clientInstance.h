/*
 * clientInstance.h
 *
 *  Created on: May 17, 2014
 *      Author: songhan
 */

#ifndef CLIENTINSTANCE_H_
#define CLIENTINSTANCE_H_
#include "networkInstance.h"
#include <map>
#include <set>
#include <string>

class ClientInstance {
 private:
  int fd;
  std::string fileName;
  int numServers;
  uint32_t GUID;
  uint32_t seqNum;
  uint32_t transNum;
  uint32_t blockID;
  std::map<int, int> mapSeqNum;  //mapping from machine id to that machine's seq number
  std::map<int, int>::iterator iterSeqNum;  //mapping from machine id to that machine's seq number
  WriteBlockPkt* pendingBlocks[MAX_PENDING];  //mapping from block id to packet that contains the payload
  Network *N;
  bool isOpened;

 public:
  ClientInstance();
  ClientInstance(unsigned short port, int dropRate, int numServers);
  virtual ~ClientInstance();
  int OpenFile(char* fileName);
  int WriteBlock(int fd, char * strData, int byteOffset, int blockSize);
  int CommitVoting(int fd);
  int CommitFinal(int fd);
  int Abort(int fd);
  int CloseFile(int fd);
 private:
  bool isTimeOut(timeval oldTime, long timeOut);
  int collectResponse(PacketBase *p);
  bool mismatch(PacketBase *ps, PacketBase *pr);
  void cleanup();
};
#endif /* CLIENTINSTANCE_H_ */

