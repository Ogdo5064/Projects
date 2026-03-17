#include "voting.h"
#include <stdlib.h>
#include <assert.h>

#define PRIMES_SZ 1024
const int Primes[PRIMES_SZ] = {
    0, 1, 2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107, 109, 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239, 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379, 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521, 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661, 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827, 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991, 997, 1009, 1013, 1019, 1021, 1031, 1033, 1039, 1049, 1051, 1061, 1063, 1069, 1087, 1091, 1093, 1097, 1103, 1109, 1117, 1123, 1129, 1151, 1153, 1163, 1171, 1181, 1187, 1193, 1201, 1213, 1217, 1223, 1229, 1231, 1237, 1249, 1259, 1277, 1279, 1283, 1289, 1291, 1297, 1301, 1303, 1307, 1319, 1321, 1327, 1361, 1367, 1373, 1381, 1399, 1409, 1423, 1427, 1429, 1433, 1439, 1447, 1451, 1453, 1459, 1471, 1481, 1483, 1487, 1489, 1493, 1499, 1511, 1523, 1531, 1543, 1549, 1553, 1559, 1567, 1571, 1579, 1583, 1597, 1601, 1607, 1609, 1613, 1619, 1621, 1627, 1637, 1657, 1663, 1667, 1669, 1693, 1697, 1699, 1709, 1721, 1723, 1733, 1741, 1747, 1753, 1759, 1777, 1783, 1787, 1789, 1801, 1811, 1823, 1831, 1847, 1861, 1867, 1871, 1873, 1877, 1879, 1889, 1901, 1907, 1913, 1931, 1933, 1949, 1951, 1973, 1979, 1987, 1993, 1997, 1999, 2003, 2011, 2017, 2027, 2029, 2039, 2053, 2063, 2069, 2081, 2083, 2087, 2089, 2099, 2111, 2113, 2129, 2131, 2137, 2141, 2143, 2153, 2161, 2179, 2203, 2207, 2213, 2221, 2237, 2239, 2243, 2251, 2267, 2269, 2273, 2281, 2287, 2293, 2297, 2309, 2311, 2333, 2339, 2341, 2347, 2351, 2357, 2371, 2377, 2381, 2383, 2389, 2393, 2399, 2411, 2417, 2423, 2437, 2441, 2447, 2459, 2467, 2473, 2477, 2503, 2521, 2531, 2539, 2543, 2549, 2551, 2557, 2579, 2591, 2593, 2609, 2617, 2621, 2633, 2647, 2657, 2659, 2663, 2671, 2677, 2683, 2687, 2689, 2693, 2699, 2707, 2711, 2713, 2719, 2729, 2731, 2741, 2749, 2753, 2767, 2777, 2789, 2791, 2797, 2801, 2803, 2819, 2833, 2837, 2843, 2851, 2857, 2861, 2879, 2887, 2897, 2903, 2909, 2917, 2927, 2939, 2953, 2957, 2963, 2969, 2971, 2999, 3001, 3011, 3019, 3023, 3037, 3041, 3049, 3061, 3067, 3079, 3083, 3089, 3109, 3119, 3121, 3137, 3163, 3167, 3169, 3181, 3187, 3191, 3203, 3209, 3217, 3221, 3229, 3251, 3253, 3257, 3259, 3271, 3299, 3301, 3307, 3313, 3319, 3323, 3329, 3331, 3343, 3347, 3359, 3361, 3371, 3373, 3389, 3391, 3407, 3413, 3433, 3449, 3457, 3461, 3463, 3467, 3469, 3491, 3499, 3511, 3517, 3527, 3529, 3533, 3539, 3541, 3547, 3557, 3559, 3571, 3581, 3583, 3593, 3607, 3613, 3617, 3623, 3631, 3637, 3643, 3659, 3671, 3673, 3677, 3691, 3697, 3701, 3709, 3719, 3727, 3733, 3739, 3761, 3767, 3769, 3779, 3793, 3797, 3803, 3821, 3823, 3833, 3847, 3851, 3853, 3863, 3877, 3881, 3889, 3907, 3911, 3917, 3919, 3923, 3929, 3931, 3943, 3947, 3967, 3989, 4001, 4003, 4007, 4013, 4019, 4021, 4027, 4049, 4051, 4057, 4073, 4079, 4091, 4093, 4099, 4111, 4127, 4129, 4133, 4139, 4153, 4157, 4159, 4177, 4201, 4211, 4217, 4219, 4229, 4231, 4241, 4243, 4253, 4259, 4261, 4271, 4273, 4283, 4289, 4297, 4327, 4337, 4339, 4349, 4357, 4363, 4373, 4391, 4397, 4409, 4421, 4423, 4441, 4447, 4451, 4457, 4463, 4481, 4483, 4493, 4507, 4513, 4517, 4519, 4523, 4547, 4549, 4561, 4567, 4583, 4591, 4597, 4603, 4621, 4637, 4639, 4643, 4649, 4651, 4657, 4663, 4673, 4679, 4691, 4703, 4721, 4723, 4729, 4733, 4751, 4759, 4783, 4787, 4789, 4793, 4799, 4801, 4813, 4817, 4831, 4861, 4871, 4877, 4889, 4903, 4909, 4919, 4931, 4933, 4937, 4943, 4951, 4957, 4967, 4969, 4973, 4987, 4993, 4999, 5003, 5009, 5011, 5021, 5023, 5039, 5051, 5059, 5077, 5081, 5087, 5099, 5101, 5107, 5113, 5119, 5147, 5153, 5167, 5171, 5179, 5189, 5197, 5209, 5227, 5231, 5233, 5237, 5261, 5273, 5279, 5281, 5297, 5303, 5309, 5323, 5333, 5347, 5351, 5381, 5387, 5393, 5399, 5407, 5413, 5417, 5419, 5431, 5437, 5441, 5443, 5449, 5471, 5477, 5479, 5483, 5501, 5503, 5507, 5519, 5521, 5527, 5531, 5557, 5563, 5569, 5573, 5581, 5591, 5623, 5639, 5641, 5647, 5651, 5653, 5657, 5659, 5669, 5683, 5689, 5693, 5701, 5711, 5717, 5737, 5741, 5743, 5749, 5779, 5783, 5791, 5801, 5807, 5813, 5821, 5827, 5839, 5843, 5849, 5851, 5857, 5861, 5867, 5869, 5879, 5881, 5897, 5903, 5923, 5927, 5939, 5953, 5981, 5987, 6007, 6011, 6029, 6037, 6043, 6047, 6053, 6067, 6073, 6079, 6089, 6091, 6101, 6113, 6121, 6131, 6133, 6143, 6151, 6163, 6173, 6197, 6199, 6203, 6211, 6217, 6221, 6229, 6247, 6257, 6263, 6269, 6271, 6277, 6287, 6299, 6301, 6311, 6317, 6323, 6329, 6337, 6343, 6353, 6359, 6361, 6367, 6373, 6379, 6389, 6397, 6421, 6427, 6449, 6451, 6469, 6473, 6481, 6491, 6521, 6529, 6547, 6551, 6553, 6563, 6569, 6571, 6577, 6581, 6599, 6607, 6619, 6637, 6653, 6659, 6661, 6673, 6679, 6689, 6691, 6701, 6703, 6709, 6719, 6733, 6737, 6761, 6763, 6779, 6781, 6791, 6793, 6803, 6823, 6827, 6829, 6833, 6841, 6857, 6863, 6869, 6871, 6883, 6899, 6907, 6911, 6917, 6947, 6949, 6959, 6961, 6967, 6971, 6977, 6983, 6991, 6997, 7001, 7013, 7019, 7027, 7039, 7043, 7057, 7069, 7079, 7103, 7109, 7121, 7127, 7129, 7151, 7159, 7177, 7187, 7193, 7207, 7211, 7213, 7219, 7229, 7237, 7243, 7247, 7253, 7283, 7297, 7307, 7309, 7321, 7331, 7333, 7349, 7351, 7369, 7393, 7411, 7417, 7433, 7451, 7457, 7459, 7477, 7481, 7487, 7489, 7499, 7507, 7517, 7523, 7529, 7537, 7541, 7547, 7549, 7559, 7561, 7573, 7577, 7583, 7589, 7591, 7603, 7607, 7621, 7639, 7643, 7649, 7669, 7673, 7681, 7687, 7691, 7699, 7703, 7717, 7723, 7727, 7741, 7753, 7757, 7759, 7789, 7793, 7817, 7823, 7829, 7841, 7853, 7867, 7873, 7877, 7879, 7883, 7901, 7907, 7919, 7927, 7933, 7937, 7949, 7951, 7963, 7993, 8009, 8011, 8017, 8039, 8053, 8059, 8069, 8081, 8087, 8089, 8093, 8101, 8111, 8117, 8123};

