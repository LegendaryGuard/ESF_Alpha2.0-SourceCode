/***
*
*	Copyright (c) 1999, Valve LLC. All rights reserved.
*	
*	This product contains software technology licensed from Id 
*	Software, Inc. ("Id Technology").  Id Technology (c) 1996 Id Software, Inc. 
*	All Rights Reserved.
*
*   Use, distribution, and modification of this source code and/or resulting
*   object code is restricted to non-commercial enhancements to products from
*   Valve LLC.  All other use, distribution, or modification is prohibited
*   without written permission from Valve LLC.
*
****/
//			
//  hud.h
//
// class CHud declaration
//
// CHud handles the message, calculation, and drawing the HUD
//


#define RGB_YELLOWISH 0x00FFA000 //255,160,0
#define RGB_REDISH 0x00FF1010 //255,160,0
#define RGB_GREENISH 0x0000A000 //0,160,0
//added by harSens
#define RGB_BLUEISH  0x000000A0 // 0,0,160
#define RGB_WHITEISH 0x00FFFFFF // 255,255,255
#define MAX_TRAILS 100

#include "wrect.h"
#include "cl_dll.h"
#include "ammo.h"

//added by harSens, used for mp3player
#include "../fmod/inc/fmod.h"
#include "../fmod/inc/fmod_errors.h"

#define DHN_DRAWZERO 1
#define DHN_2DIGITS  2
#define DHN_3DIGITS  4
#define DHN_KI		 8   //supports up to 9 digits

#define MIN_ALPHA	 100	

#define		HUDELEM_ACTIVE	1

typedef struct {
	int x, y;
} POSITION;

typedef struct {
	unsigned char r,g,b,a;
} RGBA;

struct charge_sprite
{	vec3_t origin;
	vec3_t direction;
}; 

struct trail_points
{	vec3_t point;
	trail_points *next;
};

struct trail
{	trail_points *points;
	int sprite;
	float width;
	int target;
};

struct explosion
{	vec3_t pos;
	int radius;
	char r;
	char g;
	char b;
	char a;
	explosion *next;
};
//end harSens add

#define HUD_ACTIVE	1
#define HUD_INTERMISSION 2

#define MAX_PLAYER_NAME_LENGTH		32

#define	MAX_MOTD_LENGTH				1024

//
//-----------------------------------------------------
//
class CHudBase
{
public:
	POSITION  m_pos;
	int   m_type;
	int	  m_iFlags; // active, moving, 
	virtual int Init( void ) {return 0;}
	virtual int VidInit( void ) {return 0;}
	virtual int Draw(float flTime) {return 0;}
	virtual void Think(void) {return;}
	virtual void Reset(void) {return;}
	virtual void InitHUDData( void ) {}		// called every time a server is connected to

};

struct HUDLIST {
	CHudBase	*p;
	HUDLIST		*pNext;
};


//
//-----------------------------------------------------
//


