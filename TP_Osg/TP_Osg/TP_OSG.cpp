// base
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

// Keyboard input
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>

// Materials
#include <osg/Material>
#include <osg/StateSet>
#include <osgDB/ReadFile>

//textures
#include <osg/TexMat>
#include <osg/Geometry>
#include <osg/Light>
#include <osg/LightSource>
#include <osg/MatrixTransform>

//Position
#include <osg/PositionAttitudeTransform>

#include <osg/Fog>


#include <iostream>

class InfoVisitor : public osg::NodeVisitor
{
public:
    InfoVisitor() : _level(0)
    { setTraversalMode(osg::NodeVisitor::TRAVERSE_ALL_CHILDREN); }

    std::string spaces()
    { return std::string(_level*2, ' '); }

    virtual void apply( osg::Node& node );
    virtual void apply( osg::Geode& geode );

protected:
    unsigned int _level;
};

void InfoVisitor::apply( osg::Node& node )
{
    std::cout << spaces() << node.libraryName() << "::" << node.className() << std::endl;

    _level++;
    traverse( node );
    _level--;
}

void InfoVisitor::apply( osg::Geode& geode )
{
    std::cout << spaces() << geode.libraryName() << "::" << geode.className() << std::endl;

    _level++;
    for ( unsigned int i=0; i<geode.getNumDrawables(); ++i )
    {
        osg::Drawable* drawable = geode.getDrawable(i);
        std::cout << spaces() << drawable->libraryName() << "::" << drawable->className() << std::endl;
    }

    traverse( geode );
    _level--;
}




int main()
{
/* OBJECTS CREATION */

	//Creating the viewer	
	osgViewer::Viewer viewer;

	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);
	
	//The geode containing our shape
   	osg::ref_ptr<osg::Geode> myshapegeode (new osg::Geode);
    
    //The geode containing our shape
   	osg::ref_ptr<osg::Geode> myshapegeode2 (new osg::Geode);
    
    
	
	//Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
	osg::ref_ptr<osg::Capsule> myCapsule (new osg::Capsule(osg::Vec3f(),1,2));

	//Our shape drawable
	osg::ref_ptr<osg::ShapeDrawable> capsuledrawable (new osg::ShapeDrawable(myCapsule.get()));
    
    
    
    //Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
    osg::ref_ptr<osg::Box> myBox (new osg::Box(osg::Vec3f(),10,1,1));
    
    //Our shape drawable
    osg::ref_ptr<osg::ShapeDrawable> boxdrawable (new osg::ShapeDrawable(myBox.get()));
    
    
    //Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
    osg::ref_ptr<osg::Sphere> mySphere2 (new osg::Sphere(osg::Vec3f(0,2,0),2));
    
    //Our shape drawable
    osg::ref_ptr<osg::ShapeDrawable> sphere2drawable (new osg::ShapeDrawable(mySphere2.get()));
    
    
    //Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
    osg::ref_ptr<osg::Sphere> mySphere (new osg::Sphere(osg::Vec3f(-1,-1,0),3));
    
    //Our shape drawable
    osg::ref_ptr<osg::ShapeDrawable> spheredrawable (new osg::ShapeDrawable(mySphere.get()));
    
    //Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
    osg::ref_ptr<osg::Cone> myCone (new osg::Cone(osg::Vec3f(0,2,0),2,4));
    
    //Our shape drawable
    osg::ref_ptr<osg::ShapeDrawable> conedrawable (new osg::ShapeDrawable(myCone.get()));
    
    // Create a new StateSet with default settings:
    osg::ref_ptr<osg::StateSet> nodeStateSet (myshapegeode->getOrCreateStateSet());
    osg::ref_ptr<osg::StateSet> nodeStateSet2 (myshapegeode2->getOrCreateStateSet());
    
