#include <unistd.h>
#include <stdint.h>			       
#include <stdio.h>
#include <stdlib.h>

size_t num_of_bytes = 6;

//funkcija koja vraca stanje tastera na poziciji pos
char buttonState(char pos);

int main ()
{
  FILE *fp, *fb;
  float percentage = 0.6;
  float step = 0.05;
  long int period = 20000L;
  char sd = 1;
  char* str;
  int sval1,sval2;


  while (1)
    {
      // Upali diode
      fp = fopen ("/dev/led", "w");
      if(fp == NULL)
	{
	  printf("Problem pri otvaranju /dev/led\n");
	  return -1;
	}
      fputs ("0x0f\n", fp);

      if( fclose (fp))
	{
	  printf("Problem pri zatvaranju /dev/led\n");
	  return -1;
	}
      usleep (percentage*period);
      // Ugasi diode
      fp = fopen ("/dev/led", "w");
      if(fp == NULL)
	{
	  printf("Problem pri otvaranju /dev/led\n");
	  return -1;
	}
      fputs ("0x00\n", fp);
      if( fclose (fp))
	{
	  printf("Problem pri zatvaranju /dev/led\n");
	  return -1;
	}
      usleep ((1-percentage)*period);

      // ako je pritisnut taster 0 umanji pwm
      if (buttonState(0))
	{
	  if(sd == 1)
	    {
	      sd = 0;

	      //Umanji pwm
	      if(percentage > 0)
		percentage -= step;
	      else
		{
		  printf("Step:%f\n", step);
		  printf("Can't go lower than 0% \n");
		}
	    }
	}
      else if (buttonState(1))	
	{
	if(sd == 1)
	    {
	      sd = 0;

	      //Povecaj pwm
	      if(percentage < 1)
		percentage += step;
	      else{
		printf("Step: %f\n", step);
		printf("Can't go higher than 100% \n");
	      }
	    }
	}
      else
	sd = 1;

      fp = fopen("/dev/switch", "r");
      if(fp == NULL)
	{
	  puts("Problem pri otvaranju /dev/switch");
	  return -1;
	}

      str = (char*) malloc(num_of_bytes);
      getline(&str, &num_of_bytes,fp);

      if(fclose(fp))
	{
	  puts("Problem pri zatvaranju /dev/switch");
	  return -1;
	}

      sval1= str[2] - 48;
      sval2= str[3] - 48;
      free(str);
      
      if(sval1)
	{
	  if(sval2)
	    {
	      step = 0.2;
	    }
	  else
	    {
	      step = 0.15;
	    }
	}
      else
	if(sval2)
	  {
	    step = 0.1;
	  }
	else
	  {
	    step = 0.05;
	  }
      
    }
  return 0;
  
}

      char buttonState(char pos)
      {
	char* str;
	FILE* fp = fopen ("/dev/button", "r");
	if(fp==NULL)
	  {
	    puts ("Problem pri otvaranju /dev/button");
	    return -1;
	  }
	str = (char *) malloc (num_of_bytes+1);
	getline (&str, &num_of_bytes, fp);

	if( fclose (fp))
	  {
	    puts("Problem pri zatvaranju /dev/button");
	    return -1;
	  }
	//Vrati vrijednost tastera na poziciji pos
	char state = str[pos+2] - 48;
	free(str);
	return state;

      }