/**
* Ammo 
* @version SDK 2.0
* @authors Valve LCC
*/
class CHudAmmo: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );

	/**
	* Drawing code
	* @param float flTime: time (?)
	* @return int: 1 if succeeded 0 if not
	*/
	int Draw(float flTime);
	void Think(void);
	void Reset(void);
	int DrawWList(float flTime);
	int MsgFunc_CurWeapon(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_WeaponList(const char *pszName, int iSize, void *pbuf);

	/**
	* Update the count of a known type of ammo
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_AmmoX(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_AmmoPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_WeapPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_ItemPickup( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_HideWeapon( const char *pszName, int iSize, void *pbuf );

	/**
	* Updates the max ki
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_MaxKi( const char *pszName, int iSize, void *pbuf );

	void SlotInput( int iSlot );
	void _cdecl UserCmd_Slot1( void );
	void _cdecl UserCmd_Slot2( void );
	void _cdecl UserCmd_Slot3( void );
	void _cdecl UserCmd_Slot4( void );
	void _cdecl UserCmd_Slot5( void );
	void _cdecl UserCmd_Slot6( void );
	void _cdecl UserCmd_Slot7( void );
	void _cdecl UserCmd_Slot8( void );
	void _cdecl UserCmd_Slot9( void );
	void _cdecl UserCmd_Slot10( void );
	void _cdecl UserCmd_Close( void );
	void _cdecl UserCmd_NextWeapon( void );
	void _cdecl UserCmd_PrevWeapon( void );

private:
	float m_fFade;
	RGBA  m_rgba;
	WEAPON *m_pWeapon;
	int	m_HUD_bucket0;
	int m_HUD_selection;
	//added by harSens
	int m_HUD_ki;
	int m_iMaxKi;
	int m_iActiveWeaponFrame;
	float m_flLastWeaponDraw;
};

//
//-----------------------------------------------------
//

class CHudAmmoSecondary: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	int Draw(float flTime);

	int MsgFunc_SecAmmoVal( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_SecAmmoIcon( const char *pszName, int iSize, void *pbuf );

private:
	enum {
		MAX_SEC_AMMO_VALUES = 4
	};

	int m_HUD_ammoicon; // sprite indices
	int m_iAmmoAmounts[MAX_SEC_AMMO_VALUES];
	float m_fFade;
};


#include "health.h"


#define FADE_TIME 100


//
//-----------------------------------------------------
//
class CHudGeiger: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Geiger(const char *pszName, int iSize, void *pbuf);
	
private:
	int m_iGeigerRange;

};

//
//-----------------------------------------------------
//
class CHudTrain: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Train(const char *pszName, int iSize, void *pbuf);

private:
	HSPRITE m_hSprite;
	int m_iPos;

};

//
//-----------------------------------------------------
//
// REMOVED: Vgui has replaced this.
//
/*
class CHudMOTD : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );

	int MsgFunc_MOTD( const char *pszName, int iSize, void *pbuf );

protected:
	static int MOTD_DISPLAY_TIME;
	char m_szMOTD[ MAX_MOTD_LENGTH ];
	float m_flActiveRemaining;
	int m_iLines;
};
*/

//
//-----------------------------------------------------
//
class CHudStatusBar : public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw( float flTime );
	void Reset( void );
	void ParseStatusString( int line_num );

	int MsgFunc_StatusText( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_StatusValue( const char *pszName, int iSize, void *pbuf );

protected:
	enum { 
		MAX_STATUSTEXT_LENGTH = 128,
		MAX_STATUSBAR_VALUES = 8,
		MAX_STATUSBAR_LINES = 2,
	};

	char m_szStatusText[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];  // a text string describing how the status bar is to be drawn
	char m_szStatusBar[MAX_STATUSBAR_LINES][MAX_STATUSTEXT_LENGTH];	// the constructed bar that is drawn
	int m_iStatusValues[MAX_STATUSBAR_VALUES];  // an array of values for use in the status bar

	int m_bReparseString; // set to TRUE whenever the m_szStatusBar needs to be recalculated
};

//
//-----------------------------------------------------
//
// REMOVED: Vgui has replaced this.
//
/*
class CHudScoreboard: public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int DrawPlayers( int xoffset, float listslot, int nameoffset = 0, char *team = NULL ); // returns the ypos where it finishes drawing
	void UserCmd_ShowScores( void );
	void UserCmd_HideScores( void );
	int MsgFunc_ScoreInfo( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_TeamInfo( const char *pszName, int iSize, void *pbuf );
	int MsgFunc_TeamScore( const char *pszName, int iSize, void *pbuf );
	void DeathMsg( int killer, int victim );

	int m_iNumTeams;

	int m_iLastKilledBy;
	int m_fLastKillTime;
	int m_iPlayerNum;
	int m_iShowscoresHeld;

	void GetAllPlayersInfo( void );
private:
	struct cvar_s *cl_showpacketloss;

};
*/

enum 
{ 
	MAX_PLAYERS = 64,
	MAX_TEAMS = 64,
	MAX_TEAM_NAME = 16,
};

struct extra_player_info_t 
{
	short frags;
	short deaths;
	short playerclass;
	short teamnumber;
	char teamname[MAX_TEAM_NAME];
};

struct team_info_t 
{
	char name[MAX_TEAM_NAME];
	short frags;
	short deaths;
	short ping;
	short packetloss;
	short ownteam;
	short players;
	int already_drawn;
	int scores_overriden;
	int teamnumber;
};

extern hud_player_info_t	g_PlayerInfoList[MAX_PLAYERS+1];	   // player info from the engine
extern extra_player_info_t  g_PlayerExtraInfo[MAX_PLAYERS+1];   // additional player info sent directly to the client dll
extern team_info_t			g_TeamInfo[MAX_TEAMS+1];
extern int					g_IsSpectator[MAX_PLAYERS+1];


//
//-----------------------------------------------------
//
class CHudDeathNotice : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int MsgFunc_DeathMsg( const char *pszName, int iSize, void *pbuf );

private:
	int m_HUD_d_skull;  // sprite index of skull icon
};

