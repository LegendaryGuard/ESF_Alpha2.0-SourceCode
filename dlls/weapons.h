/***
*
*	Copyright (c) 1999, 2000 Valve LLC. All rights reserved.
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

/*
highly modified by harSens 
*/

#ifndef WEAPONS_H
#define WEAPONS_H

class CBasePlayer;
extern int gmsgWeapPickup;


#define MAX_NORMAL_BATTERY		100

#define WEAPON_NONE				 0
#define WEAPON_MELEE			 1
#define WEAPON_KIBLAST			 2	
#define WEAPON_GALLITGUN		 3
#define WEAPON_KAMEHAMEHA		 4
#define	WEAPON_DESTRUCTODISC	 5
#define WEAPON_SOLARFLARE		 6
#define WEAPON_EYELASER			 7
#define WEAPON_FRIEZADISC		 8
#define WEAPON_SPECIALBEAMCANNON 9
#define WEAPON_SPIRITBOMB		10
#define WEAPON_BIGBANG			11
#define WEAPON_FINGERLASER		12
#define WEAPON_FINALFLASH		13
#define	WEAPON_MASENKO			14
#define WEAPON_DEATHBALL		15
#define WEAPON_BURNINGATTACK	16
#define WEAPON_SENSUBEAN		17

#define WEAPON_ALLWEAPONS		(~(1<<WEAPON_SUIT))

#define WEAPON_SUIT				31	// ?????

#define MAX_WEAPONS				32

// weapon weight factors (for auto-switching)   (-1 = noswitch)
#define MELEE_WEIGHT				25
#define KIBLAST_WEIGHT				25
#define GALLITGUN_WEIGHT			15
#define KAMEHAMEHA_WEIGHT			15
#define SPECIALBEAMCANNON_WEIGHT		15
#define FINGERLASER_WEIGHT			15
#define BIGBANG_WEIGHT				10
#define DESTRUCTODISC_WEIGHT			10	
#define EYELASER_WEIGHT				20
#define MASENKO_WEIGHT				 5
#define SPIRITBOMB_WEIGHT			 5
#define DEATHBALL_WEIGHT			 5
#define FINALFLASH_WEIGHT			 5 
#define BURNINGATTACK_WEIGHT		 	 5
#define FRIEZADISC_WEIGHT			-1
#define SOLARFLARE_WEIGHT			-1
#define SENSUBEAN_WEIGHT			-1

#define CHARGETIME				0.20
// weapon max charge times * CHARGETIME seconds
#define SPECIALBEAMCANNON_MAXCHARGETIME	        21
#define SOLARFLARE_MAXCHARGETIME		21
#define KAMEHAMEHA_MAXCHARGETIME		30
#define GALLITGUN_MAXCHARGETIME			24
#define BIGBANG_MAXCHARGETIME			30
#define MASENKO_MAXCHARGETIME			24
#define FINALFLASH_MAXCHARGETIME		41
#define BURNINGATTACK_MAXCHARGETIME		12
#define FINGERLASER_MAXCHARGETIME		15
#define SPIRITBOMB_MAXCHARGETIME		90
#define DEATHBALL_MAXCHARGETIME			45

//max weapon sprite sizes
#define BIGBANGATTACK_SIZE			 80
#define GUIDEDATTACK_SIZE		    128
#define SPIRITBOMB_SIZE				256
#define DEATHBALL_SIZE				256

// the maximum amount of ammo each weapon's clip can hold
#define WEAPON_NOCLIP			-1

