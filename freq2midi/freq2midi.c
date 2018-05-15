/* Find nearest MIDI note to a given frequency in Hz. 
 * Uses the log rule: 
 *  log_a(N) = log_b(N) / log_b(a)
 *      to find the log of a value to base 'semitone_ratio'.
 *
 * Taken from The Audio Programming Book */

#include <stdio.h>
#include <math.h>

int main()
{
    double semitone_ratio;
    double fracmidi;
    double c0; /* for frequency of MIDI Note 0 */
    double c5; /* for frequency of Middle C */
    double frequency; /* ... given this frequency */
    double low_frequency;   /* we calculate the closest midi note freq on lower side */
    double high_frequency;  /* ... and the closest midi note freq on higher side */
    double difference; 
    int    midinote;     /* ... we want to find this note. */
    int    bend;
    int    low_side;    /* closest MIDI note on low side */
    int    high_side;   /* closest MIDI note on high side*/
    char*   sign;

    /* calculate required numbers */

    semitone_ratio = pow(2, 1/12.0); /* approx. 1.0594631 */
    /* find Middle C, three semitones above low A = 220 */
    c5 = 220.0 * pow(semitone_ratio, 3);
    /* MIDI Note 0 is C, 5 octaves below Middle C */
    c0 = c5 * pow(0.5, 5);

    frequency = 430.0;
    fracmidi = log(frequency / c0) / log(semitone_ratio);
    low_side = (int) floor(fracmidi);
    high_side = (int) ceil(fracmidi);

    /* Round fracmidi to the nearest whole number */
    midinote = (int) (fracmidi + 0.5);
    
    low_frequency = c0 * pow(semitone_ratio,low_side);
    high_frequency = c0 * pow(semitone_ratio,high_side);

    printf("The nearest MIDI note to the frequency %f is %d\n", frequency, midinote);
    if (low_side == midinote) 
    {
        difference = frequency - low_frequency;
        sign = "+";
    } 
    else 
    {
        difference = high_frequency - frequency;
        sign = "-";
    }
    difference = difference / (high_frequency - low_frequency);
    bend = (int) (difference * 100 + 0.5);
    printf("pitchbend = %s%d%%\n",sign, bend);

    return 0;
}