const int DefaultDid = -1;
const int BlankDid = -1;
const int InvalidDid = -2;

int ParsedMaxStationsCount;
int ParsedMaxSid;
int P, A, B;

int STATION_SZ;

struct Station **Stations;
struct District Districts[DISTRICTS_SZ];
struct Party Parties[PARTIES_SZ];
struct ElectedCandidate *Parliament;

void EventAnnounceElections(int parsedMaxStationsCount, int parsedMaxSid)
{
    // DebugPrint("A %d %d\n", parsedMaxStationsCount, parsedMaxSid);
    int i = 0;

    ParsedMaxSid = parsedMaxSid;
    ParsedMaxStationsCount = parsedMaxStationsCount;
    while (i < PRIMES_SZ)
    {
        P = Primes[i];
        if (P > ParsedMaxSid)
            break;
        i++;
    }

    // metablhtes katholikhs klashs sunarthshs katakermatismou

    A = rand() % P;
    if (A == 0)
        A++;
    B = rand() % P;
    STATION_SZ = ParsedMaxStationsCount / 2;

    Stations = malloc(sizeof(struct Station *) * STATION_SZ); // allocate station structs x how many stations

    i = 0;
    while (i < DISTRICTS_SZ) // initialize all districs members
    {
        Districts[i].blanks = 0;
        Districts[i].did = -1;
        Districts[i].invalids = 0;
        Districts[i].seats = -1;

        int j = 0;
        while (j < PARTIES_SZ)
        {
            Districts[i].partyVotes[j] = 0;
            j++;
        }
        i++;
    }

    i = 0;
    while (i < PARTIES_SZ) // initialize all party members
    {
        Parties[i].pid = i;
        Parties[i].candidates = NULL;
        Parties[i].electedCount = 0;
        i++;
    }

    i = 0;
    while (i < STATION_SZ) // initialize all stations to NULL
    {
        Stations[i] = NULL;
        i++;
    }

    Parliament = NULL; // parliament list to NULL

    printf("A <%d> <%d>\nDONE\n", ParsedMaxStationsCount, ParsedMaxSid);
}
void EventCreateDistrict(int did, int seats)
{
    // DebugPrint("D %d %d\n", did, seats);

    //[1,2,3,4,5,6,7,8,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1,-1]
    // koitao sto kentro , an eisai -1 tote h ego eimai h thesi pou prepei h oi aristeres mou , analogos au3hse kai meiose ta left-right
    int left = 0, right = 55;
    int tmp = 0;
    while (left <= right) // binary search implementation for an array index in logn time
    {

        int mid = left + (right - left) / 2;

        if (Districts[mid].did == -1)
        {
            tmp = mid;
            right = mid - 1;
        }
        else
        {
            left = mid + 1;
        }
    }
    Districts[tmp].did = did;
    Districts[tmp].seats = seats;
    int i = 0;
    printf("D <%d> <%d>\nDistricts\n", did, seats);
    while (Districts[i].did != -1) // print existing districts
    {
        printf("<%d> ", Districts[i].did);
        i++;
    }
    printf("\nDONE\n");
}

