#ifndef VECTOR
#define VECTOR

typedef struct Vector2 {
  float x;
  float y;
} Vector2;

Vector2 Vector2Add(Vector2 vec1, Vector2 vec2);

Vector2 Vector2Subtract(Vector2 vec1, Vector2 vec2);

Vector2 Vector2Multiply(Vector2 vec1, Vector2 vec2);

Vector2 Vector2Divide(Vector2 vec1, Vector2 vec2);

Vector2 Vector2Scale(Vector2 vec, int scale);

float Vector2Magnitude(Vector2 vec);

Vector2 Vector2Normalize(Vector2 vec);

#endif
