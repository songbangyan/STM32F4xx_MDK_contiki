#include "bsp.h" 
#include <stdint.h>  
#include <clock.h>  
#include <sys/process.h>  
#include <sys/procinit.h>  
#include <etimer.h>  
#include <sys/autostart.h>  
#include "contiki.h"

static u8 compile_time[]=__DATE__ __TIME__;
extern volatile unsigned int systick;

unsigned int idle_count = 0;
//事件的声明 
//static process_event_t event_ledoff;
//static process_event_t event_ledon;




PROCESS(blink_process, "Blink");
AUTOSTART_PROCESSES(&blink_process);

PROCESS_THREAD(blink_process, ev, data)
{  
  PROCESS_BEGIN();
  while(1) 
  {
    static struct etimer et;
		printf("\r\n 1time %d",systick);
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_On(LED0);
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_On(LED1);
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_On(LED2);
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_On(LED3);
		
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_Off(LED0); 
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_Off(LED1); 
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_Off(LED2); 
    etimer_set(&et, CLOCK_SECOND);
    PROCESS_WAIT_EVENT_UNTIL(etimer_expired(&et));    
    LED_Off(LED3); 
		printf("\r\n 2time %d",systick);

  }
   PROCESS_END();
}


int main()
{
  Bsp_Init();
  printf("\r\nInitialising\r\n");
  printf("\r\nCompile time is:%s",compile_time);
  clock_init();
  process_init();
  process_start(&etimer_process, NULL);
  autostart_start(autostart_processes);
  printf("Processes running\r\n");
  while(1) {
    do 
    {
    } 
    while(process_run() > 0);
    idle_count++;
    /* Idle! */
    /* Stop processor clock */
    /* asm("wfi"::); */ 
  }
//  return 0;
}







