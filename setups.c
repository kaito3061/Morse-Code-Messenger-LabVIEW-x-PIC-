void setups(void){
   setup_adc_ports(AN0_AN1_AN3);
   setup_adc(ADC_CLOCK_DIV_16);
   setup_spi(FALSE);
   setup_timer_0(RTCC_INTERNAL|RTCC_DIV_2);
   setup_timer_1(T1_DISABLED);
   setup_oscillator(OSC_8MHZ);
   return;
}