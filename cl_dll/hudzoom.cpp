/****************************************************************
*																*
*				hudzoom.cpp										*
*																*
*				par Julien										*
*																*
****************************************************************/

// code du viseur du fusil de snipe


#include "hud.h"
#include "cl_util.h"
#include "const.h"
#include "entity_state.h"
#include "cl_entity.h"
#include "triangleapi.h"



int CHudSniper :: Draw	( float flTime )
{
	return 1; // New draw code is now in DrawScope().

	if ( gHUD.m_iFOV == 90 || gHUD.m_iFOV == 0 )
		return 1;

	static const int CenterX = ScreenWidth / 2;
	static const int CenterY = ScreenHeight / 2;


	if ( ScreenWidth >= 1024 )
	{
		// ligne du haut

		SPR_Set( m_sprHG, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128 - 256, CenterY -128 - 256, &m_wrc1024);	

		SPR_Set( m_sprH, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128, CenterY - 128 - 256, &m_wrc1024);

		SPR_Set( m_sprHD, 255, 255, 255);
		SPR_DrawHoles(0, CenterX + 128, CenterY -128 - 256, &m_wrc1024);

		// ligne du milieu

		SPR_Set( m_sprG, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128 - 256, CenterY -128, &m_wrc1024);	

		SPR_Set( m_sprViseur, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128, CenterY -128, &m_wrc1024);

		SPR_Set( m_sprD, 255, 255, 255);
		SPR_DrawHoles(0, CenterX + 128, CenterY -128, &m_wrc1024);

		// ligne du bas 

		SPR_Set( m_sprBG, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128 - 256, CenterY + 128, &m_wrc1024);	

		SPR_Set( m_sprB, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 128, CenterY + 128, &m_wrc1024);

		SPR_Set( m_sprBD, 255, 255, 255);
		SPR_DrawHoles(0, CenterX + 128, CenterY + 128, &m_wrc1024);


		// noir à gauche et à droite

		int i;

		for ( i = 0 ; i < ScreenHeight ; i += 256 )
		{
			m_wrcNoir.left = 0;
			m_wrcNoir.top = 0;
			m_wrcNoir.right = ScreenWidth / 2 - 128 - 256;
			m_wrcNoir.bottom = 256;

			SPR_Set( m_sprBlack, 255, 255, 255);
			SPR_DrawHoles(0, 0, i, &m_wrcNoir);

			SPR_DrawHoles( 0, ScreenWidth / 2 + 128 + 256, i, &m_wrcNoir);

		}

		if ( 256 * i + 256 < ScreenHeight )
		{
			m_wrcNoir.bottom = ScreenHeight - ( 256 * i + 256 ) ;

			SPR_Set( m_sprBlack, 255, 255, 255);
			SPR_DrawHoles(0, 0, i, &m_wrcNoir);

			SPR_DrawHoles( 0, ScreenWidth / 2 + 128 + 256, i, &m_wrcNoir);

		}

		// noir en haut et en bas

		if ( CenterY - 128 - 256 > 0 )
		{

			int i;

			for ( i = 0 ; i < 3 ; i ++ )
			{
				m_wrcNoir.left = 0;
				m_wrcNoir.top = 0;
				m_wrcNoir.right = 256;
				m_wrcNoir.bottom = CenterY - 128 - 256;

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, CenterX - 128 - 256 + i * 256 , 0, &m_wrcNoir);

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, CenterX - 128 - 256 + i * 256 , CenterY + 128 + 256, &m_wrcNoir);

			}
		}
	}


	else
	{

		// ligne du haut

		SPR_Set( m_sprHG, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 240, CenterY -240, &m_wrc640);	

		SPR_Set( m_sprHD, 255, 255, 255);
		SPR_DrawHoles(0, CenterX, CenterY -240, &m_wrc640);

		// ligne du bas 

		SPR_Set( m_sprBG, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 240, CenterY, &m_wrc640);	

		SPR_Set( m_sprBD, 255, 255, 255);
		SPR_DrawHoles(0, CenterX, CenterY, &m_wrc640);
		
		// viseur

		SPR_Set( m_sprViseur, 255, 255, 255);
		SPR_DrawHoles(0, CenterX - 16, CenterY - 16, &m_wrc640Viseur);


		// noir à gauche et à droite

		if ( CenterX - 240 > 0 )
		{
			int i;

			for ( i = 0 ; i < ScreenHeight ; i += 256 )
			{
				m_wrcNoir.left = 0;
				m_wrcNoir.top = 0;
				m_wrcNoir.right = CenterX - 240;
				m_wrcNoir.bottom = 256;

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, 0, i, &m_wrcNoir);

				SPR_DrawHoles( 0, CenterX + 240, i, &m_wrcNoir);

			}

			if ( 256 * i + 256 < ScreenHeight )
			{
				m_wrcNoir.bottom = ScreenHeight - ( 256 * i + 256 ) ;

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, 0, i, &m_wrcNoir);

				SPR_DrawHoles( 0, CenterX + 240, i, &m_wrcNoir);

			}
		}

		// noir en haut et en bas

		if ( CenterY - 240 > 0 )
		{

			int i;

			for ( i = 0 ; i < 3 ; i ++ )
			{
				m_wrcNoir.left = 0;
				m_wrcNoir.top = 0;
				m_wrcNoir.right = 256;
				m_wrcNoir.bottom = CenterY - 240;

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, CenterX - 240 + i * 256 , 0, &m_wrcNoir);

				SPR_Set( m_sprBlack, 255, 255, 255);
				SPR_DrawHoles(0, CenterX - 240 + i * 256 , CenterY + 240, &m_wrcNoir);

			}
		}
	}


	return 1;
}




