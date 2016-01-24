/**
 @file      GraphicsRendererProtocol.hpp
 @author    Tyrone Davison
 @date      September 2012
 */

// TODO: document me

#pragma once
#ifndef __TYGA_GRAPHICS_RENDERER_PROTOCOL__
#define __TYGA_GRAPHICS_RENDERER_PROTOCOL__

#include <tygra/WindowViewDelegate.hpp>
#include "GraphicsSceneProtocol.hpp"

namespace tyga
{
    
class GraphicsRendererProtocol : public tygra::WindowViewDelegate
{

public:

    virtual void
    setGraphicsScene(std::shared_ptr<tyga::GraphicsSceneProtocol> scene) =0;

};

} // end namespace tyga

#endif
