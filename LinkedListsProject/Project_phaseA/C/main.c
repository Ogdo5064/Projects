/*
 * ============================================
 * file: main.c
 * @Author John Malliotakis (jmal@csd.uoc.gr)
 * @Version 24/10/2023
 *
 * @e-mail hy240@csd.uoc.gr
 *
 * @brief Main function
 *        for CS240 Project Phase 1,
 *        Winter Semester 2024-2025
 * @see   Compile using supplied Makefile by running: make
 * ============================================
 */
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "elections.h"

/* Maximum input line size */
#define MAX_LINE 1024

/*
 * Uncomment the following line to
 * enable debugging prints
 * or comment to disable it
 */
/* #define DEBUG */
#ifdef DEBUG
#define DPRINT(...) fprintf(stderr, __VA_ARGS__);
#else
#define DPRINT(...)
#endif /* DEBUG */

/*
 * Globals:
 * you may add some here for certain events
 * (such as D and P)
 */
struct district Districts[56];
struct party Parties[5];
struct parliament Parliament;
int counterD = 0; /*counter to know to what point the District array is filled*/
int counterP = 0; /*counter to know to what point the Parties array is filled*/

void destroy_structures(void)
{
	int i = 0;
	while (i < counterD) /*for every district*/
	{
		struct station *tmp = Districts[i].stations;
		while (tmp != NULL) /*for every station*/
		{
			struct voter *tmpv = tmp->voters;
			while (tmpv != tmp->vsentinel) /*for every voter*/
			{
				struct voter *nextv = tmpv->next;
				free(tmpv);
				tmpv = nextv;
			}

			struct station *next = tmp->next;
			free(tmp);
			tmp = next;
		}

		struct candidate *tmp1 = Districts[i].candidates;
		while (tmp1 != NULL) /*for every candidate-DISTRICT*/
		{
			struct candidate *next1 = tmp1->next;
			free(tmp1);
			tmp1 = next1;
		}
		i++;
	}
	struct candidate *tmp2 = Parliament.members;
	while (tmp2 != NULL) /*for every parliament member*/
	{
		struct candidate *next2 = tmp2->next;
		free(tmp2);
		tmp2 = next2;
	}
}

void announce_elections(void)
{
	for (int i = 0; i < 56; i++)
	{
		struct district *tmp = &Districts[i];
		tmp->did = -1;
		tmp->seats = -1;
		tmp->allotted = -1;
		tmp->blanks = 0;
		tmp->voids = 0;
		tmp->stations = NULL;
		tmp->candidates = NULL;
	}
	for (int i = 0; i < 5; i++)
	{
		struct party *tmp0 = &Parties[i];
		tmp0->pid = -1;
		tmp0->nelected = -1;
		tmp0->elected = NULL;
	}
	Parliament.members = NULL;
	printf("A\nDONE\n");
}

int create_district(int did, int seats)
{
	if (56 == counterD)
	{
		printf("error create district");
		exit(0);
	}
	/*putting in the next available spot in the District array*/
	/*counterD is always at the next available spot*/
	Districts[counterD].did = did;
	Districts[counterD].seats = seats;
	Districts[counterD].allotted = 0;

	printf("D <%d> <%d>\nDistricts = ", did, seats);

	int i = 0;
	while (i < counterD)
	{
		printf("<%d>", Districts[i].did);
		i++;
	}
	counterD++;
	printf("\nDONE\n");
	return 0;
}

