  #include "objectGenerator2D.h"

#include <vector>

#include "core/engine.h"
#include "utils/gl_utils.h"

//FUNCTIONS TO CREATE EVERY VISUAL BY GIVING THE SIZE, COLOR, HEIGHT, etc.

Mesh* objectGenerator2D::CreateSquare(
    const std::string& name,
    glm::vec3 leftBottomCornerCoordonates,
    float length,
    float z,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 lbcorner = leftBottomCornerCoordonates;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(lbcorner + glm::vec3(0, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(length, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(length, length, z), color),
        VertexFormat(lbcorner + glm::vec3(0, length, z), color)
    };

    Mesh* square = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        square->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    square->InitFromData(vertices, indices);
    return square;
}

Mesh* objectGenerator2D::CreateRectangle(
    const std::string& name,
    glm::vec3 leftBottomCornerCoordonates,
    float width,
    float height,
    float z,
    glm::vec3 color,
    bool fill)
{
    glm::vec3 lbcorner = leftBottomCornerCoordonates;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(lbcorner + glm::vec3(0, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(width, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(width, height, z), color),
        VertexFormat(lbcorner + glm::vec3(0, height, z), color)
    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3 };

    if (!fill) {
        rectangle->SetDrawMode(GL_LINE_LOOP);
    }
    else {
        // Draw 2 triangles. Add the remaining 2 indices
        indices.push_back(0);
        indices.push_back(2);
    }

    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* objectGenerator2D::CreateShootingDiamond(
    const std::string& name,
    glm::vec3 leftBottomCornerCoordonates,
    float diamondXLength,
    float diamondYLength,
    float z,
    glm::vec3 color)
{
    glm::vec3 lbcorner = leftBottomCornerCoordonates;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength, diamondYLength / 2, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, diamondYLength, z), color),

        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, diamondYLength, z), color),
        VertexFormat(lbcorner + glm::vec3(0, diamondYLength / 2, z), color),

        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, (diamondYLength / 10) * 4, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2 + diamondYLength / 2, (diamondYLength / 10) * 4, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2 + diamondYLength / 2, (diamondYLength / 10) * 6, z), color),

        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2 + diamondYLength / 2, (diamondYLength / 10) * 6, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2 + diamondYLength / 2, (diamondYLength / 10) * 4, z), color),
        VertexFormat(lbcorner + glm::vec3(diamondXLength / 2, (diamondYLength / 10) * 6, z), color)

    };

    Mesh* rectangle = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
    
    rectangle->SetDrawMode(GL_TRIANGLES);
    
    rectangle->InitFromData(vertices, indices);
    return rectangle;
}

Mesh* objectGenerator2D::CreateStar(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float z,
    glm::vec3 color)
{
    //Calculated with GeoGebra:
    //a, b, c, d, e are the extreme points of the star and 
    //the lilRadius is where the inside points are located

    float lilRadius = radius * 38.6 / 100; 
    float aAngle = 18 * M_PI / 180;
    float bAngle = 90 * M_PI / 180;
    float cAngle = 162 * M_PI / 180;
    float dAngle = 234 * M_PI / 180;
    float eAngle = 306 * M_PI / 180;

    VertexFormat O = VertexFormat(center + glm::vec3(0, 0, z), color);
    VertexFormat A = VertexFormat(center + glm::vec3(radius * cos(aAngle), radius * sin(aAngle), z), color);
    VertexFormat B = VertexFormat(center + glm::vec3(radius * cos(bAngle), radius * sin(bAngle), z), color);
    VertexFormat C = VertexFormat(center + glm::vec3(radius * cos(cAngle), radius * sin(cAngle), z), color);
    VertexFormat D = VertexFormat(center + glm::vec3(radius * cos(dAngle), radius * sin(dAngle), z), color);
    VertexFormat E = VertexFormat(center + glm::vec3(radius * cos(eAngle), radius * sin(eAngle), z), color);

    VertexFormat F = VertexFormat(center + glm::vec3(lilRadius * cos((aAngle + bAngle) / 2), lilRadius * sin((aAngle + bAngle) / 2), z), color);
    VertexFormat G = VertexFormat(center + glm::vec3(lilRadius * cos((bAngle + cAngle) / 2), lilRadius * sin((bAngle + cAngle) / 2), z), color);
    VertexFormat H = VertexFormat(center + glm::vec3(lilRadius * cos((cAngle + dAngle) / 2), lilRadius * sin((cAngle + dAngle) / 2), z), color);
    VertexFormat I = VertexFormat(center + glm::vec3(lilRadius * cos((dAngle + eAngle) / 2), lilRadius * sin((dAngle + eAngle) / 2), z), color);
    VertexFormat J = VertexFormat(center + glm::vec3(lilRadius * cos((eAngle + ((18 + 360) * M_PI / 180)) / 2), lilRadius * sin((eAngle + ((18 + 360) * M_PI / 180)) / 2), z), color);

    std::vector<VertexFormat> vertices =
    {
        // The triangles:
        A, F, J,
        B, G, F,
        C, G, H,
        D, I, H,
        I, E, J,

        O, I, J,
        O, J, F,
        O, G, F,
        O, H, G,
        O, I, H
    };

    Mesh* star = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
    17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29};

    star->SetDrawMode(GL_TRIANGLES);

    star->InitFromData(vertices, indices);
    return star;
}