//Ki cost for the magic weapons
#define MELEE_KI_COST				 2500
#define KIBLAST_KI_COST				15000
#define GALLITGUN_KI_COST			11000
#define KAMEHAMEHA_KI_COST			10000
#define FINALFLASH_KI_COST			20000
#define MASENKO_KI_COST				 5000
#define SPECIALBEAMCANNON_KI_COST	10000
#define FINGERLASER_KI_COST			10000
#define DESTRUCTODISC_KI_COST		50000
#define FRIEZADISC_KI_COST			50000
#define SOLARFLARE_KI_COST			 5000
#define EYELASER_KI_COST			 5000
#define SPIRITBOMB_KI_COST			    0
#define DEATHBALL_KI_COST			 8000
#define BIGBANG_KI_COST				15000
#define BURNINGATTACK_KI_COST		 3500

//weapon speeds
#define GALLITGUN_SPEED				1300
#define KAMEHAMEHA_SPEED			1300
#define MASENKO_SPEED				1500
#define FINALFLASH_SPEED			1000
#define BIGBANG_SPEED				1900
#define SPIRITBOMB_SPEED			1000
#define DEATHBALL_SPEED				1900
#define BURNINGATTACK_SPEED			2000
#define SPECIALBEAMCANNON_SPEED		2000
#define DESTRUCTODISC_SPEED			 800
#define FRIEZADISC_SPEED			1000
#define KIBLAST_SPEED				2000
#define SENSU_SPEED					 500

//weapon damage
#define EYELASER_DAMAGE				4
#define KIBLAST_DAMAGE				5
#define KICK_DAMAGE					8
#define PUNCH_DAMAGE				6

//damages per chargepoint
#define KAMEHAMEHA_DAMAGE			3
#define GALLITGUN_DAMAGE			3
#define MASENKO_DAMAGE				3
#define SPECIALBEAMCANNON_DAMAGE	5 //'cause of shorter chargetime
#define FINGERLASER_DAMAGE			3
#define BIGBANG_DAMAGE				4
#define FINALFLASH_DAMAGE			4
#define BURNINGATTACK_DAMAGE		3
#define SPIRITBOMB_DAMAGE			2
#define DEATHBALL_DAMAGE			3

#define KAMEHAMEHA_RADIUS			5
#define GALLITGUN_RADIUS			4
#define MASENKO_RADIUS				3
#define SPECIALBEAMCANNON_RADIUS	4 
#define FINGERLASER_RADIUS			2
#define BIGBANG_RADIUS				6
#define FINALFLASH_RADIUS			5
#define BURNINGATTACK_RADIUS		3
#define SPIRITBOMB_RADIUS			3
#define DEATHBALL_RADIUS			3
// bullet types
typedef	enum
{
	BULLET_NONE = 0,
	BULLET_PLAYER_9MM, // glock
	BULLET_PLAYER_MP5, // mp5
	BULLET_PLAYER_357, // python
	BULLET_PLAYER_BUCKSHOT, // shotgun
	BULLET_PLAYER_CROWBAR, // crowbar swipe

	BULLET_MONSTER_9MM,
	BULLET_MONSTER_MP5,
	BULLET_MONSTER_12MM,
} Bullet;

#define ITEM_FLAG_SELECTONEMPTY		1
#define ITEM_FLAG_NOAUTORELOAD		2
#define ITEM_FLAG_NOAUTOSWITCHEMPTY	4
#define ITEM_FLAG_LIMITINWORLD		8
#define ITEM_FLAG_EXHAUSTIBLE		16 // A player can totally exhaust their ammo supply and lose this weapon

#define WEAPON_IS_ONTARGET 0x40

typedef struct
{	int		iSlot;
	int		iPosition;
	const char	*pszAmmo1;	// ammo 1 type
	int		iMaxAmmo1;		// max ammo 1
	const char	*pszAmmo2;	// ammo 2 type
	int		iMaxAmmo2;		// max ammo 2
	const char	*pszName;
	int		iMaxClip;
	int		iId;
	int		iFlags;
	int		iWeight;// this value used to determine this weapon's importance in autoselection.
} ItemInfo;

typedef struct
{
	const char *pszName;
	int iId;
} AmmoInfo;


