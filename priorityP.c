#include <stdlib.h>
#include <stdio.h>


int main()
{
    int pn = 0;                 //Processes Number
    int CPU = 0;            //CPU Current time
    int allTime = 0;        // Time neded to finish all processes
    printf("Enrer Processes Count: ");
    scanf("%d",&pn);
    int AT[pn];
    int ATt[pn];
    int NoP = pn;
    int PT[pn];             //Processes Time
    int PP[pn];             //Processes piriorty
    int PPt[pn];
    int waittingTime[pn];
    int turnaroundTime[pn];
    int i=0;
    //Scanning Time and Piriorty
    for(i=0 ;i<pn ;i++){
        printf("\nProcessing time for P%d: ",i+1);
        scanf("%d",&PT[i]);
        printf("Piriorty for P%d: ",i+1);
        scanf("%d",&PP[i]);
        PPt[i] = PP[i];
        printf("Arrival Time for P%d: ",i+1);
        scanf("%d",&AT[i]);
        ATt[i] = AT[i];
    }

    int LAT = 0;        //LastArrivalTime
    for(i = 0; i < pn; i++)
        if(AT[i] > LAT)
            LAT = AT[i];

    int MAX_P = 0;        //Max Piriorty
    for(i = 0; i < pn; i++)
        if(PPt[i] > MAX_P)
            MAX_P = PPt[i];

    int ATi = 0;        //Pointing to Arrival Time indix
    int P1 = PPt[0];     //Pointing to 1st piriorty Value
    int P2 = PPt[0];     //Pointing to 2nd piriorty Value


    //findding the First Arrival Time and Highst piriorty Process
    int j = -1;
    while(NoP > 0 && CPU <= 1000){
        for(i = 0; i < pn; i++){
            if((ATt[i] <= CPU) && (ATt[i] != (LAT+10))){
                if(PPt[i] != (MAX_P+1)){
                    P2 = PPt[i];
                    j= 1;

                    if(P2 < P1){
                        j= 1;
                        ATi = i;
                        P1 = PPt[i];
                        P2 = PPt[i];
                    }
                }
            }
        }
        if(j == -1){
            CPU = CPU+1;
            continue;
        }
        else{
            waittingTime[ATi] = CPU - ATt[ATi];
            CPU = CPU + PT[ATi];
            turnaroundTime[ATi] = CPU - ATt[ATi];
            ATt[ATi] = LAT +10;
            j = -1;
            PPt[ATi] = MAX_P + 1;
            ATi = 0;        //Pointing to Arrival Time indix
            P1 = MAX_P+1;     //Pointing to 1st piriorty Value
            P2 = MAX_P+1;     //Pointing to 2nd piriorty Value
            NoP = NoP - 1;

        }
    }

    printf("\nPN\tPT\tPP\tAT\tWT\tTT\n\n");
    for(i = 0; i < pn; i++){
       printf("P%d\t%d\t%d\t%d\t%d\t%d\n",i+1,PT[i],PP[i],AT[i],waittingTime[i],turnaroundTime[i]);
    }
    int AvgWT = 0;
    int AVGTaT = 0;
    for(i = 0; i < pn; i++){
        AvgWT = waittingTime[i] + AvgWT;
        AVGTaT = turnaroundTime[i] + AVGTaT;
    }
   printf("AvgWaittingTime = %d\nAvgTurnaroundTime = %d\n",AvgWT/pn,AVGTaT/pn);
}