Mesh* objectGenerator2D::CreateHex(
    const std::string& name,
    glm::vec3 center,
    float radius,
    float zIn,
    float zOut,
    glm::vec3 colorIn,
    glm::vec3 colorOut)
{
    float theta = (360 / 6) * M_PI / 180;
    float lilRadius = radius * 7 / 10;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(theta), radius * sin(theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(2 * theta), radius * sin(2 * theta), zOut), colorOut),

        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(2 * theta), radius * sin(2 * theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(3 * theta), radius * sin(3 * theta), zOut), colorOut),

        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(3 * theta), radius * sin(3 * theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(4 * theta), radius * sin(4 * theta), zOut), colorOut),

        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(4 * theta), radius * sin(4 * theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(5 * theta), radius * sin(5 * theta), zOut), colorOut),

        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(5 * theta), radius * sin(5 * theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(6 * theta), radius * sin(6 * theta), zOut), colorOut),

        VertexFormat(center + glm::vec3(0, 0, zOut) , colorOut),
        VertexFormat(center + glm::vec3(radius * cos(6 * theta), radius * sin(6 * theta), zOut), colorOut),
        VertexFormat(center + glm::vec3(radius * cos(theta), radius * sin(theta), zOut), colorOut),


        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(theta), lilRadius * sin(theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(2 * theta), lilRadius * sin(2 * theta), zIn), colorIn),

        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(2 * theta), lilRadius * sin(2 * theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(3 * theta), lilRadius * sin(3 * theta), zIn), colorIn),

        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(3 * theta), lilRadius * sin(3 * theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(4 * theta), lilRadius * sin(4 * theta), zIn), colorIn),

        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(4 * theta), lilRadius * sin(4 * theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(5 * theta), lilRadius * sin(5 * theta), zIn), colorIn),

        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(5 * theta), lilRadius * sin(5 * theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(6 * theta), lilRadius * sin(6 * theta), zIn), colorIn),

        VertexFormat(center + glm::vec3(0, 0, zIn) , colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(6 * theta), lilRadius * sin(6 * theta), zIn), colorIn),
        VertexFormat(center + glm::vec3(lilRadius * cos(theta), lilRadius * sin(theta), zIn), colorIn)
    };

    Mesh* hex = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16,
        17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35};

    hex->SetDrawMode(GL_TRIANGLES);

    hex->InitFromData(vertices, indices);
  
    return hex;
}

Mesh* objectGenerator2D::CreateHeart(
    const std::string& name,
    glm::vec3 leftBottomCornerCoordonates,
    float sizeUnit,
    float z,
    glm::vec3 color)
{
    glm::vec3 lbcorner = leftBottomCornerCoordonates;

    std::vector<VertexFormat> vertices =
    {
        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 0, z), color),
        VertexFormat(lbcorner + glm::vec3(6 * sizeUnit, 3 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(6 * sizeUnit, 3 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(6 * sizeUnit, 5 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(6 * sizeUnit, 5 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(5 * sizeUnit, 6 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(5 * sizeUnit, 6 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(4 * sizeUnit, 6 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(0, 5 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(1 * sizeUnit, 6 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(2 * sizeUnit, 6 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(1 * sizeUnit, 6 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(0, 3 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(0, 5 * sizeUnit, z), color),

        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 4 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(0, 3 * sizeUnit, z), color),
        VertexFormat(lbcorner + glm::vec3(3 * sizeUnit, 0, z), color),
    };

    Mesh* heart = new Mesh(name);
    std::vector<unsigned int> indices = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};

    heart->SetDrawMode(GL_TRIANGLES);

    heart->InitFromData(vertices, indices);
    return heart;
}

