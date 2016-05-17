#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#define MAX_ITEMS	10
#define MAX_LEN		256
#define MAX_BG 		3

extern char **environ;

// For manage background processes 
int 	bgcnt = 0;
int 	bgpid[MAX_BG];
char 	bgps[MAX_BG][MAX_LEN];

int parseitems (char* cmdln, char items[][MAX_LEN])
{
	int i = 0;
	char* pch = NULL;

	pch = strtok (cmdln, " \n");
	while (pch != NULL && i < MAX_ITEMS) {
		strcpy (items[i], pch);
		pch = strtok (NULL, " \n");
		i++;
	}

	return i;
}

void print_v (char itemv[][MAX_LEN], int itemc){
	int i;
	printf ("# of arguments: %d\n", itemc);
	for (i = 0; i < itemc; i++){
		printf ("-argv[%d]: %s\n", i, itemv[i]);
	}
	return; 
}

void bg_insert (int pid, char pname[MAX_LEN]){
	int i;
	for (i = 0; i < MAX_BG; i++){
		if (bgpid[i] == -1){
			bgpid[i] = pid;
			strcpy (bgps[i], pname);
			break;
		}
	}
	bgcnt++;
	return;
}

void bg_remove (int pid){
	int i, cs;
	for (i = 0; i < MAX_BG; i++){
		if (bgpid[i] == pid){
			bgpid[i] = -1;
			waitpid (pid, &cs, 0);
		}
	}
	bgcnt--;
	return;
}

void shell_front(){
	char cmdln[MAX_LEN];
	char items[MAX_ITEMS][MAX_LEN];
	char *myv[MAX_ITEMS];
	char cmd[MAX_LEN];
	int nr_items, i, bg, cs;
	pid_t pid;
	
	// Init
	bgcnt = 0;
	for (i = 0; i < 3; i++) bgpid[i] = -1;
		
	while(1){
		// Init
		bg = 0;
		// Get command
		printf ("> ");
		fgets (cmdln, MAX_LEN, stdin);
		nr_items = parseitems (cmdln, items);
		// Debugging station
		//print_v (items, nr_items);
		// Built-in commands
		if (!strcmp(items[0], "exit")){
			printf("Goodbye! \n");
			break;
		}
		if (!strcmp(items[0], "close")){
			bg_remove (atoi(items[1]));
			continue;
		}
		if (!strcmp(items[0], "status")){
			for (i = 0; i < MAX_BG; i++){
				if (bgpid[i] != -1)
					printf("[%d] %s\n", bgpid[i], bgps[i]);
			}
			continue;
		}
		// Check background
		if(!strcmp(items[nr_items-1], "&")){
			if (bgcnt >= MAX_BG){
				printf("Failed: maximum # of background job is 3\n");
				continue;
			}
			else bg = 1;
		}
		// New process
		if ((pid = fork()) == 0){
			if (bg) nr_items--;
			for (i = 0;i < nr_items; i++)
				myv[i] = items[i];
			if (bg)
				printf ("[%d] %s \n", getpid(), items[0]);
			execvpe (items[0], myv, environ);
		}
		else {
			if (!bg)
				waitpid (pid, &cs, 0);
			else 
				bg_insert (pid, items[0]);
		}
	}
	return;
}

int main (int argc, char* argv[])
{
	char cmdln[MAX_LEN];
	char items[MAX_ITEMS][MAX_LEN];
	int nr_items;
	
//	strcpy (cmdln, "Test string");
//	nr_items = parseitems (cmdln, items);
//	printf ("%d\n%s\n%s\n", nr_items, items[0], items[1]);
	
	shell_front();

	return 0;
}