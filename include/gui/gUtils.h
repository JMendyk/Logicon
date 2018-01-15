//
// Created by JMendyk on 28.12.17.
//

#ifndef LOGICON_UI_H
#define LOGICON_UI_H

#include "types.h"
#include <imgui.h>
#include <imgui_internal.h>

namespace Logicon {

    /**
     * Utilities for graphics classes
     */

    /// ImVec2 operators
    static inline ImVec2 operator+(const ImVec2 &lhs, const ImVec2 &rhs) { return {lhs.x + rhs.x, lhs.y + rhs.y}; }


    namespace UI {

        // TODO: make all extern and init in App.init()
        // @formatter:off
        const float     MARGIN                          = 16.0;                                                         /// Margin between elements
        const float     MENU_WIDGET_HEIGHT              = 64.0;
        const float     MENU_WIDGET_BUTTON_SIZE         = 48.0;
        const ImColor   MENU_WIDGET_BUTTON_FG_COLOR     = ImColor(229, 229, 229);                                       /// Foreground color for buttons
        const float     BLOCKS_WIDGET_WIDTH             = 300.0;
        const float     FOOTER_WIDGET_HEIGHT            = 32.0;

        const float     CANVAS_GRID_SIZE                = 32.0;                                                         /// Basic square size on canvas

        const int CANVAS_CHANNEL_COUNT = 6;                                                            /// Like z-index, that many layers to draw
        const int       DEFAULT_GBLOCK_CHANNEL          = 0;
        const int DEFAULT_CONNECTION_CHANNEL = 1;
        const int DEFAULT_GPORT_CHANNEL = 2;
        const int ACTIVE_GBLOCK_CHANNEL = 3;
        const int ACTIVE_GPORT_CHANNEL = 4;
        const int ACTIVE_CONNECTION_CHANNEL = 5;

        const float     GPORT_PADDING                   = CANVAS_GRID_SIZE / 8.0;
        const float     GPORT_SIZE                      = CANVAS_GRID_SIZE - 2*GPORT_PADDING;                           /// Dimensions for GPort button
        const float BEZIER_CONTROL_DISTANCE = UI::CANVAS_GRID_SIZE *
                                              4.0;                                   /// How far in canvas coordinates is control point away from gPort
        const float     BEZIER_THICKNESS                = 4.0;                                                          /// Thickness of bezier lines
        const int BEZIER_SEGMENTS = 20;                                                           /// Higher = smoother bezier

        const ImColor ON_STATE_COLOR = ImColor(255, 195, 17);
        const ImColor OFF_STATE_COLOR = ImColor(68, 74, 119);
        const ImColor DEFAULT_GBLOCK_COLOR = ImColor(255, 255, 255, 200);                                  /// Default
        const ImColor DIMMED_GBLOCK_COLOR = ImColor(100, 100, 100, 200);
        const ImColor DEFAULT_GPORT_COLOR = ImColor(68, 75, 119);
        const ImColor DIMMED_GPORT_COLOR = ImColor(34, 40, 61, 200);

        const std::string GPORT_NONE_HOVERED = "-";                                                          /// value for GPORT_CURRENTLY_HOVERED flag while non is hovered
        // @formatter:on

        /// Represents 2D vector for UI purposes
        struct Vec2 {
            float x, y;

            Vec2() : x(0.0f), y(0.0f) {};

            Vec2(float x, float y) : x(x), y(y) {};

            Vec2(const ImVec2 &vec2) : x(vec2.x), y(vec2.y) {};

            operator ImVec2() const { return ImVec2(x, y); };
        };

        const float Vec2_PRECISION = 0.0001;

        /// Comparison of vectors
        static inline bool operator==(const Vec2 &lhs, const Vec2 &rhs) {
            return fabsf(lhs.x - rhs.x) < Vec2_PRECISION
                   && fabsf(lhs.y - rhs.y) < Vec2_PRECISION;
        }

        static inline bool operator!=(const Vec2 &lhs, const Vec2 &rhs) { return !(lhs == rhs); }

