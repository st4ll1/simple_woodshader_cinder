#include "cinder/app/AppBasic.h"
#include "cinder/gl/gl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/GlslProg.h"
#include "cinder\Camera.h"
#include "cinder\params\Params.h"
#include "cinder/MayaCamUI.h"

#include "Resources.h"

using namespace ci;
using namespace ci::app;
using namespace std;

class shader_basicApp : public AppBasic {
  public:
	void setup();
    void prepareSettings( Settings *settings);	
	void update();
	void draw();

    gl::GlslProg mShader;

    float twist, excentricity, wavelenght;

    ci::CameraPersp cam;
    MayaCamUI mayaCam;
    Vec3f mEye, mCenter, mUp;
    Vec2i mousePos;
    params::InterfaceGl mParams;

    void mouseMove( MouseEvent event );
    void mouseDown( MouseEvent event );
    void mouseDrag( MouseEvent event );
    void mouseWheel( MouseEvent event );
    void resize( ResizeEvent event );
    
};

void shader_basicApp::mouseMove( MouseEvent event )
{
  // keep track of the mouse
  mousePos = event.getPos();
}

void shader_basicApp::mouseWheel( MouseEvent event )
{
    
}

void shader_basicApp::mouseDown( MouseEvent event )
{	
  // let the camera handle the interaction
  mayaCam.mouseDown( event.getPos() );
}

void shader_basicApp::mouseDrag( MouseEvent event )
{
  // keep track of the mouse
  mousePos = event.getPos();

  // let the camera handle the interaction  
  mayaCam.mouseDrag( event.getPos(), event.isLeftDown(), event.isMiddleDown(), event.isRightDown() );
}

void shader_basicApp::resize( ResizeEvent event )
{
  // adjust aspect ratio
  CameraPersp cam = mayaCam.getCamera();
  cam.setAspectRatio( getWindowAspectRatio() );
  mayaCam.setCurrentCam( cam );
}

void shader_basicApp::prepareSettings( Settings *settings )
{
	settings->setWindowSize( 1024, 768 );
	settings->setFrameRate( 60.0f );
	settings->setFullScreen( false );
}


void shader_basicApp::setup()
{
    mShader = gl::GlslProg( loadResource( RES_VERT_GLSL ), loadResource( RES_FRAG_GLSL ) );

    cam.setPerspective( 60.0f, getWindowAspectRatio(), 5.0f, 3000.0f );
    mEye        = Vec3f( 2.0f, 2.0f, 2.0f );
    mCenter     = Vec3f::zero();
    mUp         = Vec3f::yAxis();
    cam.lookAt( mEye, mCenter, mUp );

    mayaCam.setCurrentCam( cam );

    wavelenght = 0.1f;
    twist = 0.5 * 3.14f;
    excentricity = 0.4f;

    mParams = params::InterfaceGl("values", Vec2i(350,300));
    mParams.addParam("Wavelenght", &wavelenght);
    mParams.addParam("Excentricity", &excentricity);
    mParams.addParam("Twist", &twist);


    glClearColor( 0.1f, 0.1f, 0.1f, 1.0f );
	gl::enableDepthRead( true );
	gl::enableDepthWrite( true );
	gl::enableAlphaBlending();
}

void shader_basicApp::update()
{
}

void shader_basicApp::draw()
{
    gl::clear( Color( 0, 0, 0 ) ); 

    gl::enableDepthWrite( true );
	glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    gl::pushMatrices();
        gl::setMatrices( mayaCam.getCamera() );
   
        gl::color( Color(1.0f, 0.0f, 0.0f));
        mShader.bind();
        mShader.uniform("twist", twist);
        mShader.uniform("excentricity", excentricity);
        mShader.uniform("wavelenght", wavelenght);
        //mShader.uniform( "tex", 0 );
	
        gl::drawCube(Vec3f(0.0f,0.0f,0.0f), Vec3f(10.0f,10.0f,3.0f));
        mShader.unbind();

        gl::color( Color(1.0f, 1.0f, 1.0f));

    gl::popMatrices();
    //draw params
  params::InterfaceGl::draw();
}

CINDER_APP_BASIC( shader_basicApp, RendererGl )
