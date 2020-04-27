/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 01/03/2020
*
*   Mission0.c
*   In this mission we simulate a system that manages agents.
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <stdlib.h> 

/*
*	struct Node
*	Structure created to manage each intelligence active and mission,
*	which are simulated with the next structure ListNodes.
*/
typedef struct Node {
    struct Node *next;
	char input[70];
} Node;

/*
*	struct ListNodes
*	Structure created to manage the intelligence actives and missions
*	of each agent, which uses the structure Node for each intelligence
*	active and mission.
*/
typedef struct ListNodes {
	Node *head;
	Node *tail;
} ListNodes;

/*
*	struct Agent
*	Structure created to manage each agent's profile in the system.
*/
typedef struct Agent {
	char name[70];
	char lastName[70];
	int age;
	ListNodes intelligenceActives;
	ListNodes missions;
	struct Agent *next;
} Agent;

/*
*	struct ListAgents
*	Structure created to manage all the agents in the system.
*/
typedef struct ListAgents {
	Agent *head;
	Agent *tail;
} ListAgents;

/*
*	function menu()
*	This function displays the menu of the system.
*	Parameters: none.
*	Return value: none.
*/
void menu();

/*
*	function createEntry()
*	This function creates an agent's profile to store it in the system.
*	Parameters: none.
*	Return value: none.
*/
void createEntry();

/*
* 	function addIntelligenceActive(agent, intelligenceActive, counter)
* 	Parameters: 
*	agent: an agent where the intelligence active will be stored.
*	intelligenceActive: the intelligence active that will be stored in the agent's profile.
*	counter: this counter is used to know how to add an intelligence active to the list
*			 of the agent, depending on if it's the first or another one after that.
*	Return value: none.
*/
void addIntelligenceActive(Agent *agent, char intelligenceActive[70], int counter);

/*
* 	function addMission(agent, mission, counter)
* 	Parameters: 
*	agent: an agent where the mission will be stored.
*	mission: the mission that will be stored in the agent's profile.
*	counter: this counter is used to know how to add a mission to the list of the
*			 agent, depending on if it's the first or another one after that.
*	Return value: none.
*/
void addMission(Agent *agent, char mission[70], int counter);

/*
*	function deleteEntry()
*	This function deletes an agent's profile of the system.
*	Parameters: none.
*	Return value: none.
*/
void deleteEntry();

/*
*	function showAgentProfile(agent)
*	This function displays the profile of an agent that is received as a parameter.
*	Parameters:
*	agent: the agent whose profile will be displayed.
*	Return value: none.
*/
void showAgentProfile(Agent *agent);

/*
*	function showAgents()
*	This function displays the profiles of all the agents that are registered.
*	Parameters: none.
*	Return value: none.
*/
void showAgents();

/*
*	function validateMission(mission)
*	This function checks if the mission received is correct.
*	Parameters:
*	mission: the mission that will be checked.
*	Return value: a boolean to know if the mission received is correct.	
*/
bool validateMission(char *mission);

/*
*	function validateIntelligenceActive(intelligenceActive)
*	This function checks if the intelligence active received is correct.
*	Parameters:
*	intelligenceActive: the intelligence active that will be checked.
*	Return value: a boolean to know if the intelligence active received is correct.	
*/
bool validateIntelligenceActive(char *intelligenceActive);

// Global variable to manage the list of agents that are registered.
ListAgents agents;

// The main function.
int main(void) 
{
    menu();

    return 0;
}

void menu()
{
	int option;

	while (true)
	{
		printf("----------------------MENU----------------------\n");
		printf("Select one of the following options (1, 2, 3 or 4):\n");
		printf("1) Create a new entry\n");
		printf("2) Delete an entry\n");
		printf("3) Show all agents' profiles\n");
		printf("4) Exit\n");
		scanf("%d", &option);
		
		switch(option)
		{
			case 1:
				createEntry();
				break;
			case 2:
				deleteEntry();
				break;
			case 3:
				showAgents();
				break;
			case 4:
				exit(0);
				break;
			default:
				printf("That is not a valid option.\n");
				menu();
				break;
		}
	}
}

bool validateIntelligenceActive(char *intelligenceActive)
{
	if (strlen(intelligenceActive) < 13)
	{
		return false;
	}

	for (int i = 0; i < 4; i++)
	{
		if (intelligenceActive[i] < 'A' || (intelligenceActive[i] > 'Z' && intelligenceActive[i] < 'a') || intelligenceActive[i] > 'z')
		{
			return false;
		}
	}

	for (int i = 4; i < strlen(intelligenceActive); i++)
	{
		if (intelligenceActive[i] < '0' || intelligenceActive[i] > '9')
		{
			return false;
		}
	}

	return true;
}

bool validateMission(char *mission)
{
	if (strlen(mission) < 12)
	{
		return false;
	}

	for (int i = 0; i < 3; i++)
	{
		if (mission[i] < 'A' || (mission[i] > 'Z' && mission[i] < 'a') || mission[i] > 'z')
		{
			return false;
		}
	}

	for (int i = 3; i < strlen(mission); i++)
	{
		if (mission[i] < '0' || mission[i] > '9')
		{
			return false;
		}
	}

	return true;
}