/*POSITION*/
    osg::ref_ptr<osg::PositionAttitudeTransform> objectPAT (new osg::PositionAttitudeTransform);
    
    osg::Vec3f objectPosTrans = osg::Vec3f(0.0,-0.0,0.0);
    objectPAT->setPosition(objectPosTrans);
    objectPAT->addChild(myshapegeode2);

    /* TERRAIN */
    // Create transformation node
    osg::ref_ptr<osg::MatrixTransform> terrainScaleMAT (new osg::MatrixTransform);
    // Scale matrix
    osg::Matrix terrainScaleMatrix;
    terrainScaleMatrix.makeScale(osg::Vec3f(0.1f,0.1f,0.1f));
    //Loading the terrain node
    osg::ref_ptr<osg::Node> terrainnode (osgDB::readNodeFile("/Users/willispinaud/Dropbox/OpenSceneGraphIni/TP_Osg/TP_Osg/Terrain2.3ds"));
    //Set transformation node parameters
    terrainScaleMAT->addChild(terrainnode);
    terrainScaleMAT->setMatrix(terrainScaleMatrix);
    
/*LIGHTING*/
    
    //Create nodes
    osg::ref_ptr<osg::Group> lightGroup (new osg::Group());
    osg::ref_ptr<osg::StateSet> lightSS (lightGroup->getOrCreateStateSet());
    osg::ref_ptr<osg::LightSource> lightSource1 = new osg::LightSource;
    osg::ref_ptr<osg::LightSource> lightSource2 = new osg::LightSource;
    
    //Create a local light
    osg::Vec4f lightPosition = osg::Vec4f(10.0,1.0,1.0,1.0);
    osg::ref_ptr<osg::Light> myLight = new osg::Light;
    myLight->setLightNum(0);
    myLight->setPosition(lightPosition);
    myLight->setAmbient(osg::Vec4f(0.4f,0.4f,0.4f,0.4f));
    myLight->setDiffuse(osg::Vec4f(1,0.4f,1,1));
    myLight->setConstantAttenuation(0.3);
    
    //Set light source parameters
    lightSource1->setLight(myLight);
    lightSource1->setStateSetModes(*lightSS.get(), osg::StateAttribute::ON);

    //Add to light source group
    lightGroup->addChild(lightSource1);
    
    //Create a local light
    osg::ref_ptr<osg::Light> myLight2 = new osg::Light;
    myLight2->setLightNum(0);
    myLight2->setPosition(osg::Vec4f(-20.0,10.0,10.0,1.0));
    myLight2->setAmbient(osg::Vec4f(0.1f,0.9f,0.4f,1.0f));
    myLight2->setDiffuse(osg::Vec4f(0.5,0.4f,0.1,1));
    myLight2->setConstantAttenuation(0.1);
    
    //Set light source parameters
    lightSource2->setLight(myLight2);
    lightSource2->setStateSetModes(*lightSS.get(), osg::StateAttribute::ON);
    
    //Add to light source group
    lightGroup->addChild(lightSource2);

    
    //Light markers: small spheres
    osg::ref_ptr<osg::ShapeDrawable> markerdrawable1 (new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(10.0,1.0,1.0),2)));
    osg::ref_ptr<osg::ShapeDrawable> markerdrawable2 (new osg::ShapeDrawable(new osg::Sphere(osg::Vec3f(-20.0,10.0,10.0),2)));

    markerdrawable1->setColor(osg::Vec4f(0.4f,0.4f,0.4f,0.4f));
    markerdrawable2->setColor(osg::Vec4f(0.2f,0.1f,0.4f,1));
    osg::ref_ptr<osg::Geode> lightGeode (new osg::Geode);
    lightGroup->addChild(lightGeode);
    lightGeode->addDrawable(markerdrawable1.get());
    lightGeode->addDrawable(markerdrawable2.get());
    
/*FOG*/
    osg::ref_ptr<osg::Fog> fog = new osg::Fog;
    fog->setColor(osg::Vec4(0.1,0.4,0.9,0.9));
    fog->setMode( osg::Fog::EXP2 );
    fog->setDensity( 0.1f );
    fog->setStart(20);
    fog->setEnd(10);
    osg::ref_ptr< osg::StateSet> fogSS (new osg::StateSet);
    fogSS->setAttributeAndModes( fog.get(), osg::StateAttribute::ON );
    fogSS->setMode( GL_FOG, osg::StateAttribute::ON );
    root->setStateSet(fogSS);
    

    
