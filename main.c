#include <avr/io.h>
#include <util/delay.h>
#include "tm1637.c"
#define BUZ PB0 // PB0 as a LED pin
#define LEFT PA1
#define LEFT_READ !(PINA & (1 << PINA1))
#define CENTER PD2
#define CENTER_READ !(PIND & (1 << PIND2))
#define RIGHT PA0
#define RIGHT_READ !(PINA & (1 << PINA0))
#define LED PD1
#define LED_0FF PORTD &= ~(1 << LED);
#define LED_ON PORTD |= (1 << LED);
int STD_TIME = 57;
int32_t timer_time;
uint8_t led_on = 0;
void buz(uint16_t del)
{
        uint16_t i;
        for (i = 0; i < del * 100 / 25; i++)
        {
                PORTB ^= _BV(BUZ);
                _delay_us(250);
        }
        PORTB &= ~(1 << BUZ);
}

void buz_cycl(uint8_t n)
{
        uint8_t i1;
        for (i1 = 0; i1 < n; i1++)
        {
                buz(75);
                _delay_ms(100);
        }
        PORTB &= ~(1 << BUZ);
}
void init(void)
{
        timer_time = STD_TIME * 100;
        DDRB |= (1 << BUZ);
        DDRD |= (1 << LED);
        LED_0FF
        DDRD &= ~(1 << CENTER);
        PORTD |= (1 << CENTER);
        DDRA &= ~(1 << LEFT);
        PORTA |= (1 << LEFT);
        DDRA &= ~(1 << RIGHT);
        PORTA |= (1 << RIGHT);
        TM1637_init(1, 5);
        TM1637_display_digit(0, 0);
        TM1637_display_digit(1, 0);
        TM1637_display_digit(2, STD_TIME / 10);
        TM1637_display_digit(3, STD_TIME % 10);
}
void _delay_s(uint8_t seconds)
{
        uint8_t i;
        for (i = 0; i < seconds; i++)
        {
                _delay_ms(1000);
        }
}
void TM1637_update()
{
        TM1637_display_digit(2, timer_time / 1000);
        TM1637_display_digit(3, (timer_time / 100) % 10);
}
int main(void)
{
        init();
        buz_cycl(3);
        while (1)
        {
                if (led_on == 0)
                {

                        if (LEFT_READ)
                        {
                                _delay_ms(5);
                                if (LEFT_READ)
                                {
                                        if (STD_TIME > 0)
                                                STD_TIME--;
                                        timer_time = STD_TIME * 100;
                                        TM1637_update();
                                        _delay_ms(100);
                                }
                        }
                        if (RIGHT_READ)
                        {
                                _delay_ms(5);
                                if (RIGHT_READ)
                                {
                                        if (STD_TIME <= 99)
                                                STD_TIME++;
                                        timer_time = STD_TIME * 100;
                                        TM1637_update();
                                        _delay_ms(100);
                                }
                        }
                        if (CENTER_READ)
                        {
                                _delay_ms(5);
                                if (CENTER_READ)
                                {
                                        if (led_on == 0)
                                        {
                                                buz(300);
                                                led_on = 1;
                                                LED_ON
                                        }
                                }
                        }
                }
                if ((CENTER_READ | LEFT_READ | RIGHT_READ) & (led_on == 1))
                {
                        LED_0FF
                        led_on = 0;
                        timer_time = STD_TIME * 100;
                        TM1637_update();
                        buz(300);
                        buz_cycl(5);
                }
                if (led_on == 1)
                {
                        _delay_ms(10);
                        timer_time--;
                        if (timer_time % 100 == 0)
                        {
                                TM1637_update();
                        }
                        if (timer_time < 0)
                        {
                                LED_0FF
                                led_on = 0;
                                buz_cycl(20);
                                timer_time = STD_TIME * 100;
                                TM1637_update();
                        }
                }
        }
}
