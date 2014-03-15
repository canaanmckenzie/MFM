#ifndef STATSRENDERER_H /* -*- C++ -*- */
#define STATSRENDERER_H

#include "SDL/SDL_ttf.h"
#include "grid.h"
#include "itype.h"
#include "Point.h"

namespace MFM {

class StatsRenderer
{
private:
  Point<u32> m_dimensions;
  Point<s32> m_drawPoint;

  TTF_Font* m_drawFont;

  SDL_Surface* m_dest;

  static const u32 MAX_TYPES = 16;
  u32 m_displayTypes[MAX_TYPES];
  u32 m_displayTypesInUse;

  bool m_displayAER;

  void DisplayTypeAt(u32 lineNum, u32 type) ;

public:

  StatsRenderer() : m_displayTypesInUse(0), m_displayAER(false)
  {
    m_drawFont = TTF_OpenFont("UbuntuMono-R.ttf", 20);
  }

  bool GetDisplayAER() const { return m_displayAER; }

  void SetDisplayAER(bool displayAER) { m_displayAER = displayAER; }

  bool DisplayStatsForType(u32 type) ;

  ~StatsRenderer()
  {
    TTF_CloseFont(m_drawFont);
  }

  void SetDestination(SDL_Surface* dest)
  {
    m_dest = dest;
  }

  void SetDrawPoint(Point<s32> drawPoint)
  {
    m_drawPoint = drawPoint;
  }

  void SetDimensions(Point<u32> dimensions)
  {
    m_dimensions = dimensions;
  }
  
  template <class T, u32 R>
  void DrawString(const char* string, u32 x, u32 y);

  template<class T, u32 R, u32 W, u32 H>
  void RenderGridStatistics(Grid<T,R,W,H>& grid, double aeps, double aer);
};
} /* namespace MFM */
#include "statsrenderer.tcc"

#endif /*STATSRENDERER_H*/