int CHudSniper :: Init( void )
{

//	if ( ScreenWidth >= 1024 )
//	{
		
		m_sprHG	= SPR_Load("sprites/fsniper/fsniper_1024_up_l.spr");
		m_sprH	= SPR_Load("sprites/fsniper/fsniper_1024_up.spr");
		m_sprHD = SPR_Load("sprites/fsniper/fsniper_1024_up_r.spr");

		m_sprBD = SPR_Load("sprites/fsniper/fsniper_1024_down_r.spr");
		m_sprB	= SPR_Load("sprites/fsniper/fsniper_1024_down.spr");
		m_sprBG = SPR_Load("sprites/fsniper/fsniper_1024_down_l.spr");

		m_sprG	= SPR_Load("sprites/fsniper/fsniper_1024_left.spr");
		m_sprD	= SPR_Load("sprites/fsniper/fsniper_1024_right.spr");

		m_sprViseur	= SPR_Load("sprites/fsniper/fsniper_1024_cross.spr");
		m_sprBlack	= SPR_Load("sprites/fsniper/fsniper_black.spr");


//		m_wrc1024.left = 0;
//		m_wrc1024.top = 0;
//		m_wrc1024.right = 256;
//		m_wrc1024.bottom = 256;

//	}

//	else /* if ( ScreenWidth <= 640 )*/
/*	{

		m_sprHG	= SPR_Load("sprites/fsniper/fsniper_640_up_l.spr");
		m_sprHD = SPR_Load("sprites/fsniper/fsniper_640_up_r.spr");
		m_sprBD = SPR_Load("sprites/fsniper/fsniper_640_down_r.spr");
		m_sprBG = SPR_Load("sprites/fsniper/fsniper_640_down_l.spr");

		m_sprViseur	= SPR_Load("sprites/fsniper/fsniper_640_cross.spr");
		m_sprBlack	= SPR_Load("sprites/fsniper/fsniper_black.spr");



		m_wrc640.left	= 0;
		m_wrc640.top	= 0;
		m_wrc640.right	= 240;
		m_wrc640.bottom = 240;

		m_wrc640Viseur.left		= 0;
		m_wrc640Viseur.top		= 0;
		m_wrc640Viseur.right	= 32;
		m_wrc640Viseur.bottom	= 32;
	}*/


	m_iFlags |= HUD_ACTIVE;

	gHUD.AddHudElem(this);

	return 1;
}



int CHudSniper :: VidInit( void )
{

//	if ( ScreenWidth >= 1024 )
//	{
		
		m_sprHG	= SPR_Load("sprites/fsniper/fsniper_1024_up_l.spr");
		m_sprH	= SPR_Load("sprites/fsniper/fsniper_1024_up.spr");
		m_sprHD = SPR_Load("sprites/fsniper/fsniper_1024_up_r.spr");

		m_sprBD = SPR_Load("sprites/fsniper/fsniper_1024_down_r.spr");
		m_sprB	= SPR_Load("sprites/fsniper/fsniper_1024_down.spr");
		m_sprBG = SPR_Load("sprites/fsniper/fsniper_1024_down_l.spr");

		m_sprG	= SPR_Load("sprites/fsniper/fsniper_1024_left.spr");
		m_sprD	= SPR_Load("sprites/fsniper/fsniper_1024_right.spr");

		m_sprViseur	= SPR_Load("sprites/fsniper/fsniper_1024_cross.spr");
		m_sprBlack	= SPR_Load("sprites/fsniper/fsniper_black.spr");


//		m_wrc1024.left = 0;
//		m_wrc1024.top = 0;
//		m_wrc1024.right = 256;
//		m_wrc1024.bottom = 256;

//	}

//	else /*if ( ScreenWidth <= 640 )*/
/*	{

		m_sprHG	= SPR_Load("sprites/fsniper/fsniper_640_up_l.spr");
		m_sprHD = SPR_Load("sprites/fsniper/fsniper_640_up_r.spr");
		m_sprBD = SPR_Load("sprites/fsniper/fsniper_640_down_r.spr");
		m_sprBG = SPR_Load("sprites/fsniper/fsniper_640_down_l.spr");

		m_sprViseur	= SPR_Load("sprites/fsniper/fsniper_640_cross.spr");
		m_sprBlack	= SPR_Load("sprites/fsniper/fsniper_black.spr");



		m_wrc640.left	= 0;
		m_wrc640.top	= 0;
		m_wrc640.right	= 240;
		m_wrc640.bottom = 240;

		m_wrc640Viseur.left		= 0;
		m_wrc640Viseur.top		= 0;
		m_wrc640Viseur.right	= 32;
		m_wrc640Viseur.bottom	= 32;
	}*/

	m_iFlags |= HUD_ACTIVE;

	return 1;
}