//
//-----------------------------------------------------
//
class CHudMenu : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	void Reset( void );
	int Draw( float flTime );
	int MsgFunc_ShowMenu( const char *pszName, int iSize, void *pbuf );

	void SelectMenuItem( int menu_item );

	int m_fMenuDisplayed;
	int m_bitsValidSlots;
	float m_flShutoffTime;
	int m_fWaitingForMore;
};

//
//-----------------------------------------------------
//
class CHudSayText : public CHudBase
{
public:
	int Init( void );
	void InitHUDData( void );
	int VidInit( void );
	int Draw( float flTime );
	int MsgFunc_SayText( const char *pszName, int iSize, void *pbuf );
	void SayTextPrint( const char *pszBuf, int iBufSize, int clientIndex = -1 );
	void EnsureTextFitsInOneLineAndWrapIfHaveTo( int line );
};

//
//-----------------------------------------------------
//
class CHudBattery: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_Battery(const char *pszName,  int iSize, void *pbuf );
	
private:
	HSPRITE m_hSprite1;
	HSPRITE m_hSprite2;
	wrect_t *m_prc1;
	wrect_t *m_prc2;
	int	  m_iBat;	
	float m_fFade;
	int	  m_iHeight;		// width of the battery innards
};


//
//-----------------------------------------------------
//
class CHudFlashlight: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	void Reset( void );
	int MsgFunc_Flashlight(const char *pszName,  int iSize, void *pbuf );
	int MsgFunc_FlashBat(const char *pszName,  int iSize, void *pbuf );
	
private:
	HSPRITE m_hSprite1;
	HSPRITE m_hSprite2;
	HSPRITE m_hBeam;
	wrect_t *m_prc1;
	wrect_t *m_prc2;
	wrect_t *m_prcBeam;
	float m_flBat;	
	int	  m_iBat;	
	int	  m_fOn;
	float m_fFade;
	int	  m_iWidth;		// width of the battery innards
};

//
//-----------------------------------------------------
//
const int maxHUDMessages = 16;
struct message_parms_t
{
	client_textmessage_t	*pMessage;
	float	time;
	int x, y;
	int	totalWidth, totalHeight;
	int width;
	int lines;
	int lineLength;
	int length;
	int r, g, b;
	int text;
	int fadeBlend;
	float charTime;
	float fadeTime;
};

//
//-----------------------------------------------------
//

class CHudTextMessage: public CHudBase
{
public:
	int Init( void );
	static char *LocaliseTextString( const char *msg, char *dst_buffer, int buffer_size );
	static char *BufferedLocaliseTextString( const char *msg );
	char *LookupString( const char *msg_name, int *msg_dest = NULL );
	int MsgFunc_TextMsg(const char *pszName, int iSize, void *pbuf);
};

//
//-----------------------------------------------------
//

class CHudMessage: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	int Draw(float flTime);
	int MsgFunc_HudText(const char *pszName, int iSize, void *pbuf);
	int MsgFunc_GameTitle(const char *pszName, int iSize, void *pbuf);

	float FadeBlend( float fadein, float fadeout, float hold, float localTime );
	int	XPosition( float x, int width, int lineWidth );
	int YPosition( float y, int height );

	void MessageAdd( const char *pName, float time );
	void MessageDrawScan( client_textmessage_t *pMessage, float time );
	void MessageScanStart( void );
	void MessageScanNextChar( void );
	void Reset( void );

private:
	client_textmessage_t		*m_pMessages[maxHUDMessages];
	float						m_startTime[maxHUDMessages];
	message_parms_t				m_parms;
	float						m_gameTitleTime;
	client_textmessage_t		*m_pGameTitle;

	int m_HUD_title_life;
	int m_HUD_title_half;
};

//
//-----------------------------------------------------
//
#define MAX_SPRITE_NAME_LENGTH	24

class CHudStatusIcons: public CHudBase
{
public:
	int Init( void );
	int VidInit( void );
	void Reset( void );
	int Draw(float flTime);
	int MsgFunc_StatusIcon(const char *pszName, int iSize, void *pbuf);