void EventCreateStation(int sid, int did)
{
    // DebugPrint("S %d %d\n", sid, did);
    int hashkey = HashFunction(sid);                                        // generating hashkey
    struct Station *new = (struct Station *)malloc(sizeof(struct Station)); // allocating-initializing new node
    new->did = did;
    new->sid = sid;
    new->registered = 0;
    new->voters = NULL;
    new->next = NULL;
    struct Station *tmp = Stations[hashkey]; // new station we generated belongs to this chain of stations
    struct Station *prev = NULL;
    while (tmp != NULL && new->did < tmp->did) /*insertion in sorted list*/
    {
        prev = tmp;
        tmp = tmp->next;
    }

    if (prev == NULL) // list was empty OR list has 1 station(previous head) which failed new->did < tmp->did, become the new head
    {
        new->next = Stations[hashkey];
        Stations[hashkey] = new;
    }
    else
    {
        new->next = prev->next;
        prev->next = new;
    }
    printf("S <%d> <%d>\nStations <%d>\n", sid, did, hashkey);
    tmp = Stations[hashkey];
    while (tmp != NULL)
    {
        printf("<%d> ", tmp->sid);
        tmp = tmp->next;
    }
    printf("\nDONE\n");
}
void EventRegisterVoter(int vid, int sid)
{
    // prepei na bro to monopati pou prepei na paro gia na pao sto registered node , thelo na ftaso sto parent ths kainourgias theshs tou node
    // to monopati auto to apothikeuo se ena pinaka array
    printf("R <%d> <%d>\n", vid, sid);
    int array[100];
    int hashkey = HashFunction(sid); // stations array is accessed via hashtable
    struct Station *tmp = Stations[hashkey];
    while (tmp != NULL && tmp->sid != sid) // finding station
    {
        tmp = tmp->next;
    }
    printf("Voters[%d]\n", sid);

    int i = tmp->registered; // au3on arithmos neou kombou
    int j = 0;

    while (i > 0) // mexri to i na ftasei thn riza
    {
        int parent = (i - 1) / 2;
        i = parent;

        if (i == 0)
            break;

        array[j] = i % 2; // 0 h 1 -- monopati 0left 1right
        // printf("parent  = %d\n" , i);

        j++;
    }

    tmp->registered++;
    struct Voter *tmp1 = tmp->voters;

    // allocate new node
    struct Voter *new = (struct Voter *)malloc(sizeof(struct Voter));
    new->lc = new->rc = new->parent = NULL;
    new->vid = vid;
    new->voted = 0;

    if (tmp->registered == 1)
    {
        tmp->voters = new; // eisagwgi stin riza
        RecurvPrinterVoter(tmp->voters);
        printf("\nDONE\n");
        return;
    }
    j--;
    while (1)
    {
        if (tmp1->lc == NULL) // ean ftasame sto telos tou dentrou bale
        {
            tmp1->lc = new;
            new->parent = tmp1;
            break;
        }
        else if (tmp1->rc == NULL)
        {
            tmp1->rc = new;
            new->parent = tmp1;
            break;
        }

        if (array[j] == 0) // akoloutha to monopati tou pinaka
        {
            tmp1 = tmp1->rc;
        }
        else
        {
            tmp1 = tmp1->lc;
        }
        j--;
    }

    RecurvPrinterVoter(tmp->voters);
    printf("\nDONE\n");
}

