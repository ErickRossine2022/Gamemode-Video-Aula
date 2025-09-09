
            // Enum
enum E_ANTICHEAT {
    E_ANTICHEAT_NOTIFY = 1,
    E_ANTICHEAT_KICK = 2,
    E_ANTICHEAT_BAN = 3
};

            // Forward
forward OnBirdEYE(playerid, E_ANTICHEAT:type, const detected[], const extended_detected[]);



/*

                    ooooooooo.   ooooooooo.     .oooooo.   ooooooooooooo oooooooooooo   .oooooo.   ooooooooooooo oooooooooooo oooooooooo.   
                    `888   `Y88. `888   `Y88.  d8P'  `Y8b  8'   888   `8 `888'     `8  d8P'  `Y8b  8'   888   `8 `888'     `8 `888'   `Y8b  
                    888   .d88'  888   .d88' 888      888      888       888         888               888       888          888      888 
                    888ooo88P'   888ooo88P'  888      888      888       888oooo8    888               888       888oooo8     888      888 
                    888          888`88b.    888      888      888       888    "    888               888       888    "     888      888 
                    888          888  `88b.  `88b    d88'      888       888       o `88b    ooo       888       888       o  888     d88' 
                    o888o        o888o  o888o  `Y8bood8P'      o888o     o888ooooood8  `Y8bood8P'      o888o     o888ooooood8 o888bood8P'   

*/

stock alsGetPlayerMoney(playerid) {
    return CallRemoteFunction("OnBirdEYE_RemoteGetMoney", "i", playerid);
}

stock alsGetPlayerScore(playerid) {
    return CallRemoteFunction("OnBirdEYE_RemoteGetScore", "i", playerid);
}



/*

                    ooo        ooooo       .o.         .oooooo.   ooooooooo.     .oooooo.    .oooooo..o 
                    `88.       .888'      .888.       d8P'  `Y8b  `888   `Y88.  d8P'  `Y8b  d8P'    `Y8 
                    888b     d'888      .8"888.     888           888   .d88' 888      888 Y88bo.      
                    8 Y88. .P  888     .8' `888.    888           888ooo88P'  888      888  `"Y8888o.  
                    8  `888'   888    .88ooo8888.   888           888`88b.    888      888      `"Y88b 
                    8    Y     888   .8'     `888.  `88b    ooo   888  `88b.  `88b    d88' oo     .d8P 
                    o8o        o888o o88o     o8888o  `Y8bood8P'  o888o  o888o  `Y8bood8P'  8""88888P'  

*/

#if defined _ALS_GetPlayerMoney
    #undef GetPlayerMoney
#else
    #define _ALS_GetPlayerMoney
#endif
 
#define GetPlayerMoney alsGetPlayerMoney

#if defined _ALS_GetPlayerScore
    #undef GetPlayerScore
#else
    #define _ALS_GetPlayerScore
#endif
 
#define GetPlayerScore alsGetPlayerScore