void CHudSniper::DrawScope(void)
{
	if ( !(m_iFlags & HUD_ACTIVE) )
		return;

	if ( gHUD.m_iFOV == 90 || gHUD.m_iFOV == 0 )
		return;

	int spriteHeight = ScreenHeight / 3;
	int spriteWidth = spriteHeight;

	const int CenterX = ScreenWidth / 2;
	const int CenterY = ScreenHeight / 2;

	int x = CenterX - spriteWidth / 2 - spriteWidth;
	int y = CenterY - spriteHeight / 2 - spriteHeight;

	// Top line sprites.
	DrawScopeLine(m_sprHG, m_sprH, m_sprHD, x, y, spriteWidth, spriteHeight);

	// Middle line sprites.
	DrawScopeLine(m_sprG, m_sprViseur, m_sprD, x, y + spriteHeight, spriteWidth, spriteHeight);

	// Bottom line sprites.
	DrawScopeLine(m_sprBG, m_sprB, m_sprBD, x, y + spriteHeight * 2, spriteWidth, spriteHeight);

	// Left top-bottom black overlay.
	DrawSprite(m_sprBlack, 0, 0, 0, x, ScreenHeight);

	// Right top-bottom black overlay.
	DrawSprite(m_sprBlack, 0, ScreenWidth - x, 0, x, ScreenHeight);
}

void CHudSniper::DrawScopeLine(HSPRITE hLeft, HSPRITE hMiddle, HSPRITE hRight, int x, int y, int spriteWidth, int spriteHeight)
{
	if (hLeft)
		DrawSprite(hLeft, 0, x, y, spriteWidth, spriteHeight);
	if (hMiddle)
		DrawSprite(hMiddle, 0, x + spriteWidth, y, spriteWidth, spriteHeight);
	if (hRight)
		DrawSprite(hRight, 0, x + spriteWidth * 2, y, spriteWidth, spriteHeight);
}

void CHudSniper::DrawSprite(HSPRITE hSprite, int frame, int x, int y, int width, int height)
{
	if (!hSprite)
		return;

	struct model_s* hSpriteModel = (struct model_s*)gEngfuncs.GetSpritePointer(hSprite);
	if (!hSpriteModel)
		return;

	gEngfuncs.pTriAPI->RenderMode(kRenderTransTexture); //additive

	gEngfuncs.pTriAPI->SpriteTexture(hSpriteModel, frame);
	gEngfuncs.pTriAPI->Color4f(1.0, 1.0, 1.0, 1.0);

	gEngfuncs.pTriAPI->CullFace(TRI_NONE);
	gEngfuncs.pTriAPI->Begin(TRI_QUADS);

	//top left
	gEngfuncs.pTriAPI->TexCoord2f(0, 0);
	gEngfuncs.pTriAPI->Vertex3f(x, y, 0);

	//bottom left
	gEngfuncs.pTriAPI->TexCoord2f(0, 1);
	gEngfuncs.pTriAPI->Vertex3f(x, y + height, 0);

	//bottom right
	gEngfuncs.pTriAPI->TexCoord2f(1, 1);
	gEngfuncs.pTriAPI->Vertex3f(x + width, y + height, 0);

	//top right
	gEngfuncs.pTriAPI->TexCoord2f(1, 0);
	gEngfuncs.pTriAPI->Vertex3f(x + width, y, 0);

	gEngfuncs.pTriAPI->End();

	gEngfuncs.pTriAPI->RenderMode(kRenderNormal); //return to normal
}