int create_station(int sid, int did)
{
	int i = 0;
	while (i < counterD && Districts[i].did != did)
	{
		i++;
	}
	if (i == counterD)
	{
		printf("error create station");
		exit(0);
	}
	if (Districts[i].stations == NULL) /*first station*/
	{
		/*allocating a new station*/
		Districts[i].stations = (struct station *)malloc(sizeof(struct station));
		Districts[i].stations->next = NULL;
	}
	else
	{
		struct station *tmp = (struct station *)malloc(sizeof(struct station));
		tmp->next = Districts[i].stations;
		Districts[i].stations = tmp;
	}
	Districts[i].stations->sid = sid;
	Districts[i].stations->registered = 0;

	/*allocating and initializing the voter's sentinel node*/
	Districts[i].stations->vsentinel = (struct voter *)malloc(sizeof(struct voter));
	Districts[i].stations->vsentinel->next = NULL;
	// Districts[i].stations->voters = (struct voter *)malloc(sizeof(struct voter));
	Districts[i].stations->voters = Districts[i].stations->vsentinel; /*pointer points to sentinel*/

	printf("S <%d> <%d>\nStations = ", sid, did);
	struct station *tmp = Districts[i].stations;
	while (tmp != NULL)
	{
		printf("<%d>", tmp->sid);
		tmp = tmp->next;
	}
	printf("\nDONE\n");
	return 0;
}

void create_party(int pid)
{
	/*counterP is always at the next available spot of the Parties array*/
	if (5 == counterP)
	{
		printf("error create party\n");
		exit(0);
	}
	Parties[counterP].pid = pid;
	printf("P <%d>\nParties = ", Parties[counterP].pid);
	int i = 0;
	counterP++;
	while (i < counterP)
	{
		printf("<%d> ", Parties[i].pid);
		i++;
	}

	printf("\nDONE\n");
}

int register_candidate(int cid, int did, int pid)
{
	struct candidate *tmp;
	int i = 0;
	while (i < counterD && Districts[i].did != did)
	{
		i++;
	}
	if (i == counterD)
	{
		printf("error register candidate\n");
		return 1;
	}
	if (Districts[i].candidates == NULL) /*if this the first node in the struct*/
	{

		Districts[i].candidates = (struct candidate *)malloc(sizeof(struct candidate));
		Districts[i].candidates->cid = cid;
		Districts[i].candidates->pid = pid;
		Districts[i].candidates->votes = 0;
		Districts[i].candidates->next = NULL;
		Districts[i].candidates->prev = NULL;
	}
	else
	{
		tmp = Districts[i].candidates;
		while (tmp->next != NULL)
		{
			tmp = tmp->next;
		} /*end of the list , now create new node to put the new candidate*/
		tmp->next = (struct candidate *)malloc(sizeof(struct candidate));
		tmp->next->cid = cid;
		tmp->next->pid = pid;
		tmp->next->votes = 0;
		tmp->next->next = NULL;
		tmp->next->prev = tmp;
	}

	printf("C <%d> <%d> <%d>\nCandidates =", cid, did, pid);
	int j = 0; /*i holds the district with all the candidates i want to print*/
	struct candidate *tmp0 = Districts[i].candidates;
	while (tmp0 != NULL)
	{
		printf("<%d>", tmp0->cid);
		tmp0 = tmp0->next;
	}

	printf("\nDONE\n");
	return 0;
}

int register_voter(int vid, int did, int sid)
{
	int i = 0;
	while (i < counterD && Districts[i].did != did) /*finding the correct district*/
	{
		i++;
	}
	if (i == counterD)
	{
		printf("error register voter\n");
		exit(0);
	}
	struct station *tmp = Districts[i].stations;
	while (tmp != NULL && tmp->sid != sid) /*finding the correct station*/
	{
		tmp = tmp->next;
	}
	/*creating new node*/
	struct voter *newnode = (struct voter *)malloc(sizeof(struct voter));
	/*adding the new cell and initializing pointers*/
	newnode->vid = vid;
	newnode->next = tmp->voters;
	tmp->voters = newnode;

	tmp->registered++;

	printf("R <%d> <%d> <%d>\nVoters = ", vid, did, sid);
	struct voter *voter_iter = tmp->voters;
	while (voter_iter != tmp->vsentinel)
	{
		printf("<%d> ", voter_iter->vid);
		voter_iter = voter_iter->next;
	}
	printf("\nDONE\n");
	return 0;
}

