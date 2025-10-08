#pragma once

#include <string>

#include "core/gpu/mesh.h"
#include "utils/glm_utils.h"


namespace objectGenerator2D
{

    // Create geometrical froms
    Mesh* CreateSquare(const std::string& name, glm::vec3 leftBottomCornerCoordonates, float length, float z, glm::vec3 color, bool fill = false);

    Mesh* CreateRectangle(const std::string& name, glm::vec3 leftBottomCornerCoordonates, float width, float height, float z, glm::vec3 color, bool fill = false);
   
    Mesh* CreateShootingDiamond(const std::string& name, glm::vec3 leftBottomCornerCoordonates, float diamondXLength, float diamondYLenght, float z, glm::vec3 color);

    Mesh* CreateStar(const std::string& name, glm::vec3 center, float radius, float z, glm::vec3 color);

    Mesh* CreateHex(const std::string& name, glm::vec3 center, float radius, float zIn, float zOut, glm::vec3 colorIn, glm::vec3 colorOut);

    Mesh* CreateHeart(const std::string& name, glm::vec3 leftBottomCornerCoordonates, float sizeUnit, float z, glm::vec3 color);
}
