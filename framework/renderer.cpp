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

void Renderer::render(Camera& cam, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient)
{
  float d = cam.distance();
 
  for (unsigned y = 0; y < height_; ++y) {
    for (unsigned x = 0; x < width_; ++x) {
      Pixel p(x,y);

      p.color = trace(cam_ray(p, d, cam), shapeVec, lightVec, ambient, 0);
 
      write(p);
    }
  }
  ppm_.save(filename_);
}

Ray Renderer::cam_ray(Pixel const& p, float d, Camera& c)
{
  float x = (1.0f / width_) * p.x  - 0.5f;
  float y = (1.0f / height_) * p.y - 0.5f;
  glm::vec3 direction{ x,y,-d };
  Ray ray{ { 0,0,0 }, direction};

  glm::mat4 cam_matrix{ c.cam_transformation() };
  return Ray{ transformRay(cam_matrix, ray) };
}

HitPoint offset(HitPoint const& hp, bool out)
{
  float epsilon = 0.0001;
  HitPoint off_hp = hp;
  if (out) {
    off_hp.hitPoint.x += epsilon * hp.normal.x;
    off_hp.hitPoint.y += epsilon * hp.normal.y;
    off_hp.hitPoint.z += epsilon * hp.normal.z;
  }
  else {
    off_hp.hitPoint.x += (-2) * epsilon * hp.normal.x;
    off_hp.hitPoint.y += (-2) * epsilon * hp.normal.y;
    off_hp.hitPoint.z += (-2) * epsilon * hp.normal.z;
  }
  return off_hp;
}

Color Renderer::trace(Ray const& ray, std::vector<std::shared_ptr<Shape>> const& shapeVec, std::vector<Light> const& lightVec, Color const& ambient, int limit)
{
  limit++; // maximale Spiegelungsanzahl
  
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
    HitPoint hp = offset(closest_hp, true);

    Color hpColor = shade(hp, shapeVec, lightVec, ambient);

    Color mirroredColor = hpColor;
    Color refractedColor = hpColor;

    float mir = hp.material->mirror_;
    float op = hp.material->opacity_;

    if (limit <= 10) {
      if (mir > 0) {
        //gespiegelten Ray losschicken und dessen Shade zur�ckgeben
        glm::vec3 l = glm::normalize(-ray.direction);
        glm::vec3 n = hp.normal;
        float s = glm::dot(l, n);  // Kosinus vom Winkel zwischen n und l
        glm::vec3 rl = (2 * s * n) - l;
        Ray new_ray = Ray{ hp.hitPoint, rl };
        mirroredColor = trace(new_ray, shapeVec, lightVec, ambient, limit);
      }

      if (op < 1) {
        HitPoint in = offset(hp, false);
        glm::vec3 in_vec;
        Ray in_ray{ in.hitPoint,in_vec };

        HitPoint out = in;
        HitPoint out_2;
        bool same_material = true;
        while (same_material) {
          for (auto shape : shapeVec) {
            float t;
            HitPoint hp = (*shape).intersect(in_ray, t);
            if (hp.hit) {
              if (hp.distance < out_2.distance) {
                out_2 = hp;
              }
            }
          }
          if (out.material == out_2.material) {
            out = out_2;
          }
          else {
            same_material = false;
          }
        }

        if (in.hitPoint != out.hitPoint) {
          glm::vec3 out_vec;
          Ray out_ray{ out.hitPoint,out_vec };
          refractedColor = trace(out_ray, shapeVec, lightVec, ambient, limit);
        }
        else {
          refractedColor = trace(in_ray, shapeVec, lightVec, ambient, limit);
        }
      }
    }
    
    float r = (op - mir) * hpColor.r + mir * mirroredColor.r + (1 - op) * refractedColor.r;
    float g = (op - mir) * hpColor.g + mir * mirroredColor.g + (1 - op) * refractedColor.g;
    float b = (op - mir) * hpColor.b + mir * mirroredColor.b + (1 - op) * refractedColor.b;

    return { r,g,b };
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
      HitPoint hpl = offset((*shape).intersect(l_ray, t), true);
      if (hpl.hit && t <= 1 - 0.0001) {
      //if (hpl.hit) {
        obstructed = true;
        break;
      }
    }

    if (!obstructed) {
      glm::vec3 l = glm::normalize(l_vec);
      glm::vec3 n = hp.normal;
      float s = glm::dot(l,n);  // Kosinus vom Winkel zwischen n und l
      glm::vec3 rl = (2 * s * n) - l;
      glm::vec3 v = glm::normalize(-hp.hitPoint);
      float s2 = glm::dot(rl, v);

      r += light.brightness * ((hp.material->kd_.r * s) + (hp.material->ks_.r * pow(s2, hp.material->m_)));
      g += light.brightness * ((hp.material->kd_.g * s) + (hp.material->ks_.g * pow(s2, hp.material->m_)));
      b += light.brightness * ((hp.material->kd_.b * s) + (hp.material->ks_.b * pow(s2, hp.material->m_)));
    }
  }
  r /= (r + 1);
  g /= (g + 1);
  b /= (b + 1);

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