/* SCENE GRAPH*/

	// Add the shape drawable to the geode
	myshapegeode->addDrawable(capsuledrawable.get());
    
    // Add the shape drawable to the geode
    myshapegeode->addDrawable(conedrawable.get());

    // Add the shape drawable to the geode
    myshapegeode->addDrawable(boxdrawable.get());
    
    // Add the geode to the scene graph root (Group)
    root->addChild(myshapegeode.get());
    
    // Add the shape drawable to the geode
    myshapegeode2->addDrawable(sphere2drawable.get());
    
    // Add the shape drawable to the geode
    myshapegeode2->addDrawable(spheredrawable.get());
    
    // Add the PAT to the scene graph root (Group)
    root->addChild(objectPAT.get());
    
    root->addChild(terrainScaleMAT.get());
    
    root->addChild(lightGroup.get());

    

	

/* KEYBOARD INPUT */
	
 	//Stats Event Handler s key
	viewer.addEventHandler(new osgViewer::StatsHandler);

	//Windows size handler
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	
	// add the state manipulator
    viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );

    viewer.setThreadingModel(osgViewer::Viewer::SingleThreaded);
    
/* PARTIE COULEUR*/
    
    //De la couleur
    conedrawable->setColor(osg::Vec4f(1.0f,0.6f,0.0f,1.0f));
    
    boxdrawable->setColor(osg::Vec4f(0.53f,0.32f,0.031f,1.0f));
    
/* Matériaux */
    
    osg::ref_ptr<osg::Material> myMaterial (new osg::Material());
    
    myMaterial->setEmission(osg::Material::FRONT,osg::Vec4f(0.93f,0.12f,0.031f,1.0f));
    myMaterial->setAmbient(osg::Material::FRONT,osg::Vec4f(0.0f,1.0f,1.0f,1.0f));
    myMaterial->setShininess(osg::Material::FRONT,0.0);
    
    osg::ref_ptr<osg::Texture2D> pierre (new osg::Texture2D);
    
    // load an image by reading a file:
    osg::ref_ptr<osg::Image> img_pierre (osgDB::readImageFile("/Users/willispinaud/Dropbox/OpenSceneGraphIni/TP_Osg/TP_Osg/Fieldstone.png"));
    
    // protect from being optimized away as static state:
    pierre->setDataVariance(osg::Object::DYNAMIC);
    
    /*neige->setFilter(osg::Texture::MIN_FILTER, osg::Texture::LINEAR_MIPMAP_LINEAR);
    neige->setFilter(osg::Texture::MAG_FILTER, osg::Texture::LINEAR);
    neige->setWrap(osg::Texture::WRAP_S, osg::Texture::CLAMP);
    neige->setWrap(osg::Texture::WRAP_T, osg::Texture::CLAMP);*/
    
    // Assign the texture to the image we read from file:
    pierre->setImage(img_pierre);
    
    //nodeStateSet->setAttribute(myMaterial);
    
    // Assign texture unit 0 of our new StateSet to the texture
    //  we just created and enable the texture.
    nodeStateSet->setTextureAttributeAndModes(0, pierre,osg::StateAttribute::ON);
    
    // Associate this state set with the Geode that contains
    //  the pyramid:
    myshapegeode->setStateSet(nodeStateSet);
    
    
    osg::ref_ptr<osg::Texture2D> neige (new osg::Texture2D);
    osg::ref_ptr<osg::Image> img_neige (osgDB::readImageFile("/Users/willispinaud/Dropbox/OpenSceneGraphIni/TP_Osg/TP_Osg/fond-neige.jpg"));
    neige->setDataVariance(osg::Object::DYNAMIC);
    neige->setImage(img_neige);
    nodeStateSet2->setTextureAttributeAndModes(0, neige,osg::StateAttribute::ON);
    myshapegeode2->setStateSet(nodeStateSet2);
    
    InfoVisitor infoVisitor;
    root->accept( infoVisitor );
    // Set the scene data
    viewer.setSceneData( root.get() );
    viewer.getCamera()->setClearColor( osg::Vec4( 1,1,1,1 ) );
/* START VIEWER */

	//The viewer.run() method starts the threads and the traversals.
	return (viewer.run());
}