void EventRegisterCandidate(int cid, int pid, int did)
{
    printf("C %d %d %d\nCandidates[%d]\n", cid, pid, did, pid);
    int i = 0;
    while (i < DISTRICTS_SZ && Districts[i].did != did) // finding district
    {
        i++;
    }
    struct Party *tmp = &Parties[pid];
    struct Candidate *root = tmp->candidates;
    struct Candidate *tmp1 = NULL;
    while (root != NULL) // BST implementation // left is smaller right is bigger
    {
        if (root->cid > cid)
        {
            tmp1 = root;
            root = root->lc;
        }
        else
        {
            tmp1 = root;
            root = root->rc;
        }
    }
    struct Candidate *new = (struct Candidate *)malloc(sizeof(struct Candidate));
    new->cid = cid;
    new->did = did;
    new->votes = 0;
    new->isElected = 0;
    new->lc = new->rc = NULL;
    if (tmp1 == NULL) // root , no parent ,new head
    {
        tmp->candidates = new;
    }
    else
    {
        if (tmp1->cid > cid)
        {
            tmp1->lc = new;
        }
        else
        {
            tmp1->rc = new;
        }
    }
    RecurvPrinterCandidate(tmp->candidates, did);
    printf("DONE\n");
}
void EventVote(int vid, int sid, int cid, int pid)
{
    printf("V %d %d %d %d\n", vid, sid, cid, pid);
    int hashkey = HashFunction(sid); // stations array is accessed via hashtable
    struct Station *tmp = Stations[hashkey];
    while (tmp != NULL && tmp->sid != sid) // finding station
    {
        tmp = tmp->next;
    }
    assert(tmp != NULL);

    struct Voter *VoterGuy = PreOrderRecurvFinder(tmp->voters, vid); // returns the voter's node in the tree
    assert(VoterGuy != NULL);

    VoterGuy->voted = true;
    switch (cid)
    {
    case -1:
        Districts[tmp->did].blanks++;
        printf("District[<%d>]\nblanks <%d>\ninvalids <%d>\n", tmp->did, Districts[tmp->did].blanks,
               Districts[tmp->did].invalids);
        break;
    case -2:
        Districts[tmp->did].invalids++;
        printf("District[<%d>]\nblanks <%d>\ninvalids <%d>\n", tmp->did, Districts[tmp->did].blanks,
               Districts[tmp->did].invalids);
        break;
    default:
    {
        struct Candidate *root = Parties[pid].candidates;
        struct Candidate *VotedGuy = NULL;
        while (root != NULL) // BTS implementation
        {
            if (root->cid == cid)
            {
                VotedGuy = root; // candidate found
                VotedGuy->votes++;
                int VotedGuyDid = VotedGuy->did;
                // printf("Voter's did <%d> AND Voted's did <%d>\n" , tmp->did , VotedGuyDid);
                // printf("%d %d\n", tmp->did, VotedGuyDid);
                // assert(tmp->did == VotedGuyDid);
                Districts[VotedGuyDid].partyVotes[pid]++;
                printf("District[<%d>]\nblanks <%d>\ninvalids <%d>\n", VotedGuy->did, Districts[VotedGuyDid].blanks,
                       Districts[VotedGuyDid].invalids);
                break;
            }

            if (cid < root->cid)
            {
                root = root->lc; // go to left subtree
            }
            else
            {
                root = root->rc; // go to right subtree
            }
        }
        if (VotedGuy == NULL)
        {
            printf("ERROR: voted person not found\n");
        }
    }
    }
    int i = 0;
    printf("partyVotes\n");
    while (i < PARTIES_SZ)
    {
        printf("<%d> <%d>\n", i, Districts[tmp->did].partyVotes[i]);
        i++;
    }
    printf("DONE\n");
}

