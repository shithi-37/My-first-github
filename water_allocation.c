#include <stdio.h>
#include <string.h>

#define N 6

typedef struct {
    char id[10];
    char serviceZone[30];
    char type[25];
    double requested;
    double minimum;
    double loss;
    int waiting;
    double priority;
    double allocated;
    double effective;
    double shortage;
    char condition[30];
} Zone;


double emergencyScore(char type[]) {

    if (strcmp(type, "Hospital") == 0)
        return 100.0;

    else if (strcmp(type, "Emergency Service") == 0)
        return 95.0;

    else if (strcmp(type, "Emergency Shelter") == 0)
        return 85.0;

    else
        return 70.0;
}


void calculatePriority(Zone z[], int n) {

    int i;
    int maxWaiting = 0;

    for (i = 0; i < n; i++) {

        if (z[i].waiting > maxWaiting)
            maxWaiting = z[i].waiting;
    }


    for (i = 0; i < n; i++) {

        double emergency = emergencyScore(z[i].type);

        double minimumNeed =
            (z[i].minimum / z[i].requested) * 100.0;

        double waitingScore;

        if (maxWaiting == 0)
            waitingScore = 0.0;

        else
            waitingScore =
                ((double)z[i].waiting / maxWaiting) * 100.0;


        double efficiency = 100.0 - z[i].loss;


        z[i].priority =
            0.40 * emergency +
            0.30 * minimumNeed +
            0.20 * waitingScore +
            0.10 * efficiency;
    }
}


int comesBefore(Zone a, Zone b) {

    if (a.priority > b.priority)
        return 1;

    if (a.priority < b.priority)
        return 0;

    if (a.waiting > b.waiting)
        return 1;

    if (a.waiting < b.waiting)
        return 0;

    if (a.minimum > b.minimum)
        return 1;

    return 0;
}


void sortZones(Zone z[], int n) {

    int i, j, best;
    Zone temp;


    for (i = 0; i < n - 1; i++) {

        best = i;


        for (j = i + 1; j < n; j++) {

            if (comesBefore(z[j], z[best]))
                best = j;
        }


        if (best != i) {

            temp = z[i];

            z[i] = z[best];

            z[best] = temp;
        }
    }
}


void allocateWater(Zone z[], int n, double *available) {

    int i;
    double amount;


    for (i = 0; i < n; i++) {

        if (*available <= 0.0) {

            z[i].allocated = 0.0;

            continue;
        }


        if (*available >= z[i].requested)
            amount = z[i].requested;

        else
            amount = *available;


        z[i].allocated = amount;

        *available = *available - amount;
    }
}


void calculateResults(Zone z[], int n) {

    int i;


    for (i = 0; i < n; i++) {

        double lossAmount =
            z[i].allocated * z[i].loss / 100.0;


        z[i].effective =
            z[i].allocated - lossAmount;


        z[i].shortage =
            z[i].requested - z[i].effective;


        if (z[i].shortage < 0.0)
            z[i].shortage = 0.0;


        if (z[i].effective >= z[i].requested - 0.001)

            strcpy(z[i].condition,
                   "Full requirement");


        else if (z[i].effective >= z[i].minimum - 0.001)

            strcpy(z[i].condition,
                   "Minimum satisfied");


        else if (z[i].effective > 0.001)

            strcpy(z[i].condition,
                   "Below minimum");


        else

            strcpy(z[i].condition,
                   "Unserved");
    }
}


int findZone(Zone z[], int n, char id[]) {

    int i;


    for (i = 0; i < n; i++) {

        if (strcmp(z[i].id, id) == 0)
            return i;
    }


    return -1;
}


int findHighestShortage(Zone z[], int n) {

    int i;
    int index = 0;


    for (i = 1; i < n; i++) {

        if (z[i].shortage >
            z[index].shortage)

            index = i;
    }


    return index;
}


