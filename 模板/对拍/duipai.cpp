#include <ctime>
#include <cstdio>
#include <algorithm>

using namespace std;

typedef double db;

#define re register
#define il inline

const int times=100;
const db time_limit=2.0;

int main()
{
    system("g++ maker.cpp -o maker");
    system("g++ std.cpp -o std");
    system("g++ brute.cpp -o brute");

    for(re int Case=1;Case<=times;++Case)
    {
        puts("Making data...............");
        system("./maker > data.in");
        puts("done");puts("");

        puts("Running brute.............");
        system("./brute < data.in > data.out");
        puts("done");puts("");

        re db bg=clock();
        puts("Running std...............");
        system("./std < data.in > std.out");
        re db ed=clock();
        printf("Run std in %.2lf ms\n",(ed*1000.0-bg*1000.0)/CLOCKS_PER_SEC);

        if((ed-bg)/CLOCKS_PER_SEC>time_limit)
        {
            printf("TLE in case: %d\n",Case);
            return 0;
        }
        if(system("diff -Bb std.out data.out"))
        {
            printf("WA in case: %d\n",Case);
            return 0;
        }
        printf("pase test case: %d\n",Case);
        system("sleep 0.5");
    }
    return 0;
}