// global
int heapsize = 0;
struct Candidate **heap;

void HeapInsert(struct Candidate **A, struct Candidate *K)
{
    int m = heapsize;
    while (m > 0 && K->votes < A[(m - 1) / 2]->votes)
    {
        A[m] = A[(m - 1) / 2];
        m = (m - 1) / 2;
    }
    A[m] = K;
    heapsize++;
}

int HeapDeleteMin(struct Candidate **A)
{
    if (heapsize == 0)
    {
        printf("heap size 0 exited\n");
        exit(1);
    }
    int I = A[0]->votes;
    struct Candidate *K = A[heapsize - 1];
    heapsize--;
    if (heapsize == 1)
        return -1;
    int m = 0, p = 0;
    while ((2 * m + 1 < heapsize && K->votes > A[2 * m + 1]->votes) || (2 * m + 2 < heapsize && K->votes > A[2 * m + 2]->votes))
    {
        if (2 * m + 2 < heapsize)
        {
            if (A[2 * m + 1]->votes < A[2 * m + 2]->votes)
            {
                p = 2 * m + 1;
            }
            else
            {
                p = 2 * m + 2;
            }
        }
        else
        {
            p = heapsize - 1;
        }
        A[m] = A[p];
        m = p;
    }
    A[m] = K;
    return I;
}