        /// Add and subtract vectors
        static inline Vec2 operator+(const Vec2 &lhs, const Vec2 &rhs) { return Vec2(lhs.x + rhs.x, lhs.y + rhs.y); }

        static inline Vec2 operator-(const Vec2 &lhs, const Vec2 &rhs) { return Vec2(lhs.x - rhs.x, lhs.y - rhs.y); }

        /// Scale vector with rat as scale factor as rhs
        static inline Vec2 operator*(const Vec2 &lhs, const float &rat) { return Vec2(lhs.x * rat, lhs.y * rat); }

        static inline Vec2 operator/(const Vec2 &lhs, const float &rat) { return Vec2(lhs.x / rat, lhs.y / rat); }

        /// Add and subtract vectors with Imgui::ImVect2 as rhs
        static inline Vec2 operator+(const Vec2 &lhs, const ImVec2 &rhs) { return lhs + Vec2(rhs); }

        static inline Vec2 operator-(const Vec2 &lhs, const ImVec2 &rhs) { return lhs - Vec2(rhs); }

        /// Represents UI rectangle, or rather AABB
        struct Rect {
            Vec2 upperLeftCorner;
            Vec2 lowerRightCorner;

            Rect() : upperLeftCorner(FLT_MAX, FLT_MAX), lowerRightCorner(-FLT_MAX, -FLT_MAX) {}

            Rect(const Vec2 &min, const Vec2 &max) : upperLeftCorner(min), lowerRightCorner(max) {}

            Rect(const ImVec2 &min, const ImVec2 &max) : upperLeftCorner(min), lowerRightCorner(max) {}

            Rect(const ImVec4 &v) : upperLeftCorner(v.x, v.y), lowerRightCorner(v.z, v.w) {}

            Rect(float x1, float y1, float x2, float y2) : upperLeftCorner(x1, y1), lowerRightCorner(x2, y2) {}

            Vec2 getCenter() const {
                return Vec2((upperLeftCorner.x + lowerRightCorner.x) * 0.5f,
                            (upperLeftCorner.y + lowerRightCorner.y) * 0.5f);
            }

            Vec2 getSize() const {
                return Vec2(lowerRightCorner.x - upperLeftCorner.x, lowerRightCorner.y - upperLeftCorner.y);
            }

            float getWidth() const { return lowerRightCorner.x - upperLeftCorner.x; }

            float getHeight() const { return lowerRightCorner.y - upperLeftCorner.y; }

            Vec2 getTopLeft() const { return upperLeftCorner; }

            Vec2 getTopRight() const { return Vec2(lowerRightCorner.x, upperLeftCorner.y); }

            Vec2 getBottomLeft() const { return Vec2(upperLeftCorner.x, lowerRightCorner.y); }

            Vec2 getBottomRight() const { return lowerRightCorner; }

            /// @brief Checks if point represented by argument vector is inside this rectangle excluding right and bottom edges.
            bool contains(const Vec2 &p) const {
                return p.x >= upperLeftCorner.x && p.y >= upperLeftCorner.y &&
                       p.x < lowerRightCorner.x && p.y < lowerRightCorner.y;
            }

            /// @brief Checks if rectangle is completely inside this rectangle excluding right and bottom edges.
            bool contains(const Rect &r) const {
                return r.upperLeftCorner.x >= upperLeftCorner.x && r.upperLeftCorner.y >= upperLeftCorner.y &&
                       r.lowerRightCorner.x < lowerRightCorner.x && r.lowerRightCorner.y < lowerRightCorner.y;
            }

            /// @brief Checks if rectangle overlaps with this rectangle.
            bool overlaps(const Rect &r) const {
                return r.upperLeftCorner.y < lowerRightCorner.y && r.lowerRightCorner.y > upperLeftCorner.y &&
                       r.upperLeftCorner.x < lowerRightCorner.x && r.lowerRightCorner.x > upperLeftCorner.x;
            }

