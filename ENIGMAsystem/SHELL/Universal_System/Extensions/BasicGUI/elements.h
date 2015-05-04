/** Copyright (C) 2015 Harijs Grinbergs
***
*** This file is a part of the ENIGMA Development Environment.
***
*** ENIGMA is free software: you can redistribute it and/or modify it under the
*** terms of the GNU General Public License as published by the Free Software
*** Foundation, version 3 of the license or any later version.
***
*** This application and its source code is distributed AS-IS, WITHOUT ANY
*** WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS
*** FOR A PARTICULAR PURPOSE. See the GNU General Public License for more
*** details.
***
*** You should have received a copy of the GNU General Public License along
*** with this code. If not, see <http://www.gnu.org/licenses/>
**/

#ifndef BGUI_ELEMENTS_H
#define BGUI_ELEMENTS_H

#include <new> //Placement new

#include "sliders.h"
#include "buttons.h"
#include "toggles.h"
#include "groups.h"
#include "labels.h"
#include "windows.h"
#include "scrollbars.h"
#include "styles.h"
#include "skins.h"

#ifdef DEBUG_MODE
  #include <string>
  #include "libEGMstd.h"
  #include "Widget_Systems/widgets_mandatory.h"
  //This checks and returns an element
  #define get_elementv(element,clastype,entype,id,ret)\
    if (gui::gui_elements.find(id) == gui::gui_elements.end() || gui::gui_elements[id].type != entype) {\
      show_error("Attempting to use non-existing element " + std::to_string(id), false);\
      return ret;\
    }\
    clastype &element = gui::gui_elements[id];
  #define get_element(element,type,entype,id) get_elementv(element,type,entype,id,)
  
  //This only checks an element if it exists
  #define check_elementv(entype,id,ret) \
    if (gui::gui_elements.find(id) == gui::gui_elements.end() || gui::gui_elements[id].type != entype) {\
      show_error("Attempting to use non-existing element " + std::to_string(id), false);\
      return ret;\
    }\
   #define check_element(entype,id) check_elementv(entype,id,)
#else
  #define get_elementv(element,clastype,entype,id,ret)\
    clastype &element = gui::gui_elements[id];
  #define get_element(element,type,entype,id) get_elementv(element,type,entype,id,)
  #define check_elementv(entype,id,ret)
  #define check_element(entype,id) check_elementv(entype,id,)
#endif

namespace gui
{
  enum GUI_TYPE{
    ERROR = -1,
    BUTTON,
    TOGGLE,
    LABEL,
    SCROLLBAR,
    SLIDER,
    WINDOW,
    SKIN,
    STYLE,
    GROUP
  };

  class Element{
    public:
      GUI_TYPE type = GUI_TYPE::ERROR;
      unsigned int id = 0;

      //Unrestricted union is C++14
      union Data{
        Button button;
        Slider slider;
        Toggle toggle;
        Group group;
        Label label;
        Style style;
        Scrollbar scrollbar;
        Window window;
        Skin skin;

        Data() {}
        ~Data() {}
      };
      Data data;

      //Constructors
      inline Element(){ }

      inline Element(const Button &but){
        type = GUI_TYPE::BUTTON;
        new (&(data.button)) Button(but);
      }

      inline Element(const Slider &sli){
        type = GUI_TYPE::SLIDER;
        new (&(data.button)) Slider(sli);
      }

      inline Element(const Toggle &tog){
        type = GUI_TYPE::TOGGLE;
        new (&(data.toggle)) Toggle(tog);
      }

      inline Element(const Group &gro){
        type = GUI_TYPE::GROUP;
        new (&(data.group)) Group(gro);
      }
      
      inline Element(const Label &lab){
        type = GUI_TYPE::LABEL;
        new (&(data.label)) Label(lab);
      }
      
      inline Element(const Style &sty){
        type = GUI_TYPE::STYLE;
        new (&(data.style)) Style(sty);
      }

      inline Element(const Scrollbar &scr){
        type = GUI_TYPE::SCROLLBAR;
        new (&(data.scrollbar)) Scrollbar(scr);
      }
      
      inline Element(const Window &win){
        type = GUI_TYPE::WINDOW;
        new (&(data.window)) Window(win);
      }
      