void ElectPartyCandidatesInDistrict(int pid, int did, int partyElected)
{
    heapsize = 0;

    heap = (struct Candidate **)malloc(sizeof(struct Candidate *) * partyElected);
    int i;
    for (i = 0; i < partyElected; i++)
    {
        heap[i] = NULL;
    }

    i = 0;
    TakeTreeNodes(Parties[pid].candidates, heap, partyElected, did);
}

void EventCountVotes(int did)
{
    printf("M %d\nseats\n", did);
    int i = 0, AllVotes = 0;
    int partyElected[PARTIES_SZ] = {0};
    float Meter = 0;
    while (i < PARTIES_SZ)
    {
        AllVotes += Districts[did].partyVotes[i];
        // printf("%d\n", Districts[did].partyVotes[i]);
        i++;
    }
    if (Districts[did].seats != 0)
    {
        Meter = (float)AllVotes / (float)Districts[did].seats;
    }
    else
    {
        Meter = 0;
    }
    // printf("meter %f\n", Meter);
    i = 0;
    int j;

    while (i < PARTIES_SZ) // metro > parties->candidates
    {
        if (Meter != 0)
        {
            // RecurvPrinterCandidate(Parties[i].candidates,0);
            partyElected[i] = Districts[did].partyVotes[i] / Meter;
            // printf("party elected before %d\n", partyElected[i]);
            if (partyElected[i] != 0)
            {
                ElectPartyCandidatesInDistrict(i, did, partyElected[i]);
                if (partyElected[i] > heapsize)
                {
                    partyElected[i] = heapsize;
                }
                Parties[i].electedCount += partyElected[i];
                Districts[did].seats -= partyElected[i];
                assert(Districts[did].seats >= 0);
                // printf("party %d party elected  %d seats %d party votes %d\n", i, partyElected[i], Districts[i].seats, Districts[did].partyVotes[i]);
                for (j = 0; j < heapsize; j++)
                {
                    printf("%d %d %d\n", heap[j]->cid, i, heap[j]->votes);
                    heap[j]->isElected = 1;
                }
            }
        }
        else
        {
            return;
        }
        i++;
    }
}
void EventFormParliament(void)
{
    printf("N\nmembers\n");
    int i = 0;
    while (i < PARTIES_SZ)
    {
        struct Candidate *tmp = Parties[i].candidates;
        RecurvElectedCandidateFinder(tmp, Parties[i].pid);
        i++;
    }
    struct ElectedCandidate *tmp = Parliament;
    while (tmp != NULL)
    {
        printf("%d %d %d\n", tmp->cid, tmp->pid, tmp->did);
        tmp = tmp->next;
    }
    printf("DONE\n");
}
void EventPrintDistrict(int did)
{
    printf("I %d\n", did);
    int i = 0;
    while (i < DISTRICTS_SZ && Districts[i].did != did)
    {
        i++;
    }
    printf("seats <%d>\nblanks <%d>\ninvalids <%d>\nPartyVotes", Districts[i].seats, Districts[i].blanks, Districts[i].invalids);
    int j = 0;
    while (j < PARTIES_SZ)
    {
        printf("<%d> <%d>\n", j, Districts[i].partyVotes[j]);
        j++;
    }
    printf("DONE\n");
}
void EventPrintStation(int sid)
{
    printf("J %d\n", sid);
    int hashkey = HashFunction(sid); // stations array is accessed via hashtable
    struct Station *tmp = Stations[hashkey];
    while (tmp != NULL && tmp->sid != sid)
    {
        tmp = tmp->next;
    }
    printf("reigstered %d\nvoters\n", tmp->registered);
    struct Voter *tmp1 = tmp->voters;
    RecurvPrinterVoter(tmp1);
    printf("\nDONE\n");
}
void EventPrintParty(int pid)
{
    printf("K %d\nelected\n", pid);
    int i = 0;
    while (i < PARTIES_SZ && Parties[i].pid != pid)
    {
        i++;
    }
    struct Candidate *tmp = Parties[i].candidates;
    RecurvPrinterCandidate(tmp, -123456789);
    printf("DONE\n");
}
void EventPrintParliament(void)
{
    printf("L\nmembers\n");
    struct ElectedCandidate *tmp = Parliament;
    while (tmp != NULL)
    {
        printf("%d %d %d\n", tmp->cid, tmp->pid, tmp->did);
        tmp = tmp->next;
    }
}
void EventBonusUnregisterVoter(int vid, int sid)
{
    printf("\nBU %d %d\n", vid, sid);
    int hashkey = HashFunction(sid);
    struct Station *tmp = Stations[hashkey];
    while (tmp != NULL && tmp->sid != sid) // finding station
    {
        tmp = tmp->next;
    }
    assert(tmp != NULL);
    printf("Voters <%d>\n", tmp->sid);

    struct Voter *tmp1 = tmp->voters;
    PreOrderRecurvDeleter(tmp1, vid, tmp);
    RecurvPrinterVoter(tmp->voters);
}


