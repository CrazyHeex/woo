#ifdef WIN32
#include <windows.h> // The Win32 versions of the GL header files require that you windows.h before gl.h/glu.h/glut.h, so that you get the #define types like WINGDIAPI and such
#endif

#include <GL/gl.h>
#include <GL/glut.h>

#include "SimpleBody.hpp"
#include "Math.hpp"

#include <iostream>

using namespace std;

SimpleBody::SimpleBody() : Body()
{
	containSubBodies = false;
}

SimpleBody::~SimpleBody() 
{

}

void SimpleBody::glDrawGeometricalModel()
{
/*	glPushMatrix();
	Real angle;
	Vector3r axis;	
	se3.rotation.toAxisAngle(axis,angle);	
	glTranslatef(se3.translation[0],se3.translation[1],se3.translation[2]);
	glRotatef(angle*Mathr::RAD_TO_DEG,axis[0],axis[1],axis[2]);	
	gm->glDraw();
	glPopMatrix();*/
}

void SimpleBody::glDrawBoundingVolume()
{
/*	glPushMatrix();
	bv->glDraw();
	glPopMatrix();*/
}

void SimpleBody::glDrawCollisionGeometry()
{
/*	glPushMatrix();
	Real angle;
	Vector3r axis;	
	se3.rotation.toAxisAngle(axis,angle);	
	glTranslatef(se3.translation[0],se3.translation[1],se3.translation[2]);
	glRotatef(angle*Mathr::RAD_TO_DEG,axis[0],axis[1],axis[2]);	
	cm->glDraw();
	glPopMatrix();*/
}


void SimpleBody::postProcessAttributes(bool deserializing)
{
	Body::postProcessAttributes(deserializing);
}

void SimpleBody::registerAttributes()
{
	Body::registerAttributes();
}

void SimpleBody::moveToNextTimeStep()
{
	vector<shared_ptr<Actor> >::iterator ai    = actors.begin();
	vector<shared_ptr<Actor> >::iterator aiEnd =  actors.end();
	for(;ai!=aiEnd;++ai)
		if ((*ai)->isActivated())
			(*ai)->action(this);
}
