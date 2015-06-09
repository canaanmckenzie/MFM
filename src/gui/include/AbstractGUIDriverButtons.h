/*                                              -*- mode:C++ -*-
  AbstractGUIDriverButtons.h Buttons for the AbstractGUIDriver
  Copyright (C) 2014-2015 The Regents of the University of New Mexico.  All rights reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA 02110-1301
  USA
*/

/**
  \file AbstractGUIDriverButtons.h Buttons for the AbstractGUIDriver
  \author Trent R. Small.
  \author David H. Ackley.
  \date (C) 2014-2015 All rights reserved.
  \lgpl
 */
#ifndef ABSTRACTGUIDRIVERBUTTONS_H
#define ABSTRACTGUIDRIVERBUTTONS_H

namespace MFM
{
  template<class GC> class AbstractGUIDriver; // FORWARD
  template<class GC> class AbstractDriver; // FORWARD

  template<class GC>
  class AbstractGridButton : public AbstractButton
  {
  public:
    typedef typename AbstractDriver<GC>::OurGrid OurGrid;

    void SetDriver(AbstractGUIDriver<GC> & driver)
    {
      m_driver = &driver;
    }

    AbstractGUIDriver<GC> & GetDriver()
    {
      if (!m_driver) FAIL(ILLEGAL_STATE);
      return *m_driver;
    }

    Grid<GC> & GetGrid()
    {
      return GetDriver().GetGrid();
    }

    GridRenderer & GetGridRenderer()
    {
      return this->GetDriver().GetGridRenderer();
    }

    AbstractGridButton(const char* title)
      : AbstractButton(title)
      , m_driver(0)
      , m_grend(0)
    { }

  private:
    AbstractGUIDriver<GC> * m_driver;
    GridRenderer* m_grend;
  };

  template<class GC>
  class AbstractGridCheckboxExternal : public AbstractCheckboxExternal
  {
  public:

    void SetDriver(AbstractGUIDriver<GC> & driver)
    {
      m_driver = &driver;
    }

    AbstractGUIDriver<GC> & GetDriver()
    {
      if (!m_driver) FAIL(ILLEGAL_STATE);
      return *m_driver;
    }

    AbstractGridCheckboxExternal(const char* title)
      : AbstractCheckboxExternal(title)
      , m_driver(0)
    { }

  private:
    AbstractGUIDriver<GC> * m_driver;

  };

  template<class GC>
  class AbstractGridCheckbox : public AbstractGridCheckboxExternal<GC>
  {
  public:

    AbstractGridCheckbox(const char* title)
      : AbstractGridCheckboxExternal<GC>(title)
      , m_driver(0)
      , m_checked(false)
    {
      this->SetExternalValue(&m_checked);
    }

  private:
    AbstractGUIDriver<GC> * m_driver;
    bool m_checked;
  };



  /************************************/
  /******CONCRETE BUTTONS**************/
  /************************************/

  template<class GC>
  struct ClearButton : public AbstractGridButton<GC>
  {
    ClearButton() ;
    virtual void OnClick(u8 button) ;
  };

  template<class GC>
  struct ClearGridButton : public AbstractGridButton<GC>
  {
    ClearGridButton() ;
    virtual void OnClick(u8 button) ;
  };

  template<class GC>
  struct NukeButton : public AbstractGridButton<GC>
  {
    NukeButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_n;
      mod = KMOD_CTRL;
      return true;
    }
  };

  template<class GC>
  struct XRayButton : public AbstractGridButton<GC>
  {
    XRayButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_x;
      mod = 0;
      return true;
    }
  };

  template<class GC>
  struct GridRunCheckbox : public AbstractGridCheckboxExternal<GC>
  {
    GridRunCheckbox() ;
    virtual void OnCheck(bool value) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_SPACE;
      mod = 0;
      return true;
    }
  };

  template<class GC>
  struct GridRenderButton : public AbstractGridCheckboxExternal<GC>
  {
    GridRenderButton() ;
    virtual void OnCheck(bool value) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_g;
      mod = 0;
      return true;
    }

  };

  template<class GC>
  struct FgViewButton : public AbstractGridButton<GC>
  {
    FgViewButton() ;
    virtual void OnClick(u8 button) ;
    void UpdateLabel() ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_f;
      mod = 0;
      return true;
    }
  };

  template<class GC>
  struct GridStepCheckbox : public AbstractGridButton<GC>
  {
    GridStepCheckbox() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_s;
      mod = 0;
      return true;
    }
  };

  template<class GC>
  struct BgViewButton : public AbstractGridButton<GC>
  {
    BgViewButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_b;
      mod = 0;
      return true;
    }
    void UpdateLabel() ;
  private:
  };

  template<class GC>
  struct SaveButton : public AbstractGridButton<GC>
  {
    SaveButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_s;
      mod = KMOD_CTRL;
      return true;
    }
  };

  template<class GC>
  struct ScreenshotButton : public AbstractGridButton<GC>
  {
  public:
    ScreenshotButton() ;

    void SetScreen(SDL_Surface* screen) ;
    void SetCamera(Camera* camera) ;
    void SetDriver(AbstractDriver<GC>* driver) ;

    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_p;
      mod = 0;
      return true;
    }

  private:
    u32 m_currentScreenshot;
    SDL_Surface* m_screen;
    Camera* m_camera;
    AbstractDriver<GC>* m_driver;
  };

  template<class GC>
  struct QuitButton : public AbstractGridButton<GC>
  {
    QuitButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_q;
      mod = KMOD_CTRL;
      return true;
    }
  };

  template<class GC>
  struct ReloadButton : public AbstractGridButton<GC>
  {
    ReloadButton() ;
    virtual void OnClick(u8 button) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_r;
      mod = KMOD_CTRL;
      return true;
    }
  };

  template<class GC>
  struct PauseTileButton : public AbstractGridButton<GC>
  {
    PauseTileButton() ;
    virtual void OnClick(u8 button) ;
  };

  template<class GC>
  struct BGRButton : public AbstractGridCheckboxExternal<GC>
  {
    BGRButton() ;
    virtual void OnCheck(bool value) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_x;
      mod = KMOD_CTRL;
      return true;
    }
  };

  template<class GC>
  struct LogButton : public AbstractGridCheckbox<GC>
  {
    LogButton() ;
    virtual void OnCheck(bool value) ;
    virtual bool GetKeyboardAccelerator(u32 & keysym, u32 & mod)
    {
      keysym = SDLK_l;
      mod = 0;
      return true;
    }
  };

} /* namespace MFM */

#include "AbstractGUIDriverButtons.tcc"

#endif /* ABSTRACTGUIDRIVERBUTTONS_H */
