// base
#include <osgViewer/Viewer>
#include <osg/ShapeDrawable>

// Keyboard input
#include <osgViewer/ViewerEventHandlers>
#include <osgGA/StateSetManipulator>


int main()
{
/* OBJECTS CREATION */

	//Creating the viewer	
	osgViewer::Viewer viewer ;

	//Creating the root node
	osg::ref_ptr<osg::Group> root (new osg::Group);
	
	//The geode containing our shape
   	osg::ref_ptr<osg::Geode> myshapegeode (new osg::Geode);
	
	//Our shape: a capsule, it could have been any other geometry (a box, plane, cylinder etc.)
	osg::ref_ptr<osg::Capsule> myCapsule (new osg::Capsule(osg::Vec3f(),1,2));

	//Our shape drawable
	osg::ref_ptr<osg::ShapeDrawable> capsuledrawable (new osg::ShapeDrawable(myCapsule.get()));


/* SCENE GRAPH*/

	// Add the shape drawable to the geode
	myshapegeode->addDrawable(capsuledrawable.get());

	// Add the geode to the scene graph root (Group)
	root->addChild(myshapegeode.get());

	// Set the scene data
	viewer.setSceneData( root.get() ); 

/* KEYBOARD INPUT */
	
 	//Stats Event Handler s key
	viewer.addEventHandler(new osgViewer::StatsHandler);

	//Windows size handler
	viewer.addEventHandler(new osgViewer::WindowSizeHandler);
	
	// add the state manipulator
    	viewer.addEventHandler( new osgGA::StateSetManipulator(viewer.getCamera()->getOrCreateStateSet()) );


/* START VIEWER */

	//The viewer.run() method starts the threads and the traversals.
	return (viewer.run());
}