int unregister_voter(int vid)
{
	int i = 0;
	while (i < counterD) /* for each district */
	{
		struct station *tmp1 = Districts[i].stations;
		while (tmp1 != NULL) /* for each station */
		{
			struct voter *tmp2 = tmp1->voters;
			struct voter *prev = NULL;

			/* traverse the voter list to find the voter with vid */
			tmp1->vsentinel->vid = vid;
			while (tmp2->vid != vid)
			{
				prev = tmp2;
				tmp2 = tmp2->next;
			}

			if (tmp2 == tmp1->vsentinel)
			{
				/*didn't find voter, move to the next station */
				tmp1 = tmp1->next;
				continue;
			}
			else /*found voter*/
			{
				/*delete the voter node*/
				if (prev == NULL)
				{
					/*the voter to delete is the first voter (before sentinel)*/
					tmp1->voters = tmp2->next;
				}
				else
				{
					prev->next = tmp2->next;
				}

				free(tmp2);
				tmp1->registered--;

				/*printing*/
				struct voter *tmp_print = tmp1->voters; /*start of voters list*/
				printf("U <%d>\n<%d> <%d>\nVoters = ", vid, Districts[i].did, tmp1->sid);
				while (tmp_print != tmp1->vsentinel)
				{
					printf("<%d> ", tmp_print->vid);
					tmp_print = tmp_print->next;
				}
				printf("\nDONE\n");
				return 0;
			}
		}
		i++;
	}
	return 1; /*return 1 if the voter was not found in any district or station*/
}

void delete_empty_stations(void)
{
	int i = 0;
	printf("E\n");
	while (i < counterD) /*for each district*/
	{
		struct station *tmp = Districts[i].stations;
		struct station *prev = NULL;
		while (tmp != NULL) /*for each station*/
		{

			if (tmp->registered == 0)
			{
				struct station *tmp2 = tmp->next;
				if (prev == NULL) /*first station needs to be removed*/
				{
					Districts[i].stations = tmp->next; /*first station becomes the second*/
					printf("<%d> <%d>\n", tmp->sid, Districts[i].did);
					free(tmp);
				}
				else
				{
					prev->next = tmp->next;							   /*previous station points to the next of the station being deleted*/
					printf("<%d> <%d>\n", tmp->sid, Districts[i].did); /*removing station sid in district did*/
					free(tmp);
				}
				tmp = tmp2;
			}
			else
			{
				prev = tmp; /*previous station*/
				tmp = tmp->next;
			}
		}
		i++;
	}
	printf("DONE\n");
}