      inline Element(const Skin &ski){
        type = GUI_TYPE::SKIN;
        new (&(data.skin)) Skin(ski);
      }     
      
      //Destructor
      inline ~Element(){
        switch (type){
          case GUI_TYPE::BUTTON:
            data.button.~Button();
            break;
          case GUI_TYPE::SLIDER:
            data.slider.~Slider();
            break;
          case GUI_TYPE::TOGGLE:
            data.toggle.~Toggle();
            break;
          case GUI_TYPE::GROUP:
            data.group.~Group();
            break;
          case GUI_TYPE::LABEL:
            data.label.~Label();
            break;
          case GUI_TYPE::STYLE:
            data.style.~Style();
            break;
          case GUI_TYPE::SCROLLBAR:
            data.scrollbar.~Scrollbar();
            break;
          case GUI_TYPE::WINDOW:
            data.window.~Window();
            break;
          case GUI_TYPE::SKIN:
            data.skin.~Skin();
            break;
          default:
            printf("Unknown element type or element type == ERROR!\n");
            break;
        }
      }

      //Accessor
      inline operator Button&(){
        if (type == GUI_TYPE::BUTTON){
          return data.button;
        }
        printf("Type is not a button! This is going to crash now!\n");
        return data.button;
      }

      inline operator Slider&(){
        if (type == GUI_TYPE::SLIDER){
          return data.slider;
        }
        printf("Type is not a slider! This is going to crash now!\n");
        return data.slider;
      }

      inline operator Toggle&(){
        if (type == GUI_TYPE::TOGGLE){
          return data.toggle;
        }
        printf("Type is not a toggle! This is going to crash now!\n");
        return data.toggle;
      }

      inline operator Group&(){
        if (type == GUI_TYPE::GROUP){
          return data.group;
        }
        printf("Type is not a group! This is going to crash now!\n");
        return data.group;
      }
      
      inline operator Label&(){
        if (type == GUI_TYPE::LABEL){
          return data.label;
        }
        printf("Type is not a label! This is going to crash now!\n");
        return data.label;
      }
      
      inline operator Style&(){
        if (type == GUI_TYPE::STYLE){
          return data.style;
        }
        printf("Type is not a style! This is going to crash now!\n");
        return data.style;
      }
      
      inline operator Scrollbar&(){
        if (type == GUI_TYPE::SCROLLBAR){
          return data.scrollbar;
        }
        printf("Type is not a scrollbar! This is going to crash now!\n");
        return data.scrollbar;
      }
      
      inline operator Window&(){
        if (type == GUI_TYPE::WINDOW){
          return data.window;
        }
        printf("Type is not a window! This is going to crash now!\n");
        return data.window;
      }
      
      inline operator Skin&(){
        if (type == GUI_TYPE::SKIN){
          return data.skin;
        }
        printf("Type is not a skin! This is going to crash now!\n");
        return data.skin;
      }

      //This is only needed if we have non-trivial copy constructors, but I leave it here for now
      inline Element(const Element & rhs){
        type = rhs.type;
        switch(type){
          case GUI_TYPE::BUTTON:
              new (&(data.button)) Button(rhs.data.button);
              break;
          case GUI_TYPE::SLIDER:
              new (&(data.slider)) Slider(rhs.data.slider);
              break;
          case GUI_TYPE::TOGGLE:
              new (&(data.toggle)) Toggle(rhs.data.toggle);
              break;
          case GUI_TYPE::GROUP:
              new (&(data.group)) Group(rhs.data.group);
              break;
          case GUI_TYPE::LABEL:
              new (&(data.label)) Label(rhs.data.label);
              break;
          case GUI_TYPE::STYLE:
              new (&(data.style)) Style(rhs.data.style);
              break;
          case GUI_TYPE::SCROLLBAR:
              new (&(data.scrollbar)) Scrollbar(rhs.data.scrollbar);
              break;
          case GUI_TYPE::WINDOW:
              new (&(data.window)) Window(rhs.data.window);
              break;
          case GUI_TYPE::SKIN:
              new (&(data.skin)) Skin(rhs.data.skin);
              break;
          default:
            printf("Unknown element type or element type == ERROR!\n");
            break;
        }
      }
	};
}
#endif