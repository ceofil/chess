#pragma once
#include "Colors.h"
#include "Graphics.h"

namespace SpriteEffect
{
	class Chroma
	{
	public:
		Chroma( Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, cSrc);
			}
		}
	private:
		Color chroma;
	};
	class Substitution
	{
	public:
		Substitution( Color c, Color s)
			:
			chroma(c),
			sub(s)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				gfx.PutPixel(xDest, yDest, sub);
			}
		}
	private:
		Color chroma = Colors::Magenta;
		Color sub;
	};
	class Copy
	{
	public:
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			gfx.PutPixel(xDest, yDest, cSrc);
		}
	};
	class Ghost
	{
	public:
		Ghost(Color c)
			:
			chroma(c)
		{}
		void operator()(Color cSrc, int xDest, int yDest, Graphics& gfx) const
		{
			if (cSrc != chroma)
			{
				Color dest = gfx.GetPixel(xDest, yDest);
				Color blend = {
					unsigned char((dest.GetR() + cSrc.GetR()) / 2),
					unsigned char((dest.GetG() + cSrc.GetG()) / 2),
					unsigned char((dest.GetB() + cSrc.GetB()) / 2)
				};
				gfx.PutPixel(xDest, yDest, blend);
			}
		}
	private:
		Color chroma;
	};
}