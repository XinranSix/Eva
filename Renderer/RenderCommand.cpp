/**
 * @file    :   RenderCommand.cpp
 * @date    :   2023/06/30 19:07:27
 * @author  :   yaojie
 * @version :   1.0
 */

#include "RenderCommand.h"
#include "OpenGLRendererAPI.h"

namespace Eva {

    RendererAPI *RenderCommand::s_RendererAPI = new OpenGLRendererAPI;
}
