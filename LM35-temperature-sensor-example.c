#include <16f877.h>
#device ADC=10
#fuses XT,NOWDT,NOPROTECT,NOBROWNOUT,NOLVP,NOPUT,NOWRT,NODEBUG,NOCPD
#use delay (clock=400000000)
#use fast_io(a)
#define use_port_b_lcd TRUE
#include <lcd.c>

unsigned long int info;
float voltage,temperature;

void main(){
    setup_psp(PSP_DISABLED);
    setup_timer_1(T1_DISABLED);
    setup_timer_2(T2_DISABLED,0,1);
    setup_CCP1(CCP_OFF);
    setup_CCP2(CCP_OFF);

    set_tris_a(0x01);

    setup_adc(adc_clockk_div_32);
    setup_adc_ports(AN0);
    lcd_init();

    set_adc_channel(0);

    delay_us(20);

    printf(lcd_putc,"\ftemperature=");

    while(1)
    {
        info=read_adc();

        voltage=(0.00488281125*info)*1000;

        temperature=(voltage/10)+2;
        lcd_gotoxy(10,1);
        printf(lcd_putc,"%5.1f'C",temperature);

        delay_ms(100);
    }
}