int vote(int vid, int sid, int cid)
{
	int i = 0;
	if (vid <= 0 || sid <= 0)
	{
		printf("ERROR : invalid entries\n");
		return 1;
	}
	while (i < counterD) /*for every district*/
	{
		struct station *tmp = Districts[i].stations;
		while (tmp != NULL && tmp->sid != sid) /*finding station*/
		{
			tmp = tmp->next;
		}
		if (tmp == NULL)
		{
			i++;
			continue; /*didnt find station go to next district*/
		}
		tmp->vsentinel->vid = vid;
		struct voter *tmp1 = tmp->voters;
		while (tmp1->vid != vid) /*finding voter*/
		{
			tmp1 = tmp1->next;
		}
		if (tmp1 == tmp->vsentinel) /*didnt find voter*/
		{
			printf("ERROR : didnt find voter\n");
			return 1;
		}
		tmp1->voted = 1; /*1 meaning that he has voted*/
		if (cid == 0)	 /*blank vote for this district*/
		{
			Districts[i].blanks++;
		}
		else if (cid == 1) /*void vote for this district*/
		{
			Districts[i].voids++;
		}
		else
		{
			/* Iterate candidates list to find cid */
			struct candidate *tmp2 = Districts[i].candidates;
			while (tmp2 != NULL && tmp2->cid != cid) /*finding candidate*/
			{
				tmp2 = tmp2->next;
			}
			if (tmp2 == NULL)
			{
				printf("ERROR : didnt find candidate\n");
				return 1; /*didnt find candidate*/
			}
			tmp2->votes++;

			while (tmp2->prev != NULL && tmp2->votes > tmp2->prev->votes)
			{
				struct candidate *prevNode = tmp2->prev;
				struct candidate *nextNode = tmp2->next;

				/*make pointer transitions for swap */
				if (prevNode->prev != NULL)
				{
					prevNode->prev->next = tmp2;
				}
				else
				{
					/*if prevNode was the head, update the head to tmp2*/
					Districts[i].candidates = tmp2;
				}

				tmp2->prev = prevNode->prev;
				tmp2->next = prevNode;
				prevNode->prev = tmp2;
				prevNode->next = nextNode;

				if (nextNode != NULL)
				{
					nextNode->prev = prevNode;
				}
			}
			printf("V <%d> <%d> <%d>\nDistrict = <%d>\nCandidate votes = ", vid, sid, cid, Districts[i].did);
			struct candidate *tmp_iter = Districts[i].candidates;
			while (tmp_iter != NULL)
			{
				if (tmp_iter->next == NULL)
				{
					printf("(<%d>, <%d>)", tmp_iter->cid, tmp_iter->votes);
				}
				else
				{
					printf("(<%d>, <%d>), ", tmp_iter->cid, tmp_iter->votes);
				}
				tmp_iter = tmp_iter->next;
			}
			printf("\nBlanks = <%d>\nVoids = <%d>\nDONE\n", Districts[i].blanks, Districts[i].voids);
			return 0; /*success*/
		}
		printf("V <%d> <%d> <%d>\nDistrict = <%d>\nCandidate votes = ", vid, sid, cid, Districts[i].did);
		struct candidate *tmp_iter = Districts[i].candidates;
		while (tmp_iter != NULL)
		{
			if (tmp_iter->next == NULL)
			{
				printf("(<%d>, <%d>)", tmp_iter->cid, tmp_iter->votes);
			}
			else
			{
				printf("(<%d>, <%d>), ", tmp_iter->cid, tmp_iter->votes);
			}
			tmp_iter = tmp_iter->next;
		}
		printf("\nBlanks = <%d>\nVoids = <%d>\nDONE\n", Districts[i].blanks, Districts[i].voids);
		return 0; /*success*/
		i++;
	}
	printf("ERROR : didnt find anything within any district\n");
	return 1;
}

