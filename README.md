# Minesweeper-GUI
WIP: Quick Minesweeper game to get better using all the features of SDL, and using C++ for graphics.

This simple game is an excercise that I will later build upon to create more interesting games and applications.
Because of this, I'm trying to scructure some parts of the code so as to prepare for many different game types.

So far:

• Game loop with simple fps limiter.

• Creates one or multiple Windows. Plan to have windows be resizable.

• Draws to window using STL 2.0's hardware acceleration.

• Event Manager to handle queue of events per frame, distributing events to:

• Keyboard Manager to handle keyboard inputs. 

  - Custom Keys can be bound to the players' preferences.
  - Keys have a 'held' state, and a 'triggered' state which is 
      only true on the frames that the key is pressed and released.
      
• Mouse Manager to handle mouse inputs.

  - On mouse movement, records updated cursor position.
  - Hears and distinguishes between left and right clicks.
  
Starting work on the Board and Tile classes.
