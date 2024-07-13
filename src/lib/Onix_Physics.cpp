#include "Onix_Physics.hpp"
bool Onix::IsCollided(const Collision2D_Rect_t& first, const Collision2D_Rect_t& second) {
    float first_min_x = first.pos_x - (first.body_width / 2);
    float first_max_x = first.pos_x + (first.body_width / 2);
    float first_min_y = first.pos_y - (first.body_height / 2);
    float first_max_y = first.pos_y + (first.body_height / 2);

        // Calculate AABB boundaries for second rectangle
    float second_min_x = second.pos_x - (second.body_width / 2);
    float second_max_x = second.pos_x + (second.body_width / 2);
    float second_min_y = second.pos_y - (second.body_height / 2);
    float second_max_y = second.pos_y + (second.body_height / 2);

        // Check for AABB overlap
    if (first_min_x < second_max_x && first_max_x > second_min_x &&
        first_min_y < second_max_y && first_max_y > second_min_y) {
        return true; // Collision detected
    } else {
        return false; // No collision
    }
}
