#ifndef MP3MENU_H
#define MP3MENU_H

#include<VGUI_Panel.h>
#include<VGUI_TablePanel.h>
#include<VGUI_HeaderPanel.h>
#include<VGUI_TextGrid.h>
#include<VGUI_Label.h>

/**
* Mp3 playback menu
* @version 1-10-1980
* @author Herwin 'harSens' van Welbergen
*/
class CMp3MenuPanel : public CMenuPanel
{
public:
	/**
	* Mp3menu
	* @param int iTrans: transparency?
	* @param int iRemoveMe:??
	* @param int x: x pos
	* @param int y: y pos
	* @param int wide: width
	* @param int tall: height
	*/
	CMp3MenuPanel(int iTrans, int iRemoveMe, int x,int y,int wide,int tall);	
private:
	CTransparentPanel	*m_pPanel;
	CommandButton		*m_pCancelButton;
	CommandButton		*m_pPlayButton;
	CommandButton		*m_pPauseButton;
	CommandButton		*m_pStopButton;
	CommandButton		*m_pNextButton;
	CommandButton		*m_pPreviousButton;	

	Label				*m_pTitle;
};
#endif