/**
* Class wich handles magic attacks
* @version 13-4-2001
* @author Herwin 'harSens' van Welbergen
*/
class CMagicAttack : public CBaseMonster
{
public:
	/**
	* MagicAttack init
	*/
	void Spawn( void );
	
	/**
	* Precache stuff
	*/
	void Precache( void );

	/**
	* Removes magicattack
	*/
	void Remove(void);

	/**
	* Grows a spirit bomb (or other attack)
	*/
	void Grow (void);

	/**
	* Create magical attack Destructo Disc
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the destructodisc
	* @param Vector vecVelocity: Velocity of the destructodisc
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootDestructoDisc( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity );

	/**
	* Create a guided magical attack 
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the attack
	* @param Vector vecVelocity: Velocity of the attack
	* @param int damage: Amount of damage the attack does
	* @param char *attack: Name of the attack
	* @param float size: relative size of the attack (0..1)
	* @param int beamsprite: the sprite for the beam
	* @param int beamsprite: the radius for the beam
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootGuidedMagic( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, int damage, char *attack, float size, int r, int g, int b, short trail, int radius);
	
	/**
	* Create a wave attack 
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the attack
	* @param Vector vecVelocity: Velocity of the attack
	* @param int damage: the amount of damage the attack does
	* @param char *attack: Name of the attack
	* @param int beamsprite: the sprite for the beam
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootWave( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, int damage, char *attack, int r, int g, int b, short trail, int radius);
	
	/**
	* Create a kiblast attack 
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the attack
	* @param Vector vecVelocity: Velocity of the attack
	* @param damage: the amount of damage to be done
	*/
	static CMagicAttack *ShootKiBlast( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, int damage);
	
	/**
	* Create a bigbang attack 
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the attack
	* @param Vector vecVelocity: Velocity of the attack
	* @param damage: the amount of damage to be done
	* @param size: the size of the bigbang sprite
	*/
	static CMagicAttack *ShootBigBang( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity, int damage, float size);
	
	/**
	* Create magical attack Frieza Disc
	* @param entvars_t *pevOwner: Monster/Player who shoots it
	* @param Vector vecStart: Origin vector of the friezadisc
	* @param Vector vecVelocity: Velocity of the friezadisc
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootFriezaDisc( entvars_t *pevOwner, Vector vecStart, Vector vecVelocity );

	/**
	* Create magical attack OrbitBall
	* @param entvars_t *pevOwner: Target to orbit around
	* @param Vector vecStart: Origin vector of the orbitball
	* @param Vector vecVelocity: Velocity of the orbitball
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootOrbitBall( entvars_t *pevAimEnt, entvars_t *pevOwner, Vector vecStart, Vector vecVelocity , int damage, int r, int g, int b, short trail, int radius);

	/**
	* Create magical attack spirit bomb
	* @param entvars_t *pevOwner: monster/player who shoots it
	* @param Vector vecStart: Origin vector of the spirit bomb
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *CreateSpiritBomb( entvars_t *pevOwner, Vector vecStart);

	
	/**
	* Shoots the spiritbomb
	* @param Vector vecVelocity: velocity of the spiritbomb
	* @param int damage: damage of the spiritbomb
	*/
	void ShootSpiritBomb(Vector vecVelocity, int damage);

	/**
	* Shoots the deathball
	* @param entvars_t *pevOwner: monster/player who shoots it	
	* @param Vector vecVelocity: velocity of the spiritbomb
	* @param int damage: damage of the spiritbomb
	* @param float size: the size of the deathball
	* @return *CMagicAttack: The created MagicAttack 
	*/
	static CMagicAttack *ShootDeathBall(entvars_t *pevOwner,Vector vecSrc, Vector vecVelocity, int damage, float size);

	/**
	* Gets called whenever the MagicAttack hits another entity
	* @param CBaseEntity pOther: the entity wich is hit
	*/
	void EXPORT HitTouch( CBaseEntity *pOther );

