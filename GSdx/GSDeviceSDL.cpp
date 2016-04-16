/*
 *	Copyright (C) 2007-2009 Gabest
 *	http://www.gabest.org
 *
 *  This Program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *
 *  This Program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with GNU Make; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA.
 *  http://www.gnu.org/copyleft/gpl.html
 *
 */

#include "stdafx.h"
#include "GSDeviceSDL.h"

GSDeviceSDL::GSDeviceSDL()
	: m_free_window(false)
	, m_window(NULL)
	, m_texture(NULL)
{
	SDL_Init(SDL_INIT_VIDEO);
}

GSDeviceSDL::~GSDeviceSDL()
{
	if(m_texture != NULL)
	{
		SDL_FreeSurface(m_texture);
	}
}

bool GSDeviceSDL::Create(GSWnd* wnd)
{
	if (m_window == NULL) {
		m_window = SDL_SetVideoMode(640, 480, 32, SDL_HWSURFACE | SDL_DOUBLEBUF);
	 	m_free_window = true;
	}

	return GSDeviceSW::Create(wnd);
}

bool GSDeviceSDL::Reset(int w, int h)
{
	if(!GSDeviceSW::Reset(w, h))
	{
		return false;
	}

	delete m_backbuffer;

	m_backbuffer = new GSDummyTexture(w, h);

	if(m_texture != NULL)
	{
		SDL_FreeSurface(m_texture);

		m_texture = NULL;
	}

	return true;
}

void GSDeviceSDL::Present(GSTexture* st, GSTexture* dt, const GSVector4& dr, int shader)
{
	ASSERT(dt == m_backbuffer); // ignore m_backbuffer

	GSVector2i size = st->GetSize();

	if(m_texture != NULL)
	{
		if(m_texture->w != size.x || m_texture->h != size.y)
		{
			SDL_FreeSurface(m_texture);

			m_texture = NULL;
		}
	}

	if(m_texture == NULL)
	{
		m_texture = SDL_CreateRGBSurface(SDL_SWSURFACE, size.x, size.y, 32,
			0, 0, 0, 0);
	}

	if(m_texture == NULL)
	{
		return;
	}

	GSTexture::GSMap sm, dm;

	if(SDL_LockSurface(m_texture) == 0)
	{
		dm.bits = (uint8_t *) m_texture->pixels;
		dm.pitch = m_texture->pitch;

		if(st->Map(sm, NULL))
		{
			GSVector2i s = st->GetSize();

			if(0) //m_format == SDL_PIXELFORMAT_ARGB8888)
			{
				if(((intptr_t)dm.bits & 15) == 0 && (dm.pitch & 15) == 0)
				{
					for(int j = s.y; j > 0; j--, sm.bits += sm.pitch, dm.bits += dm.pitch)
					{
						GSVector4i* RESTRICT src = (GSVector4i*)sm.bits;
						GSVector4i* RESTRICT dst = (GSVector4i*)dm.bits;

						for(int i = s.x >> 2; i > 0; i--, dst++, src++)
						{
							*dst = ((*src & 0x00ff0000) >> 16) | ((*src & 0x000000ff) << 16) | (*src & 0x0000ff00);
						}

						uint32* RESTRICT src2 = (uint32*)src;
						uint32* RESTRICT dst2 = (uint32*)dst;

						for(int i = s.x & 3; i > 0; i--, dst2++, src2++)
						{
							*dst2 = ((*src2 & 0x00ff0000) >> 16) | ((*src2 & 0x000000ff) << 16) | (*src2 & 0x0000ff00);
						}
					}
				}
				else
				{
					// VirtualBox/Ubuntu does not return an aligned pointer

					for(int j = s.y; j > 0; j--, sm.bits += sm.pitch, dm.bits += dm.pitch)
					{
						uint32* RESTRICT src = (uint32*)sm.bits;
						uint32* RESTRICT dst = (uint32*)dm.bits;

						for(int i = s.x; i > 0; i--, dst++, src++)
						{
							*dst = ((*src & 0x00ff0000) >> 16) | ((*src & 0x000000ff) << 16) | (*src & 0x0000ff00);
						}
					}
				}
			}
			else
			{
				for(int j = s.y; j > 0; j--, sm.bits += sm.pitch, dm.bits += dm.pitch)
				{
					memcpy(dm.bits, sm.bits, s.x * 4);
				}
			}

			st->Unmap();
		}

		SDL_UnlockSurface(m_texture);
	}

	GSVector4i dri(dr);

	SDL_Rect r;

	r.x = dri.left;
	r.y = dri.top;
	r.w = dri.width();
	r.h = dri.height();

	SDL_BlitSurface(m_texture, NULL, m_window, &r);
}

void GSDeviceSDL::Flip()
{
	SDL_Flip(m_window);
}