void EventBonusFreeMemory(void)
{
    printf("BF\n");
    int i = 0;

    struct Station *tmp = NULL;
    struct Station *tmpdel = NULL;
    //printf("%d\n" , STATION_SZ);
    for (i = 0; i < STATION_SZ; i++) // for each station chain
    {
        //printf("i : %d\n" , i);
        tmp = Stations[i];
        tmpdel = Stations[i];
        while (tmp != NULL) // for each station
        {
            //printf("before free voters function\n");
            
            FreeVoters(tmp->voters); // free voters
            //printf("i returned from the free voters function\n");
            tmp = tmp->next;         // move to the next
            //printf("i am about to free voter\n");
            free(tmpdel); // free prev
            //printf("did it\n");
            tmpdel = tmp;
        }
        //printf("i went to the next loop\n");
    }

    //printf("before\n");
    free(Stations); // free the array
    //printf("after\n");
    struct Candidate *tmp1 = NULL;
    for (i = 0; i < PARTIES_SZ; i++)
    {
        tmp1 = Parties[i].candidates;
        //printf("i am about to free candidate \n");
        FreeCandidates(tmp1);
        //printf("did it \n");
    }

    struct ElectedCandidate *tmp2 = Parliament;
    struct ElectedCandidate *tmp2del = tmp2;
    while (tmp2 != NULL)
    {
        tmp2 = tmp2->next;
        //printf("i am about to free elected candidate \n");
        free(tmp2del);
        //printf("did it \n");
        tmp2del = tmp2;
    }

    printf("DONE\n");
}

void FreeVoters(struct Voter *root)
{
    //printf("i got in free voters\n");
    if (root == NULL)
    {
        //printf("root was NULL\n");
        return;
    }   
    FreeVoters(root->lc);
    FreeVoters(root->rc);
    free(root);
}

void FreeCandidates(struct Candidate *root)
{
    if (root == NULL)
        return;
    FreeCandidates(root->lc);
    FreeCandidates(root->rc);
    free(root);
}


int HashFunction(int id)
{
    return ((A * id + B) % P) % STATION_SZ;
}

void RecurvPrinterVoter(struct Voter *root)
{
    if (root == NULL)
        return;
    printf("<%d> ", root->vid);
    RecurvPrinterVoter(root->lc);
    RecurvPrinterVoter(root->rc);
}

void RecurvPrinterCandidate(struct Candidate *root, int did)
{
    if (did != -123456789)
    {
        if (root == NULL)
            return;
        RecurvPrinterCandidate(root->lc, did);
        printf("<%d> <%d>\n", root->cid, root->did);
        RecurvPrinterCandidate(root->rc, did);
    }
    else
    {
        if (root == NULL)
            return;
        RecurvPrinterCandidate(root->lc, did);
        printf("<%d> <%d>\n", root->cid, root->votes);
        RecurvPrinterCandidate(root->rc, did);
    }
}

struct Voter *PreOrderRecurvFinder(struct Voter *root, int vid)
{
    if (root == NULL)
        return NULL;

