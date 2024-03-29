﻿/******************************************
*                                         *
*	Fichier fgrenade, par Julien		  *
*                                         *
*	code de la grenade à fragmentation	  *
*										  *
******************************************/




#include "extdll.h"
#include "util.h"
#include "cbase.h"
#include "monsters.h"
#include "weapons.h"
#include "nodes.h"
#include "player.h"
#include "soundent.h"
#include "gamerules.h"

int iFgTrail;

enum fgrenade_e
{
	FGRENADE_IDLE = 0,
	FGRENADE_FIDGET,
	FGRENADE_PINPULL,
	FGRENADE_THROW1,	// toss
	FGRENADE_THROW2,	// medium
	FGRENADE_THROW3,	// hard
	FGRENADE_HOLSTER,
	FGRENADE_DEPLOY
};



LINK_ENTITY_TO_CLASS( weapon_fgrenade , CFGrenade );


#ifndef CLIENT_DLL
TYPEDESCRIPTION CFGrenade::m_SaveData[] =
{
	DEFINE_FIELD( CFGrenade, m_fInAttack, FIELD_INTEGER ),
};
IMPLEMENT_SAVERESTORE( CFGrenade, CBasePlayerWeapon );
#endif

//============================================
//
//============================================

void CFGrenade::Spawn( )
{
	pev->classname = MAKE_STRING("weapon_fgrenade");
	Precache();
	SET_MODEL(ENT(pev), "models/w_fgrenade.mdl");
	m_iId = WEAPON_FGRENADE;

	m_iDefaultAmmo = FGRENADE_DEFAULT_GIVE;

	FallInit();// get ready to fall down.
}


void CFGrenade::Precache( void )
{
	PRECACHE_MODEL("models/v_fg.mdl");
	PRECACHE_MODEL("models/w_fgrenade.mdl");
	PRECACHE_MODEL("models/p_9mmAR.mdl");

	PRECACHE_MODEL("models/w_frag.mdl");
	iFgTrail = 	PRECACHE_MODEL("sprites/laserbeam.spr");

}

int CFGrenade::GetItemInfo(ItemInfo *p)
{
	p->pszName = STRING(pev->classname);
	p->pszAmmo1 = "Fragmentation grenades";
	p->iMaxAmmo1 = FGRENADE_MAX_CARRY;
	p->iMaxClip = FGRENADE_MAX_CLIP;
	p->iSlot = 4;
	p->iPosition = 1;
	p->iId = m_iId = WEAPON_FGRENADE;
	p->iWeight = FGRENADE_WEIGHT;
	p->iFlags = 0;

	return 1;
}


int CFGrenade::AddToPlayer( CBasePlayer *pPlayer )
{
	if ( CBasePlayerWeapon::AddToPlayer( pPlayer ) )
	{
		MESSAGE_BEGIN( MSG_ONE, gmsgWeapPickup, NULL, pPlayer->pev );
			WRITE_BYTE( m_iId );
		MESSAGE_END();

		m_pPlayer->TextAmmo( TA_FRAG );

		return TRUE;
	}
	return FALSE;
}

BOOL CFGrenade :: Deploy( )
{
	return DefaultDeploy( "models/v_fg.mdl", "models/p_9mmAR.mdl", FGRENADE_DEPLOY, "crowbar" );
}


BOOL CFGrenade :: CanHolster( void )
{
	// can only holster hand grenades when not primed!
	return ( m_fInAttack != 1 );
}

void CFGrenade::Holster( int skiplocal  )
{
	m_pPlayer->m_flNextAttack = UTIL_WeaponTimeBase() + 0.5;
	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		SendWeaponAnim( FGRENADE_HOLSTER );
	}
	else
	{
		// no more grenades!
		m_pPlayer->pev->weapons &= ~(1<<WEAPON_FGRENADE);
		SetThink( &CFGrenade::DestroyItem );
		pev->nextthink = gpGlobals->time + 0.1;
	}

	EMIT_SOUND(ENT(m_pPlayer->pev), CHAN_WEAPON, "common/null.wav", 1.0, ATTN_NORM);
}



void CFGrenade::PrimaryAttack()
{
	if ( m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] == 0 )
		return;

	m_fInAttack = 1;
	SendWeaponAnim( FGRENADE_PINPULL );

	m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;
	m_flNextPrimaryAttack = GetNextAttackDelay(0xFF);
}


void CFGrenade::WeaponIdle( void )
{
	if (m_flTimeWeaponIdle > UTIL_WeaponTimeBase())
		return;

	if (m_fInAttack == 1)
	{
		Vector angThrow = m_pPlayer->pev->v_angle + m_pPlayer->pev->punchangle;

		if (angThrow.x < 0)
			angThrow.x = -10 + angThrow.x * ((90 - 10) / 90.0);
		else
			angThrow.x = -10 + angThrow.x * ((90 + 10) / 90.0);

		float flVel = (90 - angThrow.x) * 6;
		if (flVel > 1000)
			flVel = 1000;

		UTIL_MakeVectors( angThrow );

		Vector vecSrc = m_pPlayer->pev->origin + m_pPlayer->pev->view_ofs + gpGlobals->v_forward * 16;

		Vector vecThrow = gpGlobals->v_forward * flVel + m_pPlayer->pev->velocity;

		// alway explode 3 seconds after the pin was pulled
		float time = 3.0;
		if (time < 0)
			time = 0;

		CGrenade::ShootFrag( m_pPlayer->pev, vecSrc, vecThrow, 1 );

		SendWeaponAnim( FGRENADE_THROW1 );

		// player "shoot" animation
		m_pPlayer->SetAnimation( PLAYER_ATTACK1 );

		m_fInAttack = 2;
		m_flNextPrimaryAttack = GetNextAttackDelay(0.5);
		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 0.5;

		m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType]--;

		if ( !m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType] )
		{
			// just threw last grenade
			// set attack times in the future, and weapon idle in the future so we can see the whole throw
			// animation, weapon idle will automatically retire the weapon for us.
			m_flTimeWeaponIdle = m_flNextSecondaryAttack = m_flNextPrimaryAttack = GetNextAttackDelay(0.5);// ensure that the animation can finish playing
		}
		return;
	}
	else if (m_fInAttack == 2)
	{
		// we've finished the throw, restart.
		m_fInAttack = 0;

		if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
		{
			SendWeaponAnim( FGRENADE_DEPLOY );
		}
		else
		{
			RetireWeapon();
			return;
		}

		m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + UTIL_SharedRandomFloat ( m_pPlayer->random_seed, 10, 15 );
		return;
	}

	if (m_pPlayer->m_rgAmmo[m_iPrimaryAmmoType])
	{
		int iAnim;
		float flRand = UTIL_SharedRandomFloat(m_pPlayer->random_seed, 0, 1);
		if (flRand <= 0.75)
		{
			iAnim = FGRENADE_IDLE;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 21 / 5.0;// how long till we do this again.
		}
		else 
		{
			iAnim = FGRENADE_FIDGET;
			m_flTimeWeaponIdle = UTIL_WeaponTimeBase() + 7 / 6.0;
		}

		SendWeaponAnim( iAnim );

	}
}
