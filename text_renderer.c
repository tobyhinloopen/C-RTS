#include "text_renderer.h"
#include "opengl.h"
#include <string.h>
#include <ctype.h>

const GLfloat vertices[] = {
  0.0f, 0.0f,
  1.0f, 0.0f,
  2.0f, 0.0f,
  3.0f, 0.0f,
  4.0f, 0.0f,

  0.0f, 1.0f,
  2.0f, 1.0f,
  4.0f, 1.0f,

  0.0f, 2.0f,
  1.0f, 2.0f,
  2.0f, 2.0f,
  3.0f, 2.0f,
  4.0f, 2.0f,

  0.0f, 3.0f,
  2.0f, 3.0f,
  4.0f, 3.0f,

  0.0f, 4.0f,
  1.0f, 4.0f,
  2.0f, 4.0f,
  3.0f, 4.0f,
  4.0f, 4.0f,
};

/**
 0  1  2  3  4
 5     6     7
 8  9 10 11 12
13    14    15
16 17 18 19 20
*/

const GLubyte A[] = { 2, /**/ 6,  2, /**/ 16,  5,  1,  3,  7, 20, /**/  8, 12 };
const GLubyte B[] = { 2, /**/ 6,  4, /**/ 16,  0,  3,  7, 11,  8, /**/ 11, 15, 19, 16 };
const GLubyte C[] = { 1, /**/ 6, /**/  4,  1,  5, 13, 17, 20 };
const GLubyte D[] = { 1, /**/ 7, /**/ 16,  0,  3,  7, 15, 19, 16 };
const GLubyte E[] = { 2, /**/ 4,  2, /**/  4,  0, 16,  20, /**/  8, 11 };
const GLubyte F[] = { 2, /**/ 3,  2, /**/  4,  0, 16, /**/  8, 11 };
const GLubyte G[] = { 1, /**/ 9, /**/  7,  3,  1,  5, 13, 17, 20, 12, 11 };
const GLubyte H[] = { 3, /**/ 2,  2,  2, /**/  0, 16, /**/  8, 12, /**/  4, 20 };
const GLubyte I[] = { 3, /**/ 2,  2,  2, /**/  0,  4, /**/  2, 18, /**/ 16, 20 };
const GLubyte J[] = { 1, /**/ 6, /**/  3,  4, 15, 19, 17, 13 };
const GLubyte K[] = { 2, /**/ 3,  3, /**/  0,  8,  4, /**/ 16,  8, 20 };
const GLubyte L[] = { 1, /**/ 3, /**/  0, 16, 20 };
const GLubyte M[] = { 1, /**/ 5, /**/ 16,  0,  6,  4, 20 };
const GLubyte N[] = { 1, /**/ 5, /**/ 16,  0,  3,  7, 20 };
const GLubyte O[] = { 1, /**/ 9, /**/  1,  3,  7, 15, 19, 17, 13,  5,  1 };
const GLubyte P[] = { 1, /**/ 6, /**/ 16,  0,  3,  7, 11,  8 };
const GLubyte Q[] = { 2, /**/ 9,  2, /**/  1,  3,  7, 15, 19, 17, 13,  5,  1, /**/ 10, 20 };
const GLubyte R[] = { 2, /**/ 6,  2, /**/ 16,  0,  3,  7, 11,  8, /**/ 10, 20 };
const GLubyte S[] = { 1, /**/ 8, /**/  4,  1,  5,  9, 11, 15, 19, 16 };
const GLubyte T[] = { 2, /**/ 2,  2, /**/  0,  4,  2, 18 };
const GLubyte U[] = { 1, /**/ 6, /**/  0, 13, 17, 19, 15,  4 };
const GLubyte V[] = { 1, /**/ 3, /**/  0, 18,  4 };
const GLubyte W[] = { 1, /**/ 5, /**/  0, 16, 14, 20,  4 };
const GLubyte X[] = { 2, /**/ 2,  2, /**/  0, 20, /**/  4, 16 };
const GLubyte Y[] = { 2, /**/ 3,  2, /**/  0, 10, 18, /**/  4, 10 };
const GLubyte Z[] = { 1, /**/ 4, /**/  0,  4, 16, 20 };

const GLubyte DIGIT_0[] = { 1, /**/ 6, /**/  16, 4, 20, 16,  0,  4 };
const GLubyte DIGIT_1[] = { 2, /**/ 3,  2, /**/  1,  2, 18, /**/ 16, 20 };
const GLubyte DIGIT_2[] = { 1, /**/ 6, /**/  0,  4, 12,  8, 16, 20 };
const GLubyte DIGIT_3[] = { 2, /**/ 4,  2, /**/  0,  4, 20, 16, /**/  9, 12 };
const GLubyte DIGIT_4[] = { 2, /**/ 3,  2, /**/  0,  8, 12, /**/  7, 20 };
const GLubyte DIGIT_5[] = { 1, /**/ 6, /**/  4,  0,  8, 12, 20, 16 };
const GLubyte DIGIT_6[] = { 1, /**/ 5, /**/  0, 16, 20, 12,  8 };
const GLubyte DIGIT_7[] = { 1, /**/ 3, /**/  1,  4, 20 };
const GLubyte DIGIT_8[] = { 2, /**/ 5,  2, /**/  0,  4, 20, 16, 0, /**/  8, 12 };
const GLubyte DIGIT_9[] = { 1, /**/ 5, /**/ 20,  4,  0,  8, 12 };

