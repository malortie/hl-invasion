//---------------------------------------------------------
//---------------------------------------------------------
//-														---
//-					music.h							---
//-														---
//---------------------------------------------------------
//---------------------------------------------------------
//-	par JujU									-----------
//-		julien.lecorre@free.fr					-----------
//---------------------------------------------------------
//- fichier d'en t�te du lecteur mp3 pour mod HL		---
//---------------------------------------------------------
//-														---
//- compatible avec la version 3.6.1 de fmod.dll		---
//-		http://www.fmod.org/							---
//-														---
//---------------------------------------------------------



#ifndef MUSIC_H
#define MUSIC_H


#include <fmod.h>
#include <windows.h>

//---------------------------------------------------------
// defines

#define	MUSIC_AUDIO_FILE		1
#define MUSIC_LIST_FILE			0

#define FMOD_DLL_PATH			"invasion\\fmod.dll"



//---------------------------------------------------------
// structure fichier audio

struct audiofile_t
{
	char name [128];
	int repeat;
	int duration;
	BOOL bNoTrackFile;
	audiofile_t *next;
};

//---------------------------------------------------------
// classe du lecteur


class CMusic
{
public:

	// fonctions de lecture

	void OpenFile			( const char *filename, int repeat, int duration, BOOL bNoTrackFile );	// ouverture d'un simple fichier
	void OpenList			( const char *filename );						// ouverture d'un fichier texte contenant les fichiers � lire

	void Init				( void );		// initialisation

	void Play				( void );		// lecture
	void Stop				( void );		// arr�t
	void Reset				( void );		// fermeture

	// variables

//	FSOUND_STREAM *m_fsound;				// handle du fichier en cours de lecture

	BOOL m_IsPlaying;						// t�moin de lecture
	BOOL m_bInit;							// t�moin d'inititalisation
	float m_flTrackDuration;

	audiofile_t *m_pTrack;					// morceaux � jouer 

	// constructeur / destructeur

	CMusic	()	{ m_bInit = FALSE; m_IsPlaying = FALSE; m_pTrack = NULL; m_flTrackDuration = 0; Reset(); };
	~CMusic ()	{};

	// fonctions import�es de la dll fmod

/*	signed char		(_stdcall * FSOUND_INIT )				(int mixrate, int maxsoftwarechannels, unsigned int flags);
	void			(_stdcall * FSOUND_CLOSE )				(void);
	FSOUND_STREAM *	(_stdcall * FSOUND_STREAM_OPENFILE )	(const char *filename, unsigned int mode, int memlength);
	signed char		(_stdcall * FSOUND_STREAM_CLOSE )		(FSOUND_STREAM *stream); 
	int				(_stdcall * FSOUND_STREAM_PLAY )		(int channel, FSOUND_STREAM *stream);
	signed char		(_stdcall * FSOUND_STREAM_ENDCALLBACK)	(FSOUND_STREAM *stream, FSOUND_STREAMCALLBACK callback, int userdata);

	HINSTANCE		m_hFmodDll;*/

	void DeleteTrack( audiofile_t* p );
};

extern CMusic g_MusicPlayer;



#endif // MUSIC_H