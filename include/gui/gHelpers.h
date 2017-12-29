//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_UI_H
#define LOGICON_UI_H

#include <imgui.h>
#include <imgui_internal.h>

namespace Logicon {

    /*
     * Custom types for 2D, 4D vectors and Rectangle based on ImGui's respective types
     */

    struct UIVec2 {
        float x, y;
        UIVec2() { x = y = 0.0f; }
        UIVec2(float _x, float _y) { x = _x; y = _y; }
        UIVec2(const ImVec2 &vec2) { x = vec2.x; y = vec2.y; }

        operator ImVec2() const { return ImVec2(x, y); }
    };

    static inline UIVec2 operator+(const UIVec2& lhs, const UIVec2& rhs) { return UIVec2(lhs.x+rhs.x, lhs.y+rhs.y); }
    static inline UIVec2 operator-(const UIVec2& lhs, const UIVec2& rhs) { return UIVec2(lhs.x-rhs.x, lhs.y-rhs.y); }
    static inline UIVec2 operator*(const UIVec2& lhs, const float& rat) { return UIVec2(lhs.x*rat, lhs.y*rat); }
    static inline UIVec2 operator*(const float& rat, const UIVec2& rhs) { return UIVec2(rhs.x*rat, rhs.y*rat); }
    static inline UIVec2 operator/(const UIVec2& lhs, const float& rat) { return UIVec2(lhs.x/rat, lhs.y/rat); }

    static inline UIVec2 operator+(const UIVec2& lhs, const ImVec2& rhs) { return lhs + UIVec2(rhs); }
    static inline UIVec2 operator-(const UIVec2& lhs, const ImVec2& rhs) { return lhs - UIVec2(rhs); }

    struct UIVec4 {
        float x, y, z, w;
        UIVec4() { x = y = z = w = 0.0f; }
        UIVec4(float _x, float _y, float _z, float _w) { x = _x; y = _y; z = _z; w = _w; }
        UIVec4(const ImVec4 &vec4) { x = vec4.x; y = vec4.y; z = vec4.z; w = vec4.w; }

        operator ImVec4() const { return ImVec4(x, y, z, w); }
    };

    struct UIRect
    {
        UIVec2      Min;    // Upper-left
        UIVec2      Max;    // Lower-right

        UIRect()                                        : Min(FLT_MAX,FLT_MAX), Max(-FLT_MAX,-FLT_MAX)  {}
        UIRect(const UIVec2& min, const UIVec2& max)    : Min(min), Max(max)                            {}
        UIRect(const UIVec4& v)                         : Min(v.x, v.y), Max(v.z, v.w)                  {}
        UIRect(const ImVec2& min, const ImVec2& max)    : Min(min), Max(max)                            {}
        UIRect(const ImVec4& v)                         : Min(v.x, v.y), Max(v.z, v.w)                  {}
        UIRect(float x1, float y1, float x2, float y2)  : Min(x1, y1), Max(x2, y2)                      {}

        UIVec2      getCenter() const               { return UIVec2((Min.x+Max.x)*0.5f, (Min.y+Max.y)*0.5f); }
        UIVec2      getSize() const                 { return UIVec2(Max.x-Min.x, Max.y-Min.y); }
        float       getWidth() const                { return Max.x-Min.x; }
        float       getHeight() const               { return Max.y-Min.y; }
        UIVec2      getTL() const                   { return Min; }                   // Top-left
        UIVec2      getTR() const                   { return UIVec2(Max.x, Min.y); }  // Top-right
        UIVec2      getBL() const                   { return UIVec2(Min.x, Max.y); }  // Bottom-left
        UIVec2      getBR() const                   { return Max; }                   // Bottom-right
        bool        contains(const UIVec2& p) const { return p.x >= Min.x     && p.y >= Min.y     && p.x < Max.x     && p.y < Max.y; }
        bool        contains(const UIRect& r) const { return r.Min.x >= Min.x && r.Min.y >= Min.y && r.Max.x < Max.x && r.Max.y < Max.y; }
        bool        overlaps(const UIRect& r) const { return r.Min.y < Max.y  && r.Max.y > Min.y  && r.Min.x < Max.x && r.Max.x > Min.x; }
        void        add(const UIVec2& rhs)          { if (Min.x > rhs.x)     Min.x = rhs.x;     if (Min.y > rhs.y) Min.y = rhs.y;         if (Max.x < rhs.x) Max.x = rhs.x;         if (Max.y < rhs.y) Max.y = rhs.y; }
        void        add(const UIRect& rhs)          { if (Min.x > rhs.Min.x) Min.x = rhs.Min.x; if (Min.y > rhs.Min.y) Min.y = rhs.Min.y; if (Max.x < rhs.Max.x) Max.x = rhs.Max.x; if (Max.y < rhs.Max.y) Max.y = rhs.Max.y; }
        void        expand(const float amount)      { Min.x -= amount;   Min.y -= amount;   Max.x += amount;   Max.y += amount; }
        void        expand(const UIVec2& amount)    { Min.x -= amount.x; Min.y -= amount.y; Max.x += amount.x; Max.y += amount.y; }
        void        translate(const UIVec2& v)      { Min.x += v.x; Min.y += v.y; Max.x += v.x; Max.y += v.y; }
        void        clipWith(const UIRect& clip)    { if (Min.x < clip.Min.x) Min.x = clip.Min.x; if (Min.y < clip.Min.y) Min.y = clip.Min.y; if (Max.x > clip.Max.x) Max.x = clip.Max.x; if (Max.y > clip.Max.y) Max.y = clip.Max.y; }
        void        floor()                         { Min.x = (float)(int)Min.x; Min.y = (float)(int)Min.y; Max.x = (float)(int)Max.x; Max.y = (float)(int)Max.y; }
        UIVec2      getClosestPoint(UIVec2 p, bool on_edge) const
        {
            if (!on_edge && contains(p))
                return p;
            if (p.x > Max.x) p.x = Max.x;
            else if (p.x < Min.x) p.x = Min.x;
            if (p.y > Max.y) p.y = Max.y;
            else if (p.y < Min.y) p.y = Min.y;
            return p;
        }

        operator ImRect() const { return ImRect(Min, Max); }
    };


    namespace UI {
        const int MARGIN = 16;
        const int MENU_WIDGET_HEIGHT = 64;
        const int FOOTER_WIDGET_HEIGHT = 32;
        const int BLOCKS_WIDGET_WIDTH = 300;
    }

}  // namespace Logicon

#endif //LOGICON_UI_H