	enum { 
		MAX_ICONSPRITENAME_LENGTH = MAX_SPRITE_NAME_LENGTH,
		MAX_ICONSPRITES = 4,
	};

	
	//had to make these public so CHud could access them (to enable concussion icon)
	//could use a friend declaration instead...
	void EnableIcon( char *pszIconName, unsigned char red, unsigned char green, unsigned char blue );
	void DisableIcon( char *pszIconName );

private:

	typedef struct
	{
		char szSpriteName[MAX_ICONSPRITENAME_LENGTH];
		HSPRITE spr;
		wrect_t rc;
		unsigned char r, g, b;
	} icon_sprite_t;

	icon_sprite_t m_IconList[MAX_ICONSPRITES];

};

/**
* speed changer
* @version 18-4-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudSpeed: public CHudBase 
{ 
public: 
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	/**
	* handles speed messages from the server
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_Speed(const char *pszName, int iSize, void *pbuf); 
private:
	void SetSpeed( int speed ); 
}; 

/**
* Explosion maker
* @version 14-8-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudExplosion: public CHudBase 
{ 
public: 
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	/**
	* handles explosion messages from the server
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_Explosion(const char *pszName, int iSize, void *pbuf); 

	/**
	* loads explosion sprite
	* @return int: always 1
	*/
	int VidInit( void );

	/**
	* Draw function, shrinks explosions
	*/
	int Draw(float flTime);
private:
	void AddExplosion(vec3_t org, int radius, char r, char g, char b, char a);
	explosion* RemoveExplosion(explosion *exp);
	float m_flLastResize;
	int m_iBeam;
}; 

/**
* Spirit bomb charger
* @version 1-9-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudChargeSpiritBomb: public CHudBase 
{ 
public: 
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	/**
	* handles SB charge messages from the server
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_ChargeSB(const char *pszName, int iSize, void *pbuf); 

	/**
	* stops sb charging
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_StopChSB(const char *pszName, int iSize, void *pbuf); 

	/**
	* loads explosion sprite
	* @return int: always 1
	*/
	int VidInit( void );

	/**
	* Think function
	*/
	void Think();
private:
	void CreateCharger(charge_sprite &charger);
	vec3_t m_vecBomb; 
}; 

/**
* camera view changer
* @version 20-6-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudCamera: public CHudBase 
{ 
public:
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 

	/**
	* handles camera view changing messages from the server
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_ChangeView(const char *pszName, int iSize, void *pbuf); 

	///toggles the view if the changeview button is pressed
	void _cdecl UserCmd_ToggleView( void );

private:
	int m_fForceView;
}; 

/**
* Shows the credits
* @version 31-8-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudCredits: public CHudBase 
{ 
public:
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 

	///draws credits
	int Draw(float flTime);

	///Shows credits if button for that is pressed
	void _cdecl UserCmd_ShowCredits( void );

private:
	int m_fShowing;//are the credits already shown?
	int m_iCreditNr;//number of showing credit
	int m_iLastCredit;//nr of the last credit
	float m_flNextScroll;
	float m_flYOffset;
	char m_pLeftCredits[255][255];
	char m_pRightCredits[255][255];
}; 

/**
* Charge bar drawer
* @version 12-7-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudCharge: public CHudBase 
{ 
public:
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	///charge think function
	int Draw(float flTime);
	
	///draws the charge bar
	void DrawChargeBar();

	/**
	* changes the fill value
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_Charge(const char *pszName, int iSize, void *pbuf);
private:
	float m_flFill;		
};

/**
* Power Struggle drawing
* @version 28-8-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudPowerStruggle: public CHudBase 
{ 
public:
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	///charge think function
	int Draw(float flTime);

	/**
	* changes the 
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_PowerStrug(const char *pszName, int iSize, void *pbuf);
private:
	int m_fPowerStruggle;
	float m_flPowerRatio;	
};

/**
* Mp3 Player
* @version 25-8-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudMp3Player: public CHudBase
{	
public:
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void );
	
	/**
	* think function, used to change tracks
	*/
	void Think( void );

	/**
	* deinitializes
	*/
	void DeInit();
	
	///Shows Mp3Player menu
	void _cdecl UserCmd_ShowMp3Menu( void );

	///plays current song
	void Play();

	///pauses playing
	void Pause();

	///stop playing
	void Stop();

	///select next song
	void Next();

	///select previous song
	void Previous();
	
private:
	int m_iMenuOpen;
	int m_iChannel;
	int m_iError;
	int m_iPlaylistLength;
	int m_iCurrentSong;
	char m_pPlaylist[255][255];
	FSOUND_STREAM *stream;
	enum {MP3_NONE,MP3_STOP, MP3_PLAY, MP3_PAUSE}m_eStatus;
};


