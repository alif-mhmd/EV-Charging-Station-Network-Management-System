/*
--Electric Vehicle (EV) Charging Station Network Management--

This C program implements a basic management system for a network of Electric Vehicle (EV) charging stations. It uses a user-defined structure to represent
each charging station, including station ID, station name, location, number of available & total charging ports, charging time, charger types and
charging price per kWh. We can view details of all charging stations, search for stations by location and sort stations by charging price(low to high).
*/

#include <stdio.h>
#include <string.h>

struct EVChargingStation
{
    int stationID;
    char stationName[50];
    char stationLocation[50];
    int availablePorts;
    int totalPorts;
    int chargingTime;
    char chargerType[20];
    float chargingPrice;
};


void displayStation(struct EVChargingStation station)
{
    printf("Station ID: %d\n", station.stationID);
    printf("Station Name: %s\n", station.stationName);
    printf("Location: %s\n", station.stationLocation);
    printf("Available Ports: %d/%d\n", station.availablePorts, station.totalPorts);
    printf("Charging Time: Full charge in %d mins\n", station.chargingTime);
    printf("Charger Type: %s\n", station.chargerType);
    printf("Charging Price: BDT%.2f per KWh\n", station.chargingPrice);
    printf("-------------------------------------\n");
}


void searchByLocation(struct EVChargingStation stations[], int size, char location[])
{
    int found=0;
    for (int i=0; i<size; i++)
        {
            if (strstr(stations[i].stationLocation, location))
                {
                    displayStation(stations[i]);
                    found=1;
                }
        }
    if (!found)
        printf("No stations found at this location.\n");
}


void sortByPrice(struct EVChargingStation stations[], int size)
{
    struct EVChargingStation temp;
    for (int i=0; i<size-1; i++)
        {
            for (int j=i+1; j<size; j++)
            {
                if (stations[i].chargingPrice>stations[j].chargingPrice)
                {
                    temp=stations[i];
                    stations[i]=stations[j];
                    stations[j]=temp;
                }
            }
    }
}




int main()
{
    struct EVChargingStation stations[5]=
    {
        {1, "Ekhon Charge", "Tejgaon, Dhaka", 4, 5, 20, "DC Fast", 16.24},
        {2, "Impetus Center", "Gulshan, Dhaka", 6, 6, 30, "AC & DC", 18.97},
        {3, "Mulytic Energy", "Jashore Airport, Jashore", 3, 4, 60, "DC", 14.22},
        {4, "IPDC Bangladesh", "Dewanhat, Chattogram", 3, 5, 40, "AC", 12.27},
        {5, "Genex EV Hub", "Cheora, Comilla", 2, 4, 50, "AC & DC", 13.06}
    };

    int choice;
    char searchLocation[50];
    while(1)
    {
        printf("--EV Charging Station Network--\n");
        printf("1. Display all stations\n");
        printf("2. Search stations by location\n");
        printf("3. Sort stations by charging price(low to high)\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");

        if(scanf("%d", &choice)!=1)
            {
                printf("Invalid input. Please enter a number.\n");
                while (getchar()!='\n');
                continue;
            }
        getchar();

        switch(choice)
        {
            case 1:
                printf("\nAll EV Charging Stations:\n");
                for(int i=0; i<5; i++)
                    displayStation(stations[i]);
                break;

            case 2:
                printf("Enter the location to search: ");
                fgets(searchLocation, sizeof(searchLocation), stdin);
                searchLocation[strcspn(searchLocation, "\n")]='\0';
                searchByLocation(stations, 5, searchLocation);
                break;

            case 3:
                sortByPrice(stations, 5);
                printf("\nStations sorted by charging price:\n");
                for (int i=0; i<5; i++)
                    displayStation(stations[i]);
                break;

            case 4:
                printf("Exited the program. Thanks for using.\n");
                return 0;

            default:
                printf("Invalid input. Please try again.\n");
        }
    }

    return 0;
}