            /// @brief Sets this rectangle to minimal bounding box of itself and passed point combined.
            void add(const Vec2 &rhs) {
                if (upperLeftCorner.x > rhs.x) upperLeftCorner.x = rhs.x;
                if (upperLeftCorner.y > rhs.y) upperLeftCorner.y = rhs.y;
                if (lowerRightCorner.x < rhs.x) lowerRightCorner.x = rhs.x;
                if (lowerRightCorner.y < rhs.y) lowerRightCorner.y = rhs.y;
            }

            /// @brief Sets this rectangle to minimal bounding box of itself and passed rectangle combined.
            void add(const Rect &rhs) {
                if (upperLeftCorner.x > rhs.upperLeftCorner.x) upperLeftCorner.x = rhs.upperLeftCorner.x;
                if (upperLeftCorner.y > rhs.upperLeftCorner.y) upperLeftCorner.y = rhs.upperLeftCorner.y;
                if (lowerRightCorner.x < rhs.lowerRightCorner.x) lowerRightCorner.x = rhs.lowerRightCorner.x;
                if (lowerRightCorner.y < rhs.lowerRightCorner.y) lowerRightCorner.y = rhs.lowerRightCorner.y;
            }

            /// @brief Expands x and y by fixed amount from the center.
            void expand(const float amount) {
                upperLeftCorner.x -= amount;
                upperLeftCorner.y -= amount;
                lowerRightCorner.x += amount;
                lowerRightCorner.y += amount;
            }

            /// @brief Expands x and y by corresponding values of the vector.
            void expand(const Vec2 &amount) {
                upperLeftCorner.x -= amount.x;
                upperLeftCorner.y -= amount.y;
                lowerRightCorner.x += amount.x;
                lowerRightCorner.y += amount.y;
            }

            /// @brief Translates this rectangle by given vector.
            void translate(const Vec2 &v) {
                upperLeftCorner.x += v.x;
                upperLeftCorner.y += v.y;
                lowerRightCorner.x += v.x;
                lowerRightCorner.y += v.y;
            }

            /// @brief This recangle to geometrical intersection of both.
            void clipWith(const Rect &clip) {
                if (upperLeftCorner.x < clip.upperLeftCorner.x) upperLeftCorner.x = clip.upperLeftCorner.x;
                if (upperLeftCorner.y < clip.upperLeftCorner.y) upperLeftCorner.y = clip.upperLeftCorner.y;
                if (lowerRightCorner.x > clip.lowerRightCorner.x) lowerRightCorner.x = clip.lowerRightCorner.x;
                if (lowerRightCorner.y > clip.lowerRightCorner.y) lowerRightCorner.y = clip.lowerRightCorner.y;
            }

            /// @brief Sets coordinates of this rectangle to whole values.
            void floor() {
                upperLeftCorner.x = (float) (int) upperLeftCorner.x;
                upperLeftCorner.y = (float) (int) upperLeftCorner.y;
                lowerRightCorner.x = (float) (int) lowerRightCorner.x;
                lowerRightCorner.y = (float) (int) lowerRightCorner.y;
            }

            /// @brief Returns point inside this rectangle closest to given point including all edges.
            Vec2 getClosestPoint(Vec2 p, bool on_edge) const {
                if (!on_edge && contains(p))
                    return p;
                if (p.x > lowerRightCorner.x) p.x = lowerRightCorner.x;
                else if (p.x < upperLeftCorner.x) p.x = upperLeftCorner.x;
                if (p.y > lowerRightCorner.y) p.y = lowerRightCorner.y;
                else if (p.y < upperLeftCorner.y) p.y = upperLeftCorner.y;
                return p;
            }

            operator ImRect() const { return ImRect(upperLeftCorner, lowerRightCorner); }
        };

        static inline Rect operator+(const Rect &lhs, const Vec2 &rhs) {
            return Rect(lhs.upperLeftCorner + rhs, lhs.lowerRightCorner + rhs);
        }

        /**
         * @brief Rounds points in a box with sizes of step around Integer coordinates
         * @param vec given point
         * @param step
         * @return
         */
        inline static Vec2 steppify(Vec2 vec, Vec2 step) {
            return {
                    roundf(vec.x / step.x) * step.x,
                    roundf(vec.y / step.y) * step.y
            };
        };

