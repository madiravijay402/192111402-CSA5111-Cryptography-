#include <stdio.h>

int main() {
    // Define the incident details
    char incident_date[] = "August 2, 1943";
    char boat_name[] = "PT-109";
    char commander[] = "Lieutenant John F. Kennedy";
    char sinking_cause[] = "sunk by a Japanese destroyer";
    char location[] = "near the Solomon Islands";

    // Create the message
    printf("On %s, the %s American patrol boat, under the command of %s, was %s %s. The incident is a significant event in history.\n", incident_date, boat_name, commander, sinking_cause, location);

    return 0;
}
