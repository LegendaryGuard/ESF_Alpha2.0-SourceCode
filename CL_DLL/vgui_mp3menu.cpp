#include "hud.h"
#include "cl_util.h"
#include "const.h"
#include "entity_state.h"
#include "cl_entity.h"
#include "vgui_TeamFortressViewport.h"
#include "vgui_mp3menu.h"

#define PLAYER_WIDTH  ScreenWidth/2
#define PLAYER_XPOS 0
#define PLAYER_YPOS 0
#define BUTTONS 7
#define BUTTON_SPACE 2
#define BUTTON_WIDTH (PLAYER_WIDTH - BUTTON_SPACE*(BUTTONS+1))/BUTTONS
#define BUTTON_HEIGHT BUTTON_WIDTH/2
#define PLAYER_HEIGHT BUTTON_HEIGHT * 2 + BUTTON_SPACE * 3
#define BUTTON_YPOS PLAYER_HEIGHT - BUTTON_SPACE*2 - BUTTON_HEIGHT

class StopHandler : public ActionSignal
{
public:
	virtual void actionPerformed(Panel* panel)
	{	gHUD.m_Mp3Player.Stop();
	}
};

class PlayHandler : public ActionSignal
{
public:
	virtual void actionPerformed(Panel* panel)
	{	gHUD.m_Mp3Player.Play();
	}
};

class PauseHandler : public ActionSignal
{
public:
	virtual void actionPerformed(Panel* panel)
	{	gHUD.m_Mp3Player.Pause();
	}
};

class NextHandler : public ActionSignal
{
public:
	virtual void actionPerformed(Panel* panel)
	{	gHUD.m_Mp3Player.Next();		
	}
};

class PreviousHandler : public ActionSignal
{
public:
	virtual void actionPerformed(Panel* panel)
	{	gHUD.m_Mp3Player.Previous();		
	}
};

CMp3MenuPanel :: CMp3MenuPanel(int iTrans, int iRemoveMe, int x, int y, int wide, int tall) : CMenuPanel(iTrans, iRemoveMe, x,y,wide,tall)
{	m_pPanel = new CTransparentPanel( 200, PLAYER_XPOS, PLAYER_YPOS, PLAYER_WIDTH, PLAYER_HEIGHT);
	m_pPanel->setParent( this );
	m_pPanel->setBorder( new LineBorder( Color(255 * 0.7,170 * 0.7,0,0) ) );
		
	m_pTitle = new Label( "", 0, 0, PLAYER_WIDTH-1, BUTTON_HEIGHT);
	m_pTitle->setParent( m_pPanel );
	m_pTitle->setBgColor( 200, 0, 0, 150 );
	m_pTitle->setFgColor( 200, 200, 200, 150 );
	m_pTitle->setContentAlignment( vgui::Label::a_center );
	m_pTitle->setText( "ESF MP3 Player" );

	
	int button_x = BUTTON_SPACE;
	m_pPlayButton = new CommandButton( ">", button_x, BUTTON_YPOS, BUTTON_WIDTH-BUTTON_SPACE, BUTTON_HEIGHT);
	m_pPlayButton->setContentAlignment(vgui::Label::a_west);
	m_pPlayButton->setParent( m_pPanel );
	m_pPlayButton->addActionSignal( new PlayHandler );

	button_x += BUTTON_SPACE + BUTTON_WIDTH;
	m_pPauseButton = new CommandButton( "||", button_x, BUTTON_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pPauseButton->setContentAlignment(vgui::Label::a_west);
	m_pPauseButton->setParent( m_pPanel );
	m_pPauseButton->addActionSignal( new PauseHandler );

	button_x += BUTTON_SPACE + BUTTON_WIDTH;
	char text[2];
	text[0] = (signed char)0x90;
	text[1] = 0;
	m_pStopButton = new CommandButton( text, button_x, BUTTON_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pStopButton->setContentAlignment(vgui::Label::a_west);
	m_pStopButton->setParent( m_pPanel );
	m_pStopButton->addActionSignal( new StopHandler );

	button_x += BUTTON_SPACE + BUTTON_WIDTH;
	m_pPreviousButton = new CommandButton( "<<" , button_x, BUTTON_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pPreviousButton->setContentAlignment(vgui::Label::a_west);
	m_pPreviousButton->setParent( m_pPanel );
	m_pPreviousButton->addActionSignal( new PreviousHandler );	

	button_x += BUTTON_SPACE + BUTTON_WIDTH;
	m_pNextButton = new CommandButton( ">>", button_x, BUTTON_YPOS, BUTTON_WIDTH, BUTTON_HEIGHT);
	m_pNextButton->setContentAlignment(vgui::Label::a_west);
	m_pNextButton->setParent( m_pPanel );
	m_pNextButton->addActionSignal( new NextHandler );	

	button_x += BUTTON_SPACE + BUTTON_WIDTH;
	m_pCancelButton = new CommandButton( "Hide", button_x, BUTTON_YPOS, BUTTON_WIDTH*2+BUTTON_SPACE, BUTTON_HEIGHT);
	m_pCancelButton->setContentAlignment(vgui::Label::a_west);
	m_pCancelButton->setParent( m_pPanel );
	m_pCancelButton->addActionSignal( new CMenuHandler_TextWindow(HIDE_TEXTWINDOW) );
}