	/**
	* Gets called whenever the MagicAttack hits another entity 
	* and creates a bubble on the place of the hit.
	* @param CBaseEntity pOther: the entity wich is hit
	*/
	void EXPORT BubbleTouch( CBaseEntity *pOther );

	/**
	* Used for magics that explode on touch
	* @param CBaseEntity pOther: the entity wich is hit
	*/
	void EXPORT ExplodeTouch( CBaseEntity *pOther );
	
	/**
	* Called when magic is in air. 
	* Removes magic when off-map and emits magic sound.
	*/
	void EXPORT NormalThink( void );

	/**
	* Called for magics wich follow the crosshair
	*/
	void EXPORT FollowThink ( void );

	/**
	* Called for magics wich explode in bubbles
	*/
	void EXPORT BubbleThink ( void );

	/**
	* Randomly rotates the roll of magic, used for destructodisc
	*/
	void EXPORT RandomRotateThink ( void );

	/**
	* Boomerangs the magic back to the player, used for friezadisc
	*/
	void EXPORT HomeThink ( void );

	/**
	* Orbits around another magicattack, used for special beam cannon
	*/
	void EXPORT OrbitThink ( void );

	/**
	* Struggles for power with another magic attack
	*/
	void EXPORT PowerStruggleThink ( void );

	/**
	* Magics don't bleed
	*/
	virtual int	BloodColor( void ) { return DONT_BLEED; }
	
	/**
	* explodes 
	*/
	void Explode();

	int m_fPowerStruggle;
	float m_flStruggleRatio;
private:
	/**
	* adds a trail to the attack
	* @param int life: how long the trail stays on
	* @param int width: the width of the trail
	*/
	void AddTrail(int life, int width, short sprite);

	CBaseEntity *m_pPreviousHit;
	unsigned char m_cColor[4];

	float m_flSpeed;			//speed of the magic
	int m_iRadius;				//the radius for exploding attacks
	BOOL m_fTrail;				//magic has a trail?
	CBaseEntity *m_pStruggler;	//the one to struggle against
	short m_sRockGibs;
};

/**
* Items that the player has in their inventory that they can use
* @author Valve LLC
* @version SDK 2.0
*/
class CBasePlayerItem : public CBaseAnimating
{
public:
	virtual void SetObjectCollisionBox( void );

	virtual int		Save( CSave &save );
	virtual int		Restore( CRestore &restore );
	
	static	TYPEDESCRIPTION m_SaveData[];

	virtual int AddToPlayer( CBasePlayer *pPlayer );	// return TRUE if the item you want the item added to the player inventory
	virtual int AddDuplicate( CBasePlayerItem *pItem ) { return FALSE; }	// return TRUE if you want your duplicate removed from world
	void EXPORT DestroyItem( void );
	void EXPORT DefaultTouch( CBaseEntity *pOther );	// default weapon touch
	void EXPORT FallThink ( void );// when an item is first spawned, this think is run to determine when the object has hit the ground.
	void EXPORT Materialize( void );// make a weapon visible and tangible
	void EXPORT AttemptToMaterialize( void );  // the weapon desires to become visible and tangible, if the game rules allow for it
	CBaseEntity* Respawn ( void );// copy a weapon
	void FallInit( void );
	void CheckRespawn( void );
	virtual int GetItemInfo(ItemInfo *p) { return 0; };	// returns 0 if struct not filled out
	virtual BOOL CanDeploy( void ) { return TRUE; };
	virtual BOOL Deploy( )								// returns is deploy was successful
		 { return TRUE; };

	virtual BOOL CanHolster( void ) { return TRUE; };// can this weapon be put away right now?
	virtual void Holster( int skiplocal = 0 );
	virtual void UpdateItemInfo( void ) { return; };

	virtual void ItemPreFrame( void )	{ return; }		// called each frame by the player PreThink
	virtual void ItemPostFrame( void ) { return; }		// called each frame by the player PostThink

