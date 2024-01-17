#ifndef __BUTTON_H__
#define __BUTTON_H__

/* Dependencies */
#include "..\IO\IO.h"
#include "..\Time\Time.h"

/* Macros */
#define DEFAULT_BUTTON_DEBOUNCE_TIME (uint32_t)100

class Button
{
    public:
        Button(volatile uint8_t* ddr, volatile uint8_t* dir, uint8_t bit);
        ~Button();
        void    begin    (const uint8_t pullType);
        void    run      (void);
        uint8_t isPressed(void);
        void    end      (void);
    private:
        volatile uint8_t* ddr;
        volatile uint8_t* dir;
        uint8_t bit;
        uint8_t beginFunctionCalled;
        uint8_t pullType;
        uint8_t buttonState;
        uint8_t previousButtonState;
        uint32_t previousTime;
};

#endif