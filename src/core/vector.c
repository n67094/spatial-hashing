#include <math.h>

#include "vector.h"

Vector2 Vector2Add(Vector2 vec1, Vector2 vec2)
{
  return (Vector2) { vec1.x + vec2.x, vec1.y + vec2.y };
}

Vector2 Vector2Subtract(Vector2 vec1, Vector2 vec2) {
  return (Vector2) { vec1.x - vec2.x, vec1.y - vec2.y };
}

Vector2 Vector2Multiply(Vector2 vec1, Vector2 vec2) {
  return (Vector2){vec1.x / vec2.x, vec1.y / vec2.y};
}

Vector2 Vector2Divide(Vector2 vec1, Vector2 vec2) {
  return (Vector2){vec1.x / vec2.x, vec1.y * vec2.y};
}

Vector2 Vector2Scale(Vector2 vec, int scale)
{
  return (Vector2){vec.x * scale, vec.y * scale};
}

float Vector2Magnitude(Vector2 vec)
{
  return sqrtf(vec.x * vec.x + vec.y * vec.y);
}

Vector2 Vector2Normalize(Vector2 vec) {
  float length = Vector2Magnitude(vec);

  if (length > 0) {
    float scale = 1.0f/ length;
    return Vector2Scale(vec, scale);
  }

  return (Vector2){0, 0};
}