	virtual void Drop( void );
	virtual void Kill( void );
	virtual void AttachToPlayer ( CBasePlayer *pPlayer );

	virtual int PrimaryAmmoIndex() { return -1; };
	virtual int SecondaryAmmoIndex() { return -1; };

	virtual int UpdateClientData( CBasePlayer *pPlayer ) { return 0; }

	virtual CBasePlayerItem *GetWeaponPtr( void ) { return NULL; };

	static ItemInfo ItemInfoArray[ MAX_WEAPONS ];
	static AmmoInfo AmmoInfoArray[ MAX_AMMO_SLOTS ];

	CBasePlayer	*m_pPlayer;
	CBasePlayerItem *m_pNext;
	int		m_iId;												// WEAPON_???

	virtual int iItemSlot( void ) { return 0; }			// return 0 to MAX_ITEMS_SLOTS, used in hud

	int			iItemPosition( void ) { return ItemInfoArray[ m_iId ].iPosition; }
	const char	*pszAmmo1( void )	{ return ItemInfoArray[ m_iId ].pszAmmo1; }
	int			iMaxAmmo1( void )	{ return ItemInfoArray[ m_iId ].iMaxAmmo1; }
	const char	*pszAmmo2( void )	{ return ItemInfoArray[ m_iId ].pszAmmo2; }
	int			iMaxAmmo2( void )	{ return ItemInfoArray[ m_iId ].iMaxAmmo2; }
	const char	*pszName( void )	{ return ItemInfoArray[ m_iId ].pszName; }
	int			iMaxClip( void )	{ return ItemInfoArray[ m_iId ].iMaxClip; }
	int			iWeight( void )		{ return ItemInfoArray[ m_iId ].iWeight; }
	int			iFlags( void )		{ return ItemInfoArray[ m_iId ].iFlags; }

	// int		m_iIdPrimary;										// Unique Id for primary ammo
	// int		m_iIdSecondary;										// Unique Id for secondary ammo
};


/** 
* inventory items Class
* @version SDK 2.0
* @author Valve LLC
*/
class CBasePlayerWeapon : public CBasePlayerItem
{
public:
	virtual int		Save( CSave &save );
	virtual int		Restore( CRestore &restore );
	
	static	TYPEDESCRIPTION m_SaveData[];

	// generic weapon versions of CBasePlayerItem calls
	virtual int AddToPlayer( CBasePlayer *pPlayer );
	virtual int AddDuplicate( CBasePlayerItem *pItem );

	virtual int ExtractAmmo( CBasePlayerWeapon *pWeapon ); //{ return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up
	virtual int ExtractClipAmmo( CBasePlayerWeapon *pWeapon );// { return TRUE; };			// Return TRUE if you can add ammo to yourself when picked up

	virtual int AddWeapon( void ) { ExtractAmmo( this ); return TRUE; };	// Return TRUE if you want to add yourself to the player

	// generic "shared" ammo handlers
	BOOL AddPrimaryAmmo( int iCount, char *szName, int iMaxClip, int iMaxCarry );
	BOOL AddSecondaryAmmo( int iCount, char *szName, int iMaxCarry );

	virtual void UpdateItemInfo( void ) {};	// updates HUD state

	int m_iPlayEmptySound;
	int m_fFireOnEmpty;		// True when the gun is empty and the player is still holding down the
							// attack key(s)
	virtual BOOL PlayEmptySound( void );
	virtual void ResetEmptySound( void );

	virtual void SendWeaponAnim( int iAnim, int skiplocal = 0 );  // skiplocal is 1 if client is predicting weapon animations

	virtual BOOL CanDeploy( void );
	virtual BOOL IsUseable( void );
	BOOL DefaultDeploy( char *szViewModel, char *szWeaponModel, int iAnim, char *szAnimExt, int skiplocal = 0 );

