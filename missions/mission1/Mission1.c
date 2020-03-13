/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 08/03/2020
*
*   Mission1.c
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
*	function searchEntry()
*	This function searches for an agent's profile of the system.
*	Parameters: none.
*	Return value: none.
*/
void searchEntry();

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

/*
*	function encryptMessage(message)
* 	This function encrypts a message if the password introduced is wrong and
* 	also prints the message.The encryption technique used is Caesar Cipher.
* 	Parameters:
*	message: the message that will be encrypted.
*	Return value: none.
*/
void encryptMessage(char message[100]);

/*
*	function validatePassword()
*	This function receives a password introduced by the user and
*	validates it.
*	Parameters: none.
*	Return value: none.
*/
void introducePassword();

// Global variable to manage the list of agents that are registered.
ListAgents agents;

// Global variable to check if the introduced password is correct.
bool correctPassword = true;

// Global variable to store the system's password.
char systemPassword[100] = "topsecret";

// Global variable to store the message that will be encrypted.
char message[100];

// The main function.
int main(void) 
{
	introducePassword();
    menu();

    return 0;
}

void introducePassword() 
{
	char password[100];

	printf("Enter the password of the system: ");
	scanf("%s", password);

	//printf("%s %s \n", password, systemPassword);
	//printf("%d \n", strcmp(password, systemPassword));

	if (strcmp(password, systemPassword) != 0) 
	{
		correctPassword = false;

		printf("The password introduced is incorrect.\n");
	}
	else 
	{
		printf("The password introduced is correct.\n");
	}
}

void encryptMessage(char message[100]) 
{
	if (!correctPassword) 
	{
		char ch;
		int key = 4;

		for (int i = 0; i < strlen(message); i++) 
		{
			ch = message[i];
		
			if(ch >= 'a' && ch <= 'z') 
			{
				ch = ch + key;
			
				if(ch > 'z') 
				{
					ch = ch - 'z' + 'a' - 1;
				}
			
				message[i] = ch;
			}
			else if (ch >= 'A' && ch <= 'Z') 
			{
				ch = ch + key;
			
				if(ch > 'Z') 
				{
					ch = ch - 'Z' + 'A' - 1;
				}
			
				message[i] = ch;
			}
			else {
				message[i] = '!';
			}
		}
	}

	printf("%s\n", message);
}

