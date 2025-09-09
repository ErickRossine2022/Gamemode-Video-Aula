/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

// (C) Copyright 2022 by zHypezinXzL (R)

// @include  : notifications
// @country  : Brasil
// @author   : zHypezinXzL
// @github   : https://github.com/zHypezinXzL

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

#if !defined MAX_NOTIFICATIONS_USING
	#define MAX_NOTIFICATIONS_USING \
		(3)
#endif

#if !defined MAX_NOTIFICATIONS_TEXT
	#define MAX_NOTIFICATIONS_TEXT \
		(35)
#endif

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

enum pNotificationEnum
{
    bool:NotificationUsing,
    NotificationTime,
    NotificationType,
    NotificationText[MAX_NOTIFICATIONS_TEXT]
}

enum
{
    NOTIFICATION_TYPE_SUCESS = (1), 
    NOTIFICATION_TYPE_WARNING = (2),
    NOTIFICATION_TYPE_ERROR = (3)
}

new PlayerText:NotificationsPlayerTD[MAX_PLAYERS][9],
    PlayerBar:NotificationsBarTD[MAX_PLAYERS][3],
    pNotification[MAX_PLAYERS][MAX_NOTIFICATIONS_USING][pNotificationEnum];

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

ConvertForTDNotification(const text[])
{
    NotificationStr[MAX_NOTIFICATIONS_TEXT] = text;
    for(new l; l < strlen(NotificationStr); l++)
        if(NotificationStr[l] == ' ')
            NotificationStr[l] = '_';
    return NotificationStr;
}

GetValidSlotNotification(playerid)
{
    new Using = 0;
    for(new l; l < MAX_NOTIFICATIONS_USING; l++)
        if(pNotification[playerid][l][NotificationUsing])
            Using += 1;
    if(Using >= 3)
        return UpNotification(playerid);
    else
        return (Using + 1);
}

GetTDColorNotification(notificationtype)
{
    if(notificationtype == NOTIFICATION_TYPE_SUCESS)
        return (0x00FFFFAA);
    else if(notificationtype == NOTIFICATION_TYPE_ERROR)
        return (0xFFFF00AA);
    else
        return (0x0000FFAA);
}

TimeBarNotification (playerid, notificationid, value, PlayerBar: bar)
{
    if(value >= 100)
        value = 99;
    else
        value -= 1;
    if(value < 1)
        return RemoveNotification(playerid, notificationid);
    else
    {
        SetPlayerProgressBarValue(playerid, bar, float(value));
        return SetTimerEx("TimeBarNotification", 300, false, "iiii", playerid, notificationid, value, bar)
    }
}

UpNotification(playerid)
{
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][0], GetTDColorNotification(pNotification[playerid][2][NotificationType]));
    PlayerTextDrawSetString(playerid, NotificationsPlayerTD[playerid][2], ConvertForTDNotification(pNotification[playerid][2][NotificationText]));
    for(new l; l < 3; l++)
    TextDrawShowForPlayer(playerid, NotificationsPlayerTD[playerid][l]);
    pNotification[playerid][1][NotificationType] = pNotification[playerid][2][NotificationType];
    pNotification[playerid][1][NotificationText] = ConvertForTDNotification(pNotification[playerid][2][NotificationText]);
    pNotification[playerid][1][NotificationTime] = pNotification[playerid][2][NotificationTime];
    return SetTimerEx("TimeBarNotification", 300, false, "iiii", playerid, 1, pNotification[playerid][1][NotificationTime], NotificationsBarTD[playerid][1]);

    //
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][3], GetTDColorNotification(pNotification[playerid][3][NotificationType]));
    PlayerTextDrawSetString(playerid, NotificationsPlayerTD[playerid][5], ConvertForTDNotification(pNotification[playerid][3][NotificationText]));
    for(new l=4; l < 5; l++)
        TextDrawShowForPlayer(playerid, NotificationsPlayerTD[playerid][l]);
    pNotification[playerid][1][NotificationType] = pNotification[playerid][3][NotificationType];
    pNotification[playerid][1][NotificationText] = ConvertForTDNotification(pNotification[playerid][3][NotificationText]);
    pNotification[playerid][1][NotificationTime] = pNotification[playerid][3][NotificationTime];
    return SetTimerEx("TimeBarNotification", 300, false, "iiii", playerid, 1, pNotification[playerid][1][NotificationTime], NotificationsBarTD[playerid][1]);

    return (3);
}

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock ClearPlayerVarsNotifications(playerid)
{
    for(new pNotificationEnum:l; l < pNotificationEnum; l++)
        for(new i; i < MAX_NOTIFICATIONS_USING; i++)
            pNotification[playerid][i][l] = (-1);
    return true;
}

stock SendClientNotification (playerid, const notification [], notificationtype) {
    if(GetValidSlotNotification(playerid) == 1) {
        PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][0], GetTDColorNotification(notificationtype));
        PlayerTextDrawSetString(playerid, NotificationsPlayerTD[playerid][2], ConvertForTDNotification(notification));
        for(new l; l < 4; l++)
            TextDrawShowForPlayer(playerid, NotificationsPlayerTD[playerid][l]);
        pNotification[playerid][1][NotificationUsing] = true;
        pNotification[playerid][1][NotificationType] = notificationtype;
        pNotification[playerid][1][NotificationText] = ConvertForTDNotification(notification);
        pNotification[playerid][1][NotificationTime] = 100;
        return SetTimerEx("TimeBarNotification", 300, false, "iiii", playerid, 1, pNotification[playerid][1][NotificationTime], NotificationsBarTD[playerid][1]);
    }
    if(GetValidSlotNotification(playerid) == 2) {
        PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][3], GetTDColorNotification(notificationtype));
        PlayerTextDrawSetString(playerid, NotificationsPlayerTD[playerid][5], ConvertForTDNotification(notification));
    }
    else {
        PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][6], GetTDColorNotification(notificationtype));
        PlayerTextDrawSetString(playerid, NotificationsPlayerTD[playerid][8], ConvertForTDNotification(notification));
    }
    return 0;
}