void count_votes(int did)
{
	int i = 0;
	float total = 0;

	while (Districts[i].did != did)
	{
		i++;
	}

	printf("M <%d>\nSeats = \n", Districts[i].did);

	int counter[5] = {0};
	struct candidate *tmp = Districts[i].candidates;

	while (tmp != NULL)
	{
		for (int j = 0; j < 5; j++)
		{
			if (tmp->pid == Parties[j].pid)
			{
				counter[j] += tmp->votes;
				break;
			}
		}
		tmp = tmp->next;
	}

	total = (counter[0] + counter[1] + counter[2] + counter[3] + counter[4]) / (float)Districts[i].seats;
	int array[5];
	for (int j = 0; j < 5; j++)
	{
		if (total > 0)
		{
			array[j] = counter[j] / total;
		}
		else
		{
			printf("total was 0 , cant divide , returning\n");
			return;
		}
	}

	struct candidate *tmp1 = Districts[i].candidates;
	while (tmp1 != NULL)
	{
		struct candidate *next = tmp1->next;

		for (int j = 0; j < 5; j++)
		{
			if (array[j] > 0 && tmp1->pid == Parties[j].pid)
			{
				tmp1->elected = 1;
				Districts[i].allotted++;
				array[j]--;

				printf("<%d> <%d> <%d>\n", tmp1->cid, tmp1->pid, tmp1->votes);

				struct candidate *ptrdlt = tmp1;
				if (ptrdlt->prev == NULL && ptrdlt->next != NULL) /*candidate is head of the list*/
				{
					Districts[i].candidates = ptrdlt->next;
					ptrdlt->next->prev = NULL;
				}
				else if (ptrdlt->prev == NULL && ptrdlt->next == NULL) /*only candidate in the list*/
				{
					Districts[i].candidates = NULL;
				}
				else if (ptrdlt->prev != NULL && ptrdlt->next == NULL) /*last candidate spot in the list */
				{
					ptrdlt->prev->next = NULL;
				}
				else
				{
					ptrdlt->prev->next = ptrdlt->next;
					ptrdlt->next->prev = ptrdlt->prev;
				}

				tmp1->next = NULL;
				tmp1->prev = NULL;

				struct candidate *prev = NULL, *tmp2 = Parties[j].elected;
				while (tmp2 != NULL && tmp1->votes < tmp2->votes) /*insertion in sorted list*/
				{
					prev = tmp2;
					tmp2 = tmp2->next;
				}

				if (prev == NULL)
				{
					tmp1->next = Parties[j].elected;
					Parties[j].elected = tmp1;
				}
				else
				{
					tmp1->next = prev->next;
					prev->next = tmp1;
				}
				Parties[j].nelected++;

				break;
			}
		}

		tmp1 = next;
	}
	printf("DONE\n");
}

void form_government(void)
{
	int i = 0, j = 0, k = 0, remaining = 0;
	int max = Parties[0].nelected;
	int maxi = 0;
	printf("G\nSeats = \n");

	for (i = 1; i < 5; i++)
	{
		if (max < Parties[i].nelected)
		{
			max = Parties[i].nelected;
			maxi = i;
		}
	}
	i = 0;

	while (i < counterD) /*for every district*/
	{
		//printf("alloted : %d seats : %d\n", Districts[i].allotted, Districts[i].seats);
		while (Districts[i].allotted < Districts[i].seats) /*until every seat is filled*/
		{
			struct candidate *tmp = Districts[i].candidates;
			while (tmp != NULL) /*while there are candidates*/
			{
				struct candidate *next = tmp->next;

				if (tmp->pid == Parties[maxi].pid) /*if you are candidate of party[maxi]*/
				{

					printf("<%d> <%d> <%d>\n", Districts[i].did, tmp->cid, tmp->votes);

					tmp->elected = 1;
					// printf("electing %d alloted was %d\n" , tmp->cid , Districts[i].allotted);
					Districts[i].allotted++;
					// printf("alloted now is %d\n" , Districts[i].allotted);

					struct candidate *ptrdlt = tmp;
					if (ptrdlt->prev == NULL && ptrdlt->next != NULL)
					{
						Districts[i].candidates = ptrdlt->next;
						ptrdlt->next->prev = NULL;
					}
					else if (ptrdlt->prev == NULL && ptrdlt->next == NULL)
					{
						Districts[i].candidates = NULL;
					}
					else if (ptrdlt->prev != NULL && ptrdlt->next == NULL)
					{
						ptrdlt->prev->next = NULL;
					}
					else
					{
						ptrdlt->prev->next = ptrdlt->next;
						ptrdlt->next->prev = ptrdlt->prev;
					}

					tmp->next = NULL;
					tmp->prev = NULL;

					struct candidate *prev = NULL, *tmp2 = Parties[maxi].elected;
					while (tmp2 != NULL && tmp->votes < tmp2->votes)
					{
						prev = tmp2;
						tmp2 = tmp2->next;
					}

					if (prev == NULL)
					{
						tmp->next = Parties[maxi].elected;
						Parties[maxi].elected = tmp;
					}
					else
					{
						tmp->next = prev->next;
						prev->next = tmp;
					}
					Parties[maxi].nelected++;

					break;
				}
				tmp = next;
			}
			break; /*if you ever leave the while (candidate iteration, no more candidates of party[0] to be found) leave*/
		}

		struct candidate *tmp1 = Districts[i].candidates;
		while (Districts[i].allotted < Districts[i].seats) /*if seats are still not filled*/
		{
			/*take candidates from any party based on higher votes*/
			/*candidates list in district is sorted in descedning votes*/
			/*take from the start of the list*/
			while (tmp1 != NULL)
			{
				struct candidate *next1 = tmp1->next;

				printf("<%d> <%d> <%d>\n", Districts[i].did, tmp1->cid, tmp1->votes);

				tmp1->elected = 1;
				Districts[i].allotted++;

				// printf("<%d> <%d> <%d>\n", tmp1->cid, tmp1->pid, tmp1->votes);

				struct candidate *ptrdlt = tmp1;
				if (ptrdlt->prev == NULL && ptrdlt->next != NULL)
				{
					Districts[i].candidates = ptrdlt->next;
					ptrdlt->next->prev = NULL;
				}
				else if (ptrdlt->prev == NULL && ptrdlt->next == NULL)
				{
					Districts[i].candidates = NULL;
				}
				else if (ptrdlt->prev != NULL && ptrdlt->next == NULL)
				{
					ptrdlt->prev->next = NULL;
				}
				else
				{
					ptrdlt->prev->next = ptrdlt->next;
					ptrdlt->next->prev = ptrdlt->prev;
				}

				tmp1->next = NULL;
				tmp1->prev = NULL;

				struct candidate *prev = NULL, *tmp2 = Parties[maxi].elected;
				while (tmp2 != NULL && tmp1->votes < tmp2->votes)
				{
					prev = tmp2;
					tmp2 = tmp2->next;
				}

				if (prev == NULL)
				{
					tmp1->next = Parties[maxi].elected;
					Parties[maxi].elected = tmp1;
				}
				else
				{
					tmp1->next = prev->next;
					prev->next = tmp1;
				}
				Parties[maxi].nelected++;

				tmp1 = next1;
				break;
			}
		}
		i++;
	}
	printf("DONE\n");
}

