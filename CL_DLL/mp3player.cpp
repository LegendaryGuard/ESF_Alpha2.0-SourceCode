#include "hud.h"
#include "parsemsg.h"
#include "cl_util.h"
#include "vgui_TeamFortressViewport.h"
#include <fstream.h>

DECLARE_COMMAND(m_Mp3Player, ShowMp3Menu);

int mp3_end = 0;

signed char endcallback(FSOUND_STREAM *stream, void *buff, int len, int param)
{	mp3_end = 1;
	return true;
}

int CHudMp3Player::Init(void)
{	HOOK_COMMAND("mp3player",ShowMp3Menu);
	
	m_iError = false;
	m_iMenuOpen = false;
	
	//open playlist
	fstream f;

	char file_name[255];
	sprintf(file_name,"%s/mp3/playlist.txt",gEngfuncs.pfnGetGameDirectory());
	f.open(file_name,ios::in);
	
	int n=0;
	while (!f.eof())
	{	f.getline(m_pPlaylist[n],255);
		n++;
	}
	f.close();
	m_iPlaylistLength = n;
	
	//no songs on the playlist
	if(n==0)
	{	m_iError = true;
		return 1;
	}
	
	m_iCurrentSong = 0;
	
	//init sound stuff
	if (FSOUND_GetVersion() < FMOD_VERSION)
	{	m_iError = true;
		ConsolePrint("Error : You are using the wrong DLL version!\n");
		return 1;
	}
	
	if (!FSOUND_Init(44100, 32, 0))
	{	m_iError = true;
		ConsolePrint(FMOD_ErrorString(FSOUND_GetError()));
		FSOUND_Close();
		return 1;
	}

	stream = NULL;
	m_eStatus = MP3_NONE;
	mp3_end = 0;

	gHUD.AddHudElem(this);
	m_iFlags |= HUD_ACTIVE;
	return 1;
}

void CHudMp3Player::Play()
{	if (m_iError)
	{	return;
	}
	//do nothing if already playing
	if (m_eStatus==MP3_PLAY)
	{	return;
	}
	
	//unpause if on pause
	if (m_eStatus==MP3_PAUSE)
	{	if (stream)
		{	FSOUND_Stream_SetPaused(stream , false);
		}
		m_eStatus = MP3_PLAY;
		return;
	}	

	//open mp3 file
	//try global name
	stream = FSOUND_Stream_OpenFile(m_pPlaylist[m_iCurrentSong], FSOUND_NORMAL | FSOUND_LOOP_OFF, 0);
	if (!stream)
	{	//try local name
		char file_name[255];
		sprintf(file_name,"%s/%s",gEngfuncs.pfnGetGameDirectory(),m_pPlaylist[m_iCurrentSong]);
		stream = FSOUND_Stream_OpenFile(file_name, FSOUND_NORMAL | FSOUND_LOOP_OFF, 0);
		if (!stream)
		{	m_iError = true;
			ConsolePrint(FMOD_ErrorString(FSOUND_GetError()));
			ConsolePrint(m_pPlaylist[m_iCurrentSong]);
			FSOUND_Close();
			return ;
		}
	}

	//set end callback
	FSOUND_Stream_SetEndCallback(stream, endcallback, 0);
	
	// PLAY STREAM
	if ((m_iChannel = FSOUND_Stream_Play(FSOUND_FREE, stream)) == -1)
	{	m_iError = true;
		ConsolePrint(FMOD_ErrorString(FSOUND_GetError()));
		FSOUND_Close();
		return ;
	}
	
	//set stereo panning
	FSOUND_SetPan(m_iChannel, FSOUND_STEREOPAN);
	mp3_end=0;	
	m_eStatus = MP3_PLAY;
}

void CHudMp3Player::Pause()
{	if (!stream) 
		return;

	if (m_eStatus == MP3_PLAY)
	{	FSOUND_Stream_SetPaused(stream , true);
		m_eStatus = MP3_PAUSE;
		return;
	}
	if (m_eStatus == MP3_PAUSE)
	{	FSOUND_Stream_SetPaused(stream , false);
		m_eStatus = MP3_PLAY;
		return;
	}
}

void CHudMp3Player::Stop()
{	if (stream)
	{	FSOUND_Stream_Stop(stream);
		FSOUND_Stream_Close(stream);
		stream = NULL;
	}
	m_eStatus = MP3_STOP;
}

void CHudMp3Player::Next()
{	int oldstatus=m_eStatus;

	//close old mp3 stream and selects next stream
	if(stream)
	{	Stop();		
	}
	
	m_iCurrentSong++;
	if (m_iCurrentSong >= m_iPlaylistLength)
	{	m_iCurrentSong = 0;
	}
	
	if (oldstatus==MP3_PLAY)
	{	Play();
	}
}

void CHudMp3Player::Previous()
{	int oldstatus=m_eStatus;
	//close playing stream
	if(stream)
	{	Stop();
	}

	//determine previous song on the list
	m_iCurrentSong--;
	if (m_iCurrentSong < 0)
	{	m_iCurrentSong = m_iPlaylistLength-1;
	}

	if (oldstatus==MP3_PLAY)
	{	Play();
	}
}

void CHudMp3Player::Think()
{	//error while playing back mp3
	if (m_iError)
	{	return;
	}

	if (m_eStatus==MP3_NONE && m_iPlaylistLength>0)
	{	Play();
	}

	//mp3 has stopped. restart new one
	if (mp3_end && m_eStatus==MP3_PLAY)
	{	Next();
	}
}

void CHudMp3Player::DeInit()
{	if (!m_iError)	
	{	if (stream)
		{	Stop();
		}
		FSOUND_Close();
	}
}

void CHudMp3Player::UserCmd_ShowMp3Menu()
{	if (!m_iMenuOpen)
	{	gViewPort->ShowVGUIMenu(MENU_MP3MENU);
		m_iMenuOpen = true;
	}
	else
	{	gViewPort->HideVGUIMenu();
		m_iMenuOpen = false;
	}
}