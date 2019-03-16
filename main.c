#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

//set the output log file name
#define filename "pi.log"

//Write the number of point samples as well as the current approximation of pi into a logfile
int writeToFile (FILE *fp, double pi, int i) {
	fprintf(fp, "%d,%f\n", i, pi);
}

//Ask the user to input the desired amount of samples (10 to the power of the input)
int inputSamples () {
	int samples = 0;
	printf("Please enter the desired number of samples: 10e");
	scanf("%d", &samples);
	return(samples);
}
//Ask the user to input the desired save interval (10 to the power of the input, must be lower than 1/10th of the number of samples)
int inputSaveInterval (int samples) {
	int saveInterval = samples;
	while(saveInterval > samples-1) {
		printf("Please enter the desired save interval (<= samples/10): 10e");
		scanf("%d", &saveInterval);
		if (saveInterval > samples-1) {
			printf("Save interval too large!\n");
		}
	}
	return(saveInterval);
}


int main() {
	//store the start-time in clocks
	double cpuTimeUsed = clock();

	//open the log file as "append" 
	FILE *fp;
	fp = fopen(filename, "a");
	//randomise the seed for the random number generator
	srand48(time(NULL));

	//Number of points inside the quarter circle
	int insideCircle = 0;
	//Number of sample points to calculate (10 to the power of the variable)
	int samples = inputSamples();
	//Number of sample points to calculate in between saving log data to the file (10 to the power of the variable)
	int saveInterval = inputSaveInterval(samples);

	double pi;
	
	//The outer loop runs for the desired amount of samples divided by the number of samples in between save points
	for (int i=0; i<(pow(10, samples-saveInterval)); i++) {
		//The inner loop runs for the desired amount of samples in between save points
		for (int j=0; j<(pow(10, saveInterval)); j++) {
			//Generate a pair of random numbers (x,y) with x=[0,1], y=[0,1]
			double randomNumberA = drand48();
			double randomNumberB = drand48();
			//Check if the point pair (x,y) is within a quarter circle around (0,0), if so increment insideCircle
			double radius = randomNumberA*randomNumberA + randomNumberB*randomNumberB;
			if(radius <= 1){
				insideCircle++;
			}
		}
		//Calculate the current value of pi, by dividing the number of points inside the circle by the total
		//amount of points generated so far. Multiply by 4 because we only use a quarter circle.
		pi = (double)4*insideCircle/((i+1)*(pow(10, saveInterval)));
		//Write the results to the log file
		writeToFile(fp, pi, ((i+1)*pow(10, saveInterval)));
	}
	//Close the file
	fclose(fp);
	//Take the difference between the start and end time (in clocks), divide by clocks per second to get a result in seconds
	cpuTimeUsed = (double)(clock() - cpuTimeUsed)/CLOCKS_PER_SEC;
	//Print the amount of samples taken, final result and calculation time in seconds to the command line
	printf("Samples used: 10e%d\nResult for pi: %f\nThis calculation took %f s\n", samples, pi, cpuTimeUsed);
	return 0;
}
