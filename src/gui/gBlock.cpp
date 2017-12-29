//
// Created by JMendyk on 29.12.17.
//

#include "gui/gBlock.h"

namespace Logicon {

    GBlock::GBlock(const UIVec2 &size, const Texture &texture, const Data &data)
        : size(size), texture(texture), data(data), is_dragged(false) {}

    GBlock::GBlock(GBlock *other) {
        if (this == other)
            return;

        this->size = other->size;
        this->texture = other->texture;
        this->data = other->data;
        this->is_dragged = other->is_dragged;
        // TODO: Copy parent, id, pos, etc. ?
    }

    void GBlock::place(std::shared_ptr<IGCircuit> parent, ID id, UIVec2 pos) {
        this->parent = parent;
        this->id = id;
        this->pos = pos;
    }

    void GBlock::render() {
        UIVec4 color = UIVec4(1, 1, 1, 1);

        {
            /*
             * Dragging GBlock
             */
            if (is_dragged) {
                if (ImGui::IsMouseDown(0)) {
                    drag_pos = drag_pos + ImGui::GetIO().MouseDelta;
                    UIVec2 drag_pos_gridded = steppify(drag_pos, UIVec2(UI::CANVAS_GRID_SIZE, UI::CANVAS_GRID_SIZE));
                    if (parent->i_isOccupied(id, UIRect(drag_pos_gridded, drag_pos_gridded + size))) {
                        color = UIVec4(1, 0, 0, 1);
                    } else {
                        color = UIVec4(0, 1, 0, 1);
                    }
                }
                if (ImGui::IsMouseReleased(0)) {
                    UIVec2 drag_pos_gridded = steppify(drag_pos, UIVec2(UI::CANVAS_GRID_SIZE, UI::CANVAS_GRID_SIZE));
                    if (!parent->i_isOccupied(id, UIRect(drag_pos_gridded, drag_pos_gridded + size))
                        && parent->i_move(id, drag_pos_gridded)) {
                        pos = drag_pos_gridded;
                    }
                    is_dragged = false;
                }
            }
        }

        /*
         * If GBlock is dragged, we want it to draw above all other GBlocks
         */
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(is_dragged ? UI::ACTIVE_GBLOCK_CHANNEL : UI::DEFAULT_GBLOCK_CHANNEL);
        ImGui::PushID(id);
        //ImGui::BeginGroup(); // TODO: Creating group causes issues when dragging, needs investigation before usage
        {
            /*
             * Rendering GBlock
             */
            ImGui::SetCursorPos(is_dragged ? drag_pos : pos);
            if(ImGui::ImageButton((ImTextureID) texture.textureId,
                               size,
                               UIVec2(0, 0),
                               UIVec2(1, 1),
                               0,
                               UIVec4(0, 0, 0, 0),
                               color)) {
            }

        }
        //ImGui::EndGroup();
        ImGui::PopID();
        ImGui::GetWindowDrawList()->ChannelsSetCurrent(UI::DEFAULT_GBLOCK_CHANNEL);

        if (ImGui::IsItemHovered() && ImGui::IsMouseClicked(0)) {
            is_dragged = true;
            drag_pos = pos;
        }

    }

    void GBlock::update() {
        // TODO: Implement
    }

    Port GBlock::getPortAt(UIVec2 port_pos) {
        // TODO: Implement
    }

    ID GBlock::getId() const {
        return id;
    }

    UIRect GBlock::getRect() const {
        UIVec2 p = is_dragged ? drag_pos : pos;
        return UIRect(p, p + size);
    }

} // namespace Logicon