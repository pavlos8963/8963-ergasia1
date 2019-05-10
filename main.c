#include <unistd.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
#include <stdio.h>

int main(void) {
    FILE *txttimes;
    txttimes=fopen("times.txt", "w");
    FILE *txtdiff;
    txtdiff = fopen("diff.txt","w");
    FILE *txtmedian;
    txtmedian=fopen("median.txt", "w");
    FILE *txtmean;
    txtmean=fopen("mean.txt","w");
    FILE *txtmax;
    txtmax=fopen("max.txt","w");
    FILE *txtmin;
    txtmin=fopen("min.txt", "w");
    FILE *txtdeviation;
    txtdeviation=fopen("deviation.txt","w");

    float runtime=2; //Running time in seconds
    float sampletime=0.1;//Take sample in seconds
    long dt=sampletime*1000000;//Take sample in micro seconds
    long t= runtime*1000000;
    long length = runtime*sampletime*600;

    struct timeval end, start ;//For taking times
    long times[length],diff[length];
    long maxNum=0, minNum=1000000, sum=0;
    long i=0, elapsed;
    float mean, median;

    gettimeofday(&start,NULL);

    gettimeofday(&end,NULL);
    elapsed = (end.tv_sec-start.tv_sec)*1000000+end.tv_usec-start.tv_usec;

    while ((end.tv_sec-start.tv_sec) <= runtime) {//Loop untill elapsed >= t
        times[i] = elapsed;
        i++;
        fprintf(txttimes, "%lu %lu\n ", i, times[i]);
        //Difference
        diff[i - 1] = times[i] - times[i - 1];
        fprintf(txtdiff, "%lu %lu\n ", i - 1, diff[i - 1]);

        sum = sum + times[i];
        if (maxNum < times[i]) {
            maxNum = times[i];
            fprintf(txtmax, "%d \n", maxNum);
        }
        if (minNum > times[i]) {
            minNum = times[i];
            fprintf(txtmin, "%d \n", minNum);
        }


        // the following two loops sort the array x in ascending order
        int temp;
        for (int k = 0; k < i - 1; k++) {
            for (int j = i + 1; j < i; j++) {
                if (times[j] < times[k]) {
                    // swap elements
                    temp = times[k];
                    times[k] = times[j];
                    times[j] = temp;
                }
            }
        }
        if (i % 2 == 0) {
            // if there is an even number of elements, return mean of the two elements in the middle
            median = ((times[i / 2] + times[i / 2 - 1]) / 2.0);
        } else {
            // else return the element in the middle
            median = times[i / 2];
        }
        fprintf(txtmean, "%f\n ", mean);
        fprintf(txtmedian, "%f \n ", median);

        gettimeofday(&end, NULL);
        elapsed = (end.tv_sec - start.tv_sec) * 1000000 + end.tv_usec - start.tv_usec;
        printf("t: %ld\n", t);
        printf("Elapsed: %ld\n", elapsed);
        usleep(dt);
/*
        //Standar deviation
        for(int j=0;j< i;j++){
            deviation[i] += pow(times[j]-mean[i],2);
            fprintf(txtdeviation,"%f\n",deviation[i]);
        }
*/
    }

    printf("Elapsed: %ld\n", elapsed);
    fclose(txtdeviation);
    fclose(txttimes);
    fclose(txtmin);
    fclose(txtmedian);
    fclose(txtmax);
    fclose(txtdiff);
    fclose(txtmean);
    printf("done..\n");
    return 0;
}