void addIntelligenceActive(Agent *agent, char intelligenceActive[70], int counter)
{
	Node *newIntelligenceActive = 0;
	newIntelligenceActive = (Node*) malloc(sizeof(Node));
	strcpy(newIntelligenceActive->input, intelligenceActive);
	newIntelligenceActive->next = 0;

	if (counter == 0)
	{
		agent->intelligenceActives.head = newIntelligenceActive;
		agent->intelligenceActives.tail = agent->intelligenceActives.head;
	}
	else
	{
		agent->intelligenceActives.tail->next = newIntelligenceActive;
		agent->intelligenceActives.tail = newIntelligenceActive;
	}
}

void addMission(Agent *agent, char mission[70], int counter)
{
	Node *newMission = 0;
	newMission = (Node*) malloc(sizeof(Node));
	strcpy(newMission->input, mission);
	newMission->next = 0;

	if (counter == 0)
	{
		agent->missions.head = newMission;
		agent->missions.tail = agent->missions.head;
	}
	else
	{
		agent->missions.tail->next = newMission;
		agent->missions.tail = newMission;
	}
}

void createEntry()
{
    Agent *agent;
	agent = (struct Agent*) malloc(sizeof(struct Agent));
	agent->intelligenceActives.head = 0;
	agent->intelligenceActives.tail = 0;
	agent->missions.head = 0;
	agent->missions.tail = 0;

	printf("Enter the first name of the agent: ");
    scanf("%s", agent->name);

    printf("Enter the last name of the agent: ");
    scanf("%s", agent->lastName);

    printf("Enter the age of the agent: ");
    scanf("%d", &agent->age);

	// Adding intelligence actives to an agent.
	int numberIntelligenceActives = 0;
	char intelligenceActive[70];

	printf("Enter the number of intelligence actives: ");
	scanf("%d", &numberIntelligenceActives);

	for (int i = 0; i < numberIntelligenceActives; i++)
  	{
		printf("Enter the intelligence active #%d: ", i + 1);
		scanf("%s", intelligenceActive);

		while (!validateIntelligenceActive(intelligenceActive))
		{
			printf("The intelligence active is invalid. Please enter it again (4 letters followed by 9 digits): ");
			scanf("%s", intelligenceActive);
		}

		addIntelligenceActive(agent, intelligenceActive, i);
    }

	// Adding missions to an agent.
	int numberMissions = 0;
	char mission[70];

	printf("Enter the number of missions: ");
	scanf("%d", &numberMissions);

	for (int i = 0; i < numberMissions; i++)
	{
		printf("Enter mission #%d: ", i+1);
		scanf("%s", mission);

		while (!validateMission(mission))
		{
			printf("The mission is invalid. Please enter it again (3 letters followed by 9 digits): ");
			scanf("%s", mission);
		}

		addMission(agent, mission, i);
	}

	if (agents.head == 0)
	{
		agents.head = agent;
		agents.tail = agent;
	}
	else
	{
		agents.tail->next = agent;
		agents.tail = agent;
	}

	agents.tail->next = 0;

	printf("The agent profile was registered with success.\n");
}

void deleteEntry()
{
	Agent *curr = agents.head;
	Agent *prev = agents.head;
	char name[70];
	char lastName[70];
	int numberAgent = 1;

	printf("To delete an agent, please enter the following information...\n");
	printf("Agent's first name: ");
    scanf("%s", name);

    printf("Agent's last name: ");
    scanf("%s", lastName);

	printf("Looking for the agent %s %s...\n", name, lastName);

	if (curr == 0)
	{
		printf("Error: The agent %s %s was not found.\n", name, lastName);

		return;
	}

	if (!strcmp(curr->name, name) && !strcmp(curr->lastName, lastName))
	{
		agents.head = agents.head->next;
        curr->next = 0;
        free(curr);
        curr = agents.head;
        prev = agents.head;

		printf("The agent %s %s was deleted succesfully.\n", name, lastName);

		return;
	}
	else
	{
		curr = curr->next;
	}

	while (curr != 0)
	{
		if (!strcmp(curr->name, name) && !strcmp(curr->lastName, lastName))
		{
			prev->next = curr->next;
            curr->next = NULL;
            free(curr);
            curr = prev->next;

			printf("The agent %s %s was deleted succesfully.\n", name, lastName);

			return;
		}
		else
		{
			prev = prev->next;
            curr = curr->next;
		}
	}

	printf("Error: The agent %s %s was not found.\n", name, lastName);
}

void showAgentProfile(Agent *agent)
{
	printf("----------------------AGENT PROFILE----------------------\n");
	printf("Agent's name: %s\n", agent->name);
	printf("Agent's last name: %s\n", agent->lastName);
    printf("Agent's age: %d\n", agent->age);
	printf("--------AGENT'S INTELLIGENCE ACTIVES--------\n");

	Node *curr = agent->intelligenceActives.head;
	
	while (curr != 0)
	{
		printf("%s\n", curr->input);
		curr = curr->next;
	}

	printf("--------AGENT'S MISSIONS--------\n");

	curr = agent->missions.head;

	while (curr != 0)
	{
		printf("%s\n", curr->input);
		curr = curr->next;
	}
}

void showAgents()
{
	Agent *curr = agents.head;

	while (curr != 0)
	{
		showAgentProfile(curr);
		curr = curr->next;
	}
}