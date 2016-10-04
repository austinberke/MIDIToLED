#ifndef RAY_H
#define RAY_H

class Ray {
  
public:
  Ray() {
    m_direction = 0;
    m_color = CRGB::White;
    m_position = 0;
    m_life = 0;
    m_width = 1;
    m_speed_counter = 0;
  }
  Ray(bool dir, CRGB& color, uint16_t pos, byte life) {
    m_direction = dir;
    m_color = color;
    m_position = pos;
    m_life = life;
    m_width = 8;
    m_speed_counter = 0;
  }

  bool direction() { return m_direction; }
  CRGB& color() { return m_color; }
  uint16_t position() { return m_position; }
  byte life() { return m_life; }
  byte width() { return m_width; }

  
  uint8_t advance() {
    m_position++;
    return --m_life;   
  }
  
private:
  bool m_direction;
  CRGB m_color;
  uint16_t m_position;
  uint8_t m_life;
  uint8_t m_width;
  uint8_t m_speed_counter;
};

#endif /* RAY_H */