/**
* Powerlevel indicator
* @version 30-7-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudPowerLevel: public CHudBase
{
public:
	/**
	* Inits powerlevel
	* @return int: always 1 (?)
	*/
	int Init( void );

	/**
	* Load some sprites,etc
	* @return int: always 1 (?)
	*/
	int VidInit(void);
	
	/**
	* Drawing code
	* @param float flTime: time (?)
	* @return int: 1 if succeeded 0 if not
	*/
	int Draw(float flTime);
	
	/**
	* Updates the powerlevel
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_PowerLevel(const char *pszName, int iSize, void *pbuf);
	
	/**
	* Updates the max powerlevel
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_MaxPL( const char *pszName, int iSize, void *pbuf );

private:
	int m_iPowerLevel;
	int m_iMaxPowerLevel;
	int m_HUD_powerlevel;
};

/**
* Sensubean hud gfx
* @version 22-9-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudSensuBean: public CHudBase 
{ 
public: 
	/**
	* initializes 
	* @return int: always 1
	*/
	int Init( void ); 
	
	/**
	* handles senzubean messages from the server
	* @param const char *pszName: name of the message
	* @param int iSize: size of the message
	* @param void *pbuf: message buffer
	*/
	int MsgFunc_SensuBean(const char *pszName, int iSize, void *pbuf); 

	/**
	* loads sprites
	* @return int: always 1
	*/
	int VidInit( void );

	/**
	* Draw function
	* @param float time: time since last level restart
	*/
	int Draw(float flTime);
private:
	int m_iSensuBeans;
	int m_HUD_bean;
};

/**
* Attack trails
* @version 22-10-2001
* @author Herwin 'harSens' van Welbergen
*/
class CHudTrail: public CHudBase
{
public:
	/**
	* Inits trails
	* @return int: always 1 (?)
	*/
	int Init( void );

	/**
	* Drawing code
	* @param float flTime: time (?)
	* @return int: 1 if succeeded 0 if not
	*/
	int Draw(float flTime);
	
	/**
	* Starts a trail
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_CreateTrail(const char *pszName, int iSize, void *pbuf);
	
	/**
	* Adds a point to the trail
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_AddPoint( const char *pszName, int iSize, void *pbuf );

	/**
	* Removes the trail
	* @param const char *pszName: message name
	* @param int iSize: message size
	* @param void *pbuf: buffer with message info
	* @return int:always 1
	*/ 
	int MsgFunc_RemoveTrail( const char *pszName, int iSize, void *pbuf );
private:
	/**
	* Adds a trail to the trail array
	* @param Vector start: start position
	* @param int target: entity to trail to 
	* @param short sprite: trail sprite 
	* @param unsigned char width: trail width
	*/
	void AddTrail(Vector start, int target, short sprite, unsigned char width);
	
	/*
	* Draws the trail
	* @param trail *trTrail: the trail to draw
	*/
	void DrawTrail(trail *trTrail);
	
	/*
	* Finds a trail
	* @param int target: target entity to search for
	* @return int: the trail nr, -1 for not found
	*/
	int FindTrail(int target);
	int m_iTrails;
	float m_flLastBeamDraw;
	trail m_Trail[MAX_TRAILS];
};

//
//-----------------------------------------------------
//

typedef struct cvar_s cvar_t;

class CHud
{
private:
	HUDLIST						*m_pHudList;
	HSPRITE						m_hsprLogo;
	int							m_iLogo;
	client_sprite_t				*m_pSpriteList;
	int							m_iSpriteCount;
	int							m_iSpriteCountAllRes;
	float						m_flMouseSensitivity;
	int							m_iConcussionEffect; 

public:

	HSPRITE						m_hsprCursor;
	float m_flTime;	   // the current client time
	float m_fOldTime;  // the time at which the HUD was last redrawn
	double m_flTimeDelta; // the difference between flTime and fOldTime
	Vector	m_vecOrigin;
	Vector	m_vecAngles;
	int		m_iKeyBits;
	int		m_iHideHUDDisplay;
	int		m_iFOV;
	int		m_Teamplay;
	int		m_iRes;
	cvar_t  *m_pCvarStealMouse;

	int m_iFontHeight;

