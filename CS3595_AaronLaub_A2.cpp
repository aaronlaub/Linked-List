
/* File Name: CS3595_AaronLaub_A2.cpp
 * Author: Aaron Laub
 * Email: alaub2@fordham.edu
 * Assignment: Linked List Process Scheduler
 * Description: Reads in list of process names and times. 
 *	Simulates execution of processes with round robbin scheduling
 * Last Changed: 2/21/2017
 */

#include <iostream>
#include <cstdlib>
#include <iomanip>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string>
using namespace std;

struct Node {	//Struct to store each processes data
	string name;
	int time;
	Node *next;
};

Node *head = new Node;	//initialize head and tail nodes
Node *tail = new Node;
void input(){	//read input
	Node *curr = head;
	
	string name;
	int time;
	while(cin >> name >> time){
		Node *nptr = new Node;
		nptr->name = name;
		nptr->time = time;
		curr->next = nptr;
		curr = curr->next;
	}
	tail = curr;
	tail->next = head->next;
	curr->next = NULL;
}

void display(){	//function to display list to check input
	Node *curr = head;
	//curr->next = head->next;
	while(curr->next){
		curr = curr->next;
		cout << curr->name << " " << curr->time << endl;
	}
	cout << endl;
}



/* This flag controls termination of the main loop.  */
volatile sig_atomic_t keep_going = 1;
int count=0;
#define MAX_TIMES 5

/* The signal handler just clears the flag and re-enables itself.  */
void catch_alarm (int sig){

	if (!head->next) keep_going = 0;
  	puts("Interrupt\n");
  	signal (sig, catch_alarm);
  	alarm(2);

	if(head->next){
		Node *curr = head->next;
		if(curr->time > 0){
			cout << curr->name << " " << curr->time << endl;
			curr->time = curr->time - 2;
			if(curr->time <= 0){
				cout << curr->name << " Finished\n";
				head->next = curr->next;
				curr->next = NULL;
				curr = NULL;
				delete curr;
			}
	
			else {
				cout << curr->name << " " << curr->time << endl;
				head->next = curr->next;
				curr->next = tail->next;
				tail->next = curr;
				tail = curr;
			}
		}
	}
	else {
		cout << "No Processes Left\n";
	}
}

void do_stuff (){
  	//puts ("Doing stuff while waiting for alarm....");
  	sleep(1);
}

int main (void){
	input();
	//display();
	

	/* Establish a handler for SIGALRM signals.  */
	signal (SIGALRM, catch_alarm);

  	/* Set an alarm to go off in a little while.  */
  	alarm (2);

  	/* Check the flag once in a while to see when to quit.  */
  	while (keep_going){
    		do_stuff ();
	}
  	return EXIT_SUCCESS;
}