void form_parliament(void)
{
	int i = 0;

	struct candidate *final = NULL;

	final = mergeroftwo(Parties[0].elected, Parties[1].elected);

	for (i = 2; i < 5; i++)
	{
		final = mergeroftwo(final, Parties[i].elected);
	}

	printf("N\nMembers = \n");

	struct candidate *tmp1 = final;
	while (tmp1 != NULL)
	{
		printf("<%d> <%d> <%d>\n", tmp1->cid, tmp1->pid, tmp1->votes);
		tmp1 = tmp1->next;
	}
	printf("DONE\n");

	Parliament.members = final;
}

void print_district(int did)
{
	int i = 0;
	while (i < counterD) /*finding district*/
	{
		if (Districts[i].did == did)
		{
			break;
		}
		i++;
	}

	printf("I <%d>\nSeats = <%d>\nBlanks = <%d>\nVoids = <%d>\nCandidates = \n", Districts[i].did, Districts[i].seats, Districts[i].blanks, Districts[i].voids);
	struct candidate *tmp = Districts[i].candidates;
	while (tmp != NULL)
	{
		printf("<%d> <%d> <%d>\n", tmp->cid, tmp->pid, tmp->votes);
		tmp = tmp->next;
	}
	struct station *tmp1 = Districts[i].stations;
	printf("Stations = ");
	while (tmp1 != NULL)
	{
		printf("<%d> ", tmp1->sid);
		tmp1 = tmp1->next;
	}
	printf("\nDONE\n");
}

