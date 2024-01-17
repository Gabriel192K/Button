/* Dependencies */
#include "Button.h"

Button::Button(volatile uint8_t* ddr, volatile uint8_t* dir, uint8_t bit)
{
    this->ddr = ddr;
    this->dir = dir;
    this->bit = bit;
}

Button::~Button()
{
    this->ddr = NULL;
    this->dir = NULL;
    this->bit = 0xFF;
}

void Button::begin(const uint8_t pullType)
{
    if (this->beginFunctionCalled)
        return;
    this->beginFunctionCalled = 1;

    Time.begin();

    this->pullType = pullType;
    IO.setMode(this->ddr, this->bit, INPUT);
}

void Button::run(void)
{
    uint32_t currentTime = Time.milliseconds();

    if ((currentTime - this->previousTime) >= DEFAULT_BUTTON_DEBOUNCE_TIME)
    {  
        /* Read current state */
        this->buttonState = IO.read(this->dir, this->bit);
        this->previousTime = currentTime;
    }
}

uint8_t Button::isPressed(void)
{
    /* Used to store return value */
    uint8_t ret = 0;

    /* If state is different than previous and state is different than pull type */
    if ((this->buttonState != this->previousButtonState) && (this->buttonState != this->pullType))
        ret = 1;

    /* Copy state as the previous one */
    this->previousButtonState = this->buttonState;

    /* Return value */
    return (ret);
}

void Button::end(void)
{
    if (!this->beginFunctionCalled)
        return;
    this->beginFunctionCalled = 0;

    this->pullType = LOW;
}