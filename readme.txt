A Day in the Life of Judd

You take on the role of Inkopolis's Judd, the cat that judges Turf War matches.
You'll be presented with an overhead view of an inked arena, and your task is to decide which team covered the most turf.
It's not as simple as that, though! Deciding the exact percentages, thinking about how much turf went uninked,
figuring out if that blotch is green ink or just foliage, and even avoiding biases are all normal occurrences for
a day in the life of Judd.


===============
1) How to play
2) Tips
3) FAQ and troubleshooting
4) Compiling
5) Credits
6) Disclaimer
===============


===============
1) How to play
===============
Introduction
    The game presents you with an overhead view of a Splatoon arena, with the aftermath of a Turf War match.
    This means you get to see what parts of the stage are inked by what team, or even completely uninked.
    Your task is to decide how much turf each team got. Exactly what you have to do depends on the difficulty mode.

Game modes
    Story
        Complete a series of chapters that represent cherry-picked days of Judd's life.
        Each one tasks you with judging a specific Turf War match, with some sort of underlying story or theme.
        You must get at least a certain score in order to complete a chapter.
        Although you can replay chapters, the ink coverage is generated randomly every time, so don't rely on trial and error.
        Your highest scores get saved.
    Free play
        You're given randomly-generated inked arenas, and judge them at your heart's content, with no compromise.

Difficulties
    Beginner
        You only have to choose which team got more ink.
    Intermediate
        You have to decide what percentage of the arena each team covered.
        The percentage of unclaimed turf is automatically given.
    Expert
        Same as intermediate, but you must also decide the unclaimed turf percentage.
        Terrain that cannot be inked doesn't count for any percentage.

Playing
    At the top of the screen, you get the overhead view of the arena.
    At the bottom, you have some way of making your decision.
        On beginner difficulty, you have two buttons, one for each team. The one you choose becomes highlighted.
        On intermediate difficulty, you have a slider you can drag. The total percentage of area each team covered is also shown.
        On expert difficulty, you get the same as intermediate, plus a slider for the percentage of unclaimed area.
    After deciding, press the Okay button on the right side of the screen.
    Once you do, you're shown your given values, the real percentages, and your score.
    You get scored based on how accurately you estimated, on a scale from 0 to 100 points.


===============
2) Tips
===============
- Use the mouse wheel if you want to fine-tune your decision, when your mouse cursor is over a slider.
- Click the mouse button at any time after you've confirmed your decisions in order to skip to the final results.


===============
3) FAQ and troubleshooting
===============
Why can't I see the game window?
    Because the game window sometimes break under Windows.
    Right-click the game's window on the task bar, choose move, and press any arrow key on the keyboard. That should fix it.

I crunched the numbers on the results screen, and they're slightly off. What gives?
    Rounding errors. The error shouldn't be greater than 0.1%, so it's not very important.
    In addition, if you get 99.9% or 99 points, it's automatically turned into 100 for the sake of fairness.
    Finally, if the real scores reveal that both teams got exactly the same percentage,
    the values are slightly skewered in your favor, to avoid having an unfair tie.

Some colors of ink make it hard to see on the background. Why is that?
    Believe it or not, that's actually part of the challenge.

On intermediate difficulty, if Judd is only meant to compare the two teams,
why are the percentages based on the whole arena, and where does the uninked percentage come from?
    http://tvtropes.org/pmwiki/pmwiki.php/Main/GameplayAndStorySegregation
    For the sake of gameplay and scoring, it makes more sense to use the percentages compared to the entire arena.
    For the sake of convenience, the uninked percentage is also shown.
    Unfortunately, this doesn't make much sense for the plot.
    I've got no better way to do this. If you have any ideas, send them my way!

On X arena, what is Y meant to be?
    ...Use your imagination! Sorry, but I'm not an artist. Sometimes I just drew random objects on the arenas.

Why doesn't the ink coverage look like the aftermath of a real Splatoon match?
    The match simulation works on the basis of "good enough". It's impossible to simulate a real battle,
    with a lot of collisions against walls, ink sprayed on weird nooks and crannies, Charger shots,
    Kraken trails, weird movement patterns only humans can do, crafty movements and flanks using ramps,
    etc., etc. Even getting a very close approximation would make the loading times massive. In an effort
    to make the game load relatively quickly and also give convincing matches, this is as best as you can get.
    (You can get smoother coverages by editing a battle's data in the source code, increasing the number
    of simulation iterations, and decreasing the Inkling speed, aggressiveness, and ink radii. Try factors of 10.)
    

===============
4) Compiling
===============
(You likely don't need to do this to play under Windows.)
First, download the source, of course.
Under Linux...
    Install Allegro 5 on your system using the instructions here https://wiki.allegro.cc/index.php?title=Getting_Started
    On a terminal, go to the source's folder and write "make".
    If you get linker errors, edit the "makefile" file and follow the instructions. Write "make clean" and then "make" once more.
Under Windows...
    Are you SURE you want to compile it?
    Okay... Install Allegro 5 (5.0.10) by following the instructions here https://wiki.allegro.cc/index.php?title=Getting_Started
    Open the .sln with Visual Studio.
    Compile. Good luck.


===============
5) Credits
===============
Pretty much everything:
    André 'Espyo' Silva
Support and beta-testing:
    My friends at Pikipedia and Pikmin Fanon
    My friends at Brawl Snapshots
Special thanks:
    Stackoverflow and other such websites
    Inkipedia


===============
6) Disclaimer
===============
A Day in the Life of Judd is NOT affiliated with Nintendo® and should NOT be sold.
It is a NON-PROFIT project created by a fan of the Splatoon® franchise, and does not intend to infringe on the copyrights or registered trademarks of Nintendo®.
Splatoon® is a trademark of Nintendo®. The copyrights of all associated characters, names, terms, art, music, and assets belong to Nintendo®.