	//added by harSens
	/**
	* Deploys a no-model weapon 
	* @param char *szAnimExt:The name of the animation extender in the models
	*/
	BOOL DefaultDeploy( char *szAnimExt );

	/**
	* Gets the powerratio for the player
	* @returns float: the power ratio
	*/
	float GetPowerRatio ();
	//end harSens add
	
	int DefaultReload( int iClipSize, int iAnim, float fDelay );

	virtual void ItemPostFrame( void );	// called each frame by the player PostThink
	// called by CBasePlayerWeapons ItemPostFrame()
	virtual void PrimaryAttack( void ) { return; }				// do "+ATTACK"
	virtual void SecondaryAttack( void ) { return; }			// do "+ATTACK2"
	virtual void Reload( void ) { return; }						// do "+RELOAD"
	virtual void WeaponIdle( void ) { return; }					// called when no buttons pressed
	virtual int UpdateClientData( CBasePlayer *pPlayer );		// sends hud info to client dll, if things have changed
	virtual void RetireWeapon( void );
	virtual BOOL ShouldWeaponIdle( void ) {return FALSE; };
	virtual void Holster( int skiplocal = 0 );
	virtual BOOL UseDecrement( void ) { return FALSE; };

	int	PrimaryAmmoIndex(); 
	int	SecondaryAmmoIndex(); 

	void PrintState( void );

	virtual CBasePlayerItem *GetWeaponPtr( void ) { return (CBasePlayerItem *)this; };

	float	m_flNextPrimaryAttack;								// soonest time ItemPostFrame will call PrimaryAttack
	float	m_flNextSecondaryAttack;							// soonest time ItemPostFrame will call SecondaryAttack
	float	m_flTimeWeaponIdle;									// soonest time ItemPostFrame will call WeaponIdle
	int		m_iPrimaryAmmoType;									// "primary" ammo index into players m_rgAmmo[]
	int		m_iSecondaryAmmoType;								// "secondary" ammo index into players m_rgAmmo[]
	int		m_iClip;											// number of shots left in the primary weapon clip, -1 it not used
	int		m_iClientClip;										// the last version of m_iClip sent to hud dll
	int		m_iClientWeaponState;								// the last version of the weapon state sent to hud dll (is current weapon, is on target)
	int		m_fInReload;										// Are we in the middle of a reload;

	int		m_iDefaultAmmo;// how much ammo you get when you pick up this weapon as placed by a level designer.
};

/**
* Ammo Class
* @version SDK 2.0
* @author Valve LLC
*/
class CBasePlayerAmmo : public CBaseEntity
{
public:
	virtual void Spawn( void );
	void EXPORT DefaultTouch( CBaseEntity *pOther ); // default weapon touch
	virtual BOOL AddAmmo( CBaseEntity *pOther ) { return TRUE; };

	CBaseEntity* Respawn( void );
	void EXPORT Materialize( void );
};


extern DLL_GLOBAL	short	g_sModelIndexLaser;// holds the index for the laser beam
extern DLL_GLOBAL	const char *g_pModelNameLaser;

extern DLL_GLOBAL	short	g_sModelIndexLaserDot;// holds the index for the laser beam dot
extern DLL_GLOBAL	short	g_sModelIndexFireball;// holds the index for the fireball
extern DLL_GLOBAL	short	g_sModelIndexSmoke;// holds the index for the smoke cloud
extern DLL_GLOBAL	short	g_sModelIndexWExplosion;// holds the index for the underwater explosion
extern DLL_GLOBAL	short	g_sModelIndexBubbles;// holds the index for the bubbles model
extern DLL_GLOBAL	short	g_sModelIndexBloodDrop;// holds the sprite index for blood drops
extern DLL_GLOBAL	short	g_sModelIndexBloodSpray;// holds the sprite index for blood spray (bigger)

