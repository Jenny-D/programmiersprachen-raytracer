// -----------------------------------------------------------------------------
// Copyright  : (C) 2014-2017 Andreas-C. Bernstein
// License    : MIT (see the file LICENSE)
// Maintainer : Andreas-C. Bernstein <andreas.bernstein@uni-weimar.de>
// Stability  : experimental
//
// Renderer
// -----------------------------------------------------------------------------

#define _USE_MATH_DEFINES
#include "renderer.hpp"

Renderer::Renderer(unsigned w, unsigned h, std::string const& file)
  : width_(w)
  , height_(h)
  , color_buffer_(w*h, Color(0.0f, 0.0f, 0.0f))
  , filename_(file)
  , ppm_(width_, height_)
{}

void Renderer::render(Camera const& cam, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient)
{
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);

      p.color = trace(cam_ray(p, cam.distance()), shapeVec, lightVec, ambient);

      write(p);
    }
  }
  ppm_.save(filename_);
}

Ray cam_ray(Pixel const& p, float d) 
{
  return Ray{ { 0,0,0 },{ p.x,p.y,-d } };
}

Color trace(Ray const& ray, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient)
{
  HitPoint closest_hp;
  closest_hp.distance = 0;

  for (unsigned i = 0; i < shapeVec.size(); i++) {
    float t;
    HitPoint hp = shapeVec[i]->intersect(ray, t);
    if (hp.hit) {
      if (hp.distance < -1) {
        if (closest_hp.distance >= 0 || closest_hp.distance > hp.distance){
          closest_hp = hp;
        }
      }
    }
  }

  if (closest_hp.distance != 0) 
  {
    return shade(closest_hp, lightVec, ambient);
  }
  else
  {
    return Color{ 0,0,0 }; // = background_color
  }
}

Color shade(HitPoint const& hit, std::vector<Light> const& lightVec, Color const& ambient)
{
  return Color{ 0,0,1 };
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  size_t buf_pos = (width_*p.y + p.x);
  if (buf_pos >= color_buffer_.size() || (int)buf_pos < 0) {
    std::cerr << "Fatal Error Renderer::write(Pixel p) : "
      << "pixel out of ppm_ : "
      << (int)p.x << "," << (int)p.y
      << std::endl;
  } else {
    color_buffer_[buf_pos] = p.color;
  }

  ppm_.write(p);
}

unsigned Renderer::getWidth() const
{
  return width_;
}

unsigned Renderer::getHeight() const
{
  return height_;
}

std::string Renderer::getFile() const
{
  return filename_;
}

// original checkerboard render

/*void Renderer::render()
{
  std::size_t const checker_pattern_size = 20;

  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x, y);
      if (((x / checker_pattern_size) % 2) != ((y / checker_pattern_size) % 2)) {
        p.color = Color(0.0, 1.0, float(x) / height_);
      }
      else {
        p.color = Color(1.0, 0.0, float(y) / width_);
      }

      write(p);
    }
  }
  ppm_.save(filename_);
}*/
