/*
 * ============================================
 * file: voting.h
 * @Author Myron Tsatsarakis (myrontsa@csd.uoc.gr)
 * @Version 26/11/2024
 *
 * @e-mail hy240@csd.uoc.gr
 *
 * @brief Structure and function declarations
 *        for CS240 Project Phase 2,
 *        Winter Semester 2024-2025
 * ============================================
 */

#ifndef VOTING_H
#define VOTING_H

#include <stdbool.h>
#include <stdio.h>

#define DISTRICTS_SZ 56
#define PARTIES_SZ 5

struct District {
    int did;
    int seats;
    int blanks;
    int invalids;
    int partyVotes[PARTIES_SZ];
};

struct Voter {
    int vid;
    bool voted;
    struct Voter* parent;
    struct Voter* lc;
    struct Voter* rc;
};
struct Station {
    int sid;
    int did;
    int registered;
    struct Voter* voters;
    struct Station* next;
};

struct Candidate {
    int cid;
    int did;
    int votes;
    bool isElected;
    struct Candidate* lc;
    struct Candidate* rc;
};
struct Party {
    int pid;
    int electedCount;
    struct Candidate* candidates;
};

struct ElectedCandidate {
    int cid;
    int did;
    int pid;
    struct ElectedCandidate* next;
};

// Enable in Makefile
#ifdef DEBUG_PRINTS_ENABLED
#define DebugPrint(...) printf(__VA_ARGS__);
#else
#define DebugPrint(...)
#endif

void EventAnnounceElections(int parsedMaxStationsCount, int parsedMaxSid);
void EventCreateDistrict(int did, int seats);
void EventCreateStation(int sid, int did);
void EventRegisterVoter(int vid, int sid);
void EventRegisterCandidate(int cid, int pid, int did);
void EventVote(int vid, int sid, int cid, int pid);
void EventCountVotes(int did);
void EventFormParliament(void);
void EventPrintDistrict(int did);
void EventPrintStation(int sid);
void EventPrintParty(int pid);
void EventPrintParliament(void);
void EventBonusUnregisterVoter(int vid, int sid);
void EventBonusFreeMemory(void);
int HashFunction(int id);
void RecurvPrinterVoter(struct Voter *root);
void RecurvPrinterCandidate(struct Candidate *root , int did);
struct Voter *PreOrderRecurvFinder(struct Voter *root , int vid);
int HeapDeleteMin(struct Candidate **A);
void ElectPartyCandidatesInDistrict(int pid, int did, int partyElected);
void TakeTreeNodes(struct Candidate *root , struct Candidate **heap , int partyElected ,int did);
void HeapInsert(struct Candidate **A, struct Candidate *K);
void RecurvElectedCandidateFinder(struct Candidate *root , int pid);
void InsertToSortedList(struct Candidate *person , int pid);
struct Voter* FindLastOfTree(struct Station *tmp);
struct Voter *PreOrderRecurvDeleter(struct Voter *root, int vid, struct Station *tmo);
void FreeVoters(struct Voter *root);
void FreeCandidates(struct Candidate *root);










#endif
