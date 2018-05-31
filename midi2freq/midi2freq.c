/* Calculate frequency of a MIDI note number. Taken from The Audio Programming Book */
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int main()
{
    double semitone_ratio;
    double c0; /* for frequency of MIDI Note 0 */
    double c5; /* for frequency of Middle C */
    double frequency; /* ... which we want to find, */
    double string_length;
    double midifloat;   /* Used to check input type */
    int    midinote;     /* ... given this note. */
    int    i;
    int    truncated;
    char   message[256];
    char   result;

    /* calculate required numbers */

    semitone_ratio = pow(2.0, 1.0/12.0); /* approx. 1.0594631 */
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3.0);
    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5.0);
    
    /* Get user input for MIDI note to convert */
    printf("Enter MIDI note (0 - 127): ");
    result = scanf("%s", message);
    if (&result == NULL) {
        printf("There was an error reading the input.\n");
        return 1;
    }
    if (message[0] == '\0') {
        printf("Have a nice day!\n");
        return 1;
    }
    midifloat = atof(message);
    truncated = (int)midifloat;
    if (truncated != midifloat) {
        printf("Float detected. Please enter an integer value for MIDI note.\n");
        return 1;
    }
    midinote = truncated;
    if (midinote < 0) {
        printf("Sorry - %s is a bad MIDI note number\n", message);
        return 1;
    }
    if (midinote > 127) {
        printf("Sorry - %s is beyond the MIDI range!\n", message);
        return 1;
    }
    /* calculate a frequency for a given MIDI Note Number */
    frequency = c0 * pow(semitone_ratio, midinote);
    
    string_length = 660.0;
    printf("MIDI Note %d has frequency %f\n", midinote, frequency);
    /*
    printf("Sounding length of string sounding C4 is %f cm\n", string_length);
    for (i=1;i<13;i=i+1){
       string_length = string_length / pow(semitone_ratio, 1.0);
       printf("Sounding length of string for the next semitone up is %f cm\n", 
               string_length);
    } */
    return 0;
}