void print_station(int sid, int did)
{
	int i = 0;
	while (i < counterD) /* finding district */
	{
		if (Districts[i].did == did)
		{
			break;
		}
		i++;
	}

	if (i == counterD) /* Check if district was found */
	{
		printf("DISTRICT WAS NOT FOUND - RETURNING\n");
		return;
	}

	struct station *tmp = Districts[i].stations;
	while (tmp != NULL) /* finding station */
	{
		if (tmp->sid == sid)
		{
			break;
		}
		tmp = tmp->next;
	}

	if (tmp == NULL) /* Check if station was found */
	{
		printf("STATION WAS NOT FOUND - RETURNING\n");
		return;
	}

	printf("J <%d>\n", tmp->sid);
	printf("Registered = <%d>\nVoters = \n", tmp->registered);

	struct voter *tmp1 = tmp->voters;
	while (tmp1 != tmp->vsentinel)
	{
		printf("<%d> <%d>\n", tmp1->vid, tmp1->voted);
		tmp1 = tmp1->next;
	}

	printf("DONE\n");
}

void print_party(int pid)
{
	int i;
	for (i = 0; i < 5; i++)
	{
		if (Parties[i].pid == pid)
		{
			break;
		}
	}
	printf("K <%d>\nElected = \n", Parties[i].pid);
	struct candidate *tmp = Parties[i].elected;
	while (tmp != NULL)
	{
		printf("<%d> <%d>\n", tmp->cid, tmp->votes);
		tmp = tmp->next;
	}
	printf("DONE\n");
}

void print_parliament(void)
{
	printf("L\nMembers = \n");
	struct candidate *tmp = Parliament.members;
	while (tmp != NULL)
	{
		printf("<%d> <%d> <%d>\n", tmp->cid, tmp->pid, tmp->votes);
		tmp = tmp->next;
	}
	printf("DONE\n");
}

struct candidate *mergeroftwo(struct candidate *first, struct candidate *second)
{
	struct candidate *final = NULL;
	struct candidate *back = NULL;
	struct candidate *tmp = first;
	struct candidate *tmp1 = second;

	while (tmp != NULL && tmp1 != NULL)
	{

		if (tmp->votes > tmp1->votes)
		{
			struct candidate *next = tmp->next;
			if (final == NULL)
			{
				final = tmp;
				back = tmp;
				tmp->next = NULL;
			}
			else
			{
				back->next = tmp;
				back = tmp;
				tmp->next = NULL;
			}
			tmp = next;
		}
		else
		{
			struct candidate *next1 = tmp1->next;
			if (final == NULL)
			{
				final = tmp1;
				back = tmp1;
				tmp1->next = NULL;
			}
			else
			{
				back->next = tmp1;
				back = tmp1;
				tmp1->next = NULL;
			}
			tmp1 = next1;
		}
	}

	while (tmp != NULL)
	{
		struct candidate *next = tmp->next;
		if (final == NULL)
		{
			final = tmp;
			back = tmp;
			tmp->next = NULL;
		}
		else
		{
			back->next = tmp;
			back = tmp;
			tmp->next = NULL;
		}
		tmp = next;
	}
	while (tmp1 != NULL)
	{
		struct candidate *next1 = tmp1->next;
		if (final == NULL)
		{
			final = tmp1;
			back = tmp1;
			tmp1->next = NULL;
		}
		else
		{
			back->next = tmp1;
			back = tmp1;
			tmp1->next = NULL;
		}
		tmp1 = next1;
	}

	return final;
}

