#include <stdio.h>

// **********************************************
// Program1: Temperature calculation
// Course: CS451
// Student Name: Nick Burger
// Instructor: Dr. Cho
// Date of submission: 2/6/2023
// Program Description: Takes in filled with years and each 
// of its months average temps and outputs the year, average
// temperature for that year, the coldest month, the hottest month,
// as well as the average temperature for each month throughout the 
// years provided in the input.
// **********************************************

int main()
{
    //get input from user
    char file_name[100];
    printf("Enter the name of the file: ");
    scanf("%s", file_name);
    printf("\n"); 

    //open file from user input
    FILE* ptr = fopen(file_name, "r");

    //check for file
    if (ptr == NULL) {
        printf("no such file.");
        return 0;
    }

    //initial output
    printf("%s     %s     %s     %s","Year","Average","Coldest Month","Hottest Month" );
    printf("%s\n", " ");
    printf("%s     %s     %s     %s","====","=======","=============","=============");
    printf("%s\n", " ");

    int num, year;
    int i = 0;
    float temperature[12];
    fscanf(ptr, "%d", &num);

    // variables to store the average temperature for each month
    float avgJan = 0
        , avgFeb = 0
        , avgMar = 0
        , avgApr = 0
        , avgMay = 0
        , avgJun = 0
        , avgJul = 0
        , avgAug = 0
        , avgSep = 0
        , avgOct = 0
        , avgNov = 0
        , avgDec = 0;

    // variables to store the total temp for each month to calucalute the average
    float totJan = 0
        , totFeb = 0
        , totMar = 0
        , totApr = 0
        , totMay = 0
        , totJun = 0
        , totJul = 0
        , totAug = 0
        , totSep = 0
        , totOct = 0
        , totNov = 0
        , totDec = 0;

    // variable to hard store the average of eyars
    float numOfYears = num;
    //array of all of the months names
    char *months[] = {"Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};

    while (num > 0) {
        i = 0; 
        fscanf(ptr, "%d\n", &year);
        for (i; i < 12; i++) {
            fscanf(ptr, "%f", &temperature[i]);
        }
        num--;
        
        float total = 0; //variable to store total temps throughout the year to calculate the average
        float avg = 0; //varible to store the average temperature for the year
        float coldest = temperature[0]
        , hottest = temperature[0]; // variables to store the coldest and hottest temperature in the year
        int coldMonth = 0; //variable to store the index of the coldest temp
        int hotMonth = 0; //variable to store the index of the hottest month

        //keep a running total of the temperatures for a given month to calculate the average temp for that month
        totJan = totJan + temperature[0];
        totFeb = totFeb + temperature[1];
        totMar = totMar + temperature[2];
        totApr = totApr + temperature[3];
        totMay = totMay + temperature[4];
        totJun = totJun + temperature[5];
        totJul = totJul + temperature[6];
        totAug = totAug + temperature[7];
        totSep = totSep + temperature[8];
        totOct = totOct + temperature[9];
        totNov = totNov + temperature[10];
        totDec = totDec + temperature[11];

        i = 0;
        for (i; i < 12; i++){
            total = total + temperature[i]; //keep a running total of the temperatures for the year

            //find coldest month in the year
            if(coldest > temperature[i]){
                coldest = temperature[i];
                coldMonth = i;
            }
            //find hottest month in the year
            if(hottest < temperature[i]){
                hottest = temperature[i]; 
                hotMonth = i;  
            } 
        }

        avg = total / 12; //calculate the average temp for the year
        printf("%d     %.1f        %s (%.1f)        %s (%.1f)", year,avg,months[coldMonth],coldest,months[hotMonth],hottest); //output desired information
        printf("%s\n", " ");
    }

    //calculate the average temp for a given month
    avgJan = totJan / numOfYears;
    avgFeb = totFeb / numOfYears;
    avgMar = totMar / numOfYears;
    avgApr = totApr / numOfYears;
    avgMay = totMay / numOfYears;
    avgJun = totJun / numOfYears;
    avgJul = totJul / numOfYears;
    avgAug = totAug / numOfYears;
    avgSep = totSep / numOfYears;
    avgOct = totOct / numOfYears;
    avgNov = totNov / numOfYears;
    avgDec = totDec / numOfYears;

    //output avergae temp for the months
    printf("%s\n", " ");
    printf("%s\n", "Average Temperature:");
    printf("%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\t%s\n", "Jan", "Feb", "Mar", "Apr", "May", "Jun", "Jul", "Aug", "Sep", "Oct", "Nov", "Dec");
    printf("%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\t%.1f\n", avgJan, avgFeb, avgMar, avgApr, avgMay, avgJun, avgJul, avgAug, avgSep, avgOct, avgNov, avgDec);

    return 0;
}
