/**
 * @file OneButton.cpp
 *
 * @brief Library for detecting button clicks, doubleclicks and long press
 * pattern on a single button.
 *
 * @author Matthias Hertel, https://www.mathertel.de
 * @Copyright Copyright (c) by Matthias Hertel, https://www.mathertel.de.
 *
 * This work is licensed under a BSD style license. See
 * http://www.mathertel.de/License.aspx
 *
 * More information on: https://www.mathertel.de/Arduino/OneButtonLibrary.aspx
 *
 * Changelog: see OneButton.h
 */

#include "OneButton.h"

// ----- Initialization and Default Values -----

/**
 * @brief Construct a new OneButton object but not (yet) initialize the IO pin.
 */
OneButton::OneButton()
{
  _pin = -1;
  // further initialization has moved to OneButton.h
}

OneButton::OneButton(int pin, int activeLow, bool pullupActive)
{
  // OneButton();
  _pin = pin;

  if (activeLow)
  {
    // the button connects the input pin to GND when pressed.
    _buttonPressed = LOW;
  }
  else
  {
    // the button connects the input pin to VCC when pressed.
    _buttonPressed = HIGH;
  } // if

  if (pullupActive)
  {
    // use the given pin as input and activate internal PULLUP resistor.
    pinMode(pin, INPUT_PULLUP);
  }
  else
  {
    // use the given pin as input
    pinMode(pin, INPUT);
  } // if
} // OneButton

void OneButton::handleClick(void) {}
void OneButton::handleDoubleClick(void) {}
void OneButton::handleDuringLongPress(void) {}
void OneButton::handleLongPressStart(void) {}
void OneButton::handleLongPressStop(void) {}
void OneButton::handlePress(void) {}

// explicitly set the number of millisec that have to pass by before a click is
// assumed as safe.
void OneButton::setDebounceTicks(int ticks)
{
  _debounceTicks = ticks;
} // setDebounceTicks

// explicitly set the number of millisec that have to pass by before a click is
// detected.
void OneButton::setClickTicks(int ticks)
{
  _clickTicks = ticks;
} // setClickTicks

// explicitly set the number of millisec that have to pass by before a long
// button press is detected.
void OneButton::setPressTicks(int ticks)
{
  _pressTicks = ticks;
} // setPressTicks

// function to get the current long pressed state
bool OneButton::isLongPressed()
{
  return _isLongPressed;
}

int OneButton::getPressedTicks()
{
  return _stopTime - _startTime;
}

void OneButton::reset(void)
{
  _state = 0; // restart.
  _startTime = 0;
  _stopTime = 0;
  _isLongPressed = false;
}

int OneButton::getPin(void)
{
  return _pin;
}

/**
 * @brief Check input of the configured pin and then advance the finite state
 * machine (FSM).
 */
void OneButton::tick(void)
{
  if (_pin >= 0)
  {
    tick(digitalRead(_pin) == _buttonPressed);
  }
}

/**
 * @brief Advance the finite state machine (FSM) using the given level.
 */
void OneButton::tick(bool activeLevel)
{
  unsigned long now = millis(); // current (relative) time in msecs.

  // Implementation of the state machine

  if (_state == 0)
  { // waiting for menu pin being pressed.
    if (activeLevel)
    {
      _state = 1;       // step to state 1
      _startTime = now; // remember starting time
    }                   // if
  }
  else if (_state == 1)
  { // waiting for menu pin being released.

    if ((!activeLevel) &&
        ((unsigned long)(now - _startTime) < _debounceTicks))
    {
      // button was released to quickly so I assume some debouncing.
      // go back to state 0 without calling a function.
      _state = 0;
    }
    else if (!activeLevel)
    {
      _state = 2;      // step to state 2
      _stopTime = now; // remember stopping time
    }
    else if ((activeLevel) &&
             ((unsigned long)(now - _startTime) > _pressTicks))
    {
      _isLongPressed = true; // Keep track of long press state
      handlePress();
      handleLongPressStart();
      handleDuringLongPress();
      _state = 6;      // step to state 6
      _stopTime = now; // remember stopping time
    }
    else
    {
      // wait. Stay in this state.
    } // if
  }
  else if (_state == 2)
  {
    // waiting for menu pin being pressed the second time or timeout.
    if ((unsigned long)(now - _startTime) > _clickTicks)
    {
      // this was only a single short click
      handleClick();

      _state = 0; // restart.
    }
    else if ((activeLevel) &&
             ((unsigned long)(now - _stopTime) > _debounceTicks))
    {
      _state = 3;       // step to state 3
      _startTime = now; // remember starting time
    }                   // if
  }
  else if (_state == 3)
  { // waiting for menu pin being released finally.
    // Stay here for at least _debounceTicks because else we might end up in
    // state 1 if the button bounces for too long.
    if ((!activeLevel) &&
        ((unsigned long)(now - _startTime) > _debounceTicks))
    {
      // this was a 2 click sequence.
      handleDoubleClick();
      _state = 0;      // restart.
      _stopTime = now; // remember stopping time
    }                  // if
  }
  else if (_state == 6)
  {
    // waiting for menu pin being release after long press.
    if (!activeLevel)
    {
      _isLongPressed = false; // Keep track of long press state
      handleLongPressStop();
      _state = 0;      // restart.
      _stopTime = now; // remember stopping time
    }
    else
    {
      // button is being long pressed
      _isLongPressed = true; // Keep track of long press state
      handleDuringLongPress();
    } // if

  } // if
} // OneButton.tick()

// end.
