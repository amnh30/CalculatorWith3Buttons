#include "STD_TYPES.h"
#include "MDIO/MDIO_Interface.h"
#include "MDIO/MDIO_Private.h"
#include "HLCD/HLCD_interface.h"
#include "HKPD_interface.h"
#include <util/delay.h>

#define C_CPU 8000000UL // Define CPU frequency for accurate delay calculations

void NumberCounter(u8 Copy_u8Num);
void SignSlector();
void Sum();
u8 ACALC_Au8Signs[4] = {'+', '-', '*', '/'};

u8 ACALC_u8Mode = 0;
u8 ACALC_u8FirstNum = 0;
u8 ACALC_u8Sign = 0;
u8 ACALC_u8SecNum = 0;

int main(void)
{
    u8 Local_u8Mode = 0;

    // Initialize the MDIO and LCD
    MDIO_IntialPins();  // Initialize all necessary pins (assuming this function sets up ports and pins)
    HLCD_VoidLcdIint(); // Initialize the LCD
    HLCD_u8WriteStr("0+0=");
    while (1)
    {

        NumberCounter(0);
        SignSlector();
        NumberCounter(2);
        Sum();
        clear();
    }
}
void NumberCounter(u8 Copy_u8Num)
{
    u8 Local_u8Counter = 0;
    u8 Local_u8PressedUp = 0;
    u8 Local_u8PressedDown = 0;
    u8 Local_u8PressedOut = 1;
    while (0 != Local_u8PressedOut)
    {
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_3, &Local_u8PressedUp);
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_4, &Local_u8PressedDown);
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_5, &Local_u8PressedOut);
        _delay_ms(200);

        if (0 == Local_u8PressedUp)
        {
            Local_u8Counter++;
            if (10 == Local_u8Counter)
            {
                Local_u8Counter = 0;
            }
            HLCD_VoidSetCurser(HLCD_LINE_1, Copy_u8Num);

            HLCD_VoidLcdWriteInt(Local_u8Counter);
            Local_u8PressedUp = 0;
        }
        else if (0 == Local_u8PressedDown)
        {
            Local_u8Counter--;
            if (-1 == Local_u8Counter)
            {
                Local_u8Counter = 9;
            }
            HLCD_VoidSetCurser(HLCD_LINE_1, Copy_u8Num);

            HLCD_VoidLcdWriteInt(Local_u8Counter);
            Local_u8PressedDown = 0;
        }
        if (0 == Copy_u8Num)
        {
            ACALC_u8FirstNum = Local_u8Counter;
        }
        else
        {
            ACALC_u8SecNum = Local_u8Counter;
        }
    }
}
void SignSlector()
{
    u8 Local_u8Counter = 0;
    u8 Local_u8PressedUp = 0;
    u8 Local_u8PressedDown = 0;
    u8 Local_u8PressedOut = 1;
    while (0 != Local_u8PressedOut)
    {
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_3, &Local_u8PressedUp);
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_4, &Local_u8PressedDown);
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_5, &Local_u8PressedOut);
        _delay_ms(200);

        if (0 == Local_u8PressedUp)
        {
            Local_u8Counter++;
            if (4 == Local_u8Counter)
            {
                Local_u8Counter = 0;
            }

            HLCD_VoidSetCurser(HLCD_LINE_1, 1);
            HLCD_VoidLcdWriteChar(ACALC_Au8Signs[Local_u8Counter]);
            Local_u8PressedUp = 0;
        }
        if (0 == Local_u8PressedDown)
        {
            Local_u8Counter--;
            if (255 == Local_u8Counter)
            {
                Local_u8Counter = 3;
            }

            HLCD_VoidSetCurser(HLCD_LINE_1, 1);
            HLCD_VoidLcdWriteChar(ACALC_Au8Signs[Local_u8Counter]);
            Local_u8PressedDown = 0;
        }
    }
    ACALC_u8Sign = Local_u8Counter;
}
void Sum()
{
    
    // HLCD_VoidSetCurser(HLCD_LINE_2, 0);
    // HLCD_VoidLcdWriteInt(ACALC_u8FirstNum);
    // HLCD_VoidLcdWriteInt(ACALC_u8Sign);
    // HLCD_VoidLcdWriteInt(ACALC_u8SecNum);
    HLCD_VoidSetCurser(HLCD_LINE_1, 4);
    switch (ACALC_u8Sign)
    {
    case 0:
        HLCD_VoidLcdWriteInt(ACALC_u8FirstNum + ACALC_u8SecNum);
        break;
    case 1:
        HLCD_VoidLcdWriteInt(ACALC_u8FirstNum - ACALC_u8SecNum);
        break;
    case 2:
        HLCD_VoidLcdWriteInt(ACALC_u8FirstNum * ACALC_u8SecNum);
        break;
    case 3 :
        if (0 == ACALC_u8SecNum)
        {
            HLCD_VoidSetCurser(HLCD_LINE_2, 0);
            HLCD_u8WriteStr("Invalid Division By Zero");
            
        }
        else
        {
            f16 Div =   ((f16)ACALC_u8FirstNum) / ((f16)ACALC_u8SecNum);
            HLCD_VoidLcdWriteFloat(Div);

        }

        break;

    default:
        break;
    }
}
void clear(){
    
    u8 Local_u8PressedOut = 1;
    while (0 != Local_u8PressedOut)
    {
        MDIO_u8GetPinValue(MDIO_PORTD, MDIO_PIN_5, &Local_u8PressedOut);
        
    }
    HLCD_VoidLcdClear();
    HLCD_u8WriteStr("0+0=");
    _delay_ms(300);
}