void showSummary(Zone z[], int n,
                 double originalAvailable,
                 double remainingWater) {

    int i;

    int full = 0;
    int minimum = 0;
    int below = 0;
    int unserved = 0;


    double totalRequested = 0.0;

    double totalAllocated = 0.0;

    double totalEffective = 0.0;

    double totalShortage = 0.0;


    printf("\n===============================================================\n");

    printf(" WATER ALLOCATION SUMMARY\n");

    printf("===============================================================\n");


    printf("%-5s %-10s %8s %8s %8s %10s %10s %10s %-18s\n",

           "ID",
           "Zone",
           "Request",
           "Minimum",
           "Priority",
           "Allocated",
           "Effective",
           "Shortage",
           "Condition");


    for (i = 0; i < n; i++) {

        printf("%-5s %-10s %8.0f %8.0f %8.2f %10.0f %10.2f %10.2f %-18s\n",

               z[i].id,
               z[i].serviceZone,
               z[i].requested,
               z[i].minimum,
               z[i].priority,
               z[i].allocated,
               z[i].effective,
               z[i].shortage,
               z[i].condition);


        totalRequested += z[i].requested;

        totalAllocated += z[i].allocated;

        totalEffective += z[i].effective;

        totalShortage += z[i].shortage;


        if (strcmp(z[i].condition,
                   "Full requirement") == 0)

            full++;


        else if (strcmp(z[i].condition,
                        "Minimum satisfied") == 0)

            minimum++;


        else if (strcmp(z[i].condition,
                        "Below minimum") == 0)

            below++;


        else

            unserved++;
    }


    printf("\nOriginal available water : %.2f L\n",
           originalAvailable);

    printf("Total requested : %.2f L\n",
           totalRequested);

    printf("Total allocated : %.2f L\n",
           totalAllocated);

    printf("Total effective delivery : %.2f L\n",
           totalEffective);

    printf("Total unresolved demand : %.2f L\n",
           totalShortage);

    printf("Remaining centre water : %.2f L\n",
           remainingWater);


    printf("\nFull requirement zones : %d\n",
           full);

    printf("Minimum satisfied zones : %d\n",
           minimum);

    printf("Below minimum zones : %d\n",
           below);

    printf("Unserved zones : %d\n",
           unserved);
}


int main() {

    Zone z[N] = {

        {"Z01", "Hospital",
         "Hospital", 4000, 3000, 2, 0},

        {"Z02", "FloodShelter",
         "Emergency Shelter", 3500, 2500, 4, 1},

        {"Z03", "Ward3",
         "Residential", 4500, 2000, 8, 2},

        {"Z04", "Ward5",
         "Residential", 3800, 1800, 12, 3},

        {"Z05", "SchoolShelter",
         "Emergency Shelter", 2600, 1600, 5, 1},

        {"Z06", "FireService",
         "Emergency Service", 2000, 1500, 1, 0}
    };


    double available;

    double remainingWater;

    char searchID[10];

    int index;

    int highestShortage;


    printf("Emergency Potable Water Allocation\n");

    printf("----------------------------------\n");

    printf("Enter available water (litres): ");

    scanf("%lf", &available);


    if (available < 0) {

        printf("Available water cannot be negative.\n");

        return 0;
    }


    calculatePriority(z, N);


    {

        double totalRequested = 0.0;

        int i;


        for (i = 0; i < N; i++)

            totalRequested += z[i].requested;


        if (available < totalRequested)

            sortZones(z, N);
    }


    remainingWater = available;


    allocateWater(z, N,
                  &remainingWater);


    calculateResults(z, N);


    showSummary(z, N,
                available,
                remainingWater);


    printf("\nEnter a Zone ID to search (example: Z03): ");

    scanf("%9s", searchID);


    index = findZone(z, N,
                     searchID);


    if (index != -1) {

        printf("\nZone found: %s\n",
               z[index].id);

        printf("Service Zone : %s\n",
               z[index].serviceZone);

        printf("Priority : %.2f\n",
               z[index].priority);

        printf("Allocated : %.2f L\n",
               z[index].allocated);

        printf("Effective : %.2f L\n",
               z[index].effective);

        printf("Shortage : %.2f L\n",
               z[index].shortage);

        printf("Condition : %s\n",
               z[index].condition);
    }


    else {

        printf("\nZone not found.\n");
    }


    highestShortage =
        findHighestShortage(z, N);


    printf("\nZone with highest unresolved requirement: %s (%s)\n",

           z[highestShortage].id,

           z[highestShortage].serviceZone);


    printf("Unresolved requirement: %.2f L\n",

           z[highestShortage].shortage);


    return 0;
}
