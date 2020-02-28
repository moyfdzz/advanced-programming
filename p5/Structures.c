/*
*   Author: Moisés Fernández Zárate A01197049
*   Date created: 22/02/2020
*
*   Structures.c
*   A practice to learn structures in C.
*/
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#define LETTER_CODE_SIZE 3
#define MISSION_ID_SIZE 12

// This struct stores the profile of an agent.
struct agent
{
    char name[70];
    char lastName[70];
    char gender[6];
    char mission[MISSION_ID_SIZE];
    int age;
};

typedef struct agent Agent;

/*
*   Function: fillAgentProfile(Agent *agent)
*   This function receives the information of an agent and stores it
*   to create a profile.
*   Parameters: Agent *agent: stores the information of an agent.
*   Return value: None.
*/
void fillAgentProfile(Agent *agent);

/*
*   Function: printAgentProfile(Agent agent)
*   This function receives the profile of an agent and prints its information.
*   Parameters: Agent *agent: stores the information of an agent.
*   Return value: None.
*/
void printAgentProfile(Agent agent);

/*
*   Function: validateMission(char cMission[MISSION_ID_SIZE])
*   This function validates the mission of an agent.
*   Parameters: char cMission[]: stores the mission of an agent.
*   Return value: None.
*/
void validateMission(char cMission[MISSION_ID_SIZE]);

/*
*   main()
*   This is the main function where the flow of the program happens.
*/
int main(void)
{
    // Creates an agent using the struct Agent.
    Agent agent;

    fillAgentProfile(&agent);
    printAgentProfile(agent);

    return 0;
}

void fillAgentProfile(Agent *agent) 
{
    char cMission[MISSION_ID_SIZE];

    printf("Enter the first name of the agent: ");
    scanf("%s", agent->name);

    printf("Enter the last name of the agent: ");
    scanf("%s", agent->lastName);

    printf("Enter the age of the agent: ");
    scanf("%d", &agent->age);

    printf("Enter the gender of the agent: ");
    scanf("%s", agent->gender);

    validateMission(cMission);

    strcpy(agent->mission, cMission);
}

void validateMission(char cMission[MISSION_ID_SIZE])
{
    bool isValidMission = true;

    do {
        printf("Enter the mission of the agent (this is an Id, which includes a 3 letter code and 9 digits): ");
        scanf("%s", cMission);

        isValidMission = true;

        if (strlen(cMission) < MISSION_ID_SIZE)
        {
            isValidMission = false;
        }

        for (int i = 0; i < LETTER_CODE_SIZE; i++)
        {
            if (cMission[i] < 'A' || (cMission[i] > 'Z' && cMission[i] < 'a') || cMission[i] > 'z') 
            {
                isValidMission = false;
            }
        }

        for (int i = LETTER_CODE_SIZE; i < MISSION_ID_SIZE; i++) 
        {
            if (cMission[i] < '0' || cMission[i] > '9')
            {
                isValidMission = false;
            }
        }

        if (!isValidMission) {
            printf("%s", "The mission of the agent is invalid.\n");
        }
    }
    while (!isValidMission);
}

void printAgentProfile(Agent agent)
{
    printf("Here is the profile of the agent \n");
    printf("Name: %s\n", agent.name);
    printf("Last name: %s\n", agent.lastName);
    printf("Age: %d years old\n", agent.age);
    printf("Gender: %s\n", agent.gender);
    printf("Mission: %s\n", agent.mission);
}