const GLubyte SYMBOL_DOT[]     = { 1, /**/ 2, /**/ 14, 18 };
const GLubyte SYMBOL_COMMA[]   = { 1, /**/ 3, /**/ 14, 18, 17 };
const GLubyte SYMBOL_SPACE[]   = { 0 };
const GLubyte SYMBOL_DCOLON[]  = { 2, /**/ 2,  2, /**/ 14, 18, /**/  6, 10 };
const GLubyte SYMBOL_PERCENT[] = { 3, /**/ 2,  2,  2, /**/  4, 16, /**/  0,  5, /**/ 15, 20 };
const GLubyte SYMBOL_MINUS[]   = { 1, /**/ 2, /**/  8, 12 };

static const GLubyte * get_indices_for_char(char character) {
  switch(toupper(character)) {
    case 'A': return (const GLubyte *)&A;
    case 'B': return (const GLubyte *)&B;
    case 'C': return (const GLubyte *)&C;
    case 'D': return (const GLubyte *)&D;
    case 'E': return (const GLubyte *)&E;
    case 'F': return (const GLubyte *)&F;
    case 'G': return (const GLubyte *)&G;
    case 'H': return (const GLubyte *)&H;
    case 'I': return (const GLubyte *)&I;
    case 'J': return (const GLubyte *)&J;
    case 'K': return (const GLubyte *)&K;
    case 'L': return (const GLubyte *)&L;
    case 'M': return (const GLubyte *)&M;
    case 'N': return (const GLubyte *)&N;
    case 'O': return (const GLubyte *)&O;
    case 'P': return (const GLubyte *)&P;
    case 'Q': return (const GLubyte *)&Q;
    case 'R': return (const GLubyte *)&R;
    case 'S': return (const GLubyte *)&S;
    case 'T': return (const GLubyte *)&T;
    case 'U': return (const GLubyte *)&U;
    case 'V': return (const GLubyte *)&V;
    case 'W': return (const GLubyte *)&W;
    case 'X': return (const GLubyte *)&X;
    case 'Y': return (const GLubyte *)&Y;
    case 'Z': return (const GLubyte *)&Z;
    case '0': return (const GLubyte *)&DIGIT_0;
    case '1': return (const GLubyte *)&DIGIT_1;
    case '2': return (const GLubyte *)&DIGIT_2;
    case '3': return (const GLubyte *)&DIGIT_3;
    case '4': return (const GLubyte *)&DIGIT_4;
    case '5': return (const GLubyte *)&DIGIT_5;
    case '6': return (const GLubyte *)&DIGIT_6;
    case '7': return (const GLubyte *)&DIGIT_7;
    case '8': return (const GLubyte *)&DIGIT_8;
    case '9': return (const GLubyte *)&DIGIT_9;

    case '.': return (const GLubyte *)&SYMBOL_DOT;
    case ',': return (const GLubyte *)&SYMBOL_COMMA;
    case ' ': return (const GLubyte *)&SYMBOL_SPACE;
    case ':': return (const GLubyte *)&SYMBOL_DCOLON;
    case '%': return (const GLubyte *)&SYMBOL_PERCENT;
    case '-': return (const GLubyte *)&SYMBOL_MINUS;
    // case '+': return plus;
    // case '_': return underscore;
    // case '/': return slash;
    // case ' ': return space;
    default: return NULL;
  }
}

static void start_character_rendering() {
  glEnableClientState(GL_VERTEX_ARRAY);
  glVertexPointer(2, GL_FLOAT, 0, vertices);
  glPushMatrix();
  glScalef(1.4f, -3.0f, 1.0f);
}

static void render_char(char character) {
  const GLubyte * indices = get_indices_for_char(character);
  if (indices == NULL)
    return;
  const unsigned int draw_count = indices[0];
  unsigned int offset = draw_count + 1;
  for (unsigned int i = 0; i < draw_count; i++) {
    const GLsizei indices_length = indices[i+1];
    glDrawElements(GL_LINE_STRIP, indices_length, GL_UNSIGNED_BYTE, indices + offset);
    offset += indices_length;
  }
}

static void stop_character_rendering() {
  glDisableClientState(GL_VERTEX_ARRAY);
  glPopMatrix();
}

void text_renderer_render_character(char character) {
  start_character_rendering();
  render_char(character);
  stop_character_rendering();
}

void text_renderer_render_string(const char * string, int length) {
  if (length) {
    start_character_rendering();
    size_t line_length = 0;
    glTranslatef(0.5f, 0.5f, 0.0f);
    for (size_t i = 0; i < length; i++) {
      const char character = string[i];
      if (character == '\n') {
        glTranslatef(line_length * -6.0f, 6.0f, 0.0f);
        line_length = 0;
      } else {
        line_length++;
        render_char(character);
        glTranslatef(6.0f, 0.0f, 0.0f);
      }
    }
    stop_character_rendering();
  }
}
