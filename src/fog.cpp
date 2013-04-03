
#include <GL/gl.h>

#include "fog.h"

void fog::turn_on()
{
	GLfloat fog_color[4] = {r, g, b, 1};

	glEnable(GL_FOG);
	glFogfv(GL_FOG_COLOR, fog_color);
	glFogf(GL_FOG_DENSITY, 0.003);
	glFogi(GL_FOG_MODE, GL_EXP2);
	glFogf(GL_FOG_START, minfog);
	glFogf(GL_FOG_END, maxfog);
}

void fog::turn_off()
{
	glDisable(GL_FOG);
}