    if (root->vid == vid)
    {
        return root; // voter found
    }
    struct Voter *found = PreOrderRecurvFinder(root->lc, vid); // search left subtree
    if (found != NULL)
    {
        return found;
    }
    return PreOrderRecurvFinder(root->rc, vid); // search right subtree
}

void TakeTreeNodes(struct Candidate *root, struct Candidate **heap, int partyElected, int did)
{
    if (root == NULL)
        return;
    TakeTreeNodes(root->lc, heap, partyElected, did);
    TakeTreeNodes(root->rc, heap, partyElected, did);
    if (heapsize < partyElected)
    {
        if (did == root->did)
        {
            // printf("i got in the if\n");
            HeapInsert(heap, root);
        }
    }
    else
    {
        if (did == root->did)
        {

            if (root->votes > heap[0]->votes)
            {
                // printf("i go in the else\n");
                HeapDeleteMin(heap);
                HeapInsert(heap, root);
            }
        }
    }
}

void InsertToSortedList(struct Candidate *person, int pid)
{
    struct ElectedCandidate *tmp = Parliament;
    struct ElectedCandidate *prev = NULL;
    while (tmp != NULL && person->cid < tmp->cid)
    {
        prev = tmp;
        tmp = tmp->next;
    }

    struct ElectedCandidate *new = (struct ElectedCandidate *)malloc(sizeof(struct ElectedCandidate));
    new->cid = person->cid;
    new->did = person->did;
    new->pid = pid;
    new->next = NULL;

    if (tmp == NULL && prev == NULL) // new head of the list
    {
        Parliament = new;
        return;
    }

    if (tmp == NULL && prev != NULL) // last in the list
    {
        prev->next = new;
        return;
    }

    if (prev == NULL)
    {
        Parliament = new;
    }
    else
    {
        prev->next = new;
    }

    new->next = tmp;
}

void RecurvElectedCandidateFinder(struct Candidate *root, int pid)
{
    if (root == NULL)
        return;
    RecurvElectedCandidateFinder(root->lc, pid);
    RecurvElectedCandidateFinder(root->rc, pid);
    if (root->isElected == 1)
    {
        // printf("-%d %d-\n", pid, root->cid);
        InsertToSortedList(root, pid);
    }
}

struct Voter *PreOrderRecurvDeleter(struct Voter *root, int vid, struct Station *tmo)
{

    if (root == NULL)
        return NULL;

    if (root->vid == vid)
    {
        struct Voter *k = FindLastOfTree(tmo);
        root->vid = k->vid;
        root->voted = k->voted;
        // printf("K found %d %p\n", k->vid, k->parent);
        if (k->parent != NULL)
        {
            if (k->parent->lc == k)
            {
                k->parent->lc = NULL;
            }
            else
            {
                k->parent->rc = NULL;
            }
        }
        else
        {
            tmo->voters = NULL;
        }
        tmo->registered--;
        return root; // voter found
    }
    struct Voter *found = PreOrderRecurvDeleter(root->lc, vid, tmo); // search left subtree
    if (found != NULL)
    {
        return found;
    }
    return PreOrderRecurvDeleter(root->rc, vid, tmo); // search right subtree
}

struct Voter *FindLastOfTree(struct Station *tmp)
{
    int array[100];
    int i = tmp->registered - 1; // au3on arithmos neou kombou

    if (i == -1)
        return NULL;
    if (i == 0)
        return tmp->voters;

    int j = 0;

    array[j] = i % 2; // 0 h 1 -- monopati 0left 1right
    j++;

    while (i > 0) // mexri to i na ftasei thn riza
    {
        int parent = (i - 1) / 2;
        i = parent;

        if (i == 0)
            break;

        array[j] = i % 2; // 0 h 1 -- monopati 0left 1right
        // printf("parent  = %d\n" , i);

        j++;
    }

    struct Voter *tmp1 = tmp->voters;

    j--;
    while (1)
    {
        if (array[j] == 0)
        {
            tmp1 = tmp1->rc;
        }
        else
        {
            tmp1 = tmp1->lc;
        }
        if (j == 0)
            return tmp1;
        j--;
    }

    return NULL;
}
