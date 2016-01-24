/**
 @file      GraphicsCentreEx.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

#pragma once
#ifndef __TYGA_GRAPHICS_CENTRE_EX__
#define __TYGA_GRAPHICS_CENTRE_EX__

#include "GraphicsCentre.hpp"
#include <vector>

namespace tyga
{

struct GraphicsMesh
{
protected:
    std::vector<GraphicsMeshVertex> vertex_array;
    std::vector<unsigned int> element_array;
    std::string identifier;

    friend class GraphicsCentre;
    GraphicsMesh();
    GraphicsMesh(GraphicsMesh&&);

    std::weak_ptr<GraphicsMeshDelegate> delegate;
    int current_index;
};

struct GraphicsSprite
{
protected:
    std::vector<GraphicsSpriteVertex> vertex_array;
    std::string texture;

    friend class GraphicsCentre;
    GraphicsSprite();
    GraphicsSprite(GraphicsSprite&&);

    std::weak_ptr<GraphicsSpriteDelegate> delegate;
};

/*
struct GraphicsMaterialEx : public GraphicsMaterial
{
    int current_index;
};
*/

} // end namespace tyga

#endif
