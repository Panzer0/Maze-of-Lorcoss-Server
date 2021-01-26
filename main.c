#include <stdio.h>
#include <unistd.h>
#include <string.h>


enum fieldType
{
    INVALID = 0,
    SPACE = 1,
    WALL = 2,
    PLAYER = 3,
    BEAST = 4,
    BUSH = 5,
    COIN = 6,
    TREASURE = 7,
    LARGE_TREASURE = 8,
    DROPPED_TREASURE = 9,
    CAMP = 10
};

struct coordinates
{
    int x;              //Pokusić się o unsigned int?
    int y;
};

char map[MAP_HEIGHT][MAP_WIDTH] =
        {
        "###################################################",
        "#c  #       #   %%%%%       #         #ccccccc#   #",
        "# # ### ### ########### ### # ####### ### ##### t #",
        "# #   # # #           # # #   #     #     #   #   #",
        "# ### # # ###%%%##### # # ##### ############# ### #",
        "# #T#   #           # # # %%  #      c#       # # #",
        "# # ##### ### ####### # # # ### ### ### ### # # # #",
        "# #         # #       # # #     #   #   # # #   # #",
        "# # ####### ### ####### ##### ### ### ### # ### # #",
        "# #T#     #   #   #     #   #   #         # # # # #",
        "# ### ### ### ### ### ### # ### ########### # # # #",
        "# #   #       # #  c#  A  # #   # #       # #   # #",
        "# # ######%## # ### ### ### ### # # ##### # # ### #",
        "# #    %#   # #   #   #   #   #   # #     # # #   #",
        "# # # %%# ### ### ### ####### ### # ### ### # # ###",
        "# # #%% #    %  #   # #  %%%  #   #   #     # # # #",
        "# # #%  ####### # # # # ##%#### ##### ####### # # #",
        "# # #%      #   # # #   #     #   # #       %%#   #",
        "# ######### # ### ####### ####### # ##### # %%### #",
        "# #%      # #     #     #       #   #   # # %%  # #",
        "# # ##### # ####### # ### ##### ### # # ###%##### #",
        "#%%%#     #         #  %%%#%% #     # #   #%%%%%% #",
        "#c### #####################%# ####### ### #%    % #",
        "#ccc#                 %%%%%%#%%         #    %%   #",
        "###################################################"
        };
char sharedMap[VISION_RANGE][VISION_RANGE];            //The player's field of view, as the name indicates, it's shared with the client process.

enum fieldType identifyField(int x, int y)
{

    if (x < 0 || x >= MAP_WIDTH || y < 0 || y >= MAP_HEIGHT)    //No field outside the map is valid
    {
        return INVALID;
    }

    switch(map[y][x])      //Identify the field directly from the map array and return the appropriate enum value
    {
        case ' ':
            return SPACE;
        case '#':
            return WALL;
        case '1':
        case '2':
        case '3':               //Useless for the most basic version of the game
        case '4':               //Useless for the most basic version of the game
            return PLAYER;      ///What about the field type underneath the player?
        case '*':
            return BEAST;
        case '%':
            return BUSH;
        case 'c':
            return COIN;
        case 't':
            return TREASURE;
        case 'T':
            return LARGE_TREASURE;
        case 'D':
            return DROPPED_TREASURE;
        case 'A':
            return CAMP;
        default:
            return INVALID;     //Invalid symbol located on the map
    }
}

struct coordinates findCamp(void)
{
    struct coordinates location;
    for(int i = 0; i < MAP_HEIGHT; i+)  //Go row by row
    {
        if(strcspn(map[i]) != MAP_WIDTH)    //Found a camp in this row
        {
            location.x = strcspn(map[i]);
            location.y = i;
            return location;
        }
    }
    location.x = 0;
    location.y = 0;
    return location;    //This only happens if the map is invalid or I'm doing something wrong
}

void getPlayerStatistics(int playerID)
{

}

void generateStatistics(void)       ///Should I run this function every single turn, or should I just adjust the statistics on the go?
{                                   ///Half of these make more sense as global variables. Maybe make it so this function only prints stats?
    //Constant statistics, they remain unchanging for the entirety of the game's runtime
    if(FIRST_TIME)
    {
        int serverPID = getpid();
        struct coordinates campLocation = findCamp();
    }

    for(int i = 0, i<4; i++)
    {
        if(PLAYER_EXISTS)
        {

        }
    }




}

void revealSurroundings(int x, int y)       //x and y are player coordinates
{                                           ///Wouldn't it be better to get the player's ID or something along the lines of that?
    //Error handling
    enum fieldType fieldType = identifyField(x, y);
    if(fieldType == WALL || fieldType == INVALID || fieldType == BEAST)        //Invalid coordinates.
    {
        return;         ///Shouldn't I alert someone?
    }

    //Filling out the sharedMap array
    for(int i = SIGHT_RANGE * -1; i <= SIGHT_RANGE; i++)    //Iterates columns
    {
        for(int j = SIGHT_RANGE * -1; j <= SIGHT_RANGE; j++)    //Iterates rows
        {
            if(x + j < 0 || x + j >= MAP_WIDTH || y + i < 0 || y + i >= MAP_HEIGHT)         //Field outside the map
            {
                sharedMap[i][j] = NULL;                           //This field is not within the map
            }
            else        //Valid field
            {
                sharedMap[i][j] = map[y + i][x + j];        //There is no need to add an offset because i and j do not iterate from 0
            }
        }
    }

    /*      ////////////////////////////////////////////
     *      Miejsce na międzyprocesową magię
     */    /////////////////////////////////////////////
}

void refreshMap(void)
{
    ///Muszę włączyć wszystkie rzeczy z ncurses  w tej funkcji, czy zajmę się tym w mainie?
}

int main() {
    printf("Hello, World!\n");
    return 0;
}