/*///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

native SendClientNotification (playerid, const notification [], notificationtype);

*////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

stock LoadNotificatios(playerid)
{
    NotificationsPlayerTD[playerid][0] = CreatePlayerTextDraw(playerid, 11.000000, 236.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][0], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][0], 0.600000, 2.250000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][0], 289.500000, 1.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][0], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][0], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][0], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][0], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][0], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][0], 16711935);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][0], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][0], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][0], 0);

    NotificationsPlayerTD[playerid][1] = CreatePlayerTextDraw(playerid, 71.000000, 236.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][1], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][1], 0.512498, 1.600000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][1], 289.500000, 109.500000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][1], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][1], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][1], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][1], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][1], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][1], 255);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][1], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][1], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][1], 0);

    NotificationsPlayerTD[playerid][2] = CreatePlayerTextDraw(playerid, 16.000000, 236.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][2], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][2], 0.179166, 1.399999);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][2], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][2], 0);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][2], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][2], 1);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][2], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][2], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][2], 50);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][2], 0);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][2], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][2], 0);

    NotificationsPlayerTD[playerid][3] = CreatePlayerTextDraw(playerid, 11.000000, 268.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][3], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][3], 0.600000, 2.250000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][3], 289.500000, 1.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][3], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][3], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][3], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][3], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][3], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][3], -65281);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][3], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][3], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][3], 0);

    NotificationsPlayerTD[playerid][4] = CreatePlayerTextDraw(playerid, 71.000000, 268.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][4], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][4], 0.512498, 1.600000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][4], 289.500000, 109.500000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][4], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][4], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][4], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][4], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][4], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][4], 255);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][4], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][4], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][4], 0);

    NotificationsPlayerTD[playerid][5] = CreatePlayerTextDraw(playerid, 16.000000, 268.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][5], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][5], 0.179166, 1.399999);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][5], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][5], 0);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][5], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][5], 1);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][5], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][5], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][5], 50);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][5], 0);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][5], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][5], 0);

    NotificationsPlayerTD[playerid][6] = CreatePlayerTextDraw(playerid, 11.000000, 301.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][6], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][6], 0.600000, 2.250000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][6], 289.500000, 1.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][6], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][6], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][6], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][6], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][6], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][6], -16776961);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][6], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][6], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][6], 0);

    NotificationsPlayerTD[playerid][7] = CreatePlayerTextDraw(playerid, 71.000000, 301.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][7], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][7], 0.512498, 1.600000);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][7], 289.500000, 109.500000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][7], 1);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][7], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][7], 2);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][7], 16711935);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][7], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][7], 255);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][7], 1);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][7], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][7], 0);

    NotificationsPlayerTD[playerid][8] = CreatePlayerTextDraw(playerid, 16.000000, 301.000000, "_");
    PlayerTextDrawFont(playerid, NotificationsPlayerTD[playerid][8], 1);
    PlayerTextDrawLetterSize(playerid, NotificationsPlayerTD[playerid][8], 0.179166, 1.399999);
    PlayerTextDrawTextSize(playerid, NotificationsPlayerTD[playerid][8], 400.000000, 17.000000);
    PlayerTextDrawSetOutline(playerid, NotificationsPlayerTD[playerid][8], 0);
    PlayerTextDrawSetShadow(playerid, NotificationsPlayerTD[playerid][8], 0);
    PlayerTextDrawAlignment(playerid, NotificationsPlayerTD[playerid][8], 1);
    PlayerTextDrawColor(playerid, NotificationsPlayerTD[playerid][8], 1296911871);
    PlayerTextDrawBackgroundColor(playerid, NotificationsPlayerTD[playerid][8], 255);
    PlayerTextDrawBoxColor(playerid, NotificationsPlayerTD[playerid][8], 50);
    PlayerTextDrawUseBox(playerid, NotificationsPlayerTD[playerid][8], 0);
    PlayerTextDrawSetProportional(playerid, NotificationsPlayerTD[playerid][8], 1);
    PlayerTextDrawSetSelectable(playerid, NotificationsPlayerTD[playerid][8], 0);

    NotificationsBarTD[playerid][0] = CreateNotificationsBarTD(playerid, 16.000000, 255.000000, 114.000000, 2.000000, 1296911871, 100.000000, 0);
    SetPlayerProgressBarValue(playerid, NotificationsBarTD[playerid][0], 100.000000);

    NotificationsBarTD[playerid][1] = CreateNotificationsBarTD(playerid, 16.000000, 287.000000, 114.000000, 2.000000, 1296911871, 100.000000, 0);
    SetPlayerProgressBarValue(playerid, NotificationsBarTD[playerid][1], 100.000000);

    NotificationsBarTD[playerid][2] = CreateNotificationsBarTD(playerid, 16.000000, 320.000000, 114.000000, 2.000000, 1296911871, 100.000000, 0);
    SetPlayerProgressBarValue(playerid, NotificationsBarTD[playerid][2], 100.000000);
    return true;
}