int main(int argc, char *argv[])
{
	FILE *event_file;
	char line_buffer[MAX_LINE];

	if (argc != 2)
	{
		fprintf(stderr, "Usage: %s <input_file>\n",
				argv[0]);
		exit(EXIT_FAILURE);
	}

	event_file = fopen(argv[1], "r");
	if (!event_file)
	{
		perror("fopen error for event file open");
		exit(EXIT_FAILURE);
	}

	while (fgets(line_buffer, MAX_LINE, event_file))
	{
		char *trimmed_line;
		char event;
		int did, sid, vid, cid, pid, seats;
		int ret = 0;
		/*
		 * First trim any whitespace
		 * leading the line.
		 */
		trimmed_line = line_buffer;
		while (trimmed_line && isspace(*trimmed_line))
			trimmed_line++;
		if (!trimmed_line)
			continue;
		/*
		 * Find the event,
		 * or comment starting with #
		 */
		if (sscanf(trimmed_line, "%c", &event) != 1)
		{
			fprintf(stderr, "Could not parse event type out of input line:\n\t%s",
					trimmed_line);
			fclose(event_file);
			exit(EXIT_FAILURE);
		}

		switch (event)
		{
		/* Comment, ignore this line */
		case '#':
			break;
		case 'A':
			announce_elections();
			break;
		case 'D':
			if (sscanf(trimmed_line, "D %d %d", &did, &seats) != 2)
			{
				fprintf(stderr, "Event D parsing error\n");
				ret = 1;
				break;
			}
			ret = create_district(did, seats);
			break;
		case 'S':
			if (sscanf(trimmed_line, "S %d %d", &sid, &did) != 2)
			{
				fprintf(stderr, "Event S parsing error\n");
				ret = 1;
				break;
			}
			ret = create_station(sid, did);
			break;
		case 'P':
			if (sscanf(trimmed_line, "P %d", &pid) != 1)
			{
				fprintf(stderr, "Event P parsing error\n");
				ret = 1;
				break;
			}
			create_party(pid);
			break;
		case 'C':
			if (sscanf(trimmed_line, "C %d %d %d", &cid, &did, &pid) != 3)
			{
				fprintf(stderr, "Event C parsing error\n");
				ret = 1;
				break;
			}
			ret = register_candidate(cid, did, pid);
			break;
		case 'R':
			if (sscanf(trimmed_line, "R %d %d %d", &vid, &did, &sid) != 3)
			{
				fprintf(stderr, "Event R parsing error\n");
				ret = 1;
				break;
			}
			ret = register_voter(vid, did, sid);
			break;
		case 'U':
			if (sscanf(trimmed_line, "U %d", &vid) != 1)
			{
				fprintf(stderr, "Event U parsing error\n");
				ret = 1;
				break;
			}
			ret = unregister_voter(vid);
			break;
		case 'E':
			delete_empty_stations();
			break;
		case 'V':
			if (sscanf(trimmed_line, "V %d %d %d", &vid, &sid, &cid) != 3)
			{
				fprintf(stderr, "Event V parsing error\n");
				ret = 1;
				break;
			}
			ret = vote(vid, sid, cid);
			break;
		case 'M':
			if (sscanf(trimmed_line, "M %d", &did) != 1)
			{
				fprintf(stderr, "Event M parsing error\n");
				ret = 1;
				break;
			}
			count_votes(did);
			break;
		case 'G':
			form_government();
			break;
		case 'N':
			form_parliament();
			break;
		case 'I':
			if (sscanf(trimmed_line, "I %d", &did) != 1)
			{
				fprintf(stderr, "Event I parsing error\n");
				ret = 1;
				break;
			}
			print_district(did);
			break;
		case 'J':
			if (sscanf(trimmed_line, "J %d %d", &sid, &did) != 2)
			{
				fprintf(stderr, "Event J parsing error\n");
				ret = 1;
				break;
			}
			print_station(sid, did);
			break;
		case 'K':
			if (sscanf(trimmed_line, "K %d", &pid) != 1)
			{
				fprintf(stderr, "Event I parsing error\n");
				ret = 1;
				break;
			}
			print_party(pid);
			break;
		case 'L':
			print_parliament();
			break;
		default:
			fprintf(stderr, "WARNING: Unrecognized event %c. Continuing...\n",
					event);
			ret = 1;
			break;
		}
		fprintf(stderr, "Event %c %s.\n", event,
				ret ? "failed" : "succeeded");
	}
	fclose(event_file);
	destroy_structures();
	return 0;
}
