#ifndef RAY_H
#define RAY_H

class Ray {
  
public:
  Ray() {
    m_direction = 0;
    m_color = CRGB::White;
    m_speed = 10;
    m_position = 0;
    m_width = 1;
    m_speed_counter = 0;
  }
  Ray(bool dir, CRGB& color, uint8_t spd, uint8_t pos) {
    m_direction = dir;
    m_color = color;
    m_speed = spd;
    m_position = pos;
    m_width = 5;
    m_speed_counter = 0;
  }

  bool direction() { return m_direction; }
  CRGB& color() { return m_color; }
  uint8_t position() { return m_position; }
  uint8_t width() { return m_width; }
  uint8_t speed() { return m_speed; }

  
  uint8_t advance() {
    if (m_speed_counter < m_speed) {
      m_speed_counter+=4;
      return m_position;
    }
    
    m_speed_counter = 0;
    return ++m_position;
    
  }
  
private:
  bool m_direction;
  CRGB m_color;
  uint8_t m_position;
  uint8_t m_width;
  uint8_t m_speed;
  uint8_t m_speed_counter;
};

#endif /* RAY_H */
