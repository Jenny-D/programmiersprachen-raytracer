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
  float d = cam.distance();
 
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);
      
      p.color = trace(cam_ray(p, d), shapeVec, lightVec, ambient);
 
      write(p);
    }
  }
  ppm_.save(filename_);
}

Ray Renderer::cam_ray(Pixel const& p, float d)
{
  float x = (1.0f / width_) * p.x  - 0.5f;
  float y = (1.0f / height_) * p.y - 0.5f;
  glm::vec3 direction{ x,y,-d };
  return Ray{ { 0,0,0 }, direction};
}

Color Renderer::trace(Ray const& ray, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient)
{
  HitPoint closest_hp;

  for (auto shape : shapeVec) {
    float t;
    HitPoint hp = (*shape).intersect(ray, t);
    if (hp.hit) {
      if (hp.distance < closest_hp.distance){
        closest_hp = hp;
      }
    }
  }

  if (closest_hp.hit) 
  {
    return shade(closest_hp, shapeVec, lightVec, ambient);
  }
  else
  {
    return Color{ 0,0,0 }; // = background_color
  }
}

Color Renderer::shade(HitPoint const& hp, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient)
{
  float r, g, b;

  // ambiente Beleuchtung
  r = hp.material->ka_.r * ambient.r;
  g = hp.material->ka_.g * ambient.g;
  b = hp.material->ka_.b * ambient.b;

  // diffuse Beleuchtung
  for (auto light : lightVec) {
    bool obstructed = false;

    float dir_x = light.position.x - hp.hitPoint.x;
    float dir_y = light.position.y - hp.hitPoint.y;
    float dir_z = light.position.z - hp.hitPoint.z;
    glm::vec3 l_vec{ dir_x,dir_y,dir_z };
    Ray l_ray{ light.position,{ -dir_x,-dir_y,-dir_z } };
    float t;

    for (auto shape : shapeVec) {
      HitPoint hpl = (*shape).intersect(l_ray, t);
      if (hpl.hit && t <= 1-0.00001) {
        obstructed = true;
        break;
      }
    }

    if (!obstructed) {
      glm::vec3 l = glm::normalize(l_vec);
      glm::vec3 n = glm::normalize(hp.normal);
      float s = glm::dot(l,n);

      r += hp.material->kd_.r * light.brightness * s;
      g += hp.material->kd_.g * light.brightness * s;
      b += hp.material->kd_.b * light.brightness * s;
    }
  }
  /*r /= (r + 1);
  g /= (g + 1);
  b /= (b + 1);*/
  return Color{ r,g,b };
}

void Renderer::write(Pixel const& p)
{
  // flip pixels, because of opengl glDrawPixels
  //size_t buf_pos = (width_*p.y + p.x);
  unsigned int buf_pos = (width_ * p.y + p.x);
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
