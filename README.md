# Arduino-Pong-Game

Bring retro gaming to life with this Arduino-based recreation of the iconic 1972 Pong game by Allan Alcorn. With simply two paddles and one ball this game brings endless amounts of fun. This project draws inspiration from and credits eholk's Arduino-Pong. 

# Picture

![IMG_5264](https://github.com/user-attachments/assets/c0a7cc1e-ae65-4cf6-926b-60b4e4182943)

# Video



# Materials

* ELEGOO Uno R3 (Arduino Uno R3 clone)
* OLED I2C 128x64 Screen (To display the game)
* Passive Buzzer (To play the notes 🎵)
* 4 Buttons for the user's input
* Breadboard and a wires

# What I added

While my code is very similar to eholk's version, I added several new features which allow for a more immersive game experience. First off, I made the code compatible for the OLED screen I am using (OLED I2C 128x64). Second, I added a new "dimension" to the paddles each player controls. Initially, when the paddle bounced off a player's paddle, the ball would always go up in the opposite direction. I made it so that if the ball hits the bottom hald of the paddle the ball would bounce downwards and if it hit the upper hald it'd bounce upwards. This change, as small as it may seem, adds more diversity to the game's possibilities in terms of outcomes. Finally, I added a passive buzzer to add sounds for whenever a the ball hit the paddles, when someoned scored, and when someone won. 

# Construction

# Credits
https://github.com/eholk/Arduino-Pong

