https://github.com/Woestijnbok/Woestijn

# Keyboard input

Aim with the mouse and shoot with right mouse click.
You can move around using WASD
Use M to mute the audio
You can skip a level by pressing F1 (if not the last level)
You can go back to the menu using BACKSPACE
You can close the application using ESC

# Controller input

You can aim using the right joystick.
Fire bullets with the right shoulder r1.
Movem is done with the DPAD

# Design choices

I tried using pimpl where possible instead of service locaters or other methods.
I also prefered using the singleton pattern, espacially with pimpl.
The two reasons why I choose to use pimpl and singleton over the service locater:
	- The singleton pattern is more straightforward no dependencies trough a central object aka locator
	- I found it clearer to understand when the instance is being created with the singleton pattern

I found the event queue the best way to handle sound requests since it decouples the request and process completly.
This is espacially handy when working on a different thread which my audio is doing.

On the other hand I used the observer pattern for some actions in the game logic.
Let's say you lost a live and you want to update the ui or you shot, I used the pattern there.
The main reason was that i wanted more direct communication when someting like that happened.
Also know when it's getting processed (at the same moment in my case).

More in general the engine uses the scene - gameobject - component system.
It's possible for multiple scenes to be active at the same time.
You can deactive, activate and destroy any of the three objects.
For instance in the game I made i deactivate the main menu and when I want to "go back to the main menu" I activate it again and destroy the other scenes.

I have a game loop with a normal update fixed update (usefull for collision detection) and a late update.
In make use of all three because in some cases one is "better" than the other.

For input I use the command design pattern since it decouples actions from input handling.
And maybe in the future I could make a system that tracks the history for ease of debuging.


P.S. The resource folder is supposed to be outside the folder of the .exe, this might look weird but it was easier to work on both the engine and the game that way for me.