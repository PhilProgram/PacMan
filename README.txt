PacMan : Philip Pinta, January 28th 2018, C++ OOP
________________________________________________________________________________________________________________
How to play: Run program, click play( You can click the .exe file if you don't want to build it )

Instructions: Eat all BROWN cookies to finish the level. Red cookies make you faster, green cookies slower.

You can create your own levels : Just edit the board.txt as you wish - just make sure that the format 
follows the following: Number of rows, number of columns, and the board.

Example:
5
5
#####
#%*K#
# @G#
#I T#
#DDD#

Pacman symbols: @ = Default PacMan, W = Green PacMan, S = Red PacMan
Cookie symbols: * = Brown cookie, K = Power Up, I = Poison
Wall symbols  : # = Default wall, E = Green Wall, D = Purple Wall
Game symbols  : e = End of game, winner winner!

________________________________________________________________________________________________________________
Notes about code:
- All non leaves are pure abstract virtual classes.
- Ghost movement is a combination of random speed and smart ghost flag at construct
, and timer switches with random percentile loops determining direction, as well
as smart ghosts being able to exit collisions alot better.
- Double dispatch is used for all functions except for collision, where RTTI is used instead.
- Animation was done using spritesheets, and iterating through it using a animation timer(sf::clock)
Other
- The sprite which contains the texture is larger than the ghost image, so even if ghost is close it can
kill pacman because the rectangle is intersecting with pacmans rectangle.
- The cookie is eaten when it is 3 times the radius of distance to pac.
- Even though the excercise was for all cookies to be eaten, it doesn't make sense and isn't fun,
so I designed that part different and I promise it's worth it because it's way better gameplay