	/**
	* Draws a number
	* @param int x: x position to draw at
	* @param int y: y position to draw at
	* @param int iFlags: 
	* @param int iNumber: number to be drawn
	* @param int r: red value of color
	* @param int g: green value of color
	* @param int b: blue value of color
	*/
	int DrawHudNumber(int x, int y, int iFlags, int iNumber, int r, int g, int b );
	int DrawHudString(int x, int y, int iMaxX, char *szString, int r, int g, int b );
	int DrawHudStringReverse( int xpos, int ypos, int iMinX, char *szString, int r, int g, int b );
	int DrawHudNumberString( int xpos, int ypos, int iMinX, int iNumber, int r, int g, int b );
	int GetNumWidth(int iNumber, int iFlags);

private:
	// the memory for these arrays are allocated in the first call to CHud::VidInit(), when the hud.txt and associated sprites are loaded.
	// freed in ~CHud()
	HSPRITE *m_rghSprites;	/*[HUD_SPRITE_COUNT]*/			// the sprites loaded from hud.txt
	wrect_t *m_rgrcRects;	/*[HUD_SPRITE_COUNT]*/
	char *m_rgszSpriteNames; /*[HUD_SPRITE_COUNT][MAX_SPRITE_NAME_LENGTH]*/

	struct cvar_s *default_fov;
public:
	HSPRITE GetSprite( int index ) 
	{
		return (index < 0) ? 0 : m_rghSprites[index];
	}

	wrect_t& GetSpriteRect( int index )
	{
		return m_rgrcRects[index];
	}

	
	int GetSpriteIndex( const char *SpriteName );	// gets a sprite index, for use in the m_rghSprites[] array

	CHudAmmo	m_Ammo;
	CHudHealth	m_Health;
	CHudGeiger	m_Geiger;
	CHudBattery	m_Battery;
	CHudTrain	m_Train;
	CHudFlashlight m_Flash;
	CHudMessage m_Message;
	CHudStatusBar    m_StatusBar;
	CHudDeathNotice m_DeathNotice;
	CHudSayText m_SayText;
	CHudMenu	m_Menu;
	CHudAmmoSecondary	m_AmmoSecondary;
	CHudTextMessage m_TextMessage;
	CHudStatusIcons m_StatusIcons;
	//speed changer by harSens
	CHudSpeed m_Speed;
	//camera changer by harSens
	CHudCamera m_Camera;
	//magic charger by harSens
	CHudCharge m_Charge;
	//powerlevel bar by harSens
	CHudPowerLevel m_PowerLevel;
	//explosion trigger by harSens
	CHudExplosion m_Explosion;
	//mp3player by harSens
	CHudMp3Player m_Mp3Player;
	//powerstruggle hud gfx by harSens
	CHudPowerStruggle m_PowerStruggle;
	//credits player by harSens
	CHudCredits m_Credits;
	//spirit bomb charger by harSens
	CHudChargeSpiritBomb m_ChargeSpiritBomb;
	//sensubean gfx by harSens
	CHudSensuBean m_SensuBean;
	//attack trails by harSens
	CHudTrail m_Trail;


	void Init( void );
	void VidInit( void );
	void Think(void);
	int Redraw( float flTime, int intermission );
	int UpdateClientData( client_data_t *cdata, float time );

	CHud() : m_iSpriteCount(0), m_pHudList(NULL) {}  
	~CHud();			// destructor, frees allocated memory

	// user messages
	int _cdecl MsgFunc_Damage(const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_GameMode(const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_Logo(const char *pszName,  int iSize, void *pbuf);
	int _cdecl MsgFunc_ResetHUD(const char *pszName,  int iSize, void *pbuf);
	void _cdecl MsgFunc_InitHUD( const char *pszName, int iSize, void *pbuf );
	int _cdecl MsgFunc_SetFOV(const char *pszName,  int iSize, void *pbuf);
	int  _cdecl MsgFunc_Concuss( const char *pszName, int iSize, void *pbuf );
	// Screen information
	SCREENINFO	m_scrinfo;

	int	m_iWeaponBits;
	int	m_fPlayerDead;
	int m_iIntermission;

	// sprite indexes
	int m_HUD_number_0;


	void AddHudElem(CHudBase *p);

	float GetSensitivity();

};

class TeamFortressViewport;

extern CHud gHUD;
extern TeamFortressViewport *gViewPort;

extern int g_iPlayerClass;
extern int g_iTeamNumber;
extern int g_iUser1;
extern int g_iUser2;

