// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#ifndef BUW_RENDERER_HPP
#define BUW_RENDERER_HPP

#include "color.hpp"
#include "pixel.hpp"
#include "ray.hpp"
#include "hitpoint.hpp"
#include "ppmwriter.hpp"
#include "scene.hpp"
#include "camera.hpp"
#include <string>
#include <glm/glm.hpp>
#include <limits>

class Renderer
{
public:
  Renderer(unsigned w, unsigned h, std::string const& file);

  unsigned getWidth() const;
  unsigned getHeight() const;
  std::string getFile() const;

  void render (Camera const& cam, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient);
  void write(Pixel const& p);


  inline std::vector<Color> const& color_buffer() const
  {
    return color_buffer_;
  }

private:
  unsigned width_;
  unsigned height_;
  std::vector<Color> color_buffer_;
  std::string filename_;
  PpmWriter ppm_;
};

Ray cam_ray(Pixel const& p, Camera const& cam);

Color trace(Ray const& ray, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient);

Color shade(HitPoint const& hit, std::vector<Light> const& lightVec, Color const& ambient);

#endif // #ifndef BUW_RENDERER_HPP