        inline static Vec2 steppify(Vec2 vec, float step) {
            return steppify(vec, Vec2(step, step));
        };

        static Rect steppify(Rect rect, Vec2 step) {
            return {
                    UI::steppify(rect.upperLeftCorner, step),
                    UI::steppify(rect.upperLeftCorner, step) + rect.getSize()
            };
        };

        inline static float toGridCoordinates(float coord) { return coord / CANVAS_GRID_SIZE; }

        inline static float toCanvasCoordinates(float coord) { return coord * CANVAS_GRID_SIZE; }

        inline static Vec2 toGridCoordinates(Vec2 vec) { return vec / CANVAS_GRID_SIZE; }

        inline static Rect toGridCoordinates(Rect rect) {
            return {rect.upperLeftCorner / CANVAS_GRID_SIZE, rect.lowerRightCorner / CANVAS_GRID_SIZE};
        }

        inline static Vec2 toCanvasCoordinates(Vec2 vec) { return vec * CANVAS_GRID_SIZE; }

        inline static Rect toCanvasCoordinates(Rect rect) {
            return {rect.upperLeftCorner * CANVAS_GRID_SIZE, rect.lowerRightCorner * CANVAS_GRID_SIZE};
        }

        // TODO: make extern and init in App::init()
        static Vec2 gPortInputPositions[GATE_TYPE_COUNT][2]                                                             /// Positions of inputs in gates
                {{Vec2(0, 1), {}},              // NOT
                 {Vec2(0, 1), {}},              // DELAY
                 {Vec2(0, 1), {}},              // SWITCH_ON
                 {Vec2(0, 1), {}},              // SWITCH_OFF
                 {Vec2(0, 0), Vec2(0, 2)},      // AND
                 {Vec2(0, 0), Vec2(0, 2)},      // OR
                 {Vec2(0, 0), Vec2(0, 2)},      // XOR
                 {Vec2(0, 0), Vec2(0, 2)},      // NAND
                 {Vec2(0, 0), Vec2(0, 2)},      // NOR
                 {Vec2(0, 0), Vec2(0, 2)},      // XNOR
                 {{},         {}},              // INPUT_ON
                 {{},         {}}               // INPUT_OFF
                };

        static Vec2 gPortOutputPositions[GATE_TYPE_COUNT][1]                                                            /// Positions of outputs in gates
                {{Vec2(4, 1)},                  // NOT
                 {Vec2(4, 1)},                  // DELAY
                 {Vec2(4, 1)},                  // SWITCH_ON
                 {Vec2(4, 1)},                  // SWITCH_OFF
                 {Vec2(4, 1)},                  // AND
                 {Vec2(4, 1)},                  // OR
                 {Vec2(4, 1)},                  // XOR
                 {Vec2(4, 1)},                  // NAND
                 {Vec2(4, 1)},                  // NOR
                 {Vec2(4, 1)},                  // XNOR
                 {Vec2(2, 1)},                  // CLOCK
                 {Vec2(2, 1)},                  // INPUT_ON
                 {Vec2(2, 1)},                  // INPUT_OFF
                };

        static Vec2 gBlockDimensions[GATE_TYPE_COUNT]
                {{Vec2(5, 3)},                  // NOT
                 {Vec2(5, 3)},                  // DELAY
                 {Vec2(5, 3)},                  // SWITCH_ON
                 {Vec2(5, 3)},                  // SWITCH_OFF
                 {Vec2(5, 3)},                  // AND
                 {Vec2(5, 3)},                  // OR
                 {Vec2(5, 3)},                  // XOR
                 {Vec2(5, 3)},                  // NAND
                 {Vec2(5, 3)},                  // NOR
                 {Vec2(5, 3)},                  // XNOR
                 {Vec2(3, 3)},                  // CLOCK
                 {Vec2(3, 3)},                  // INPUT_ON
                 {Vec2(3, 3)},                  // INPUT_OFF
                };
    } // namespace UI

}  // namespace Logicon

#endif //LOGICON_UI_H
