# Arduino-Pong-Game 🏓

Bring retro gaming to life with this Arduino-based recreation of the iconic 1972 Pong game by Allan Alcorn. With simply two paddles and one ball this game brings endless amounts of fun. This project draws inspiration from and credits eholk's Arduino-Pong. 

# Picture

![IMG_5264](https://github.com/user-attachments/assets/c0a7cc1e-ae65-4cf6-926b-60b4e4182943)

# Video

https://github.com/user-attachments/assets/538eef77-33ab-4178-bcd7-608b6d97a748

# Materials

* ELEGOO Uno R3 (Arduino Uno R3 clone)
* OLED I2C 128x64 Screen (To display the game)
* Passive Buzzer (To play the notes 🎵)
* 4 Buttons for the user's input
* Breadboard and a wires

# What I added

While my code closely resembles eholk's original version, I’ve added several new features to enhance the game experience. First, I made the code compatible with the OLED I2C 128x64 screen I’m using. Second, I introduced a new "dimension" to the paddle mechanics. Originally, the ball would always bounce upward in the opposite direction after hitting a paddle. I modified this behavior so that if the ball hits the bottom half of the paddle, it bounces downward, and if it hits the upper half, it bounces upward. This seemingly small change significantly increases the variety of possible outcomes in the game. Finally, I incorporated a passive buzzer to play sounds whenever the ball hits a paddle, when a point is scored, and when a player wins.

# Construction

<img width="301" alt="image" src="https://github.com/user-attachments/assets/86c1afd4-3b5d-48e7-86b4-b089932233a0" />


# Credits
https://github.com/eholk/Arduino-Pong