void menu()
{
	int option;

	while (true)
	{
		strcpy(message, "----------------------MENU----------------------");
		encryptMessage(message);
		strcpy(message, "Select one of the following options (1, 2, 3 or 4):");
		encryptMessage(message);
		strcpy(message, "1) Create a new entry");
		encryptMessage(message);
		strcpy(message, "2) Delete an entry");
		encryptMessage(message);
		strcpy(message, "3) Search for an entry");
		encryptMessage(message);
		strcpy(message, "4) Show all agents' profiles");
		encryptMessage(message);
		strcpy(message, "5) Exit");
		encryptMessage(message);
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
				searchEntry();
				break;
			case 4:
				showAgents();
				break;
			case 5:
				exit(0);
				break;
			default:
				strcpy(message, "That is not a valid option.");
				encryptMessage(message);
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

	strcpy(message, "Enter the first name of the agent ");
	encryptMessage(message);
    scanf("%s", agent->name);

    strcpy(message, "Enter the last name of the agent ");
	encryptMessage(message);
    scanf("%s", agent->lastName);

    strcpy(message, "Enter the age of the agent ");
	encryptMessage(message);
    scanf("%d", &agent->age);

	// Adding intelligence actives to an agent.
	int numberIntelligenceActives = 0;
	char intelligenceActive[70];

	strcpy(message, "Enter the number of intelligence actives");
	encryptMessage(message);
	scanf("%d", &numberIntelligenceActives);

	for (int i = 0; i < numberIntelligenceActives; i++)
  	{
		strcpy(message, "Enter the intelligence active");
		encryptMessage(message);
		scanf("%s", intelligenceActive);

		while (!validateIntelligenceActive(intelligenceActive))
		{
			strcpy(message, "The intelligence active is invalid. Please enter it again (4 letters followed by 9 digits)");
			encryptMessage(message);
			scanf("%s", intelligenceActive);
		}

		addIntelligenceActive(agent, intelligenceActive, i);
    }

	// Adding missions to an agent.
	int numberMissions = 0;
	char mission[70];

	strcpy(message, "Enter the number of missions");
	encryptMessage(message);
	scanf("%d", &numberMissions);

	for (int i = 0; i < numberMissions; i++)
	{
		strcpy(message, "Enter the mission");
		encryptMessage(message);
		scanf("%s", mission);

		while (!validateMission(mission))
		{
			strcpy(message, "The mission is invalid. Please enter it again (3 letters followed by 9 digits)");
			encryptMessage(message);
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

	strcpy(message, "The agent profile was registered with success.");
	encryptMessage(message);
}

void deleteEntry()
{
	Agent *curr = agents.head;
	Agent *prev = agents.head;
	char name[70];
	char lastName[70];

	printf("To delete an agent, please enter the following information...");
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

void searchEntry() {
	Agent *curr = agents.head;
	Agent *prev = agents.head;
	char lastName[70];
	int option;

	strcpy(message, "To search for an entry, please enter the following information...");
	encryptMessage(message);
	strcpy(message, "Agent's last name");
	encryptMessage(message);
    scanf("%s", lastName);

	strcpy(message, "Looking for the agent...");
	encryptMessage(message);

	if (curr == 0)
	{
		strcpy(message, "Error: The agent was not found.");
		encryptMessage(message);

		return;
	}

	if (!strcmp(curr->lastName, lastName))
	{
		strcpy(message, "The agent was found.");
		encryptMessage(message);

		while (true)
		{
			strcpy(message, "Select one of the following options (1, 2, 3 or 4):");
			encryptMessage(message);
			strcpy(message, "1) Delete the entry");
			encryptMessage(message);
			strcpy(message, "2) Edit the entry");
			encryptMessage(message);
			strcpy(message, "3) Return to the main menu");
			encryptMessage(message);
			strcpy(message, "4) Exit the system");
			encryptMessage(message);
			scanf("%d", &option);

			if (option == 1) {
				agents.head = agents.head->next;
        		curr->next = 0;
        		free(curr);
        		curr = agents.head;
        		prev = agents.head;

				strcpy(message, "The agent was deleted succesfully.");
				encryptMessage(message);

				return;
			}
			else if (option == 2) {
				// Adding intelligence actives to an agent.
				int numberIntelligenceActives = 0;
				char intelligenceActive[70];

				strcpy(message, "Enter the number of intelligence actives that you want to add to the agent");
				encryptMessage(message);
				scanf("%d", &numberIntelligenceActives);

				for (int i = 0; i < numberIntelligenceActives; i++)
				{
					strcpy(message, "Enter the intelligence active");
					encryptMessage(message);
					scanf("%s", intelligenceActive);

					while (!validateIntelligenceActive(intelligenceActive))
					{
						strcpy(message, "The intelligence active is invalid. Please enter it again (4 letters followed by 9 digits)");
						encryptMessage(message);
						scanf("%s", intelligenceActive);
					}

					addIntelligenceActive(curr, intelligenceActive, 1);
				}

				// Adding missions to an agent.
				int numberMissions = 0;
				char mission[70];

				strcpy(message, "Enter the number of missions that you want to add to the agent");
				encryptMessage(message);
				scanf("%d", &numberMissions);

				for (int i = 0; i < numberMissions; i++)
				{
					strcpy(message, "Enter the mission");
					encryptMessage(message);
					scanf("%s", mission);

					while (!validateMission(mission))
					{
						strcpy(message, "The mission is invalid. Please enter it again (3 letters followed by 9 digits)");
						encryptMessage(message);
						scanf("%s", mission);
					}

					addMission(curr, mission, 1);
				}

				strcpy(message, "The agent profile was updated with success.");
				encryptMessage(message);
			}
			else if (option == 3) {
				return;
			}
			else if (option == 4) {
				exit(0);
			}
			else {
				strcpy(message, "That is not a valid option.");
				encryptMessage(message);
				printf("Select one of the following options (1, 2, 3 or 4):");
				encryptMessage(message);
				strcpy(message, "1) Delete the entry");
				encryptMessage(message);
				strcpy(message, "2) Edit the entry");
				encryptMessage(message);
				strcpy(message, "3) Return to the main menu");
				encryptMessage(message);
				strcpy(message, "4) Exit the system");
				encryptMessage(message);
				scanf("%d", &option);
			}
		}
	}
	else
	{
		curr = curr->next;
	}

	while (curr != 0)
	{
		if (!strcmp(curr->lastName, lastName))
		{
			strcpy(message, "The agent was found.");
			encryptMessage(message);

			while (true)
			{
				strcpy(message, "Select one of the following options (1, 2, 3 or 4)");
				encryptMessage(message);
				strcpy(message, "1) Delete the entry");
				encryptMessage(message);
				strcpy(message, "2) Edit the entry");
				encryptMessage(message);
				strcpy(message, "3) Return to the main menu");
				encryptMessage(message);
				strcpy(message, "4) Exit the system");
				encryptMessage(message);
				scanf("%d", &option);

				if (option == 1) {
					prev->next = curr->next;
					curr->next = 0;
					free(curr);
					curr = prev->next;

					strcpy(message, "The agent was deleted succesfully.");

					return;
				}
				else if (option == 2) {
					// Adding intelligence actives to an agent.
					int numberIntelligenceActives = 0;
					char intelligenceActive[70];

					strcpy(message, "Enter the number of intelligence actives that you want to add to the agent");
					encryptMessage(message);
					scanf("%d", &numberIntelligenceActives);

					for (int i = 0; i < numberIntelligenceActives; i++)
					{
						strcpy(message, "Enter the intelligence active");
						encryptMessage(message);
						scanf("%s", intelligenceActive);

						while (!validateIntelligenceActive(intelligenceActive))
						{
							strcpy(message, "The intelligence active is invalid. Please enter it again (4 letters followed by 9 digits)");
							encryptMessage(message);
							scanf("%s", intelligenceActive);
						}

						addIntelligenceActive(curr, intelligenceActive, 1);
					}

					// Adding missions to an agent.
					int numberMissions = 0;
					char mission[70];

					strcpy(message, "Enter the number of missions that you want to add to the agent");
					encryptMessage(message);
					scanf("%d", &numberMissions);

					for (int i = 0; i < numberMissions; i++)
					{
						strcpy(message, "Enter the mission");
						encryptMessage(message);
						scanf("%s", mission);

						while (!validateMission(mission))
						{
							strcpy(message, "The mission is invalid. Please enter it again (3 letters followed by 9 digits");
							encryptMessage(message);
							scanf("%s", mission);
						}

						addMission(curr, mission, 1);
					}

					strcpy(message, "The agent profile was updated with success.");
					encryptMessage(message);
				}
				else if (option == 3) {
					return;
				}
				else if (option == 4) {
					exit(0);
				}
				else {
					strcpy(message, "That is not a valid option.");
					encryptMessage(message);
					strcpy(message, "Select one of the following options (1, 2, 3 or 4):");
					encryptMessage(message);
					strcpy(message, "1) Delete the entry");
					encryptMessage(message);
					strcpy(message, "2) Edit the entry");
					encryptMessage(message);
					strcpy(message, "3) Return to the main menu");
					encryptMessage(message);
					strcpy(message, "4) Exit the system");
					encryptMessage(message);
					scanf("%d", &option);
				}
			}
		}
		else
		{
			prev = prev->next;
            curr = curr->next;
		}
	}

	strcpy(message, "Error: The agent was not found.");
	encryptMessage(message);
}

void showAgentProfile(Agent *agent)
{
	strcpy(message, "----------------------AGENT PROFILE----------------------");
	encryptMessage(message);
	strcpy(message, "Agent's name");
	encryptMessage(message);
	strcpy(message, agent->name);
	encryptMessage(message);
	strcpy(message, "Agent's last name");
	encryptMessage(message);
	strcpy(message, agent->lastName);
	encryptMessage(message);
    strcpy(message, "Agent's age");
	encryptMessage(message);
	sprintf(message, "%d", agent->age);
	encryptMessage(message);
	strcpy(message, "--------AGENT'S INTELLIGENCE ACTIVES--------");
	encryptMessage(message);

	Node *curr = agent->intelligenceActives.head;
	
	while (curr != 0)
	{
		strcpy(message, curr->input);
		encryptMessage(message);
		curr = curr->next;
	}

	strcpy(message, "--------AGENT'S MISSIONS--------");
	encryptMessage(message);

	curr = agent->missions.head;

	while (curr != 0)
	{
		strcpy(message, curr->input);
		encryptMessage(message);
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