extern void ClearMultiDamage(void);
extern void ApplyMultiDamage(entvars_t* pevInflictor, entvars_t* pevAttacker );
extern void AddMultiDamage( entvars_t *pevInflictor, CBaseEntity *pEntity, float flDamage, int bitsDamageType);

extern void DecalGunshot( TraceResult *pTrace, int iBulletType );
extern void SpawnBlood(Vector vecSpot, int bloodColor, float flDamage);
extern int DamageDecal( CBaseEntity *pEntity, int bitsDamageType );
extern void RadiusDamage( Vector vecSrc, entvars_t *pevInflictor, entvars_t *pevAttacker, float flDamage, float flRadius, int iClassIgnore, int bitsDamageType );

typedef struct 
{
	CBaseEntity		*pEntity;
	float			amount;
	int				type;
} MULTIDAMAGE;

extern MULTIDAMAGE gMultiDamage;


#define LOUD_GUN_VOLUME			1000
#define NORMAL_GUN_VOLUME		600
#define QUIET_GUN_VOLUME		200

#define	BRIGHT_GUN_FLASH		512
#define NORMAL_GUN_FLASH		256
#define	DIM_GUN_FLASH			128

#define BIG_EXPLOSION_VOLUME	2048
#define NORMAL_EXPLOSION_VOLUME	1024
#define SMALL_EXPLOSION_VOLUME	512

#define	WEAPON_ACTIVITY_VOLUME	64

#define VECTOR_CONE_1DEGREES	Vector( 0.00873, 0.00873, 0.00873 )
#define VECTOR_CONE_2DEGREES	Vector( 0.01745, 0.01745, 0.01745 )
#define VECTOR_CONE_3DEGREES	Vector( 0.02618, 0.02618, 0.02618 )
#define VECTOR_CONE_4DEGREES	Vector( 0.03490, 0.03490, 0.03490 )
#define VECTOR_CONE_5DEGREES	Vector( 0.04362, 0.04362, 0.04362 )
#define VECTOR_CONE_6DEGREES	Vector( 0.05234, 0.05234, 0.05234 )
#define VECTOR_CONE_7DEGREES	Vector( 0.06105, 0.06105, 0.06105 )
#define VECTOR_CONE_8DEGREES	Vector( 0.06976, 0.06976, 0.06976 )
#define VECTOR_CONE_9DEGREES	Vector( 0.07846, 0.07846, 0.07846 )
#define VECTOR_CONE_10DEGREES	Vector( 0.08716, 0.08716, 0.08716 )
#define VECTOR_CONE_15DEGREES	Vector( 0.13053, 0.13053, 0.13053 )
#define VECTOR_CONE_20DEGREES	Vector( 0.17365, 0.17365, 0.17365 )


/**
* A single entity that can store weapons and ammo. 
* @version SDK 2.0
* @author Valve LLC
*/
class CWeaponBox : public CBaseEntity
{
	void Precache( void );
	void Spawn( void );
	void Touch( CBaseEntity *pOther );
	void KeyValue( KeyValueData *pkvd );
	BOOL IsEmpty( void );
	int  GiveAmmo( int iCount, char *szName, int iMax, int *pIndex = NULL );
	void SetObjectCollisionBox( void );

public:
	void EXPORT Kill ( void );
	int		Save( CSave &save );
	int		Restore( CRestore &restore );
	static	TYPEDESCRIPTION m_SaveData[];

	HasWeapon( CBasePlayerItem *pCheckItem );
	BOOL PackWeapon( CBasePlayerItem *pWeapon );
	BOOL PackAmmo( int iszName, int iCount );
	
	CBasePlayerItem	*m_rgpPlayerItems[MAX_ITEM_TYPES];// one slot for each 

	int m_rgiszAmmo[MAX_AMMO_SLOTS];// ammo names
	int	m_rgAmmo[MAX_AMMO_SLOTS];// ammo quantities

	int m_cAmmoTypes;// how many ammo types packed into this box (if packed by a level designer)
};
#endif // WEAPONS_H
