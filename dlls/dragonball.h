#ifndef DRAGONBALL_H
#define DRAGONBALL_H

/**
* Dragonball
* @version 19-9-2001
* @author Herwin 'harSens' van Welbergen
*/
class CDragonBall: public CBaseEntity
{
public:
	/**
	* Spawns the ball
	*/
	void Spawn( void );
	
	/**
	* Precaches the models
	*/
	void Precache( void );

	/**
	* Creates a dragonball
	* @param Vector origin: the origin of the ball
	* @param int nr: the number of the ball (appearing on the model)
	*/
	static CDragonBall *CreateDragonBall(Vector origin,int nr);
};

#endif