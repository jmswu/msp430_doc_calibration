
   calibrate the DCO in msp430 with a watch crystal.
   A watch crystal must be connected. This will use
   TimerA in capture mode. And this function will
   reset TimerA.
 
   ref: http://www.ti.com/lit/an/slaa336a/slaa336a.pdf
 
   @param: data - one of the pre-define value above
   @param: isStable - when false, the function will
   		wait for the 32k crystal to be stablized
   		first before calibartion.
 
   Tested on:
   - msp430g2333
   - msp430g2452
 
