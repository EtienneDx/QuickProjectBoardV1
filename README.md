# QuickProjectBoardV1

This project contains the code that goes with the quick project board project that I made, which can be found here : https://hackaday.io/project/160059

## Features

### Board relative

This library defines all pins according to their functions, so you can directly use : 

    digitalWrite(LED1, HIGH);
    
or 

    myservo.attach(SERVO);
    
Additionally, it includes the code relative to the other features.

It also includes the possibility to display a number or a letter on the 7 segment display incorporated.

To use it, here's an example code : 

    #include "QuickProjectBoardV1.h"
    
    QuickProject quickProject;
    
    void setup()
    {
      quickProject.Init();
    }
    
    void loop()
    {
      for(int i = 0; i < 10; i++)
      {
        quickProject.WriteNumber(i);
        delay(1000);
      }
      for(char c = 'a'; c < 'z'; c++)
      {
        quickProject.WriteLetter(c);
        delay(1000);
      }
    }
    
### Buttons features

Here is also another useful library, Buttons.h

This library includes a management for buttons, that include callbacks on button down or up. This library is included by default if you use QuickProjectBoardV1.h

Here are the possibilities : 

    #include "Buttons.h"
    
    Button b;
    
    void setup()
    {
      b = new Button(12);// 12 being the pin the button is connected to
      b.registerCallback(BUTTON_DOWN, &on_button_down);
      b.registerCallback(BUTTON_UP, &on_button_up);
    }
    
    void loop()
    {
      b.Update();
    }
    
    void on_button_down()
    {
      // do something
    }
    
    void on_button_up()
    {
      // do something
    }
    
When you use multiple buttons, you can also use the ButtonEvents class, to hold multiple buttons : 

    #include "Buttons.h"
    
    ButtonEvents buttons;
    
    void setup()
    {
      // with a button on the pin 10 and 12
      buttons.registerCallback(10, BUTTON_DOWN, &on_button_down);
      buttons.registerCallback(10, BUTTON_UP, &on_button_up);
      buttons.registerCallback(12, BUTTON_DOWN, &on_button_12_down);
      buttons.registerCallback(12, BUTTON_UP, &on_button_12_up);
    }
    
    void loop()
    {
      buttons.Update();
    }
    
    void on_button_down()
    {
      // do something
    }
    
    void on_button_up()
    {
      // do something
    }
    
    void on_button_12_down()
    {
      // do something
    }
    
    void on_button_12_up()
    {
      // do something
    }

You can always deactivate a button's callbacks by calling the clear function. If you have access to the button object (example 1), you can use :

    b.Clear();

If you're using the ButtonEvents object, you can do it like this : 

    #include "Buttons.h"
    
    ButtonEvents buttons;
    
    char b;
    
    void setup()
    {
      // with a button on the pin 10 and 12
      b = buttons.registerCallback(10, BUTTON_DOWN, &on_button_down);// we keep the adress of the button
      buttons.registerCallback(10, BUTTON_UP, &on_button_up);
      buttons.registerCallback(12, BUTTON_DOWN, &on_button_12_down);
      buttons.registerCallback(12, BUTTON_UP, &on_button_12_up);
    }
    
    void loop()
    {
      buttons.Update();
    }
    
    void on_button_down()
    {
      // do something
      buttons.Clear(b);// we clear 
    }
    
    void on_button_up()
    {
      // do something
    }
    
    void on_button_12_down()
    {
      // do something
    }
    
    void on_button_12_up()
    {
      // do something
    }
    
### Timer features

The final piece of code included is timer.h

This file includes the basics of pseudo asynchroneous programming. Basically, it includes a timeout and an interval class, both wrapped up in an optionnal Timer class.

.......
